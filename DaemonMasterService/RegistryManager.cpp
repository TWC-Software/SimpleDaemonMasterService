//  DaemonMasterService: RegistryManager
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
#include "RegistryManager.h"
#include "Exceptions.h"
#include "ProcessStartInfo.h"
#include "ProcessStartInfo.h"

#define REG_PATH L"SYSTEM\\CurrentControlSet\\Services\\"
#define	PARAMS_SUBKEY L"\\Parameters"
#define	PROCINFO_SUBKEY L"\\ProcessInfo"

using namespace std;


// https://msdn.microsoft.com/en-us/magazine/mt808504.aspx

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   Read                                                          //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

wstring RegistryManager::ReadString(const HKEY& hKey, const wstring& valueName)
{
	LSTATUS retCode;
	DWORD dataSize = {};

	//Get data size
	retCode = RegGetValueW(hKey, NULL, valueName.c_str(), RRF_RT_REG_SZ, nullptr, nullptr, &dataSize);
	if(retCode != ERROR_SUCCESS)
	{
		throw RegistryError("Cannot acquire the string size from the registry.", retCode);
	}

	//Get the lenght in wchars
	DWORD stringLengthInWchars = dataSize / sizeof(wchar_t);

	wstring data;
	data.resize(stringLengthInWchars);

	//The &data[0] is the address of the wstring internal buffer that will be written by the RegGetValue API.
	retCode = RegGetValueW(hKey, NULL, valueName.c_str(), RRF_RT_REG_SZ, nullptr, &data[0], &dataSize);
	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError("Cannot read the string from the registry.", retCode);
	}

	//Remove double NUL-terminator at the end of the string
	stringLengthInWchars--;
	data.resize(stringLengthInWchars);

	return data;
}

DWORD RegistryManager::ReadDWORD(const HKEY& hKey, const wstring& valueName)
{
	LSTATUS retCode;
	DWORD dataSize = sizeof(DWORD);
	DWORD data;

	retCode = RegGetValueW(hKey, NULL, valueName.c_str(), RRF_RT_DWORD, NULL, &data, &dataSize);
	if (retCode != ERROR_SUCCESS)
	{	
		throw RegistryError("Cannot read the DWORD value from the registry.", retCode);
	}

	return data;
}

bool RegistryManager::ReadBool(const HKEY& hKey, const wstring& valueName)
{
	DWORD const result = ReadDWORD(hKey, valueName);

	return result != 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   Write                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RegistryManager::WriteString(const HKEY& hKey, const wstring& valueName, const wstring& value)
{
	LSTATUS retCode;
	DWORD dataSize = {};

	//Set data in reg
	retCode = RegSetValueExW(hKey, valueName.c_str(), NULL, RRF_RT_REG_SZ, (LPBYTE)(value.c_str()), value.size() * sizeof(wchar_t));
	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError("Cannot write the string into the registry.", retCode);
	}
}

void RegistryManager::WriteDWORD(const HKEY& hKey, const wstring& valueName, const DWORD value)
{
	LSTATUS retCode;

	retCode = RegSetValueExW(hKey, valueName.c_str(), NULL, RRF_RT_DWORD, reinterpret_cast<LPBYTE>(value), sizeof(DWORD));
	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError("Cannot write the DWORD into the registry.", retCode);
	}
}

void RegistryManager::WriteBool(const HKEY& hKey, const wstring& valueName, const bool value)
{
	WriteDWORD(hKey, valueName,value);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   Other                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ProcessStartInfo RegistryManager::ReadProcessStartInfoFromRegistry(const wstring& serviceName)
{
	const wstring regPath = REG_PATH + serviceName + PARAMS_SUBKEY;
	ProcessStartInfo processStartInfo;
	LSTATUS retCode;
	HKEY hKey;


	retCode = RegOpenKeyExW(HKEY_LOCAL_MACHINE, regPath.c_str(), 0, KEY_READ, &hKey);
	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError("Cannot open the registry key.", retCode);
	}

	try
	{
		processStartInfo.SetFileDir(ReadString(hKey, L"FileDir"));
		processStartInfo.SetFileName(ReadString(hKey, L"FileName"));
		processStartInfo.SetFullPath(Functions::CombinePaths(processStartInfo.GetFileDir(), processStartInfo.GetFileName()));
		processStartInfo.SetParameters(ReadString(hKey, L"Parameter"));

		processStartInfo.SetIsConsoleApp(ReadBool(hKey, L"ConsoleApplication"));
		processStartInfo.SetUseCtrlC(ReadBool(hKey, L"UseCtrlC"));

		processStartInfo.SetMaxRestarts(ReadDWORD(hKey, L"MaxRestarts"));
		processStartInfo.SetRestartCounterResetTime(ReadDWORD(hKey, L"CounterResetTime"));
	}
	//This catch only close the regkey and then throw the exception to the caller
	catch(RegistryError)
	{
		RegCloseKey(hKey);
		throw;
	}

	RegCloseKey(hKey);
	return processStartInfo;
}

void RegistryManager::WriteProcessInformationInRegistry(const wstring& serviceName, const ProcessInfo& processInfo)
{
	//TODO:
	//const wstring regPath = REG_PATH + serviceName + PROCINFO_SUBKEY;
	//LSTATUS retCode;
	//HKEY hKey;


	//retCode = RegOpenKeyExW(HKEY_LOCAL_MACHINE, regPath.c_str(), 0, KEY_WRITE, &hKey);
	//if (retCode != ERROR_SUCCESS)
	//{
	//	throw RegistryError("Cannot open the registry key.", retCode);
	//}

	//try
	//{
	//	WriteDWORD(hKey, L"PID", processInfo.processId);
	//	WriteDWORD(hKey, L"TID", processInfo.threadId);
	//}
	////This catch only close the regkey and then throw the exception to the caller
	//catch (RegistryError)
	//{
	//	RegCloseKey(hKey);
	//	throw;
	//}

	//RegCloseKey(hKey);
}