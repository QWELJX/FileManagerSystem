#include "TreeNodeType.h"
// 引入映射容器头文件，提供std::map（键值对集合），用于存储文件扩展名与文件类型的对应关系
#include <map> 

// 函数实现在.cpp文件中
std::pair<std::string, std::string> fileTypeToString(TreeNodeType type) {
    switch (type) {
    case TreeNodeType::DIRECTORY: return { "文件夹", "" };
    case TreeNodeType::TXT: return { "文本文件", ".txt" };
    /*case TreeNodeType::RTF: return { "RTF格式文档（富文本格式）", ".rtf" };
    case TreeNodeType::DOC: return { "Word文档（旧版）", ".doc" };
    case TreeNodeType::DOCX: return { "Word文档（新版）", ".docx" };
    case TreeNodeType::XLS: return { "Excel表格（旧版）", ".xls" };
    case TreeNodeType::XLSX: return { "Excel表格（新版）", ".xlsx" };
    case TreeNodeType::PPT: return { "PowerPoint演示文稿（旧版）", ".ppt" };
    case TreeNodeType::PPTX: return { "PowerPoint演示文稿（新版）", ".pptx" };
    case TreeNodeType::PDF: return { "PDF文档（便携式文档格式）", ".pdf" };
    case TreeNodeType::JNG: return { "JNG图像文件", ".jng" };
    case TreeNodeType::GIF: return { "GIF图像文件（图形交换格式）", ".gif" };
    case TreeNodeType::BMP: return { "BMP位图文件", ".bmp" };
    case TreeNodeType::PSD: return { "Photoshop文档（分层图像）", ".psd" };
    case TreeNodeType::SVG: return { "SVG矢量图形（可缩放）", ".svg" };
    case TreeNodeType::MP3: return { "MP3音频文件", ".mp3" };
    case TreeNodeType::WAV: return { "WAV音频文件（波形无损）", ".wav" };
    case TreeNodeType::FLAC: return { "FLAC音频文件（无损压缩）", ".flac" };
    case TreeNodeType::M4A: return { "M4A音频文件", ".m4a" };
    case TreeNodeType::OGG: return { "OGG音频文件", ".ogg" };
    case TreeNodeType::MP4: return { "MP4视频文件", ".mp4" };
    case TreeNodeType::AVI: return { "AVI视频文件（音视频交错）", ".avi" };
    case TreeNodeType::MKV: return { "MKV视频文件（Matroska容器）", ".mkv" };
    case TreeNodeType::FLV: return { "FLV视频文件（Flash视频）", ".flv" };
    case TreeNodeType::MOV: return { "MOV视频文件（QuickTime）", ".mov" };
    case TreeNodeType::RMVB: return { "RMVB视频文件（RealMedia可变比特率）", ".rmvb" };
    case TreeNodeType::EXE: return { "可执行文件（Windows）", ".exe" };
    case TreeNodeType::DMG: return { "磁盘镜像文件（macOS）", ".dmg" };
    case TreeNodeType::APK: return { "Android应用安装包", ".apk" };
    case TreeNodeType::DEB: return { "Debian软件包（Linux）", ".deb" };
    case TreeNodeType::SH: return { "Shell脚本文件（Linux/macOS）", ".sh" };
    case TreeNodeType::IOS: return { "iOS应用文件", ".ios" };
    case TreeNodeType::ZIP: return { "ZIP压缩文件", ".zip" };
    case TreeNodeType::RAR: return { "RAR压缩文件", ".rar" };
    case TreeNodeType::JAVA: return { "Java源代码文件", ".java" };
    case TreeNodeType::CPP: return { "C++源代码文件", ".cpp" };
    case TreeNodeType::CJ: return { "C#源代码文件", ".cj" };
    case TreeNodeType::C: return { "C语言源代码文件", ".c" };
    case TreeNodeType::CS: return { "C#源代码文件", ".cs" };
    case TreeNodeType::PY: return { "Python源代码文件", ".py" };
    case TreeNodeType::JS: return { "JavaScript源代码文件", ".js" };
    case TreeNodeType::TS: return { "TypeScript源代码文件", ".ts" };
    case TreeNodeType::PHP: return { "PHP源代码文件", ".php" };
    case TreeNodeType::RB: return { "Ruby源代码文件", ".rb" };
    case TreeNodeType::GO: return { "Go源代码文件", ".go" };
    case TreeNodeType::RS: return { "Rust源代码文件", ".rs" };
    case TreeNodeType::SWIFT: return { "Swift源代码文件", ".swift" };
    case TreeNodeType::KT: return { "Kotlin源代码文件", ".kt" };
    case TreeNodeType::PL: return { "Perl源代码文件", ".pl" };
    case TreeNodeType::PM: return { "Perl模块文件", ".pm" };
    case TreeNodeType::R: return { "R语言源代码文件", ".r" };
    case TreeNodeType::RMD: return { "R Markdown文档", ".rmd" };
    case TreeNodeType::ERROR: return { "错误日志文件", ".error" };*/
    default: return { "其他文件", "" };
    }

}

TreeNodeType stringToFileType(const std::string& temp) {
    std::string extension = toLower(temp);
    if (temp == "dirctory")
        return TreeNodeType::DIRECTORY;
    else if (temp == "txt")
        return TreeNodeType::TXT;
    /*else if (temp == "rtf")
        return TreeNodeType::RTF;
    else if (temp == "doc")
        return TreeNodeType::DOC;
    else if (temp == "docx")
        return TreeNodeType::DOCX;
    else if (temp == "xls")
        return TreeNodeType::XLS;
    else if (temp == "xlsx")
        return TreeNodeType::XLSX;
    else if (temp == "ppt")
        return TreeNodeType::PPT;
    else if (temp == "pptx")
        return TreeNodeType::PPTX;
    else if (temp == "pdf")
        return TreeNodeType::PDF;
    else if (temp == "jng")
        return TreeNodeType::JNG;
    else if (temp == "gif")
        return TreeNodeType::GIF;
    else if (temp == "bmp")
        return TreeNodeType::BMP;
    else if (temp == "psd")
        return TreeNodeType::PSD;
    else if (temp == "svg")
        return TreeNodeType::SVG;
    else if (temp == "mp3")
        return TreeNodeType::MP3;
    else if (temp == "wav")
        return TreeNodeType::WAV;
    else if (temp == "flac")
        return TreeNodeType::FLAC;
    else if (temp == "mp4")
        return TreeNodeType::MP4;
    else if (temp == "avi")
        return TreeNodeType::AVI;
    else if (temp == "mkv")
        return TreeNodeType::MKV;
    else if (temp == "flv")
        return TreeNodeType::FLV;
    else if (temp == "mov")
        return TreeNodeType::MOV;
    else if (temp == "rmvb")
        return TreeNodeType::RMVB;
    else if (temp == "exe")
        return TreeNodeType::EXE;
    else if (temp == "dmg")
        return TreeNodeType::DMG;
    else if (temp == "apk")
        return TreeNodeType::APK;
    else if (temp == "deb")
        return TreeNodeType::DEB;
    else if (temp == "sh")
        return TreeNodeType::SH;
    else if (temp == "zip")
        return TreeNodeType::ZIP;
    else if (temp == "rar")
        return TreeNodeType::RAR;
    else if (temp == "ios")
        return TreeNodeType::IOS;
    else if (temp == "java")
        return TreeNodeType::JAVA;
    else if (temp == "cpp")
        return TreeNodeType::CPP;
    else if (temp == "cj")
        return TreeNodeType::CJ;
    else if (temp == "c")
        return TreeNodeType::C;
    else if (temp == "cs")
        return TreeNodeType::CS;
    else if (temp == "py")
        return TreeNodeType::PY;
    else if (temp == "js")
        return TreeNodeType::JS;
    else if (temp == "ts")
        return TreeNodeType::TS;
    else if (temp == "php")
        return TreeNodeType::PHP;
    else if (temp == "rb")
        return TreeNodeType::RB;
    else if (temp == "go")
        return TreeNodeType::GO;
    else if (temp == "rs")
        return TreeNodeType::RS;
    else if (temp == "swift")
        return TreeNodeType::SWIFT;
    else if (temp == "kt")
        return TreeNodeType::KT;
    else if (temp == "pl")
        return TreeNodeType::PL;
    else if (temp == "pm")
        return TreeNodeType::PM;
    else if (temp == "r")
        return TreeNodeType::R;
    else if (temp == "rmd")
        return TreeNodeType::RMD;
    else*/
        return TreeNodeType::DIRECTORY;
}
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}