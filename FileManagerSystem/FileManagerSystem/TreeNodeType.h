//�����

#pragma once
#include <string>
#include <utility>//����pair


enum class TreeNodeType
{
    DIRECTORY, FILE, TXT, UNKNOWN
};



std::pair<std::string, std::string> treeNodeTypeToString(TreeNodeType type);

TreeNodeType stringToTreeNodeType(std::string temp);

std::string toLower(std::string str);
