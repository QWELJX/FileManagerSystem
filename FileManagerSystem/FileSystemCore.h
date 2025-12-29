#pragma once

#include <ctime>
#include <filesystem>
#include <string>
#pragma region 命名空间
namespace fs = std::filesystem;
namespace  FileSystemUtils {
    // 编码转换工具
    // 宽字符串 (UTF-16) 转 UTF-8 字符串
    std::string WideToUTF8(const std::wstring& wideStr);
    std::wstring UTF8ToWide(const std::string& utf8Str);
    //格式工具
    std::time_t fileTimeToTimeT(const fs::file_time_type& ftime);
    std::string formatFileSize(uintmax_t size);
    //绝对路径工具

    fs::path makeAbsoluteFromCurrentDir(const std::string& relative_or_abs); // 基于系统exe当前目录
    fs::path makeAbsolutePath(const std::string& path, const fs::path& base); // 基于指定 base
    //权限检擦
    bool isCriticalSystemPath(const fs::path& path); // 关键路径检查（Windows）
    bool hasDeletePermission(const fs::path& path); // 权限检查（简单版）
    //字符处理
    std::pair<int, int> parseUtf8Char(const unsigned char* str, size_t len, size_t pos);
    // 内部实现细节

    int getDisplayWidth(const std::string& str);
    std::string padToDisplayWidth(const std::string& str, int width, bool leftAlign);

}
#pragma endregion


class FileSystemCore {
public:
    // 构造函数：初始化文件系统核心
    FileSystemCore();

    // 获取/设置当前路径
    // 返回：当前工作目录的路径对象
    fs::path getCurrentPath() const;
    
    // 获取当前目录的父目录
    // 返回：父目录路径（UTF-8编码）
    std::string getParentPath() const;
    // 获取最近的错误信息
    // 返回：错误信息字符串
    const std::string& getLastError() const { return last_error_; }

    // 核心操作
    // 创建目录
    // 参数：dir_name - 要创建的目录名称（UTF-8编码）
    //       recursive - 是否递归创建父目录（默认为false）
    // 返回：成功返回true，失败返回false并设置错误信息
    bool createDirectory(const std::string& dir_name, bool recursive = false);
    // 创建空文件
    // 参数：file_name - 要创建的文件名称（UTF-8编码）
    // 返回：成功返回true，失败返回false并设置错误信息
    bool createFile(const std::string& file_name);
    // 删除文件或目录
    // 参数：path - 要删除的路径（UTF-8编码）
    //       recursive - 是否递归删除目录内容（默认为false）
    // 返回：成功返回true，失败返回false并设置错误信息
    bool deletePath(const std::string& path, bool recursive = false);
    // 移动或重命名文件/目录
    // 参数：source - 源路径（UTF-8编码）
    //       destination - 目标路径（UTF-8编码）
    // 返回：成功返回true，失败返回false并设置错误信息
    bool movePath(const std::string& source, const std::string& destination);
    // 重命名文件或目录
    // 参数：old_name - 旧名称（UTF-8编码）
    //       new_name - 新名称（UTF-8编码）
    // 返回：成功返回true，失败返回false并设置错误信息
    bool renamePath(const std::string& old_name, const std::string& new_name);
	// 更改当前工作目录
	// 参数：new_path - 要切换到的新目录路径（UTF-8编码）
	// 返回：成功返回true，失败返回false并设置错误信息
    bool ChangePath(const std::string& new_path);
    // 查询与列表
    // 列出目录内容
    // 参数：detailed - 是否显示详细信息（默认为false）
    //       recursive - 是否递归列出子目录（默认为false）
    // 返回：目录内容的字符串表示
    std::string listDirectory(bool detailed = false,bool recursive = false) const;
    // 检查路径是否存在
    // 参数：path - 要检查的路径（UTF-8编码）
    // 返回：存在返回true，不存在返回false
    bool pathExists(const std::string& path) const;
    //绝对路径获取辅助工具
    fs::path makeAbsolutePath(const std::string& relative_or_abs) const; // 基于 current_path
private:
    fs::path current_path;     // 当前工作目录
    std::string last_error_{}; // 最近一次错误信息
    // 设置当前工作目录
    // 参数：new_path - 要设置的新目录路径（UTF-8编码）
    // 返回：成功返回true，失败返回false并设置错误信息
    bool setCurrentPath(const fs::path& new_path);
    //内部实现 
    bool deleteSingle(const fs::path& target);    // 非递归删除
    bool deleteRecursive(const fs::path& target); // 递归删除

    void setLastError(const std::string& msg) { last_error_ = msg; }
    void listDirectoryImpl(const fs::path& dir, bool detailed, bool recursive, std::ostringstream& output) const;
    
};