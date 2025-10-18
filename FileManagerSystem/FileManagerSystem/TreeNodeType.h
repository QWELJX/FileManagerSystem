//�����

#pragma once
#include <string>
#include <utility>//����pair
#include <algorithm>    // ���� std::transform
#include <cctype> 

enum class TreeNodeType
{
    DIRECTORY, TXT, RTF, DOC, DOCX, XLS, XLSX, PPT, PPTX, PDF, JNG, GIF, BMP, PSD, SVG, MP3, WAV, FLAC, M4A, OGG, MP4, AVI, MKV, FLV, MOV, RMVB,
    EXE, DMG, APK, DEB, SH, ZIP, RAR, IOS, JAVA, CPP, CJ, C, CS, PY, JS, TS, PHP, RB, GO, RS, SWIFT, KT, PL, PM, R, RMD, ERROR
};
enum class FilePermission {
    READ_ONLY,//ֻ��
	WRITE_ONLY,//ֻд
	READ_WRITE,//��д
	EXECUTE_ONLY,//��ִ��Ȩ��
	FULL_CONTROL,//��ȫ����Ȩ��
	NONE_CONTROL//��ȫ��Ȩ�� ֻ���ڸ��ڵ� 
};

// ��������
std::pair<std::string, std::string> fileTypeToString(TreeNodeType type);

TreeNodeType stringToFileType(const std::string& temp);

std::string toLower(const std::string& str);
