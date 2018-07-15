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

#include "ProcessStartInfo.h"

class ProcessManager
{
public:
	ProcessManager();
	~ProcessManager();

	void SetProcessStartInfo(const ProcessStartInfo& processStartInfo);
	void SetStartMode(bool startInUserSession);
	bool StartProcess();
	bool StopProcess();
	void KillProcess();

private:
	ProcessStartInfo _processStartInfo;
	bool _startInUserSession;
};

