#include "FileNodeType.h"

// 函数实现在.cpp文件中
std::pair<std::string, std::string> fileTypeToString(FileNodeType type) {
    switch (type) {
    case FileNodeType::DIRECTORY: return { "文件夹" ,"" };
    case FileNodeType::TXT: return { "文本文件",".txt" };
    default: return { "其他","" };
    }
}

FileNodeType stringToFileType(const std::string& temp) {
    std::string extension = toLower(temp);
    if (temp == "dirctory")
        return FileNodeType::DIRECTORY;
    else if (temp == "txt")
        return FileNodeType::TXT;
    else
        return FileNodeType::DIRECTORY;
}
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}