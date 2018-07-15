//  DaemonMasterService: ServiceMain
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
#include "ServiceMain.h"


ServiceMain::ServiceMain(std::wstring& serviceName): ServiceBase(serviceName)
{
}

ServiceMain::~ServiceMain()
{
}

//Get called when the service starts (argv[0] is the service name)
void ServiceMain::OnStart(DWORD argc, PWSTR* argv)
{

}

//Get called when the service shold stop
void ServiceMain::OnStop()
{

}

void ServiceMain::OnShutdown()
{

}
