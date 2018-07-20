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

#include "stdafx.h"
#include "ProcessStartInfo.h"

using namespace std;

const wstring& ProcessStartInfo::GetFileDir() const
{
	return _fileDir;
}

void ProcessStartInfo::SetFileDir(wstring fileDir)
{
	for (size_t i = 0; i < fileDir.length(); i++)
	{
		if (fileDir[i] == '\\')
		{
			fileDir.insert(i, 1, '\\');
			i++; // Skip inserted char
		}
	}

	_fileDir = fileDir;
}


//------------------------------------------------------------------------------------------------------

const wstring& ProcessStartInfo::GetFileName() const
{
	return _fileName;
}

void ProcessStartInfo::SetFileName(const wstring& fileName)
{
	_fileName = fileName;
}


//------------------------------------------------------------------------------------------------------

const wstring& ProcessStartInfo::GetFullPath() const
{
	return _fullPath;
}

void ProcessStartInfo::SetFullPath(const wstring& fullPath)
{
	_fullPath = fullPath;
}


//------------------------------------------------------------------------------------------------------

const wstring& ProcessStartInfo::GetParameters() const
{
	return _params;
}

void ProcessStartInfo::SetParameters(const wstring& params)
{
	_params = params;
}


//------------------------------------------------------------------------------------------------------

const bool ProcessStartInfo::GetUnlimitedRestarts() const
{
	return _unlimitedRestarts;
}

void ProcessStartInfo::SetUnlimitedRestarts(const bool unlimitedRestarts)
{
	_unlimitedRestarts = unlimitedRestarts;
}


//------------------------------------------------------------------------------------------------------

const DWORD ProcessStartInfo::GetMaxRestarts() const
{
	return _maxRestarts;
}

void ProcessStartInfo::SetMaxRestarts(const unsigned long maxRestarts)
{
	_maxRestarts = maxRestarts;
}


//------------------------------------------------------------------------------------------------------

const DWORD ProcessStartInfo::GetRestartCounterResetTime() const
{
	return _restartCounterResetTime;
}

void ProcessStartInfo::SetRestartCounterResetTime(const DWORD restartCounterResetTime)
{
	_restartCounterResetTime = restartCounterResetTime;
}


//------------------------------------------------------------------------------------------------------

const bool ProcessStartInfo::GetIsConsoleApp() const
{
	return _isConsoleApp;
}

void ProcessStartInfo::SetIsConsoleApp(const bool isConsoleApp)
{
	_isConsoleApp = isConsoleApp;
}


//------------------------------------------------------------------------------------------------------

const bool ProcessStartInfo::GetUseCtrlC() const
{
	return _useCtrlC;
}

void ProcessStartInfo::SetUseCtrlC(const bool useCtrlC)
{
	_useCtrlC = useCtrlC;
}


//------------------------------------------------------------------------------------------------------

const bool ProcessStartInfo::GetAssignAutoKillJob() const
{
	return _assignAutoKillJob;
}

void ProcessStartInfo::SetAssignAutoKillJob(const bool assignAutoKillJob)
{
	_assignAutoKillJob = assignAutoKillJob;
}


//------------------------------------------------------------------------------------------------------

const int ProcessStartInfo::GetPriority() const
{
	return _priority;
}

void ProcessStartInfo::SetPriority(const int priority)
{
	_priority = priority;
}
