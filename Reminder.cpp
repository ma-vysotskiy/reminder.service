
#include "Reminder.h"
#include "ThreadPool.h"

using namespace std;

void CReminder::OnStart(DWORD dwArgc, PWSTR *pszArgv){
	CThreadPool::QueueUserWorkItem(&CReminder::Worker, this);
}

void CReminder::OnStop(){
	m_stopping = true;
}

void CReminder::OnPause(){
}

void CReminder:: OnContinue(){
}

void CReminder::OnShutdown(){
}

void CReminder::Worker(){
	HANDLE hToken;
	//Need to get user token
	if(LogonUser(L"Admin", L"WORLGROUP", L"1", LOGON32_LOGON_NETWORK, LOGON32_PROVIDER_DEFAULT, &hToken)){
		HANDLE hDubToken;
		//Dublicate it
		if(!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hDubToken)) {
			WriteErrorLogEntry(L"DuplicateToken ");
		}

		STARTUPINFO siStartupInfo;
		PROCESS_INFORMATION piProcessInfo;
		memset(&siStartupInfo, 0, sizeof(siStartupInfo));
		memset(&piProcessInfo, 0, sizeof(piProcessInfo));
		siStartupInfo.cb = sizeof(siStartupInfo); 

		//TODO: Seek some info how to launch interactive process using this structure
		siStartupInfo.cb=sizeof(STARTUPINFO);
		siStartupInfo.lpReserved  =NULL;
		siStartupInfo.lpDesktop   =NULL;
		siStartupInfo.lpTitle     =NULL;
		siStartupInfo.dwFlags     =STARTF_USESHOWWINDOW;
		siStartupInfo.wShowWindow =SW_SHOWNORMAL;
		siStartupInfo.cbReserved2 =0;
		siStartupInfo.lpReserved2 =NULL;
		//Create process with dublicated token
		if(!CreateProcessAsUser(hDubToken, L"D:\\temp\\notifu\\notifu.exe", L" /p title /m msg", 0, 0, false,
				 CREATE_BREAKAWAY_FROM_JOB, 0, 0, &siStartupInfo, &piProcessInfo)) {
			WriteErrorLogEntry(L"CreateProcessAsUser ");
		}
		//Output some info to file
		logFile<< "PID: " << piProcessInfo.dwProcessId << endl;
		logFile<< "TID: " << piProcessInfo.dwThreadId << endl;
		logFile<< "Process: " << piProcessInfo.hProcess << endl;
		logFile<< "Thread: " << piProcessInfo.hThread << endl;
	} else {
		WriteErrorLogEntry(L"Error in worker");
	}
	//Wait until we stop
	while(!m_stopping){}
}