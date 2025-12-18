//第五个

#pragma once
#include <string>
#include <utility>//引入pair


enum class TreeNodeType {
    TXT,        // 文本文件
    FILE,       // 未知文件
    DIRECTORY,  // 目录
    DOC,        // Word文档
    DOCX,       // Word文档(新格式)
    XLS,        // Excel表格
    XLSX,       // Excel表格(新格式)
    PPT,        // PowerPoint演示文稿
    PPTX,       // PowerPoint演示文稿(新格式)
    PDF,        // PDF文档
    JPG,        // JPG图片
    JPEG,       // JPEG图片
    PNG,        // PNG图片
    GIF,        // GIF图片
    BMP,        // BMP图片
    TIFF,       // TIFF图片
    MP3,        // MP3音频
    WAV,        // WAV音频
    FLAC,       // FLAC音频
    AAC,        // AAC音频
    MP4,        // MP4视频
    AVI,        // AVI视频
    MOV,        // MOV视频
    MKV,        // MKV视频
    EXE,        // 可执行程序
    DLL,        // 动态链接库
    CPP,        // C++源代码
    H,          // C/C++头文件
    C,          // C源代码
    JAVA,       // Java源代码
    PY,         // Python脚本
    JS,         // JavaScript脚本
    HTML,       // HTML文件
    CSS,        // CSS文件
    ZIP,        // ZIP压缩包
    RAR,
    TAR,
    GZ,
    ISO,        // 光盘镜像
    SQL,        // SQL数据库文件
    JSON,       // JSON文件
    XML,         // XML文件
    UNKNOWN	  // 未知类型
};



std::pair<std::string, std::string> treeNodeTypeToString(TreeNodeType type);

TreeNodeType stringToTreeNodeType(std::string temp);

std::string toLower(std::string str);
