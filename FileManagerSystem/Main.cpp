#include "CMDManager.h"

int main() {
    // 设置控制台代码页为UTF-8（支持中文路径）

#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    std::cout << "========================================\n";
    std::cout << "     C++ 文件管理器 v1.0\n";
    std::cout << "     基于 std::filesystem\n";
    std::cout << "========================================\n\n";

    try {
        // 启动命令管理器
        CMDManager::getInstance().run();
    }
    catch (const std::exception& e) {
        std::cerr << "程序异常: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}