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

#pragma once

class ProcessManager
{
public:
	ProcessManager();
	~ProcessManager();

	void SetStartMode(bool startInUserSession);
	bool StartProcess(const std::wstring& serviceName);
	bool StopProcess();
	void KillProcess();

private:
	void StartInSession0();
	void ReadProcessStartInfoFromRegistry(const std::wstring& serviceName);
	
	//Registry infos
	std::wstring _fileDir{ L"" };
	std::wstring _fileName{ L"" };
	std::wstring _fullPath{ L"" };
	std::wstring _params{ L"" };

	bool _useLocalSystemAccount{ true };
	bool _unlimitedRestarts{ false };
	int _maxRestarts{ 3 };
	int _restartCounterResetTime{ 0 };

	bool _isConsoleApp{ false };
	bool _useCtrlC{ false };

	bool _assignAutoKillJob{ true };
	int _processPriority{ 0 };
	std::vector<wchar_t> _environmentVariables{ L'\0\0' };

	//Process
	PROCESS_INFORMATION _pi;
	bool _startInUserSession{ false };
};

