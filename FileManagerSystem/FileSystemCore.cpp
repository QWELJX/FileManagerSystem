#include "FileSystemCore.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <windows.h>

// 扩展名到友好类型名的简单映射表
static const std::unordered_map<std::string, std::string> EXT_TYPE_MAP = {
    {"txt", "文本文件"},
    {"md", "Markdown 文本"},
    {"html", "HTML 文件"},
    {"htm", "HTML 文件"},
    {"cpp", "C++ 源文件"},
    {"h", "C/C++ 头文件"},
    {"hpp", "C++ 头文件"},
    {"doc", "Microsoft Word 文档"},
    {"docx", "Microsoft Word 文档"},
    {"xls", "Microsoft Excel 工作簿"},
    {"xlsx", "Microsoft Excel 工作簿"},
    {"ppt", "Microsoft PowerPoint 演示文稿"},
    {"pptx", "Microsoft PowerPoint 演示文稿"},
    {"pdf", "PDF 文档"},
    {"jpg", "JPEG 图片"},
    {"jpeg", "JPEG 图片"},
    {"png", "PNG 图片"},
    {"gif", "GIF 图片"},
    {"bmp", "位图图片"},
    {"zip", "ZIP 压缩包"},
    {"rar", "RAR 压缩包"},
};










// 构造函数：初始化为当前目录
FileSystemCore::FileSystemCore() { current_path = fs::current_path(); }






// 时间转换工具函数：将 filesystem 时间转换为 time_t
std::time_t FileSystemCore::fileTimeToTimeT(const fs::file_time_type &ftime) {
  using namespace std::chrono;
  auto sctp = time_point_cast<system_clock::duration>(
      ftime - fs::file_time_type::clock::now() + system_clock::now());
  return system_clock::to_time_t(sctp);
}

// 格式化文件大小
std::string FileSystemCore::formatFileSize(uintmax_t size) {
  const char *units[] = {" B", "KB", "MB", "GB"};
  int unit = 0;
  double formatted_size = static_cast<double>(size);

  while (formatted_size >= 1024.0 && unit < 3) {
    formatted_size /= 1024.0;
    unit++;
  }

  std::ostringstream ss;
  if (unit == 0) {
    ss << size << " " << units[unit];
  } else {
    ss << std::fixed << std::setprecision(1) << formatted_size << " "
       << units[unit];
  }
  return ss.str();
}
// 核心函数：解析UTF-8字符并返回其【字节数】和【显示宽度】
// 针对常见控制台环境：ASCII=1宽度，中文等宽字符=2宽度
std::pair<int, int> FileSystemCore::parseUtf8Char(const unsigned char* str, size_t len, size_t pos) {
    if (pos >= len) return { 1, 2 }; // 防御性处理：默认按宽字符处理

    unsigned char lead = str[pos];
    int bytes = 0;
    int width = 2; // 默认非ASCII字符宽度为2

    // 1. ASCII (U+0000 ~ U+007F)
    if (lead < 0x80) {
        return { 1, 1 };
    }
    // 2. 2字节序列 (U+0080 ~ U+07FF)
    else if ((lead & 0xE0) == 0xC0) {
        bytes = 2;
    }
    // 3. 3字节序列 (U+0800 ~ U+FFFF) - 包含绝大部分常用汉字
    else if ((lead & 0xF0) == 0xE0) {
        bytes = 3;
    }
    // 4. 4字节序列 (U+10000 ~ U+10FFFF)
    else if ((lead & 0xF8) == 0xF0) {
        bytes = 4;
    }
    else {
        // 非法UTF-8起始字节，按单个宽字符处理
        return { 1, 2 };
    }

    // 关键：检查是否有足够的剩余字节，并验证每个后续字节的格式是否为10xxxxxx
    if (pos + bytes > len) {
        // 字节序列不完整，按残缺处理（这里保守地按首字节宽度处理）
        return { 1, 2 };
    }

    // 验证后续字节格式
    for (int j = 1; j < bytes; ++j) {
        if ((str[pos + j] & 0xC0) != 0x80) { // 检查是否以10开头
            // 后续字节格式非法，整个序列无效
            return { 1, 2 };
        }
    }
    // 对于中英文控制台，所有非ASCII字符通常按2宽度处理
    return { bytes, width };
}
// 计算字符串的显示宽度
int FileSystemCore::getDisplayWidth(const std::string& str) {
    int total_width = 0;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(str.c_str());
    size_t len = str.length();

    for (size_t i = 0; i < len;) {
        auto [bytes, width] = parseUtf8Char(p, len, i);
        total_width += width;
        i += bytes;
    }
    return total_width;
}

// 改进的格式化函数：可指定对齐方式
std::string FileSystemCore::padToDisplayWidth(const std::string& str, int targetWidth, bool leftAlign) {
    int currentWidth = getDisplayWidth(str);

    // 情况1：宽度不足
    if (currentWidth <= targetWidth) {
        int paddingSpaces = targetWidth - currentWidth;
        if (leftAlign) {
            // 左对齐：文本在左，空格在右
            return str + std::string(paddingSpaces, ' ');
        }
        else {
            // 右对齐：空格在左，文本在右
            return std::string(paddingSpaces, ' ') + str;
        }
    }

    // 情况2：宽度超过，截断并添加省略号
    std::string result;
    int accumulatedWidth = 0;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(str.c_str());
    size_t len = str.length();

    // 为省略号预留3个显示宽度
    int availableWidth = targetWidth - 3;
    if (availableWidth <= 0) {
        // 宽度太小，只显示省略号
        return std::string(targetWidth, '.');
    }

    for (size_t i = 0; i < len;) {
        auto [bytes, charWidth] = parseUtf8Char(p, len, i);

        if (accumulatedWidth + charWidth > availableWidth) {
            break;
        }

        result.append(reinterpret_cast<const char*>(p + i), bytes);
        accumulatedWidth += charWidth;
        i += bytes;
    }

    // 添加省略号并用空格填充剩余宽度
    result += "...";
    accumulatedWidth += 3;

    // 确保最终宽度精确等于targetWidth
    if (accumulatedWidth < targetWidth) {
        result += std::string(targetWidth - accumulatedWidth, ' ');
    }

    return result;
}

// 统一生成绝对路径（基于 current_path）
fs::path FileSystemCore::makeAbsolutePath(const std::string &relative_or_abs) const {
  fs::path p(relative_or_abs);
  // 如果已经是绝对路径，直接返回规范化后的结果
  if (p.is_absolute())
    return p.lexically_normal();
  // 相对路径则基于当前工作目录拼接后规范化
  return (current_path / p).lexically_normal();
}
// 辅助函数：如果你想提供一个“基于系统当前目录”的版本
fs::path FileSystemCore::makeAbsoluteFromCurrentDir(const std::string &relative_or_abs) {
  // 这个函数的行为才和之前有 fs::absolute 的版本类似（但也不完全一样）
  fs::path p(relative_or_abs);
  // 这里直接依赖 fs::current_path()
  return fs::absolute(p).lexically_normal();
}

// 基于指定 base 生成绝对路径（静态版本）
fs::path FileSystemCore::makeAbsolutePath(const std::string &path,const fs::path &base) {
  fs::path p(path);
  // 如果已经是绝对路径，直接返回规范化后的结果
  if (p.is_absolute())
    return p.lexically_normal();
  // 相对路径则基于指定的 base 目录拼接后规范化
  return (base / p).lexically_normal();
}

// 获取当前路径
fs::path FileSystemCore::getCurrentPath() const { return current_path; }

// 设置当前路径（跳转目录）
bool FileSystemCore::setCurrentPath(const std::string &new_path) {
  try {
    // 支持相对路径和绝对路径
    fs::path abs_path = makeAbsolutePath(new_path);

    if (!fs::exists(abs_path)) {
      setLastError("路径不存在: " + abs_path.string());
      return false;
    }

    if (!fs::is_directory(abs_path)) {
      setLastError("不是目录: " + abs_path.string());
      return false;
    }

    current_path = abs_path; // 更新当前目录
    last_error_.clear();
    return true;

  } catch (const fs::filesystem_error &e) {
    setLastError(e.what());
    return false;
  }
}

// 安全辅助函数：检查是否为系统关键路径（仅 Windows，防止误删系统目录）
bool FileSystemCore::isCriticalSystemPath(const fs::path& path) {
    const std::string path_str = path.lexically_normal().string();

    // 防止删除典型系统目录或磁盘根
    static const std::vector<std::string> critical_paths = {
        "C:\\Windows",
        "C:\\Program Files",
        "C:\\Program Files (x86)",
        "C:\\System32",
        "C:\\$",
    };

    for (const auto& critical : critical_paths) {
        if (path_str.rfind(critical, 0) == 0) {
            return true;
        }
    }

    /* 盘符根目录，如 C:\ 或 D:\*/
    if (path_str.size() == 3 && path_str[1] == ':' &&
        (path_str[2] == '\\' || path_str[2] == '/')) {
        return true;
    }

    return false;
}

// 权限检查：检查是否有删除权限（简化版本，检查写权限）
bool FileSystemCore::hasDeletePermission(const fs::path& path) {
    std::error_code ec;

    // 检查文件/目录权限
    auto status = fs::status(path, ec);
    if (ec) {
        return false; // 无法访问
    }

    // 简单检查：是否可写
    // 在实际应用中，可能需要更复杂的权限检查
    fs::perms p = status.permissions();

    // 检查是否有写权限
    bool is_writable = false;

    if (fs::is_directory(path)) {
        is_writable = (p & fs::perms::owner_write) != fs::perms::none &&
            (p & fs::perms::owner_exec) != fs::perms::none;
    }
    else {
        is_writable = (p & fs::perms::owner_write) != fs::perms::none;
    }

    return is_writable;
}
















// 创建目录
bool FileSystemCore::createDirectory(const std::string &dir_name,bool recursive) {
    try {
        //转换为绝对路径（统一路径处理，避免相对路径歧义）
        fs::path full_path = makeAbsolutePath(dir_name);

        // 1. 检查路径是否已存在
        if (fs::exists(full_path)) {
            setLastError(fs::is_directory(full_path) ?
                "目录已存在: " + full_path.string() :
                "路径已存在但不是目录: " + full_path.string());
            return false;
        }

        // 2. 非递归模式需要检查父目录
        if (!recursive && !fs::exists(full_path.parent_path())) {
            setLastError("父目录:"+ full_path.parent_path().string()+"不存在，请使用递归模式");
            return false;
        }

        // 3. 执行创建操作
        std::error_code ec;
        bool success = recursive ?
            fs::create_directories(full_path, ec) :
            fs::create_directory(full_path, ec);
        // 注：fs::create_directories会创建所有不存在的父目录；fs::create_directory仅创建最后一级

        // 4. 统一处理结果
        if (success) {
            last_error_.clear();
            return true;
        }
        else {
            setLastError(ec.message());
            return false;
        }

    }
    catch (const std::exception& e) {
        setLastError("创建目录异常: " + std::string(e.what()));
        return false;
    }
}

// 创建空文件
bool FileSystemCore::createFile(const std::string &file_name) {
  try {
    fs::path full_path = makeAbsolutePath(file_name);

    if (fs::exists(full_path)) {
      setLastError("文件已存在: " + full_path.string());
      return false;
    }
	//检测父目录是否存在
    if (!fs::exists(full_path.parent_path())) {
        setLastError("父目录不存在: " + full_path.parent_path().string());
    }
    // 创建空文件
    std::ofstream file(full_path);
    if (!file.is_open()) {
      setLastError("无法创建文件: " + full_path.string());
      return false;
    }

    last_error_.clear();
    return true;
  } catch (const fs::filesystem_error &e) {
    setLastError(e.what());
    return false;
  }
}

// 删除路径（对外统一接口）：包含安全检查（关键路径检查、权限检查）
bool FileSystemCore::deletePath(const std::string &path, bool recursive) {
  try {
    // 1. 转换为绝对路径
    fs::path abs_target = makeAbsolutePath(path);

    // 2. 检查路径是否存在
    if (!fs::exists(abs_target)) {
      setLastError("路径不存在: " + abs_target.string());
      return false;
    }

    // 3. 安全检查：确认不是系统关键路径
    if (isCriticalSystemPath(abs_target)) {
      setLastError("禁止删除系统关键路径: " + abs_target.string());
      return false;
    }

    // 4. 检查删除权限
    if (!hasDeletePermission(abs_target)) {
      setLastError("没有删除权限: " + abs_target.string());
      return false;
    }

    // 5. 根据 recursive 参数选择删除方式
    if (recursive) {
      return deleteRecursive(abs_target);
    } else {
      return deleteSingle(abs_target);
    }
  } catch (const fs::filesystem_error &e) {
    setLastError(std::string("文件系统错误: ") + e.what());
    return false;
  } catch (const std::exception &e) {
    setLastError(std::string("一般错误: ") + e.what());
    return false;
  }
}
// 递归删除：删除目录及其所有子文件和子目录
bool FileSystemCore::deleteRecursive(const fs::path &target) {
  try {
    std::error_code ec; // 使用 error_code 避免异常

    // 执行删除
    uintmax_t removed_count = fs::remove_all(target, ec);

    if (ec) {
      setLastError("递归删除失败: " + target.string() + " - " + ec.message());
      return false;
    }

    // removed_count == 0 也视为成功（可能是空目录或文件已不存在）
    return true;

  } catch (const std::exception &e) {
    setLastError(std::string("递归删除异常: ") + e.what());
    return false;
  }
}
// 非递归删除：只能删除文件或空目录
bool FileSystemCore::deleteSingle(const fs::path &target) {
  try {
    std::error_code ec;

    // 执行删除
    bool success = fs::remove(target, ec);

    if (ec) {
      setLastError("删除失败: " + target.string() + " - " + ec.message());
      return false;
    }

    if (!success) {
      setLastError("删除操作失败: " + target.string());
      return false;
    }

    return true;

  } catch (const std::exception &e) {
    setLastError(std::string("删除异常: ") + e.what());
    return false;
  }
}

// 移动/复制文件或目录
bool FileSystemCore::movePath(const std::string &source, const std::string &destination) {
  try {
    // 构建源路径和目标路径（支持相对与绝对）
	fs::path abs_src = makeAbsolutePath(source);//获得源文件的绝对路径
	fs::path abs_dst = makeAbsolutePath(destination);//获得目标文件的绝对路径

    // 检查源路径是否存在
    if (!fs::exists(abs_src)) {
      setLastError("源路径不存在: " + abs_src.string());
      return false;
    }

    // 如果目标是已存在的目录，则移动文件到此目录内
    if (fs::exists(abs_dst) && fs::is_directory(abs_dst)) {
		abs_dst = abs_dst / abs_src.filename();//拼接目标路径
    }

    // 执行移动/重命名
    fs::rename(abs_src, abs_dst);//fs::rename(abs_src, abs_dst) 就是 “把abs_src这个文件 / 文件夹，挪到abs_dst这个位置（或改名为abs_dst）”
	last_error_.clear();//清除错误信息
    return true;

  } catch (const fs::filesystem_error &e) {
    setLastError(e.what());//记录错误信息
    return false;
  }
}

// 重命名
bool FileSystemCore::renamePath(const std::string &old_name,
                                const std::string &new_name) {
  return movePath(old_name, new_name); // 重命名本质是原地移动
}

// 对外列表接口：支持详细/递归
std::string FileSystemCore::listDirectory(bool detailed, bool recursive) const {
  std::ostringstream output;
  listDirectoryImpl(current_path, detailed, recursive, output);
  return output.str();
}

// 目录列表实现：对指定目录进行列表显示，支持详细模式和递归
void FileSystemCore::listDirectoryImpl(const fs::path &dir, bool detailed,bool recursive,std::ostringstream &output) const {
  try {
    output << "目录: " << dir << "\n\n";

    if (detailed) {
        // 收集条目并排序
        std::vector<fs::directory_entry> entries;
        for (const auto& entry : fs::directory_iterator(dir)) {
            entries.push_back(entry);
        }

        std::sort(entries.begin(), entries.end(),
            [](const fs::directory_entry& a, const fs::directory_entry& b) {
                bool a_is_dir = a.is_directory();
                bool b_is_dir = b.is_directory();
                if (a_is_dir != b_is_dir)
                    return a_is_dir > b_is_dir;
                return a.path().filename().string() <
                    b.path().filename().string();
            });
        const int NAME_WIDTH = 30;    // 文件名列宽度
        const int TYPE_WIDTH = 28;    // 类型列宽度
        const int SIZE_WIDTH = 12;    // 大小列宽度
        const int COL_SPACING = 2;    // 列间间距（显示宽度）
        const int TIME_WIDTH = 19;    // 时间列宽度（固定格式，纯ASCII）
       std::string header_name = padToDisplayWidth("Name", NAME_WIDTH);
       std::string header_type = padToDisplayWidth("类型", TYPE_WIDTH);
        std::string header_time = padToDisplayWidth("修改时间", TIME_WIDTH);
        std::string header_size = padToDisplayWidth("大小", SIZE_WIDTH, false); // 右对齐
        output << header_name << std::string(COL_SPACING, ' ') << header_type<<std::string(COL_SPACING,' ') << header_time << std::string(COL_SPACING, ' ') << header_size << "\n";

        // 2. 输出表头分隔线（可选，视觉辅助）
        int total_width = NAME_WIDTH + TIME_WIDTH + TYPE_WIDTH + SIZE_WIDTH + (3 * COL_SPACING);
        output << std::string(total_width, '-') << "\n";
        // 格式化输出
        for (const auto& entry : entries) {
            try {
                auto status = entry.status();
                bool is_dir = fs::is_directory(status);
                bool is_file = fs::is_regular_file(status);
				//获取文件名
                const std::string name = LocalToUTF8(entry.path().filename().string());
                // 计算类型名称
                std::string type_name;
                if (is_dir) {
                    type_name = "文件夹";
                }
                else {
                    std::string ext = entry.path().extension().string();
                    if (!ext.empty() && ext.front() == '.') {
                        ext.erase(ext.begin());
                    }
                    for (char& ch : ext) {
                        ch = static_cast<char>(::tolower(static_cast<unsigned char>(ch)));
                    }
                    if (!ext.empty()) {
                        auto it = EXT_TYPE_MAP.find(ext);
                        type_name =
                            (it != EXT_TYPE_MAP.end()) ? it->second : (ext + " 文件");
                    }
                    else {
                        type_name = "文件";
                    }
                }
				// 获取时间
				auto ftime = fs::last_write_time(entry);
				std::time_t tt = fileTimeToTimeT(ftime);
				std::tm tm;
				localtime_s(&tm, &tt);
				char time_buf[20];
				std::strftime(time_buf, sizeof(time_buf), "%Y/%m/%d %H:%M", &tm);

				// 获取大小
				std::string size_str;
				if (is_file) {
					size_str = formatFileSize(fs::file_size(entry));
				}
				else {
					size_str = "";
				}

				

				// ===== 关键修改：使用统一的宽度格式化 =====
				// 文件名列：左对齐
				std::string display_name = padToDisplayWidth(name, NAME_WIDTH, true);
				// 时间列：左对齐（纯ASCII，但为了统一也格式化）
				std::string display_time = padToDisplayWidth(time_buf, TIME_WIDTH, true);
				// 类型列：左对齐
				std::string display_type = padToDisplayWidth(type_name, TYPE_WIDTH, true);
				// 大小列：右对齐（数字通常右对齐）
				std::string display_size = padToDisplayWidth(size_str, SIZE_WIDTH, false);

				// 输出格式化后的行，手动控制列间距
				output << display_name << std::string(COL_SPACING, ' ')<< display_type << std::string(COL_SPACING, ' ')<< display_time << std::string(COL_SPACING, ' ')<< display_size << "\n";
               
            }
            catch (const fs::filesystem_error&) {
                output << " [无法访问] " << LocalToUTF8(entry.path().filename().string()) << "\n";
            }
        }
		int file_count = std::count_if(
			entries.begin(), entries.end(),
			[](const fs::directory_entry& e) { return e.is_regular_file(); });
		int dir_count = static_cast<int>(entries.size()) - file_count;
		output << "\n          " << file_count << " 个文件, " << dir_count
			<< " 个目录\n\n";
    }
    else if(recursive){
        try {
            // 遍历递归目录迭代器
            for (fs::recursive_directory_iterator it(dir), end; it != end; ++it) {
                try {
                    // 获取相对于起始目录 dir 的递归深度
                    int depth = it.depth();

                    // 计算缩进：每级深度缩进2个空格
                    std::string indent(depth * 2, '-');

                    // 获取文件名
                    std::string name = LocalToUTF8(it->path().filename().string());

                    // 如果是目录，添加标记
                    if (it->is_directory()) {
                        output << indent << "[+] " << name << "\n";
                    }
                    else {
                        output << indent << "[-] " << name << "\n";
                    }
                }
                catch (const fs::filesystem_error&) {
                    int depth = 0;
                    try {
                        depth = it.depth();
                    }
                    catch (...) {
                        depth = 0;
                    }
                    std::string indent(depth * 2, ' ');
                    output << indent << "[无法访问条目]\n";
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            output << "无法开始递归遍历: " << e.what() << "\n";
            return;
        }

    }
   

  } catch (const fs::filesystem_error &e) {
    output << "无法访问目录: " << e.what() << "\n";
  }
}

// 检查路径是否存在
bool FileSystemCore::pathExists(const std::string &path) const {
  try {
    fs::path abs_path = makeAbsolutePath(path);
    return fs::exists(abs_path);
  } catch (const fs::filesystem_error &e) {
    return false;
  }
}

// 清屏函数（Windows）
void FileSystemCore::clearScreen() { system("cls"); }

// 获取父目录路径
std::string FileSystemCore::getParentPath() const {
  return current_path.parent_path().string();
}
//转换成utf-8
std::string FileSystemCore::LocalToUTF8(const std::string& localStr) {
#ifdef _WIN32
    // Windows 专用：将本地代码页字符串转换为 UTF-8
    int wideLen = MultiByteToWideChar(CP_ACP, 0, localStr.c_str(), -1, nullptr, 0);
    if (wideLen == 0) return localStr; // 转换失败，返回原字符串

    std::wstring wideStr(wideLen, 0);
    MultiByteToWideChar(CP_ACP, 0, localStr.c_str(), -1, &wideStr[0], wideLen);

    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Len == 0) return localStr;

    std::string utf8Str(utf8Len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Len, nullptr, nullptr);

    // 去除末尾的 null 终止符
    if (!utf8Str.empty() && utf8Str.back() == '\0') {
        utf8Str.pop_back();
    }
    return utf8Str;
#else
    // Linux/macOS 通常原生使用 UTF-8，直接返回
    return localStr;
#endif
}