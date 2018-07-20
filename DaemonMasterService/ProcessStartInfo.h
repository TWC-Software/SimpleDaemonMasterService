//  DaemonMasterService: ProcessStartInfo
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

class ProcessStartInfo
{
public:
	const std::wstring& GetFileDir() const;
	void SetFileDir(std::wstring filePath);

	const std::wstring& GetFileName() const;
	void SetFileName(const std::wstring& fileName);

	const std::wstring& GetFullPath() const;
	void SetFullPath(const std::wstring& fullPath);

	const std::wstring& GetParameters() const;
	void SetParameters(const std::wstring& params);


	const bool GetUnlimitedRestarts() const;
	void SetUnlimitedRestarts(const bool unlimitedRestarts);

	const DWORD GetMaxRestarts() const;
	void SetMaxRestarts(const unsigned long maxRestarts);

	const DWORD GetRestartCounterResetTime() const;
	void SetRestartCounterResetTime(const DWORD restartCounterResetTime);


	const bool GetIsConsoleApp() const;
	void SetIsConsoleApp(const bool isConsoleApp);

	const bool GetUseCtrlC() const;
	void SetUseCtrlC(const bool useCtrlC);

	const bool GetAssignAutoKillJob() const;
	void SetAssignAutoKillJob(const bool assignAutoKillJob);

	const int GetPriority() const;
	void SetPriority(const int priority);




private:
	std::wstring _fileDir = L"";
	std::wstring _fileName = L"";
	std::wstring _fullPath = L"";
	std::wstring _params = L"";

	bool _useLocalSystemAccount = true;
	bool _unlimitedRestarts = false;
	DWORD _maxRestarts = 3;
	DWORD _restartCounterResetTime = 0;

	bool _isConsoleApp = false;
	bool _useCtrlC = false;

	bool _assignAutoKillJob = true;
	int _priority = 0;
};