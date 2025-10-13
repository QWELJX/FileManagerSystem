#include "CMDManager.h"
int main() {
	CMDManager& cmdManager = CMDManager::getInstance();
	cmdManager.Run();
	return 0;
}