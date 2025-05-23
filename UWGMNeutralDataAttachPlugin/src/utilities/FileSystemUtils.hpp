#pragma once
#include <xstring.h>
#include <string>

class FileSystemUtils
{
public:
	static bool copyFile(xstring pathFrom, xstring pathTo);

	static bool copyFile(std::wstring pathFrom, std::wstring pathTo);

	static bool copyFile(const wchar_t* pathFrom, const wchar_t* pathTo);
};