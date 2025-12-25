#include "CMDManager.h"
#include <iostream>

int main() {
    std::cout << "测试引号处理功能...\n";
    
    // 创建CMDManager实例
    CMDManager& manager = CMDManager::getInstance();
    
    // 测试1：普通命令（无引号）
    std::cout << "\n测试1：普通命令 mkdir test_dir\n";
    manager.executeCommand("mkdir test_dir");
    
    // 测试2：带空格的文件名（使用引号）
    std::cout << "\n测试2：带空格的文件名 touch \"my file.txt\"\n";
    manager.executeCommand("touch \"my file.txt\"");
    
    // 测试3：带空格的目录名（使用引号）
    std::cout << "\n测试3：带空格的目录名 mkdir \"my dir\"\n";
    manager.executeCommand("mkdir \"my dir\"");
    
    // 测试4：查看目录内容，验证创建是否成功
    std::cout << "\n测试4：查看目录内容 dir /d\n";
    manager.executeCommand("dir /d");
    
    // 清理测试文件和目录
    std::cout << "\n清理测试文件和目录...\n";
    manager.executeCommand("del \"my file.txt\"");
    manager.executeCommand("del \"my dir\" /r");
    manager.executeCommand("del test_dir /r");
    
    std::cout << "\n测试完成！\n";
    return 0;
}