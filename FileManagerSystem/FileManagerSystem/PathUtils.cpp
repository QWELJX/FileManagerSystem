#include "PathUtils.h"
#include <algorithm>
#include <sstream>
#include <utility>
#include <cctype>

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
    // 分割组件
	 auto head1 = result[0];
     auto results= splitComponents(result);
	 auto is_absolute = results.first;
	 auto components = results.second;
	 auto head = components.size() > 0 ? components[0] : "";
    std::vector<std::string> normalized;
    for (const auto& component : components) {
        if (component.empty() || isCurrentDirectory(component)) {
            continue;
        }

        if (isParentDirectory(component)) {
            if (!is_absolute) {
                if (!normalized.empty() && !isParentDirectory(normalized.back())) {                   
                    normalized.pop_back();                  
                }
                else {                   
                    normalized.push_back(component);  // 相对路径保留 ".."                   
                }
            }
            else {
                if (normalized.size()>1) {
                    normalized.pop_back();
                }
            }
           
        }
        else {
            normalized.push_back(component);
        }
    }

    result.clear();
    for (size_t i = 0; i < normalized.size(); ++i) {
        if (i > 0) {
            result += SEPARATOR;
        }
        result += normalized[i];
    }
    if (is_absolute && head1 == SEPARATOR) {
        result = SEPARATOR + result;

    }
    if (!is_absolute&& result.size() == 0) {
        result = '.';
    }

    return result;
}

bool PathUtils::isAbsolute(const std::string& path) {
    if (path.empty()) return false;

#ifdef _WIN32  // Windows 系统（包括 32/64 位）
	// 规则1：以反斜杠或正斜杠开头（根目录）
    if (path.size() > 0 && path[0] == SEPARATOR) {
        return true;
    }
    // 规则2：盘符路径（如 "C:"，字母+冒号）
    if (path.size() >= 1 && std::isalpha(path[0]) && path[1] == ':') { 
        return true;
    }

#elif defined(__linux__) || defined(__APPLE__)  // Linux 或 macOS 系统
    // 规则：以 '/' 开头（根目录）
    if (path[0] == '/') {
        return true;
    }

#endif  // 结束条件编译

    // 所有系统下都不满足绝对路径规则，则为相对路径
    return false;
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

std::pair<bool, std::vector<std::string>> PathUtils::splitComponents(const std::string& path) {
    std::vector<std::string> components;
    bool is_absolute = isAbsolute(path);  // 复用之前的绝对路径判断函数

    if (path.empty()) {
        return std::make_pair(is_absolute, components);
    }

    std::stringstream ss(path);
    std::string component;
    char sep = SEPARATOR;  // 假设已通过条件编译定义（如 '\' 或 '/'）

    // 按分隔符切割剩余部分
    while (std::getline(ss, component, sep)) {
        if (!component.empty()) {
            components.push_back(component);
        }
    }

    return std::make_pair(is_absolute, components);
}