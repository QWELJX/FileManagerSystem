#pragma once
#include <string>
#include <vector>

/**
 * @brief �򻯰�·����������
 * ֻ������õ�·����������
 */
const static char SEPARATOR = '\\';

class PathUtils {
public:
    // ��ֹ����ʵ��
    PathUtils() = delete;
    ~PathUtils() = delete;
    PathUtils(const PathUtils&) = delete;
    PathUtils& operator=(const PathUtils&) = delete;




    /**
     * @brief ����·���������õĹ��ܣ�
     */
    static std::string join(const std::string& path1, const std::string& path2);
    static std::string join(const std::vector<std::string>& components);

    /**
     * @brief ��ȡ·����Ŀ¼����
     */
    static std::string getDirectory(const std::string& path);

    /**
     * @brief ��ȡ·�����ļ�������
     */
    static std::string getFilename(const std::string& path);

    /**
     * @brief ��ȡ�ļ���չ��
     */
    static std::string getExtension(const std::string& path);

    /**
     * @brief ��ȡ�ļ�����������չ����
     */
    static std::string getStem(const std::string& path);

    /**
     * @brief �淶��·��
     * - ͳһ�ָ���
     * - ���� "." �� ".."
     * - �Ƴ�����ָ���
     */
    static std::string normalize(const std::string& path);

    /**
     * @brief ���·���Ƿ�Ϊ����·��
     */
    static bool isAbsolute(const std::string& path);

    /**
     * @brief ���·���Ƿ�Ϊ���·��
     */
    static bool isRelative(const std::string& path);

    /**
     * @brief �ָ�·��ΪĿ¼���ļ���
     */
    static std::pair<std::string, std::string> split(const std::string& path);

    /**
     * @brief ͳһ·���ָ���
     */
    static std::string uniformSeparator(const std::string& path, char separator = SEPARATOR);

    /**
     * @brief ·�������Ƴ�����ȫ�ַ�
     */
    static std::string sanitize(const std::string& path);

    /**
     * @brief ���·���Ƿ���ָ����չ����β
     */
    static bool hasExtension(const std::string& path, const std::string& extension);

private:
    // �ڲ����ߺ���
    static bool isSeparator(char c);
    static bool isCurrentDirectory(const std::string& component);
    static bool isParentDirectory(const std::string& component);
    static std::pair<bool, std::vector<std::string>> splitComponents(const std::string& path);
};