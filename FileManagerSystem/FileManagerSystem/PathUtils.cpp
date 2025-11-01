#include "PathUtils.h"
#include <algorithm>
#include <sstream>
#include <utility>
#include <cctype>

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
                    normalized.push_back(component);  // ���·������ ".."                   
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

#ifdef _WIN32  // Windows ϵͳ������ 32/64 λ��
	// ����1���Է�б�ܻ���б�ܿ�ͷ����Ŀ¼��
    if (path.size() > 0 && path[0] == SEPARATOR) {
        return true;
    }
    // ����2���̷�·������ "C:"����ĸ+ð�ţ�
    if (path.size() >= 1 && std::isalpha(path[0]) && path[1] == ':') { 
        return true;
    }

#elif defined(__linux__) || defined(__APPLE__)  // Linux �� macOS ϵͳ
    // ������ '/' ��ͷ����Ŀ¼��
    if (path[0] == '/') {
        return true;
    }

#endif  // ������������

    // ����ϵͳ�¶����������·��������Ϊ���·��
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

std::pair<bool, std::vector<std::string>> PathUtils::splitComponents(const std::string& path) {
    std::vector<std::string> components;
    bool is_absolute = isAbsolute(path);  // ����֮ǰ�ľ���·���жϺ���

    if (path.empty()) {
        return std::make_pair(is_absolute, components);
    }

    std::stringstream ss(path);
    std::string component;
    char sep = SEPARATOR;  // ������ͨ���������붨�壨�� '\' �� '/'��

    // ���ָ����и�ʣ�ಿ��
    while (std::getline(ss, component, sep)) {
        if (!component.empty()) {
            components.push_back(component);
        }
    }

    return std::make_pair(is_absolute, components);
}