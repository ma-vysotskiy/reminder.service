// reminder.service.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include "Reminder.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CReminder service;
	if(!CServiceBase::Run(service)) {
		cout << " Service failed to run w/err " << hex << GetLastError() << endl;
	}
	return 0;
}

