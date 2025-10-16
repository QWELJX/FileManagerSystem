#include "FileNodeType.h"
// 引入映射容器头文件，提供std::map（键值对集合），用于存储文件扩展名与文件类型的对应关系
#include <map> 

// 函数实现在.cpp文件中
std::pair<std::string, std::string> fileTypeToString(FileNodeType type) {
    switch (type) {
    case FileNodeType::DIRECTORY: return { "文件夹", "" };
    case FileNodeType::TXT: return { "文本文件", ".txt" };
    case FileNodeType::RTF: return { "RTF格式文档（富文本格式）", ".rtf" };
    case FileNodeType::DOC: return { "Word文档（旧版）", ".doc" };
    case FileNodeType::DOCX: return { "Word文档（新版）", ".docx" };
    case FileNodeType::XLS: return { "Excel表格（旧版）", ".xls" };
    case FileNodeType::XLSX: return { "Excel表格（新版）", ".xlsx" };
    case FileNodeType::PPT: return { "PowerPoint演示文稿（旧版）", ".ppt" };
    case FileNodeType::PPTX: return { "PowerPoint演示文稿（新版）", ".pptx" };
    case FileNodeType::PDF: return { "PDF文档（便携式文档格式）", ".pdf" };
    case FileNodeType::JNG: return { "JNG图像文件", ".jng" };
    case FileNodeType::GIF: return { "GIF图像文件（图形交换格式）", ".gif" };
    case FileNodeType::BMP: return { "BMP位图文件", ".bmp" };
    case FileNodeType::PSD: return { "Photoshop文档（分层图像）", ".psd" };
    case FileNodeType::SVG: return { "SVG矢量图形（可缩放）", ".svg" };
    case FileNodeType::MP3: return { "MP3音频文件", ".mp3" };
    case FileNodeType::WAV: return { "WAV音频文件（波形无损）", ".wav" };
    case FileNodeType::FLAC: return { "FLAC音频文件（无损压缩）", ".flac" };
    case FileNodeType::M4A: return { "M4A音频文件", ".m4a" };
    case FileNodeType::OGG: return { "OGG音频文件", ".ogg" };
    case FileNodeType::MP4: return { "MP4视频文件", ".mp4" };
    case FileNodeType::AVI: return { "AVI视频文件（音视频交错）", ".avi" };
    case FileNodeType::MKV: return { "MKV视频文件（Matroska容器）", ".mkv" };
    case FileNodeType::FLV: return { "FLV视频文件（Flash视频）", ".flv" };
    case FileNodeType::MOV: return { "MOV视频文件（QuickTime）", ".mov" };
    case FileNodeType::RMVB: return { "RMVB视频文件（RealMedia可变比特率）", ".rmvb" };
    case FileNodeType::EXE: return { "可执行文件（Windows）", ".exe" };
    case FileNodeType::DMG: return { "磁盘镜像文件（macOS）", ".dmg" };
    case FileNodeType::APK: return { "Android应用安装包", ".apk" };
    case FileNodeType::DEB: return { "Debian软件包（Linux）", ".deb" };
    case FileNodeType::SH: return { "Shell脚本文件（Linux/macOS）", ".sh" };
    case FileNodeType::IOS: return { "iOS应用文件", ".ios" };
    case FileNodeType::ZIP: return { "ZIP压缩文件", ".zip" };
    case FileNodeType::RAR: return { "RAR压缩文件", ".rar" };
    case FileNodeType::JAVA: return { "Java源代码文件", ".java" };
    case FileNodeType::CPP: return { "C++源代码文件", ".cpp" };
    case FileNodeType::CJ: return { "C#源代码文件", ".cj" };
    case FileNodeType::C: return { "C语言源代码文件", ".c" };
    case FileNodeType::CS: return { "C#源代码文件", ".cs" };
    case FileNodeType::PY: return { "Python源代码文件", ".py" };
    case FileNodeType::JS: return { "JavaScript源代码文件", ".js" };
    case FileNodeType::TS: return { "TypeScript源代码文件", ".ts" };
    case FileNodeType::PHP: return { "PHP源代码文件", ".php" };
    case FileNodeType::RB: return { "Ruby源代码文件", ".rb" };
    case FileNodeType::GO: return { "Go源代码文件", ".go" };
    case FileNodeType::RS: return { "Rust源代码文件", ".rs" };
    case FileNodeType::SWIFT: return { "Swift源代码文件", ".swift" };
    case FileNodeType::KT: return { "Kotlin源代码文件", ".kt" };
    case FileNodeType::PL: return { "Perl源代码文件", ".pl" };
    case FileNodeType::PM: return { "Perl模块文件", ".pm" };
    case FileNodeType::R: return { "R语言源代码文件", ".r" };
    case FileNodeType::RMD: return { "R Markdown文档", ".rmd" };
    case FileNodeType::ERROR: return { "错误日志文件", ".error" };
    default: return { "其他文件", "" };
    }

}

FileNodeType stringToFileType(const std::string& temp) {
    std::string extension = toLower(temp);
    if (temp == "dirctory")
        return FileNodeType::DIRECTORY;
    else if (temp == "txt")
        return FileNodeType::TXT;
    else if (temp == "rtf")
        return FileNodeType::RTF;
    else if (temp == "doc")
        return FileNodeType::DOC;
    else if (temp == "docx")
        return FileNodeType::DOCX;
    else if (temp == "xls")
        return FileNodeType::XLS;
    else if (temp == "xlsx")
        return FileNodeType::XLSX;
    else if (temp == "ppt")
        return FileNodeType::PPT;
    else if (temp == "pptx")
        return FileNodeType::PPTX;
    else if (temp == "pdf")
        return FileNodeType::PDF;
    else if (temp == "jng")
        return FileNodeType::JNG;
    else if (temp == "gif")
        return FileNodeType::GIF;
    else if (temp == "bmp")
        return FileNodeType::BMP;
    else if (temp == "psd")
        return FileNodeType::PSD;
    else if (temp == "svg")
        return FileNodeType::SVG;
    else if (temp == "mp3")
        return FileNodeType::MP3;
    else if (temp == "wav")
        return FileNodeType::WAV;
    else if (temp == "flac")
        return FileNodeType::FLAC;
    else if (temp == "mp4")
        return FileNodeType::MP4;
    else if (temp == "avi")
        return FileNodeType::AVI;
    else if (temp == "mkv")
        return FileNodeType::MKV;
    else if (temp == "flv")
        return FileNodeType::FLV;
    else if (temp == "mov")
        return FileNodeType::MOV;
    else if (temp == "rmvb")
        return FileNodeType::RMVB;
    else if (temp == "exe")
        return FileNodeType::EXE;
    else if (temp == "dmg")
        return FileNodeType::DMG;
    else if (temp == "apk")
        return FileNodeType::APK;
    else if (temp == "deb")
        return FileNodeType::DEB;
    else if (temp == "sh")
        return FileNodeType::SH;
    else if (temp == "zip")
        return FileNodeType::ZIP;
    else if (temp == "rar")
        return FileNodeType::RAR;
    else if (temp == "ios")
        return FileNodeType::IOS;
    else if (temp == "java")
        return FileNodeType::JAVA;
    else if (temp == "cpp")
        return FileNodeType::CPP;
    else if (temp == "cj")
        return FileNodeType::CJ;
    else if (temp == "c")
        return FileNodeType::C;
    else if (temp == "cs")
        return FileNodeType::CS;
    else if (temp == "py")
        return FileNodeType::PY;
    else if (temp == "js")
        return FileNodeType::JS;
    else if (temp == "ts")
        return FileNodeType::TS;
    else if (temp == "php")
        return FileNodeType::PHP;
    else if (temp == "rb")
        return FileNodeType::RB;
    else if (temp == "go")
        return FileNodeType::GO;
    else if (temp == "rs")
        return FileNodeType::RS;
    else if (temp == "swift")
        return FileNodeType::SWIFT;
    else if (temp == "kt")
        return FileNodeType::KT;
    else if (temp == "pl")
        return FileNodeType::PL;
    else if (temp == "pm")
        return FileNodeType::PM;
    else if (temp == "r")
        return FileNodeType::R;
    else if (temp == "rmd")
        return FileNodeType::RMD;
    else
        return FileNodeType::DIRECTORY;
}
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}