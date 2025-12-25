# FileManagerSystem - C++ 文件管理系统

## 项目简介

### 主要功能
`FileManagerSystem` 是一个基于 C++ 实现的**命令行文件管理器**，使用 `std::filesystem` 提供完整的真实文件系统操作功能：

- **目录管理**：创建目录（`mkdir/md`）、切换目录（`cd`）、删除目录（`del/rm`）
- **文件管理**：创建文件（`touch`）、删除文件（`del/rm`）、重命名文件（`rename`）、移动文件/目录（`move/mv`）
- **路径导航**：支持绝对路径、相对路径、`..` 和 `.` 等路径操作，自动路径规范化
- **信息展示**：格式化表格展示目录内容，支持详细模式（`/d`）和递归模式（`/r`）
- **快捷目录跳转**：自定义快捷标记系统（`mark`、`go`），支持复合路径语法
- **程序运行**：运行可执行文件（`run`）和打开文件（`open`）
- **命令系统**：类 CMD 风格的交互界面，支持命令别名和帮助系统

### 核心特性

#### 🚀 快捷目录跳转
- **自定义标记**：`mark work D:\Code\Project` 设置快捷方式
- **快速跳转**：`go work` 或 `cd ${work}` 直接跳转
- **复合路径**：`cd ${work}/src/components` 支持多级路径
- **标记管理**：`mark list`、`mark del <标记>` 管理快捷方式

#### 📁 智能文件操作
- **运行程序**：`run notepad.exe` 执行可执行文件
- **打开文件**：`open document.txt` 用默认程序打开文件
- **批量操作**：支持目录递归删除、移动等操作

#### 🌳 树形目录显示
- **递归显示**：`dir /r` 显示完整的目录树结构
- **层级缩进**：每级目录自动缩进，清晰显示层级关系
- **类型标识**：`[+]` 表示目录，`[-]` 表示文件

## 项目架构

### 核心模块

#### 🎯 CMDManager - 命令管理器
- **命令解析**：将用户输入解析为命令和参数
- **命令分发**：基于哈希表的命令映射系统
- **输出管理**：统一的输出缓冲和显示机制
- **快捷目录**：管理自定义快捷标记和展开逻辑

#### 🔧 FileSystemCore - 文件系统核心
- **文件操作**：基于 `std::filesystem` 的完整文件系统操作
- **路径处理**：自动路径规范化，处理相对路径、绝对路径
- **目录显示**：支持普通显示、详细显示、递归树形显示
- **编码转换**：UTF-8 和宽字符编码转换

#### 📊 数据结构
- **命令映射表**：`unordered_map<string, function<...>>`
- **快捷目录映射**：`unordered_map<string, string>`
- **文件类型映射**：40+ 种文件类型识别

## 运行方式

### 编译运行
1. 使用 Visual Studio 打开 `FileManagerSystem.sln`
2. 或者使用命令行：`msbuild FileManagerSystem.sln /p:Configuration=Debug /p:Platform=x64`
3. 运行生成的可执行文件

### 命令使用示例
```bash
# 目录操作
mkdir projects              # 创建目录
cd projects                 # 切换目录
cd ..                       # 返回上级目录
pwd                         # 显示当前目录

# 文件操作
touch hello.txt             # 创建文件
del hello.txt               # 删除文件
rename old.txt new.txt      # 重命名

# 目录显示
dir                         # 列出当前目录
dir /d                      # 详细显示（带类型、大小、时间）
dir /r                      # 递归显示目录树

# 快捷目录
mark work D:\Code\Project   # 设置快捷标记
mark home C:\Users\John     # 设置家目录标记
mark list                   # 查看所有标记
go work                     # 跳转到work目录
cd ${work}/src              # 复合路径跳转

# 程序运行
run notepad.exe             # 运行记事本
open document.txt           # 用记事本打开txt文件

# 其他
cls                         # 清屏
help                        # 显示帮助
exit                        # 退出程序
```

### 快捷标记高级用法
```bash
# 基础用法
mark code D:\Development
cd ${code}                  # 跳转到 D:\Development

# 复合路径
cd ${code}/projects         # 跳转到 D:\Development\projects
cd ${code}/../Documents     # 相对路径: D:\Documents

# 在其他命令中使用
copy ${code}/template.txt .
move ${code}/old.txt ${code}/backup/
```

### 树形目录显示
```bash
dir /r                      # 显示树形目录结构
```
输出示例：
```
----folder1/
   |---file1.txt
   |---subfolder/
      |---file2.txt
      |---deepfolder/
         |---file3.txt
----folder2/
   |---file4.txt
```

## 完整命令列表

| 命令 | 别名 | 参数 | 描述 |
|------|------|------|------|
| `help` | - | - | 显示帮助信息 |
| `dir` | `ls` | `[/d /r]` | 列出目录内容 |
| `mkdir` | `md` | `<目录名>` | 创建目录 |
| `touch` | - | `<文件名>` | 创建空文件 |
| `del` | `rm` | `<路径> [/r]` | 删除文件或目录 |
| `move` | `mv` | `<源> <目标>` | 移动文件或目录 |
| `rename` | - | `<旧名> <新名>` | 重命名文件或目录 |
| `cd` | - | `<路径>` | 切换当前目录 |
| `pwd` | - | - | 显示当前目录 |
| `exists` | - | `<路径>` | 检查路径是否存在 |
| `mark` | - | `<标记> <路径>` | 设置快捷标记 |
| `mark` | - | `del <标记>` | 删除快捷标记 |
| `mark` | - | `list` | 列出所有快捷标记 |
| `go` | - | `<标记>` | 跳转到快捷目录 |
| `run` | - | `<exe文件>` | 运行exe文件 |
| `open` | - | `<txt文件>` | 用记事本打开txt文件 |
| `cls` | `clear` | - | 清屏 |
| `exit` | `quit` | - | 退出程序 |

### 命令选项说明
- `/d`：详细显示模式（包含文件类型、大小、修改时间）
- `/r`：递归显示模式（树形目录结构）
- `/p`：父目录创建模式（mkdir命令，递归创建父目录）

## 项目文件结构
```
FileManagerSystem1/
├── FileManagerSystem.sln          # Visual Studio解决方案
├── FileManagerSystem.vcxproj      # 项目文件
├── README.md                      # 项目说明文档
├── x64/Debug/                     # 编译输出目录
│   └── FileManagerSystem.exe      # 可执行文件
└── FileManagerSystem/             # 源代码目录
    ├── Main.cpp                   # 程序入口
    ├── CMDManager.h/.cpp          # 命令管理器
    ├── FileSystemCore.h/.cpp      # 文件系统核心
    └── shortcuts.txt              # 快捷标记配置文件（运行时自动创建）
```

### 核心文件说明
- **Main.cpp**：程序入口，启动命令管理器
- **CMDManager**：命令解析、分发和用户交互的核心
- **FileSystemCore**：基于std::filesystem的文件操作封装
- **shortcuts.txt**：快捷标记配置文件（运行时自动创建）

## 技术栈与特性

### 🛠️ 技术栈
- **C++17**：使用现代C++特性
- **std::filesystem**：标准文件系统库
- **Windows API**：程序运行和文件打开功能
- **STL容器**：unordered_map、vector、string等

### ⚡ 核心特性
- **真实文件系统**：基于std::filesystem的实际文件操作
- **UTF-8支持**：完整的中文路径支持
- **命令行界面**：类似CMD的交互体验
- **快捷标记系统**：自定义目录快捷方式
- **树形目录显示**：层级缩进的目录结构展示
- **智能路径解析**：支持绝对路径、相对路径、快捷标记展开

## 开发与扩展

### 扩展新命令
在 `CMDManager::initCommands()` 中添加：
```cpp
command_map["newcmd"] = [this](auto& args) { handleNewCommand(args); };
```

### 添加新的快捷标记语法
修改 `expandShortcut()` 函数支持新的语法格式。

### 自定义显示格式
修改 `FileSystemCore::listDirectoryImpl()` 实现不同的显示样式。

## 注意事项

### 系统要求
- Windows 10/11
- Visual Studio 2019+ 或支持C++17的编译器
- 支持std::filesystem的运行时环境

### 使用建议
- 谨慎使用删除命令（`del`）
- 快捷标记会自动保存到 `shortcuts.txt`
- 支持拖拽文件到命令行窗口

---

**FileManagerSystem** 是一个功能完整、易于扩展的命令行文件管理器，展示了现代C++在系统编程中的强大能力。通过这个项目，你可以学习命令行应用开发、文件系统操作、用户界面设计等多个重要技能。

