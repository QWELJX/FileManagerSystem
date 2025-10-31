//第五个

#pragma once
#include <string>
#include <utility>//引入pair


enum class TreeNodeType
{
    DIRECTORY, TXT, RTF, DOC, DOCX, XLS, XLSX, PPT, PPTX, PDF, JNG, GIF, BMP, PSD, SVG, MP3, WAV, FLAC, M4A, OGG, MP4, AVI, MKV, FLV, MOV, RMVB,
    EXE, DMG, APK, DEB, SH, ZIP, RAR, IOS, JAVA, CPP, CJ, C, CS, PY, JS, TS, PHP, RB, GO, RS, SWIFT, KT, PL, PM, R, RMD, UNKNOWN
};


std::pair<std::string, std::string> treeNodeTypeToString(TreeNodeType type);

TreeNodeType stringToTreeNodeType(std::string temp);

std::string toLower(std::string str);
