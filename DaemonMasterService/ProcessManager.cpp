//  DaemonMasterService: ProcessManager
//  
//  This file is part of DeamonMasterService.
// 
//  DeamonMaster is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//   DeamonMaster is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with DeamonMasterService.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProcessManager.h"
#include <minwinbase.h>
#include "RegistryManager.h"

#define REG_PATH L"SYSTEM\\CurrentControlSet\\Services\\"
#define	PARAMS_SUBKEY L"\\Parameters"
#define	PROCINFO_SUBKEY L"\\ProcessInfo"

using namespace std;


ProcessManager::ProcessManager()
{

}

ProcessManager::~ProcessManager()
{	

}

//Set start mode (start in user session)
void ProcessManager::SetStartMode(bool startInUserSession)
{
	_startInUserSession = startInUserSession;
}

bool ProcessManager::StartProcess(const wstring& serviceName)
{
	//Read data from Registry
	ReadProcessStartInfoFromRegistry(serviceName);


	if (_fullPath.empty())
		throw invalid_argument("The full path a not be empty.");

	try
	{
		if (_startInUserSession)
		{

		}
		else
		{
			StartInSession0();
		}
	}
	catch(const APICallFail& ex)
	{
		Logger::Error(ex.what() + string("\nError code: ") + std::to_string(ex.ErrorCode()));
		return false;
	}

	return true;
}

bool ProcessManager::StopProcess()
{

}

void ProcessManager::KillProcess()
{
}

//---------

void  ProcessManager::StartInSession0()
{
	DWORD creationFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT | CREATE_BREAKAWAY_FROM_JOB;
	//Process priority
	switch (_processPriority)
	{
	case -2:
		creationFlags |= IDLE_PRIORITY_CLASS;
		break;

	case -1:
		creationFlags |= BELOW_NORMAL_PRIORITY_CLASS;
		break;

	case 0:
		creationFlags |= NORMAL_PRIORITY_CLASS;
		break;

	case 1:
		creationFlags |= ABOVE_NORMAL_PRIORITY_CLASS;
		break;

	case 2:
		creationFlags |= HIGH_PRIORITY_CLASS;
		break;

	case 3:
		creationFlags |= REALTIME_PRIORITY_CLASS;
		break;

	default:
		creationFlags |= NORMAL_PRIORITY_CLASS;
		break;
	}

	STARTUPINFO si;

	//Start info
	wstring desktop = L"winsta0\default";
	ZeroMemory(&si, sizeof(si));
	si.cb           = sizeof(si);
	si.lpDesktop = &desktop[0];

	//Process info
	ZeroMemory(&_pi, sizeof(_pi));

	if(!CreateProcessW(_fullPath.c_str(), _tcsdup(_params.c_str()), NULL, NULL, false, creationFlags, &_environmentVariables[0], _fileDir.c_str(), &si, &_pi))
	{
		const DWORD lastError = GetLastError();
		throw APICallFail("CreateProcessW is failed", lastError);
	}
}

void ProcessManager::ReadProcessStartInfoFromRegistry(const wstring& serviceName)
{
	const wstring regPath = REG_PATH + serviceName + PARAMS_SUBKEY;
	LSTATUS retCode;
	HKEY hKey;


	retCode = RegOpenKeyExW(HKEY_LOCAL_MACHINE, regPath.c_str(), 0, KEY_READ, &hKey);
	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError("Cannot open the registry key.", retCode);
	}

	try
	{
		_fileDir = RegistryManager::ReadString(hKey, L"FileDir");
		_fileName = RegistryManager::ReadString(hKey, L"FileName");
		_fullPath = _fileDir + L"\\" + _fileName;
		_params = RegistryManager::ReadString(hKey, L"Parameter");

		_isConsoleApp = RegistryManager::ReadBool(hKey, L"ConsoleApplication");
		_useCtrlC= RegistryManager::ReadBool(hKey, L"UseCtrlC");

		_maxRestarts = RegistryManager::ReadDWORD(hKey, L"MaxRestarts");
		_restartCounterResetTime = RegistryManager::ReadDWORD(hKey, L"CounterResetTime");
	}
	//This catch only close the regkey and then throw the exception to the caller
	catch (RegistryError)
	{
		RegCloseKey(hKey);
		throw;
	}

	RegCloseKey(hKey);
}