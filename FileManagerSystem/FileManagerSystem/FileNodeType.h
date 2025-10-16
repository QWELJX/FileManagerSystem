//第五个

#pragma once
#include <string>
#include <utility>//引入pair
#include <algorithm>    // 用于 std::transform
#include <cctype> 

enum class FileNodeType
{
    DIRECTORY, TXT, RTF, DOC, DOCX, XLS, XLSX, PPT, PPTX, PDF, JNG, GIF, BMP, PSD, SVG, MP3, WAV, FLAC, M4A, OGG, MP4, AVI, MKV, FLV, MOV, RMVB,
    EXE, DMG, APK, DEB, SH, ZIP, RAR, IOS, JAVA, CPP, CJ, C, CS, PY, JS, TS, PHP, RB, GO, RS, SWIFT, KT, PL, PM, R, RMD, ERROR
};
enum class FilePermission {
    READ_ONLY,//只读
	WRITE_ONLY,//只写
	READ_WRITE,//读写
	EXECUTE_ONLY,//仅执行权限
	FULL_CONTROL,//完全控制权限
	NONE_CONTROL//完全无权限 只属于根节点 
};

// 函数声明
std::pair<std::string, std::string> fileTypeToString(FileNodeType type);

FileNodeType stringToFileType(const std::string& temp);

std::string toLower(const std::string& str);
