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

#pragma once

class ProcessStartInfo;
struct ProcessInfo;

class RegistryManager
{
public:
	static std::wstring ReadString(const HKEY& hKey, const std::wstring& valueName);
	static DWORD ReadDWORD(const HKEY& hKey, const std::wstring& valueName);
	static ULONGLONG ReadQWORD(const HKEY& hKey, const std::wstring& valueName);
	static bool ReadBool(const HKEY& hKey, const std::wstring& valueName);
	static std::vector<std::wstring> ReadMultiString(const HKEY& hKey, const std::wstring& valueName);
	static void WriteString(const HKEY& hKey, const std::wstring& valueName, const std::wstring& value);
	static void WriteDWORD(const HKEY& hKey, const std::wstring& valueName, const DWORD value);
	static void WriteQWORD(const HKEY& hKey, const std::wstring& valueName, const ULONGLONG value);
	static void WriteBool(const HKEY& hKey, const std::wstring& valueName, const bool value);
	static void WriteMultiString(const HKEY& hKey, const std::wstring& valueName, const std::vector<std::wstring>& value);

	static void WriteProcessInformationInRegistry(const std::wstring& serviceName, const ProcessInfo& processInfo);
	static std::vector<std::wstring> ConvertMultiStringToWString(const std::vector<wchar_t>& data);
	static std::vector<wchar_t> ConvertWStringToMultiString(const std::vector<std::wstring>& data);
};
