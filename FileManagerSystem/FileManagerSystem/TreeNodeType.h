//第五个

#pragma once
#include <string>
#include <utility>//引入pair


enum class TreeNodeType
{
    DIRECTORY, FILE, TXT, UNKNOWN
};



std::pair<std::string, std::string> treeNodeTypeToString(TreeNodeType type);

TreeNodeType stringToTreeNodeType(std::string temp);

std::string toLower(std::string str);
