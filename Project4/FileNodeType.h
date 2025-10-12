//�����

#pragma once
#include <string>
#include <utility>//����pair
#include <algorithm>    // ���� std::transform
#include <cctype> 
enum class FileNodeType
{
    DIRECTORY,
    TXT,
    ERROR
};

// ��������
std::pair<std::string,std::string> fileTypeToString(FileNodeType type);

FileNodeType stringToFileType(const std::string& temp);

std::string toLower(const std::string& str);
