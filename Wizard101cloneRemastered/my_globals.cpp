#include "my_globals.h"

std::unordered_map<std::wstring, locations_enum> map_wstr_location = {
    { L"Headmaster Ambrose Office", locations_enum::Headmaster_Ambrose_Office },
    { L"The Commons", locations_enum::The_Commons },
    { L"Ravenwood", locations_enum::Ravenwood },
    { L"Unicorn Way", locations_enum::Unicorn_Way }
};
std::unordered_map<std::wstring, school_enum> map_wstr_school = {
    { L"Fire", school_enum::Fire },
    { L"Ice", school_enum::Ice },
    { L"Storm", school_enum::Storm },
    { L"Myth", school_enum::Myth },
    { L"Life", school_enum::Life },
    { L"Death", school_enum::Death },
    { L"Balance", school_enum::Balance },
    { L"Any", school_enum::Any }
};

// convert a wide Unicode string to a UTF8 string
std::string narrow(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

// convert a UTF8 string to a wide Unicode String
std::wstring widen(const std::string& str)
{
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}