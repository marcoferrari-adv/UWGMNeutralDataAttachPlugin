#include "pch.hpp"

#include "UWGMClientIni.hpp"

#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <sstream>
#include <iomanip>

//inizializzazione thread safe da c++11
//non necessario uso mutext o lock e sconsigliato
//in ambito dll
UWGMClientIni* UWGMClientIni::getInstance()
{
    static UWGMClientIni instance;
    return &instance;
}

UWGMClientIni::UWGMClientIni()
{
    loadIniFile();
}

UWGMClientIni::~UWGMClientIni()
{
}

std::wstring UWGMClientIni::getValue(const std::wstring& section, const std::wstring& key) const
{
    auto secIt = m_SectionToValuesMap.find(section);
    if (secIt != m_SectionToValuesMap.end())
    {
        const auto& innerMap = secIt->second;
        auto valIt = innerMap.find(key);
        if (valIt != innerMap.end())
            return valIt->second;
    }
    return L"";
}

void UWGMClientIni::loadIniFile()
{
    wchar_t executablePath[MAX_PATH];
    DWORD result = GetModuleFileName(NULL, executablePath, MAX_PATH);
    if (!result)
        return;

    std::wstring path = executablePath;
    for (int i = 0; i <= 2; ++i)
    {
        size_t pos = path.find_last_of(L"\\");
        if (pos != std::string::npos)
            path = path.substr(0, pos);
    }

    path.append(L"\\").append(UWGM_CLIENT_INI_FILE_NAME);
    
    std::wifstream  file(path);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!file)
        return;

    std::wstring line;
    std::wstring currentSection = DEFAULT_SECTION;
    while (std::getline(file, line))
    {
        
        line.erase(0, line.find_first_not_of(L" \t\r\n"));
        line.erase(line.find_last_not_of(L" \t\r\n") + 1);

        if (line.empty() || line.front() == '#' || line.front() == ';')
            continue;

        if (line.front() == L'[' && line.back() == L']')
        {
            currentSection = line.substr(1, line.length() - 2);
            continue;
        }

        size_t equalPos = line.find(L'=');
        if (equalPos != std::wstring::npos)
        {
            std::wstring key = line.substr(0, equalPos);
            std::wstring value = line.substr(equalPos + 1);

            // Trim spazi
            key.erase(0, key.find_first_not_of(L" \t\r\n"));
            key.erase(key.find_last_not_of(L" \t\r\n") + 1);
            value.erase(0, value.find_first_not_of(L" \t\r\n"));
            value.erase(value.find_last_not_of(L" \t\r\n") + 1);

            m_SectionToValuesMap[currentSection][key] = value;
        }
    }
}

std::wstring UWGMClientIni::readProperty(const std::wstring& authoringApp, const std::wstring& propertyKey) const
{
    // Prima ricerca nella sezione specifica
    auto sectionIt = m_SectionToValuesMap.find(authoringApp);
    if (sectionIt != m_SectionToValuesMap.end())
    {
        const auto& valueMap = sectionIt->second;
        auto keyIt = valueMap.find(propertyKey);
        if (keyIt != valueMap.end())
            return keyIt->second;
    }

    // Seconda ricerca nel DEFAULT_SECTION
    auto defaultIt = m_SectionToValuesMap.find(DEFAULT_SECTION);
    if (defaultIt != m_SectionToValuesMap.end())
    {
        const auto& valueMap = defaultIt->second;
        auto keyIt = valueMap.find(propertyKey);
        if (keyIt != valueMap.end())
            return keyIt->second;
    }

    // Non trovato
    return L"";
}

std::wstring UWGMClientIni::dumpIniMap()
{
    std::wostringstream oss;
    oss << L"{\n";
    for (const auto& section : m_SectionToValuesMap)
    {
        oss << L"\t[" << section.first << L"] {\n";
        for (const auto& kv : section.second)
        {
            oss << L"\t\t" << kv.first << L"=" << kv.second << L"\n";
        }
        oss << L"\t}\n";
    }
    oss << L"}";
    return oss.str();
}

std::vector<std::wstring> UWGMClientIni::getMultiValueTokens(const std::wstring& input, wchar_t delimiter)
{
    std::vector<std::wstring> tokens;
    std::wstring current;

    for (const auto ch : input)
    {
        if (ch == delimiter)
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current.clear();
            }
        }
        else
        {
            current += ch;
        }
    }

    // Aggiungi l'ultimo token se non vuoto
    if (!current.empty())
    {
        tokens.push_back(current);
    }

    return tokens;
}
