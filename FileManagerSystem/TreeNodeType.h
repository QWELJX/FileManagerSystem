// 树节点类型

#pragma once
#include <string>
#include <utility> // 包含pair

enum class TreeNodeType {
  TXT,       // 文本文件
  FILE,      // 未知文件
  DIRECTORY, // 目录
  DOC,       // Word文档
  DOCX,      // Word文档(新格式)
  XLS,       // Excel工作簿
  XLSX,      // Excel工作簿(新格式)
  PPT,       // PowerPoint演示文稿
  PPTX,      // PowerPoint演示文稿(新格式)
  PDF,       // PDF文档
  JPG,       // JPG图片
  JPEG,      // JPEG图片
  PNG,       // PNG图片
  GIF,       // GIF图片
  BMP,       // BMP图片
  TIFF,      // TIFF图片
  MP3,       // MP3音频
  WAV,       // WAV音频
  FLAC,      // FLAC音频
  AAC,       // AAC音频
  MP4,       // MP4视频
  AVI,       // AVI视频
  MOV,       // MOV��Ƶ
  MKV,       // MKV��Ƶ
  EXE,       // ��ִ�г���
  DLL,       // ��̬���ӿ�
  CPP,       // C++Դ����
  H,         // C/C++ͷ�ļ�
  C,         // CԴ����
  JAVA,      // JavaԴ����
  PY,        // Python�ű�
  JS,        // JavaScript�ű�
  HTML,      // HTML�ļ�
  CSS,       // CSS�ļ�
  ZIP,       // ZIPѹ����
  RAR,
  TAR,
  GZ,
  ISO,    // ���̾���
  SQL,    // SQL���ݿ��ļ�
  JSON,   // JSON�ļ�
  XML,    // XML�ļ�
  UNKNOWN // δ֪����
};

std::pair<std::string, std::string> treeNodeTypeToString(TreeNodeType type);

TreeNodeType stringToTreeNodeType(std::string temp);

std::string toLower(std::string str);
