#include "TreeNodeType.h"
#include <algorithm>    // 用于 std::transform
#include <cctype> 
#include <unordered_map> 

// 函数实现在.cpp文件中
// 用 static 限制全局变量作用域
static const std::unordered_map<std::string, TreeNodeType> str_to_type = {
    {"txt", TreeNodeType::TXT},
    {"",TreeNodeType::DIRECTORY},

};

static const std::unordered_map<TreeNodeType, std::pair<std::string, std::string>> type_to_str = {
    {TreeNodeType::TXT, {"txt", "文本文件"}},
	{TreeNodeType::DIRECTORY, {"", "目录"}},
};


std::pair<std::string, std::string> treeNodeTypeToString(TreeNodeType type) {
    auto it = type_to_str.find(type);
    if (it != type_to_str.end()) {
        return it->second;
    }
    return { "", "未知文件类型" };
}

TreeNodeType stringToTreeNodeType(std::string temp) {
    std::string extension = toLower(temp);
    auto it = str_to_type.find(extension);
    return (it != str_to_type.end()) ? it->second : TreeNodeType::UNKNOWN;
}

std::string toLower(std::string str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}