
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

    // �������

    void handleRgt(const std::vector<std::string>& tokens);//ע���û�
	void handleLogin(const std::vector<std::string>& tokens);//��¼�û�
    void handleCls(const std::vector<std::string>& tokens);//����
    void handleAdd(const std::vector<std::string>& tokens);//���
    void handleDelete(const std::vector<std::string>& tokens);//ɾ��
    void handleGoto(const std::vector<std::string>& tokens);//��ת
    void handleBack(const std::vector<std::string>& tokens);//����
    void handleSet(const std::vector<std::string>& tokens);//�����ļ�Ȩ��
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
    const std::string& getContent() const { return CONTENT; }
    void clearContent() { CONTENT.clear(); }
    void appendContent(const std::string& text) {CONTENT += text;}
    void showContent() { std::cout << this->getContent(); }


};