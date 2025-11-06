#include "TreeNodeType.h"
#include <algorithm>    // 用于 std::transform
#include <cctype> 
#include <unordered_map> 

// 函数实现在.cpp文件中
// 用 static 限制全局变量作用域
static const std::unordered_map<std::string, TreeNodeType> str_to_type = {
    {".txt", TreeNodeType::TXT},
    {".doc", TreeNodeType::DOC},
    {".docx", TreeNodeType::DOCX},
    {".xls", TreeNodeType::XLS},
    {".xlsx", TreeNodeType::XLSX},
    {".ppt", TreeNodeType::PPT},
    {".pptx", TreeNodeType::PPTX},
    {".pdf", TreeNodeType::PDF},
    {".jpg", TreeNodeType::JPG},
    {".jpeg", TreeNodeType::JPEG},
    {".png", TreeNodeType::PNG},
    {".gif", TreeNodeType::GIF},
    {".bmp", TreeNodeType::BMP},
    {".tiff", TreeNodeType::TIFF},
    {".mp3", TreeNodeType::MP3},
    {".wav", TreeNodeType::WAV},
    {".flac", TreeNodeType::FLAC},
    {".aac", TreeNodeType::AAC},
    {".mp4", TreeNodeType::MP4},
    {".avi", TreeNodeType::AVI},
    {".mov", TreeNodeType::MOV},
    {".mkv", TreeNodeType::MKV},
    {".exe", TreeNodeType::EXE},
    {".dll", TreeNodeType::DLL},
    {".cpp", TreeNodeType::CPP},
    {".h", TreeNodeType::H},
    {".c", TreeNodeType::C},
    {".java", TreeNodeType::JAVA},
    {".py", TreeNodeType::PY},
    {".js", TreeNodeType::JS},
    {".html", TreeNodeType::HTML},
    {".css", TreeNodeType::CSS},
    {".zip", TreeNodeType::ZIP},
    {".rar", TreeNodeType::RAR},
    {".tar", TreeNodeType::TAR},
    {".gz", TreeNodeType::GZ},
    {".iso", TreeNodeType::ISO},
    {".sql", TreeNodeType::SQL},
    {".json", TreeNodeType::JSON},
    {".xml", TreeNodeType::XML},
    {"", TreeNodeType::FILE}
};

// 文件类型到扩展名和显示名称的映射
static const std::unordered_map<TreeNodeType, std::pair<std::string, std::string>> type_to_str = {
    {TreeNodeType::TXT, {".txt", "文本文件"}},
    {TreeNodeType::DOC, {".doc", "Word文档"}},
    {TreeNodeType::DOCX, {".docx", "Word文档"}},
    {TreeNodeType::XLS, {".xls", "Excel表格"}},
    {TreeNodeType::XLSX, {".xlsx", "Excel表格"}},
    {TreeNodeType::PPT, {".ppt", "PowerPoint演示文稿"}},
    {TreeNodeType::PPTX, {".pptx", "PowerPoint演示文稿"}},
    {TreeNodeType::PDF, {".pdf", "PDF文档"}},
    {TreeNodeType::JPG, {".jpg", "JPG图片"}},
    {TreeNodeType::JPEG, {".jpeg", "JPEG图片"}},
    {TreeNodeType::PNG, {".png", "PNG图片"}},
    {TreeNodeType::GIF, {".gif", "GIF图片"}},
    {TreeNodeType::BMP, {".bmp", "BMP图片"}},
    {TreeNodeType::TIFF, {".tiff", "TIFF图片"}},
    {TreeNodeType::MP3, {".mp3", "MP3音频"}},
    {TreeNodeType::WAV, {".wav", "WAV音频"}},
    {TreeNodeType::FLAC, {".flac", "FLAC音频"}},
    {TreeNodeType::AAC, {".aac", "AAC音频"}},
    {TreeNodeType::MP4, {".mp4", "MP4视频"}},
    {TreeNodeType::AVI, {".avi", "AVI视频"}},
    {TreeNodeType::MOV, {".mov", "MOV视频"}},
    {TreeNodeType::MKV, {".mkv", "MKV视频"}},
    {TreeNodeType::EXE, {".exe", "可执行程序"}},
    {TreeNodeType::DLL, {".dll", "动态链接库"}},
    {TreeNodeType::CPP, {".cpp", "C++源代码"}},
    {TreeNodeType::H, {".h", "头文件"}},
    {TreeNodeType::C, {".c", "C源代码"}},
    {TreeNodeType::JAVA, {".java", "Java源代码"}},
    {TreeNodeType::PY, {".py", "Python脚本"}},
    {TreeNodeType::JS, {".js", "JavaScript脚本"}},
    {TreeNodeType::HTML, {".html", "HTML文件"}},
    {TreeNodeType::CSS, {".css", "CSS文件"}},
    {TreeNodeType::ZIP, {".zip", "ZIP压缩包"}},
    {TreeNodeType::RAR, {".rar", "RAR压缩包"}},
    {TreeNodeType::TAR, {".tar", "TAR归档文件"}},
    {TreeNodeType::GZ, {".gz", "GZ压缩文件"}},
    {TreeNodeType::ISO, {".iso", "光盘镜像文件"}},
    {TreeNodeType::SQL, {".sql", "SQL数据库文件"}},
    {TreeNodeType::JSON, {".json", "JSON文件"}},
    {TreeNodeType::XML, {".xml", "XML文件"}},
	{TreeNodeType::DIRECTORY, {"", "目录"}},
    {TreeNodeType::FILE, {"", "文件"}}
    
};

// 将文件类型转换为扩展名和显示名称
std::pair<std::string, std::string> treeNodeTypeToString(TreeNodeType type) {
    auto it = type_to_str.find(type);
    if (it != type_to_str.end()) {
        return it->second;
    }
    return { "", "未知文件类型" };
}

TreeNodeType stringToTreeNodeType(std::string temp) {
    std::string extension = toLower(temp);
    auto it = str_to_type.find(extension);
    return (it != str_to_type.end()) ? it->second : TreeNodeType::UNKNOWN;
}

std::string toLower(std::string str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}