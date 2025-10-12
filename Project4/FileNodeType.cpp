#include "FileNodeType.h"
// 引入映射容器头文件，提供std::map（键值对集合），用于存储文件扩展名与文件类型的对应关系
#include <map> 

// 函数实现在.cpp文件中
std::pair<std::string, std::string> fileTypeToString(FileNodeType type) {
    switch (type) {
    case FileNodeType::DIRECTORY: return { "文件夹" ,""};
    case FileNodeType::TXT: return { "文本文件",".txt"};
    case FileNodeType::RTF: return { "RTF 格式文档（富文本格式）",".rft" };
    case FileNodeType::DOC: return { "",".doc" };
    default: return { "其他",""};
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
std::string toLower(const std::string& str)  {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}