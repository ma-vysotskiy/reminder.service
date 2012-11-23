#pragma once

#include <Windows.h>
#include "ServiceBase.h"

class CReminder : public CServiceBase {
public:
	CReminder() : CServiceBase(L"servicename", true, true, true) {
	}

	// When implemented in a derived class, executes when a Start command is 
    // sent to the service by the SCM or when the operating system starts 
    // (for a service that starts automatically). Specifies actions to take 
    // when the service starts.
    virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);

    // When implemented in a derived class, executes when a Stop command is 
    // sent to the service by the SCM. Specifies actions to take when a 
    // service stops running.
    virtual void OnStop();

    // When implemented in a derived class, executes when a Pause command is 
    // sent to the service by the SCM. Specifies actions to take when a 
    // service pauses.
    virtual void OnPause();

    // When implemented in a derived class, OnContinue runs when a Continue 
    // command is sent to the service by the SCM. Specifies actions to take 
    // when a service resumes normal functioning after being paused.
    virtual void OnContinue();

    // When implemented in a derived class, executes when the system is 
    // shutting down. Specifies what should occur immediately prior to the 
    // system shutting down.
    virtual void OnShutdown();
};