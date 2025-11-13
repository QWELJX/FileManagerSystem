#pragma once
#include <string>
#include <vector>


const static char SEPARATOR = '\\';

class PathUtils {
public:
    // 禁止创建实例
    PathUtils() = delete;
    ~PathUtils() = delete;
    PathUtils(const PathUtils&) = delete;
    PathUtils& operator=(const PathUtils&) = delete;




    /**
     * @brief 连接路径组件（最常用的功能）
     */
    static std::string join(const std::string& path1, const std::string& path2);
    static std::string join(const std::vector<std::string>& components);

    /**
     * @brief 获取路径的目录部分
     */
    static std::string getDirectory(const std::string& path);

    /**
     * @brief 获取路径的文件名部分
     */
    static std::string getFilename(const std::string& path);

    /**
     * @brief 获取文件扩展名
     */
    static std::string getExtension(const std::string& path);

    /**
     * @brief 获取文件名（不含扩展名）
     */
    static std::string getStem(const std::string& path);

    /**
     * @brief 规范化路径
     * - 统一分隔符
     * - 处理 "." 和 ".."
     * - 移除多余分隔符
     */
    static std::string normalize(const std::string& path);
	
    /**
     * @brief 检查路径是否为绝对路径
     */
    static bool isAbsolute(const std::string& path);



    /**
     * @brief 分割路径为目录和文件名
     */
    static std::pair<std::string, std::string> split(const std::string& path);

    /**
     * @brief 统一路径分隔符
     */
    static std::string uniformSeparator(const std::string& path, char separator = SEPARATOR);

    /**
     * @brief 路径清理，移除不安全字符
     */
    static std::string sanitize(const std::string& path);

    /**
     * @brief 检查路径是否以指定扩展名结尾
     */
    static bool hasExtension(const std::string& path, const std::string& extension);

private:
    // 内部工具函数
    static bool isSeparator(char c);
    static bool isCurrentDirectory(const std::string& component);
    static bool isParentDirectory(const std::string& component);
    static std::pair<bool, std::vector<std::string>> splitComponents(const std::string& path);
};