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


ProcessManager::ProcessManager()
{
}

ProcessManager::~ProcessManager()
{	
}

//Set the process start infos
void ProcessManager::SetProcessStartInfo(const ProcessStartInfo& processStartInfo)
{
	_processStartInfo = processStartInfo;
}

//Set start mode (start in user session)
void ProcessManager::SetStartMode(bool startInUserSession)
{
	_startInUserSession = startInUserSession;
}

bool ProcessManager::StartProcess()
{

}

bool ProcessManager::StopProcess()
{

}

void ProcessManager::KillProcess()
{
}