#include "FileSystemCore.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>  
#include <chrono>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

// 构造函数：初始化为当前目录
FileSystemCore::FileSystemCore() {
    current_path = fs::current_path();
}

// 时间转换工具函数（你之前困惑的部分）
std::time_t FileSystemCore::fileTimeToTimeT(const fs::file_time_type& ftime) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + system_clock::now()
    );
    return system_clock::to_time_t(sctp);
}

// 格式化文件大小
std::string FileSystemCore::formatFileSize(uintmax_t size) {
    const char* units[] = { "B", "KB", "MB", "GB" };
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
        ss << std::fixed << std::setprecision(1) << formatted_size << " " << units[unit];
    }
    return ss.str();
}

// 获取当前路径
fs::path FileSystemCore::getCurrentPath() const {
    return current_path;
}

// 设置当前路径（跳转目录）
bool FileSystemCore::setCurrentPath(const std::string& new_path) {
    try {
        // 构建新路径（基于当前目录）
        fs::path new_dir = current_path / new_path;
        new_dir = new_dir.lexically_normal();

        // 获取绝对路径并检查
        fs::path abs_path = fs::absolute(new_dir);

        if (!fs::exists(abs_path)) {
            std::cerr << "错误: 路径不存在 - " << new_path << std::endl;
            return false;
        }

        if (!fs::is_directory(abs_path)) {
            std::cerr << "错误: 不是目录 - " << new_path << std::endl;
            return false;
        }

        current_path = abs_path;  // 更新当前目录
        return true;

    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "系统错误: " << e.what() << std::endl;
        return false;
    }
}

// 创建目录
bool FileSystemCore::createDirectory(const std::string& dir_name) {
    try {
        fs::path full_path = current_path / dir_name;

        if (fs::exists(full_path)) {
            std::cerr << "错误: 目录已存在 - " << dir_name << std::endl;
            return false;
        }

        return fs::create_directory(full_path);
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "创建失败: " << e.what() << std::endl;
        return false;
    }
}

// 创建空文件
bool FileSystemCore::createFile(const std::string& file_name) {
    try {
        fs::path full_path = current_path / file_name;

        if (fs::exists(full_path)) {
            std::cerr << "错误: 文件已存在 - " << file_name << std::endl;
            return false;
        }

        // 创建空文件
        std::ofstream file(full_path);
        return file.is_open();
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "创建文件失败" << std::endl;
        return false;
    }
}

// 删除文件或目录
bool FileSystemCore::deletePath(const std::string& path, bool recursive) {
    try {
        // 构建目标路径
        fs::path target = current_path / path;
        target = target.lexically_normal();
        fs::path abs_target = fs::absolute(target);

        if (!fs::exists(abs_target)) {
            std::cerr << "错误: 路径不存在 - " << path << std::endl;
            return false;
        }

        if (recursive) {
            uintmax_t count = fs::remove_all(abs_target);
            std::cout << "删除成功: " << abs_target << " (" << count << " 个项)" << std::endl;
            return count > 0;
        }
        else {
            bool success = fs::remove(abs_target);
            if (success) {
                std::cout << "删除成功: " << abs_target << std::endl;
            }
            return success;
        }

    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "删除失败: " << e.what() << std::endl;
        return false;
    }
}

// 移动/复制文件或目录
bool FileSystemCore::movePath(const std::string& source, const std::string& destination) {
    try {
        // 构建源路径和目标路径（基于当前目录）
        fs::path src_path = current_path / source;
        fs::path dst_path = current_path / destination;

        // 规范化路径
        src_path = src_path.lexically_normal();
        dst_path = dst_path.lexically_normal();

        // 获取绝对路径（如果需要）
        fs::path abs_src = fs::absolute(src_path);
        fs::path abs_dst = fs::absolute(dst_path);

        // 检查源路径是否存在
        if (!fs::exists(abs_src)) {
            std::cerr << "错误: 源路径不存在 - " << source << std::endl;
            return false;
        }

        // 如果目标是已存在的目录，则移动文件到此目录内
        if (fs::exists(abs_dst) && fs::is_directory(abs_dst)) {
            abs_dst = abs_dst / abs_src.filename();
        }

        // 执行移动/重命名
        fs::rename(abs_src, abs_dst);
        std::cout << "移动成功: " << abs_src << " -> " << abs_dst << std::endl;
        return true;

    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "移动失败: " << e.what() << std::endl;
        return false;
    }
}

// 重命名
bool FileSystemCore::renamePath(const std::string& old_name, const std::string& new_name) {
    return movePath(old_name, new_name);  // 重命名本质是原地移动
}

// 列出目录内容（类似dir命令）
std::string FileSystemCore::listDirectory(bool detailed) const {
    std::ostringstream output;

    try {
        output << "  目录: " << current_path << "\n\n";

        // 收集条目并排序
        std::vector<fs::directory_entry> entries;
        for (const auto& entry : fs::directory_iterator(current_path)) {
            entries.push_back(entry);
        }

        std::sort(entries.begin(), entries.end(),
            [](const fs::directory_entry& a, const fs::directory_entry& b) {
                // 目录优先，然后按名称排序
                bool a_is_dir = fs::is_directory(a.status());
                bool b_is_dir = fs::is_directory(b.status());
                if (a_is_dir != b_is_dir) return a_is_dir > b_is_dir;
                return a.path().filename().string() < b.path().filename().string();
            });

        // 格式化输出
        for (const auto& entry : entries) {
            try {
                auto status = entry.status();

                // 类型指示符
                std::string type_marker = fs::is_directory(status) ? "[DIR] " : "      ";

                if (detailed) {
                    // 详细模式：显示时间、大小
                    auto ftime = fs::last_write_time(entry);
                    std::time_t tt = fileTimeToTimeT(ftime);

                    std::tm tm;
#ifdef _WIN32
                    localtime_s(&tm, &tt);
#else
                    localtime_r(&tt, &tm);
#endif

                    char time_buf[20];
                    std::strftime(time_buf, sizeof(time_buf), "%Y/%m/%d %H:%M", &tm);

                    output << time_buf << "  ";

                    // 文件大小
                    if (fs::is_regular_file(status)) {
                        output << std::setw(10) << std::right
                            << formatFileSize(fs::file_size(entry)) << "  ";
                    }
                    else {
                        output << std::setw(10) << std::right << "<DIR>" << "  ";
                    }
                }

                output << type_marker << entry.path().filename().string() << "\n";

            }
            catch (const fs::filesystem_error& e) {
                output << " [无法访问] " << entry.path().filename().string() << "\n";
            }
        }

        // 统计信息
        int file_count = std::count_if(entries.begin(), entries.end(),
            [](const fs::directory_entry& e) { return fs::is_regular_file(e.status()); });

        int dir_count = entries.size() - file_count;
        output << "\n          " << file_count << " 个文件, " << dir_count << " 个目录\n";

    }
    catch (const fs::filesystem_error& e) {
        output << "无法访问目录: " << e.what();
    }

    return output.str();
}

// 检查路径是否存在
bool FileSystemCore::pathExists(const std::string& path) const {
    try {
        fs::path dst_path = current_path / path;
		dst_path = dst_path.lexically_normal();
        return fs::exists(fs::absolute(dst_path));
    }
    catch (const fs::filesystem_error& e) {
        return false;
    }
}

// 清屏函数（Windows优化版）
void FileSystemCore::clearScreen() {
#ifdef _WIN32
    // Windows系统调用，比system("cls")快得多
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hStdOut, ' ', cellCount, coord, &count);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
#else
    // Linux/macOS备用方案
    std::cout << "\033[2J\033[1;1H";
#endif
}

// 获取父目录路径
std::string FileSystemCore::getParentPath() const {
    return current_path.parent_path().string();
}