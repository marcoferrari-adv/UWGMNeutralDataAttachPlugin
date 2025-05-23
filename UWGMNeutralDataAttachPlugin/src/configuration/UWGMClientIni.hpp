#pragma once

#include <string>
#include <unordered_map>

static constexpr const wchar_t* DEFAULT_SECTION = L"General";
static constexpr const wchar_t* UWGM_CLIENT_INI_FILE_NAME = L"wgmclient.ini";

class UWGMClientIni
{
public:
    static UWGMClientIni* getInstance();

    static std::vector<std::wstring> getMultiValueTokens(const std::wstring& input, wchar_t delimiter = L';');

    // Esempio di metodo
    std::wstring getValue(const std::wstring& section, const std::wstring& key) const;
    std::wstring readProperty(const std::wstring& authoringApp, const std::wstring& propertyKey) const;
    std::wstring dumpIniMap();

    ~UWGMClientIni(); // distruttore privato

private:
    std::unordered_map<std::wstring, std::unordered_map<std::wstring, std::wstring>> m_SectionToValuesMap;

    UWGMClientIni();  // costruttore privato
  
    UWGMClientIni(const UWGMClientIni&) = delete;
    UWGMClientIni& operator=(const UWGMClientIni&) = delete;

    
    void loadIniFile();
};