//第五个

#pragma once
#include <string>
#include <utility>//引入pair
#include <algorithm>    // 用于 std::transform
#include <cctype> 
enum class FileNodeType
{
    DIRECTORY,
    TXT,
    ERROR
};

// 函数声明
std::pair<std::string,std::string> fileTypeToString(FileNodeType type);

FileNodeType stringToFileType(const std::string& temp);

std::string toLower(const std::string& str);
