
#include <algorithm>
#include <sstream>
#include "PathUtils.h"


std::string PathUtils::join(const std::string& path1, const std::string& path2) {
    if (path1.empty()) return path2;
    if (path2.empty()) return path1;

    // 如果 path2 是绝对路径，直接返回 path2
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

    // 统一分隔符
    std::string result = uniformSeparator(path);
    int x = 1;
    // 分割组件
    auto components = splitComponents(result);
    x = 1;
    std::vector<std::string> normalized;

    for (const auto& component : components) {
        if (component.empty() || isCurrentDirectory(component)) {
            continue;
        }

        if (isParentDirectory(component)) {
            if (!normalized.empty() && !isParentDirectory(normalized.back())) {
                normalized.pop_back();
            }
            else {
                normalized.push_back(component);
            }
        }
        else {
            normalized.push_back(component);
        }
    }

    // 重新组合
    result.clear();
    for (size_t i = 0; i < normalized.size(); ++i) {
        if (i > 0) {
            result += SEPARATOR;
        }
        result += normalized[i];
    }

    // 处理根路径
    if (isAbsolute(path) && result.empty()) {
        result = std::string(1, SEPARATOR);
    }

    return result;
}

bool PathUtils::isAbsolute(const std::string& path) {
    if (path.empty()) return false;
    return (path[0] != SEPARATOR);

}

bool PathUtils::isRelative(const std::string& path) {
    return !isAbsolute(path);
}

std::pair<std::string, std::string> PathUtils::split(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return { "", path };
    }
    return { path.substr(0, pos), path.substr(pos + 1) };
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

    // 移除或替换不安全字符
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

    // 确保扩展名以点开头
    std::string expected = extension;
    if (expected[0] != '.') {
        expected = "." + expected;
    }

    // 不区分大小写比较
    std::string actualLower = actualExtension;
    std::string expectedLower = expected;
    std::transform(actualLower.begin(), actualLower.end(), actualLower.begin(), ::tolower);
    std::transform(expectedLower.begin(), expectedLower.end(), expectedLower.begin(), ::tolower);

    return actualLower == expectedLower;
}

// 私有工具函数
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