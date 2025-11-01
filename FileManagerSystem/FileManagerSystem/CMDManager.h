
#pragma once
#include <iostream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
//#include "FileManager.h"
// ʹ��ǰ���������ֱ�Ӱ���������ѭ������
class FileManager;

class CMDManager {
private:
    // ˽�й��캯��
    CMDManager();
    // ��ֹ�����͸�ֵ
    CMDManager(const CMDManager&) = delete;
    CMDManager& operator=(const CMDManager&) = delete;

    std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>> commandMap;

    std::string CONTENT;//չʾ����
    void handleCls(const std::vector<std::string>& tokens);//����
    void handleMkdir(const std::vector<std::string>& tokens);//����ļ���
	void HandleCreateFile(const std::vector<std::string>& tokens);//����ļ�
    void handleDelete(const std::vector<std::string>& tokens);//ɾ��
    void handleGoto(const std::vector<std::string>& tokens);//��ת
    //void handleBack(const std::vector<std::string>& tokens);����
    void handleDir(const std::vector<std::string>& tokens);//!
    void handleHelp(const std::vector<std::string>& tokens);//����

    // ���ߺ���
    bool isPureNumber(const std::string& str);//�жϴ�����
    std::string toLower(const std::string& str);  // ����������

    void nl(int t);//����
 
public:
    // ��ȡ����ʵ��
    static CMDManager& getInstance() {
        static CMDManager instance;
        return instance;
    }

    // ԭ�еĹ�������
    void Run();
    void RunCMD(const std::vector<std::string>& tokens);
    void Show();
    
    // ��ȡ��ǰ���ݣ�������ʾ��
    const std::string& getContent() const;
    void clearContent();
    void appendContent(const std::string& text);
    void showContent();


};