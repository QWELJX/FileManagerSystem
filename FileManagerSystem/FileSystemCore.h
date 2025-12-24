#pragma once

#include <ctime>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

class FileSystemCore {
public:
  FileSystemCore();

  // 获取/设置当前路径
  fs::path getCurrentPath() const;
  bool setCurrentPath(const std::string &new_path);
  std::string getParentPath() const;
  const std::string &getLastError() const { return last_error_; }

  // 核心操作
  bool createDirectory(const std::string &dir_name,bool recursive=false);
  bool createFile(const std::string &file_name);
  bool deletePath(const std::string &path,bool recursive = false); // 对外统一名称，内部做安全删除
  bool movePath(const std::string &source, const std::string &destination);
  bool renamePath(const std::string &old_name, const std::string &new_name);

  // 查询与列表
  std::string listDirectory(bool detailed = false,bool recursive = false) const;
  bool pathExists(const std::string &path) const;

  // 辅助功能
  static void clearScreen();

private:
  fs::path current_path;     // 当前工作目录
  std::string last_error_{}; // 最近一次错误信息

  // 内部工具函数
  static std::time_t fileTimeToTimeT(const fs::file_time_type &ftime);
  static std::string formatFileSize(uintmax_t size);

  fs::path makeAbsolutePath(const std::string &relative_or_abs) const; // 基于 current_path
  static fs::path makeAbsoluteFromCurrentDir(const std::string &relative_or_abs); // 基于系统exe当前目录
  static fs::path makeAbsolutePath(const std::string &path,
                                   const fs::path &base); // 基于指定 base

  bool deleteSingle(const fs::path &target);    // 非递归删除
  bool deleteRecursive(const fs::path &target); // 递归删除

  static bool isCriticalSystemPath(const fs::path &path); // 关键路径检查（Windows）
  static bool hasDeletePermission(const fs::path &path); // 权限检查（简单版）

  void setLastError(const std::string &msg) { last_error_ = msg; }
  void listDirectoryImpl(const fs::path &dir, bool detailed, bool recursive,std::ostringstream &output) const;
  //字符处理
  static int getDisplayWidth(const std::string& str);
  static std::string padToDisplayWidth(const std::string& str, int targetWidth, bool leftAlign = true);
  static std::pair<int, int> parseUtf8Char(const unsigned char* str, size_t len, size_t pos);
  static std::string LocalToUTF8(const std::string& localStr);
};