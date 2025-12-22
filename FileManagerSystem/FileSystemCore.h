#pragma once
#include <filesystem>
#include <string>
#include <vector>
namespace fs = std::filesystem;

class FileSystemCore {
private:
    fs::path current_path;  // 当前工作目录

    // 内部工具函数
    static std::time_t fileTimeToTimeT(const fs::file_time_type& ftime);
    static std::string formatFileSize(uintmax_t size);

public:
    FileSystemCore();

    // 获取/设置当前路径
    fs::path getCurrentPath() const;
    bool setCurrentPath(const std::string& new_path);

    // 核心操作
    bool createDirectory(const std::string& dir_name);
    bool createFile(const std::string& file_name);
    bool deletePath(const std::string& path, bool recursive = false);
    bool movePath(const std::string& source, const std::string& destination);
    bool renamePath(const std::string& old_name, const std::string& new_name);

    // 查询与列表
    std::string listDirectory(bool detailed = false) const;
    bool pathExists(const std::string& path) const;

    // 辅助功能
    static void clearScreen();
    std::string getParentPath() const;
};