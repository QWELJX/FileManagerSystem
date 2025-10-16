#include "FileNodeType.h"
// ����ӳ������ͷ�ļ����ṩstd::map����ֵ�Լ��ϣ������ڴ洢�ļ���չ�����ļ����͵Ķ�Ӧ��ϵ
#include <map> 

// ����ʵ����.cpp�ļ���
std::pair<std::string, std::string> fileTypeToString(FileNodeType type) {
    switch (type) {
    case FileNodeType::DIRECTORY: return { "�ļ���", "" };
    case FileNodeType::TXT: return { "�ı��ļ�", ".txt" };
    case FileNodeType::RTF: return { "RTF��ʽ�ĵ������ı���ʽ��", ".rtf" };
    case FileNodeType::DOC: return { "Word�ĵ����ɰ棩", ".doc" };
    case FileNodeType::DOCX: return { "Word�ĵ����°棩", ".docx" };
    case FileNodeType::XLS: return { "Excel��񣨾ɰ棩", ".xls" };
    case FileNodeType::XLSX: return { "Excel����°棩", ".xlsx" };
    case FileNodeType::PPT: return { "PowerPoint��ʾ�ĸ壨�ɰ棩", ".ppt" };
    case FileNodeType::PPTX: return { "PowerPoint��ʾ�ĸ壨�°棩", ".pptx" };
    case FileNodeType::PDF: return { "PDF�ĵ�����Яʽ�ĵ���ʽ��", ".pdf" };
    case FileNodeType::JNG: return { "JNGͼ���ļ�", ".jng" };
    case FileNodeType::GIF: return { "GIFͼ���ļ���ͼ�ν�����ʽ��", ".gif" };
    case FileNodeType::BMP: return { "BMPλͼ�ļ�", ".bmp" };
    case FileNodeType::PSD: return { "Photoshop�ĵ����ֲ�ͼ��", ".psd" };
    case FileNodeType::SVG: return { "SVGʸ��ͼ�Σ������ţ�", ".svg" };
    case FileNodeType::MP3: return { "MP3��Ƶ�ļ�", ".mp3" };
    case FileNodeType::WAV: return { "WAV��Ƶ�ļ�����������", ".wav" };
    case FileNodeType::FLAC: return { "FLAC��Ƶ�ļ�������ѹ����", ".flac" };
    case FileNodeType::M4A: return { "M4A��Ƶ�ļ�", ".m4a" };
    case FileNodeType::OGG: return { "OGG��Ƶ�ļ�", ".ogg" };
    case FileNodeType::MP4: return { "MP4��Ƶ�ļ�", ".mp4" };
    case FileNodeType::AVI: return { "AVI��Ƶ�ļ�������Ƶ����", ".avi" };
    case FileNodeType::MKV: return { "MKV��Ƶ�ļ���Matroska������", ".mkv" };
    case FileNodeType::FLV: return { "FLV��Ƶ�ļ���Flash��Ƶ��", ".flv" };
    case FileNodeType::MOV: return { "MOV��Ƶ�ļ���QuickTime��", ".mov" };
    case FileNodeType::RMVB: return { "RMVB��Ƶ�ļ���RealMedia�ɱ�����ʣ�", ".rmvb" };
    case FileNodeType::EXE: return { "��ִ���ļ���Windows��", ".exe" };
    case FileNodeType::DMG: return { "���̾����ļ���macOS��", ".dmg" };
    case FileNodeType::APK: return { "AndroidӦ�ð�װ��", ".apk" };
    case FileNodeType::DEB: return { "Debian�������Linux��", ".deb" };
    case FileNodeType::SH: return { "Shell�ű��ļ���Linux/macOS��", ".sh" };
    case FileNodeType::IOS: return { "iOSӦ���ļ�", ".ios" };
    case FileNodeType::ZIP: return { "ZIPѹ���ļ�", ".zip" };
    case FileNodeType::RAR: return { "RARѹ���ļ�", ".rar" };
    case FileNodeType::JAVA: return { "JavaԴ�����ļ�", ".java" };
    case FileNodeType::CPP: return { "C++Դ�����ļ�", ".cpp" };
    case FileNodeType::CJ: return { "C#Դ�����ļ�", ".cj" };
    case FileNodeType::C: return { "C����Դ�����ļ�", ".c" };
    case FileNodeType::CS: return { "C#Դ�����ļ�", ".cs" };
    case FileNodeType::PY: return { "PythonԴ�����ļ�", ".py" };
    case FileNodeType::JS: return { "JavaScriptԴ�����ļ�", ".js" };
    case FileNodeType::TS: return { "TypeScriptԴ�����ļ�", ".ts" };
    case FileNodeType::PHP: return { "PHPԴ�����ļ�", ".php" };
    case FileNodeType::RB: return { "RubyԴ�����ļ�", ".rb" };
    case FileNodeType::GO: return { "GoԴ�����ļ�", ".go" };
    case FileNodeType::RS: return { "RustԴ�����ļ�", ".rs" };
    case FileNodeType::SWIFT: return { "SwiftԴ�����ļ�", ".swift" };
    case FileNodeType::KT: return { "KotlinԴ�����ļ�", ".kt" };
    case FileNodeType::PL: return { "PerlԴ�����ļ�", ".pl" };
    case FileNodeType::PM: return { "Perlģ���ļ�", ".pm" };
    case FileNodeType::R: return { "R����Դ�����ļ�", ".r" };
    case FileNodeType::RMD: return { "R Markdown�ĵ�", ".rmd" };
    case FileNodeType::ERROR: return { "������־�ļ�", ".error" };
    default: return { "�����ļ�", "" };
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