#include "pch.hpp"

#include "FileSystemUtils.hpp"

bool FileSystemUtils::copyFile(const xstring& pathFrom, const xstring& pathTo)
{
    return copyFile(static_cast<const wchar_t*>(pathFrom), static_cast<const wchar_t*>(pathTo));
}

bool FileSystemUtils::copyFile(const std::wstring& pathFrom, const std::wstring& pathTo)
{
    return copyFile(pathFrom.c_str(), pathFrom.c_str());
}

bool FileSystemUtils::copyFile(const wchar_t* pathFrom, const wchar_t* pathTo)
{

    if (pathFrom == nullptr || pathTo == nullptr || wcslen(pathFrom) == 0 || wcslen(pathTo) == 0)
    {
        return false;
    }

    std::ifstream src(pathFrom, std::ios::binary);
    std::ofstream dst(pathTo, std::ios::binary);

    if (!src.is_open() || src.bad() || !dst.is_open() || dst.bad())
    {
        return false;
    }

    dst << src.rdbuf();

    return true;
}


