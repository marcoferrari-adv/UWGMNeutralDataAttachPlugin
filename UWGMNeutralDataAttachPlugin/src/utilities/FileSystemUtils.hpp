#pragma once
#include <xstring.h>
#include <string>

class FileSystemUtils
{
public:
	static bool copyFile(const xstring& pathFrom, const xstring& pathTo);

	static bool copyFile(const std::wstring& pathFrom, const std::wstring& pathTo);

	static bool copyFile(const wchar_t* pathFrom, const wchar_t* pathTo);
};