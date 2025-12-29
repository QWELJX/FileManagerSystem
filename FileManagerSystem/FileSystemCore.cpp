// 标准库头文件
#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

// 系统头文件
#include <windows.h>

// 自定义头文件
#include "FileSystemCore.h"

// 编码转换工具命名空间
#pragma region 编码工具
namespace EncodingUtils {
    // UTF-8 字符串转宽字符串 (UTF-16)
    std::wstring UTF8ToWide(const std::string& utf8Str) {
        if (utf8Str.empty()) {
            return L"";
        }

        int wideLen =
            MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
        if (wideLen == 0) {
            return L"";
        }

        std::wstring wideStr(wideLen, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &wideStr[0], wideLen);

        // 移除末尾的 null 终止符
        if (!wideStr.empty() && wideStr.back() == L'\0') {
            wideStr.pop_back();
        }

        return wideStr;
    }

    // 宽字符串 (UTF-16) 转 UTF-8 字符串
    std::string WideToUTF8(const std::wstring& wideStr) {
        if (wideStr.empty()) {
            return "";
        }

        int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0,
            nullptr, nullptr);
        if (utf8Len == 0) {
            return "";
        }

        std::string utf8Str(utf8Len, 0);
        WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Len,
            nullptr, nullptr);

        // 移除末尾的 null 终止符
        if (!utf8Str.empty() && utf8Str.back() == '\0') {
            utf8Str.pop_back();
        }

        return utf8Str;
    }

    // 公共的WideToUTF8函数

} // namespace EncodingUtils
std::string FileSystemUtils::WideToUTF8(const std::wstring& wideStr) {
    return EncodingUtils::WideToUTF8(wideStr);
}
std::wstring FileSystemUtils::UTF8ToWide(const std::string& utf8Str) {
    return EncodingUtils::UTF8ToWide(utf8Str);
}

#pragma endregion

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
#pragma region 文件管理器静态工具函数实现
// 时间转换工具函数：将 filesystem 时间转换为 time_t
std::time_t FileSystemUtils::fileTimeToTimeT(const fs::file_time_type& ftime) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

// 格式化文件大小
std::string FileSystemUtils::formatFileSize(uintmax_t size) {
    const char* units[] = { " B", "KB", "MB", "GB" };
    int unit = 0;
    double formatted_size = static_cast<double>(size);

    while (formatted_size >= 1024.0 && unit < 3) {
        formatted_size /= 1024.0;
        unit++;
    }

    std::ostringstream ss;
    if (unit == 0) {
        ss << size << " " << units[unit];
    }
    else {
        ss << std::fixed << std::setprecision(1) << formatted_size << " "
            << units[unit];
    }
    return ss.str();
}
// 核心函数：解析UTF-8字符并返回其【字节数】和【显示宽度】
// 针对常见控制台环境：ASCII=1宽度，中文等宽字符=2宽度
std::pair<int, int> FileSystemUtils::parseUtf8Char(const unsigned char* str,
    size_t len, size_t pos) {
    if (pos >= len) {
        return { 1, 2 }; // 防御性处理：默认按宽字符处理
    }

    unsigned char lead_char = str[pos];
    int byte_count = 0;
    int display_width = 2; // 默认非ASCII字符宽度为2

    // 1. ASCII (U+0000 ~ U+007F)
    if (lead_char < 0x80) {
        return { 1, 1 };
    }
    // 2. 2字节序列 (U+0080 ~ U+07FF)
    else if ((lead_char & 0xE0) == 0xC0) {
        byte_count = 2;
    }
    // 3. 3字节序列 (U+0800 ~ U+FFFF) - 包含绝大部分常用汉字
    else if ((lead_char & 0xF0) == 0xE0) {
        byte_count = 3;
    }
    // 4. 4字节序列 (U+10000 ~ U+10FFFF)
    else if ((lead_char & 0xF8) == 0xF0) {
        byte_count = 4;
    }
    else {
        // 非法UTF-8起始字节，按单个宽字符处理
        return { 1, 2 };
    }

    // 关键：检查是否有足够的剩余字节，并验证每个后续字节的格式是否为10xxxxxx
    if (pos + byte_count > len) {
        // 字节序列不完整，按残缺处理（这里保守地按首字节宽度处理）
        return { 1, 2 };
    }

    // 验证后续字节格式
    for (int j = 1; j < byte_count; ++j) {
        if ((str[pos + j] & 0xC0) != 0x80) { // 检查是否以10开头
            // 后续字节格式非法，整个序列无效
            return { 1, 2 };
        }
    }
    // 对于中英文控制台，所有非ASCII字符通常按2宽度处理
    return { byte_count, display_width };
}
// 计算字符串的显示宽度
int FileSystemUtils::getDisplayWidth(const std::string& str) {
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
std::string FileSystemUtils::padToDisplayWidth(const std::string& str, int targetWidth, bool leftAlign = true) {
    int currentWidth = FileSystemUtils::getDisplayWidth(str);

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
        auto [bytes, charWidth] = FileSystemUtils::parseUtf8Char(p, len, i);

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

// 辅助函数：基于系统当前目录生成绝对路径
fs::path FileSystemUtils::makeAbsoluteFromCurrentDir(const std::string& relative_or_abs) {
    // 将UTF-8字符串转换为宽字符串，确保中文等非ASCII字符正确处理
    std::wstring wide_path = EncodingUtils::UTF8ToWide(relative_or_abs);
    fs::path p(wide_path);
    // 这里直接依赖 fs::current_path()
    return fs::absolute(p).lexically_normal();
}

// 基于指定 base 生成绝对路径（静态版本）
fs::path FileSystemUtils::makeAbsolutePath(const std::string& path, const fs::path& base) {
    // 将UTF-8字符串转换为宽字符串，确保中文等非ASCII字符正确处理
    std::wstring wide_path = EncodingUtils::UTF8ToWide(path);
    fs::path p(wide_path);
    // 如果已经是绝对路径，直接返回规范化后的结果
    if (p.is_absolute()) {
        return p.lexically_normal();
    }
    // 相对路径则基于指定的 base 目录拼接后规范化
    return (base / p).lexically_normal();
}

// 安全辅助函数：检查是否为系统关键路径（仅 Windows，防止误删系统目录）
bool FileSystemUtils::isCriticalSystemPath(const fs::path& path) {
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
bool FileSystemUtils::hasDeletePermission(const fs::path& path) {
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
#pragma endregion
#pragma region FileManager内部函数实现
// 构造函数：初始化为当前目录
FileSystemCore::FileSystemCore() { current_path = fs::current_path(); }


// 统一生成绝对路径（基于 current_path）
fs::path FileSystemCore::makeAbsolutePath(const std::string& relative_or_abs) const {
    // 将UTF-8字符串转换为宽字符串，确保中文等非ASCII字符正确处理
    std::wstring wide_path = EncodingUtils::UTF8ToWide(relative_or_abs);
    fs::path p(wide_path);
    // 如果已经是绝对路径，直接返回规范化后的结果
    if (p.is_absolute()) {
        return p.lexically_normal();
    }
    // 相对路径则基于当前工作目录拼接后规范化
    return (current_path / p).lexically_normal();
}



// 获取当前路径
fs::path FileSystemCore::getCurrentPath() const { return current_path; }

// 设置当前路径（跳转目录）
bool FileSystemCore::ChangePath(const fs::path& new_path) {
    try {
        // 支持相对路径和绝对路径
        fs::path abs_path =new_path;

        if (!fs::exists(abs_path)) {
            setLastError("路径不存在: " +
                EncodingUtils::WideToUTF8(abs_path.wstring()));
            return false;
        }

        if (!fs::is_directory(abs_path)) {
            setLastError("不是目录: " +
                EncodingUtils::WideToUTF8(abs_path.wstring()));
            return false;
        }

        current_path = abs_path; // 更新当前目录
        last_error_.clear();
        return true;

    }
    catch (const fs::filesystem_error& e) {
        setLastError(e.what());
        return false;
    }
}
bool FileSystemCore::setCurrentPath(const fs::path& new_path) {
    try
    {
        if (!fs::exists(new_path)) {
            setLastError("路径不存在: " +
                EncodingUtils::WideToUTF8(new_path.wstring()));
            return false;
        }

        if (!fs::is_directory(new_path)) {
            setLastError("不是目录: " +
                EncodingUtils::WideToUTF8(new_path.wstring()));
            return false;
        }

        current_path = new_path; // 更新当前目录
        last_error_.clear();
        return true;

    }
    catch (const fs::filesystem_error& e) {
        setLastError(e.what());
        return false;
    }
}

// 创建目录
bool FileSystemCore::createDirectory(const fs::path& dir_name,
    bool recursive) {
    try {
        fs::path full_path = dir_name;

        // 1. 检查路径是否已存在
        if (fs::exists(full_path)) {
            setLastError(fs::is_directory(full_path)
                ? "目录已存在: " +
                EncodingUtils::WideToUTF8(full_path.wstring())
                : "路径已存在但不是目录: " +
                EncodingUtils::WideToUTF8(full_path.wstring()));
            return false;
        }

        // 2. 非递归模式需要检查父目录
        if (!recursive && !fs::exists(full_path.parent_path())) {
            setLastError(
                "父目录不存在，请使用递归模式: " +
                EncodingUtils::WideToUTF8(full_path.parent_path().wstring()));
            return false;
        }

        // 3. 执行创建操作
        std::error_code ec;
        bool success = recursive ? fs::create_directories(full_path, ec)
            : fs::create_directory(full_path, ec);

        // 4. 统一处理结果
        if (success) {
            last_error_.clear();
            return true;
        }
        else {
            setLastError(
                "创建目录失败: " + EncodingUtils::WideToUTF8(full_path.wstring()) +
                " - " + ec.message());
            return false;
        }

    }
    catch (const std::exception& e) {
        setLastError("创建目录异常: " + std::string(e.what()));
        return false;
    }
}

// 创建空文件
bool FileSystemCore::createFile(const fs::path& file_name) {
    try {
        fs::path full_path = file_name;

        if (fs::exists(full_path)) {
            setLastError("文件已存在: " +
                EncodingUtils::WideToUTF8(full_path.wstring()));
            return false;
        }

        // 检测父目录是否存在
        if (!fs::exists(full_path.parent_path())) {
            setLastError("父目录不存在: " + EncodingUtils::WideToUTF8(
                full_path.parent_path().wstring()));
            return false; // 添加return语句，防止父目录不存在时继续执行
        }

        // 创建空文件 - 使用宽字符API确保正确处理非ASCII文件名
        std::wstring widePath = full_path.wstring();
        FILE* file = nullptr;

        // 使用_wfopen_s打开文件，确保支持UTF-16路径
        errno_t err = _wfopen_s(&file, widePath.c_str(), L"w, ccs=UTF-8");
        if (err != 0 || file == nullptr) {
            setLastError("无法创建文件: " + EncodingUtils::WideToUTF8(widePath));
            return false;
        }

        // 关闭文件
        fclose(file);

        last_error_.clear();
        return true;
    }
    catch (const fs::filesystem_error& e) {
        setLastError("文件系统错误: " + std::string(e.what()));
        return false;
    }
    catch (const std::exception& e) {
        setLastError("一般错误: " + std::string(e.what()));
        return false;
    }
}

// 删除路径（对外统一接口）：包含安全检查（关键路径检查、权限检查）
bool FileSystemCore::deletePath(const fs::path& path, bool recursive) {
    try {
        // 1. 转换为绝对路径
        fs::path abs_target =path;

        // 2. 检查路径是否存在
        if (!fs::exists(abs_target)) {
            setLastError("路径不存在: " +
                EncodingUtils::WideToUTF8(abs_target.wstring()));
            return false;
        }

        // 3. 安全检查：确认不是系统关键路径
        if (FileSystemUtils::isCriticalSystemPath(abs_target)) {
            setLastError("禁止删除系统关键路径: " +
                EncodingUtils::WideToUTF8(abs_target.wstring()));
            return false;
        }

        // 4. 检查删除权限
        if (!FileSystemUtils::hasDeletePermission(abs_target)) {
            setLastError("没有删除权限: " +
                EncodingUtils::WideToUTF8(abs_target.wstring()));
            return false;
        }

        // 5. 根据 recursive 参数选择删除方式
        if (recursive) {
            return deleteRecursive(abs_target);
        }
        else {
            return deleteSingle(abs_target);
        }
    }
    catch (const fs::filesystem_error& e) {
        setLastError(std::string("文件系统错误: ") + e.what());
        return false;
    }
    catch (const std::exception& e) {
        setLastError(std::string("一般错误: ") + e.what());
        return false;
    }
}


// 递归删除：删除目录及其所有子文件和子目录
bool FileSystemCore::deleteRecursive(const fs::path& target) {
    try {
        std::error_code ec; // 使用 error_code 避免异常

        // 执行删除
        uintmax_t removed_count = fs::remove_all(target, ec);

        if (ec) {
            setLastError(
                "递归删除失败: " + EncodingUtils::WideToUTF8(target.wstring()) +
                " - " + ec.message());
            return false;
        }

        // removed_count == 0 也视为成功（可能是空目录或文件已不存在）
        return true;

    }
    catch (const std::exception& e) {
        setLastError(std::string("递归删除异常: ") + e.what());
        return false;
    }
}
// 非递归删除：只能删除文件或空目录
bool FileSystemCore::deleteSingle(const fs::path& target) {
    try {
        std::error_code ec;

        // 执行删除
        bool success = fs::remove(target, ec);

        if (ec) {
            setLastError("删除失败: " + EncodingUtils::WideToUTF8(target.wstring()) +
                " - " + ec.message());
            return false;
        }

        if (!success) {
            setLastError("删除操作失败: " +
                EncodingUtils::WideToUTF8(target.wstring()));
            return false;
        }

        return true;

    }
    catch (const std::exception& e) {
        setLastError(std::string("删除异常: ") + e.what());
        return false;
    }
}

// 移动/复制文件或目录
bool FileSystemCore::movePath(const fs::path& source, const fs::path& destination) {
    try {
        // 构建源路径和目标路径（支持相对与绝对）
        fs::path abs_src = source;
        fs::path abs_dst =destination;

        // 检查源路径是否存在
        if (!fs::exists(abs_src)) {
            setLastError("源路径不存在: " +
                EncodingUtils::WideToUTF8(abs_src.wstring()));
            return false;
        }

        // 如果目标是已存在的目录，则移动文件到此目录内
        if (fs::exists(abs_dst) && fs::is_directory(abs_dst)) {
            abs_dst = abs_dst / abs_src.filename();
        }

        // 执行移动/重命名
        fs::rename(abs_src, abs_dst);
        last_error_.clear();
        return true;

    }
    catch (const fs::filesystem_error& e) {
        setLastError(e.what());
        return false;
    }
}


// 重命名
bool FileSystemCore::renamePath(const fs::path& old_name, const fs::path& new_name) {
    return movePath(old_name, new_name); // 重命名本质是原地移动
}

// 对外列表接口：支持详细/递归
std::string FileSystemCore::listDirectory(bool detailed, bool recursive) const {
    std::ostringstream output;
    listDirectoryImpl(current_path, detailed, recursive, output);
    return output.str();
}

// 目录列表实现：对指定目录进行列表显示，支持详细模式和递归
void FileSystemCore::listDirectoryImpl(const fs::path& dir, bool detailed,
    bool recursive,
    std::ostringstream& output) const {
    try {
        output << "目录: " << EncodingUtils::WideToUTF8(dir.wstring()) << "\n\n";

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
            const int NAME_WIDTH = 40; // 文件名列宽度
            const int TYPE_WIDTH = 28; // 类型列宽度
            const int SIZE_WIDTH = 12; // 大小列宽度
            const int COL_SPACING = 2; // 列间间距（显示宽度）
            const int TIME_WIDTH = 19; // 时间列宽度（固定格式，纯ASCII）
            std::string header_name = FileSystemUtils::padToDisplayWidth("Name", NAME_WIDTH);
            std::string header_type = FileSystemUtils::padToDisplayWidth("类型", TYPE_WIDTH);
            std::string header_time = FileSystemUtils::padToDisplayWidth("修改时间", TIME_WIDTH);
            std::string header_size = FileSystemUtils::padToDisplayWidth("大小", SIZE_WIDTH, false); // 右对齐
            output << header_name << std::string(COL_SPACING, ' ') << header_type
                << std::string(COL_SPACING, ' ') << header_time
                << std::string(COL_SPACING, ' ') << header_size << "\n";

            // 2. 输出表头分隔线（可选，视觉辅助）
            int total_width =
                NAME_WIDTH + TIME_WIDTH + TYPE_WIDTH + SIZE_WIDTH + (3 * COL_SPACING);
            output << std::string(total_width, '-') << "\n";
            // 格式化输出
            for (const auto& entry : entries) {
                try {
                    auto status = entry.status();
                    bool is_dir = fs::is_directory(status);
                    bool is_file = fs::is_regular_file(status);
                    // 获取文件名
                    const std::string name =
                        EncodingUtils::WideToUTF8(entry.path().filename().wstring());
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
                    std::time_t tt = FileSystemUtils::fileTimeToTimeT(ftime);
                    std::tm tm;
                    localtime_s(&tm, &tt);
                    char time_buf[20];
                    std::strftime(time_buf, sizeof(time_buf), "%Y/%m/%d %H:%M", &tm);

                    // 获取大小
                    std::string size_str;
                    if (is_file) {
                        size_str = FileSystemUtils::formatFileSize(fs::file_size(entry));
                    }
                    else {
                        size_str = "";
                    }

                    // ===== 关键修改：使用统一的宽度格式化 =====
                    // 文件名列：左对齐
                    std::string display_name = FileSystemUtils::padToDisplayWidth(name, NAME_WIDTH, true);
                    // 时间列：左对齐（纯ASCII，但为了统一也格式化）
                    std::string display_time = FileSystemUtils::padToDisplayWidth(time_buf, TIME_WIDTH, true);
                    // 类型列：左对齐
                    std::string display_type = FileSystemUtils::padToDisplayWidth(type_name, TYPE_WIDTH, true);
                    // 大小列：右对齐（数字通常右对齐）
                    std::string display_size = FileSystemUtils::padToDisplayWidth(size_str, SIZE_WIDTH, false);

                    // 输出格式化后的行，手动控制列间距
                    output << display_name << std::string(COL_SPACING, ' ')
                        << display_type << std::string(COL_SPACING, ' ')
                        << display_time << std::string(COL_SPACING, ' ')
                        << display_size << "\n";

                }
                catch (const fs::filesystem_error&) {
                    output << " [无法访问] "
                        << EncodingUtils::WideToUTF8(entry.path().filename().wstring()) << "\n";
                }
            }
            int file_count = std::count_if(
                entries.begin(), entries.end(),
                [](const fs::directory_entry& e) { return e.is_regular_file(); });
            int dir_count = static_cast<int>(entries.size()) - file_count;
            output << "\n          " << file_count << " 个文件, " << dir_count
                << " 个目录\n\n";
        }
        else if (recursive) {
            try {
                // 递归显示，使用层级缩进
                for (fs::recursive_directory_iterator it(dir), end; it != end; ++it) {
                    try {
                        // 获取深度
                        int depth = it.depth();

                        // 根据深度生成前缀，每级增加4个字符的缩进
                        std::string prefix;
                        if (depth == 0) {
                            // 根目录：----
                            prefix = "----";
                        }
                        else {
                            // 子项：depth*4个空格 + |---
                            prefix = std::string(depth * 3, ' ') + "|---";
                        }

                        // 获取文件名
                        std::string name = EncodingUtils::WideToUTF8(it->path().filename().wstring());

                        // 如果是目录，添加/
                        if (it->is_directory()) {
                            output << prefix << "[+]" << name << "\n";
                        }
                        else {
                            output << prefix << "[-]" << name << "\n";
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
                        std::string prefix = (depth == 0) ? "----" : std::string(depth * 4, ' ') + "|---";
                        output << prefix << "[无法访问条目]\n";
                    }
                }
            }
            catch (const fs::filesystem_error& e) {
                output << "无法开始递归遍历: " << e.what() << "\n";
                return;
            }
        }

    }
    catch (const fs::filesystem_error& e) {
        output << "无法访问目录: " << e.what() << "\n";
    }
}

// 检查路径是否存在
bool FileSystemCore::pathExists(const fs::path& path) const {
    try {
       
        return fs::exists(path);
    }
    catch (const fs::filesystem_error& e) {
        return false;
    }
}

// 获取父目录路径
std::string FileSystemCore::getParentPath() const {
    return current_path.parent_path().string();
}
#pragma endregion







