#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include "CMDManager.h"

int main() {
    // ====== 最关键的初始化 ======
#ifdef _WIN32
    // 1. 直接设置控制台代码页，不通过任何可能提前初始化std::cout/cerr的函数
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // ====== 原有的业务逻辑 ======
    try {
        CMDManager::getInstance().run();
    }
    catch (const std::exception& e) {
        // 现在使用std::cerr是安全的，因为代码页已设置
        std::cerr << "程序异常: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}