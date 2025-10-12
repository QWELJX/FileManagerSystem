
#include <algorithm>
#include <sstream>
#include "PathUtils.h"


std::string PathUtils::join(const std::string& path1, const std::string& path2) {
    if (path1.empty()) return path2;
    if (path2.empty()) return path1;
    
    // ��� path2 �Ǿ���·����ֱ�ӷ��� path2
    if (isAbsolute(path2)) {
        return normalize(path2);
    }
    
    return normalize(path1 + SEPARATOR + path2);
}

std::string PathUtils::join(const std::vector<std::string>& components) {
    if (components.empty()) return "";
    
    std::string result;
    for (size_t i = 0; i < components.size(); ++i) {
        if (i > 0) {
            result += SEPARATOR;
        }
        result += components[i];
    }
    
    return normalize(result);
}

std::string PathUtils::getDirectory(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return "";
    }
    return path.substr(0, pos);
}

std::string PathUtils::getFilename(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(pos + 1);
}

std::string PathUtils::getExtension(const std::string& path) {
    std::string filename = getFilename(path);
    size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos || pos == 0) {
        return "";
    }
    return filename.substr(pos);
}

std::string PathUtils::getStem(const std::string& path) {
    std::string filename = getFilename(path);
    size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos || pos == 0) {
        return filename;
    }
    return filename.substr(0, pos);
}

std::string PathUtils::normalize(const std::string& path) {
    if (path.empty()) return "";
    
    // ͳһ�ָ���
    std::string result = uniformSeparator(path);
    
    // �ָ����
    auto components = splitComponents(result);
    std::vector<std::string> normalized;
    
    for (const auto& component : components) {
        if (component.empty() ||isCurrentDirectory(component)) {
            continue;
        }
        
        if (isParentDirectory(component)) {
            if (!normalized.empty() && !isParentDirectory(normalized.back())) {
                normalized.pop_back();
            } else {
                normalized.push_back(component);
            }
        } else {
            normalized.push_back(component);
        }
    }
    
    // �������
    result.clear();
    for (size_t i = 0; i < normalized.size(); ++i) {
        if (i > 0) {
            result += SEPARATOR;
        }
        result += normalized[i];
    }
    
    // �����·��
    if (isAbsolute(path) && result.empty()) {
        result = std::string(1, SEPARATOR);
    }
    
    return result;
}

bool PathUtils::isAbsolute(const std::string& path) {
    if (path.empty()) return false;
    return (path[0]!= '.');
        
}

bool PathUtils::isRelative(const std::string& path) {
    return !isAbsolute(path);
}

std::pair<std::string, std::string> PathUtils::split(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return {"", path};
    }
    return {path.substr(0, pos), path.substr(pos + 1)};
}

std::string PathUtils::uniformSeparator(const std::string& path, char separator) {
    std::string result = path;
    for (char& c : result) {
        if (isSeparator(c)) {
            c = separator;
        }
    }
    return result;
}

std::string PathUtils::sanitize(const std::string& path) {
    std::string result = path;
    
    // �Ƴ����滻����ȫ�ַ�
    for (char& c : result) {
        if (c == '\0' || c == '\"' || c == '<' || c == '>' || c == '|' || c == '*' || c == '?') {
            c = '_';
        }
    }
    
    return normalize(result);
}

bool PathUtils::hasExtension(const std::string& path, const std::string& extension) {
    std::string actualExtension = getExtension(path);
    if (extension.empty()) {
        return actualExtension.empty();
    }
    
    // ȷ����չ���Ե㿪ͷ
    std::string expected = extension;
    if (expected[0] != '.') {
        expected = "." + expected;
    }
    
    // �����ִ�Сд�Ƚ�
    std::string actualLower = actualExtension;
    std::string expectedLower = expected;
    std::transform(actualLower.begin(), actualLower.end(), actualLower.begin(), ::tolower);
    std::transform(expectedLower.begin(), expectedLower.end(), expectedLower.begin(), ::tolower);
    
    return actualLower == expectedLower;
}

// ˽�й��ߺ���
bool PathUtils::isSeparator(char c) {
    return c == '/' || c == '\\';
}

bool PathUtils::isCurrentDirectory(const std::string& component) {
    return component == ".";
}

bool PathUtils::isParentDirectory(const std::string& component) {
    return component == "..";
}

std::vector<std::string> PathUtils::splitComponents(const std::string& path) {
    std::vector<std::string> components;
    if (path.empty()) {
        return components;
    }
    
    std::stringstream ss(path);
    std::string component;
    
    while (std::getline(ss, component, SEPARATOR)) {
        if (!component.empty()) {
            components.push_back(component);
        }
    }
    
    return components;
}