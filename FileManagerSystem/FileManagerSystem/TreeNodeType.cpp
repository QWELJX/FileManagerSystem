#include "TreeNodeType.h"
// ����ӳ������ͷ�ļ����ṩstd::map����ֵ�Լ��ϣ������ڴ洢�ļ���չ�����ļ����͵Ķ�Ӧ��ϵ
#include <map> 

// ����ʵ����.cpp�ļ���
std::pair<std::string, std::string> fileTypeToString(TreeNodeType type) {
    switch (type) {
    case TreeNodeType::DIRECTORY: return { "�ļ���", "" };
    case TreeNodeType::TXT: return { "�ı��ļ�", ".txt" };
    /*case TreeNodeType::RTF: return { "RTF��ʽ�ĵ������ı���ʽ��", ".rtf" };
    case TreeNodeType::DOC: return { "Word�ĵ����ɰ棩", ".doc" };
    case TreeNodeType::DOCX: return { "Word�ĵ����°棩", ".docx" };
    case TreeNodeType::XLS: return { "Excel��񣨾ɰ棩", ".xls" };
    case TreeNodeType::XLSX: return { "Excel����°棩", ".xlsx" };
    case TreeNodeType::PPT: return { "PowerPoint��ʾ�ĸ壨�ɰ棩", ".ppt" };
    case TreeNodeType::PPTX: return { "PowerPoint��ʾ�ĸ壨�°棩", ".pptx" };
    case TreeNodeType::PDF: return { "PDF�ĵ�����Яʽ�ĵ���ʽ��", ".pdf" };
    case TreeNodeType::JNG: return { "JNGͼ���ļ�", ".jng" };
    case TreeNodeType::GIF: return { "GIFͼ���ļ���ͼ�ν�����ʽ��", ".gif" };
    case TreeNodeType::BMP: return { "BMPλͼ�ļ�", ".bmp" };
    case TreeNodeType::PSD: return { "Photoshop�ĵ����ֲ�ͼ��", ".psd" };
    case TreeNodeType::SVG: return { "SVGʸ��ͼ�Σ������ţ�", ".svg" };
    case TreeNodeType::MP3: return { "MP3��Ƶ�ļ�", ".mp3" };
    case TreeNodeType::WAV: return { "WAV��Ƶ�ļ�����������", ".wav" };
    case TreeNodeType::FLAC: return { "FLAC��Ƶ�ļ�������ѹ����", ".flac" };
    case TreeNodeType::M4A: return { "M4A��Ƶ�ļ�", ".m4a" };
    case TreeNodeType::OGG: return { "OGG��Ƶ�ļ�", ".ogg" };
    case TreeNodeType::MP4: return { "MP4��Ƶ�ļ�", ".mp4" };
    case TreeNodeType::AVI: return { "AVI��Ƶ�ļ�������Ƶ����", ".avi" };
    case TreeNodeType::MKV: return { "MKV��Ƶ�ļ���Matroska������", ".mkv" };
    case TreeNodeType::FLV: return { "FLV��Ƶ�ļ���Flash��Ƶ��", ".flv" };
    case TreeNodeType::MOV: return { "MOV��Ƶ�ļ���QuickTime��", ".mov" };
    case TreeNodeType::RMVB: return { "RMVB��Ƶ�ļ���RealMedia�ɱ�����ʣ�", ".rmvb" };
    case TreeNodeType::EXE: return { "��ִ���ļ���Windows��", ".exe" };
    case TreeNodeType::DMG: return { "���̾����ļ���macOS��", ".dmg" };
    case TreeNodeType::APK: return { "AndroidӦ�ð�װ��", ".apk" };
    case TreeNodeType::DEB: return { "Debian�������Linux��", ".deb" };
    case TreeNodeType::SH: return { "Shell�ű��ļ���Linux/macOS��", ".sh" };
    case TreeNodeType::IOS: return { "iOSӦ���ļ�", ".ios" };
    case TreeNodeType::ZIP: return { "ZIPѹ���ļ�", ".zip" };
    case TreeNodeType::RAR: return { "RARѹ���ļ�", ".rar" };
    case TreeNodeType::JAVA: return { "JavaԴ�����ļ�", ".java" };
    case TreeNodeType::CPP: return { "C++Դ�����ļ�", ".cpp" };
    case TreeNodeType::CJ: return { "C#Դ�����ļ�", ".cj" };
    case TreeNodeType::C: return { "C����Դ�����ļ�", ".c" };
    case TreeNodeType::CS: return { "C#Դ�����ļ�", ".cs" };
    case TreeNodeType::PY: return { "PythonԴ�����ļ�", ".py" };
    case TreeNodeType::JS: return { "JavaScriptԴ�����ļ�", ".js" };
    case TreeNodeType::TS: return { "TypeScriptԴ�����ļ�", ".ts" };
    case TreeNodeType::PHP: return { "PHPԴ�����ļ�", ".php" };
    case TreeNodeType::RB: return { "RubyԴ�����ļ�", ".rb" };
    case TreeNodeType::GO: return { "GoԴ�����ļ�", ".go" };
    case TreeNodeType::RS: return { "RustԴ�����ļ�", ".rs" };
    case TreeNodeType::SWIFT: return { "SwiftԴ�����ļ�", ".swift" };
    case TreeNodeType::KT: return { "KotlinԴ�����ļ�", ".kt" };
    case TreeNodeType::PL: return { "PerlԴ�����ļ�", ".pl" };
    case TreeNodeType::PM: return { "Perlģ���ļ�", ".pm" };
    case TreeNodeType::R: return { "R����Դ�����ļ�", ".r" };
    case TreeNodeType::RMD: return { "R Markdown�ĵ�", ".rmd" };
    case TreeNodeType::ERROR: return { "������־�ļ�", ".error" };*/
    default: return { "�����ļ�", "" };
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