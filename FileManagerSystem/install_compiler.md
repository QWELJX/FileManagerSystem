# MinGW-w64 安装教程及项目编译指南

## 一、安装 MinGW-w64 编译器

### 1. 下载 MinGW-w64

你可以通过以下两种方式下载：

**方式一：官方下载**
1. 访问官方网站：[MinGW-w64 - for 32 and 64 bit Windows download | SourceForge.net](https://sourceforge.net/projects/mingw-w64/)
2. 向下滚动页面，找到最新版本的下载链接
3. 选择适合你系统的版本（64位系统选择 x86_64）

**方式二：直接下载压缩包**
1. 你也可以使用百度网盘分享的文件：
   - 链接: https://pan.baidu.com/s/... (根据搜索结果提供的链接)
   - 下载 mingw64.zip 文件

### 2. 安装/解压

**如果你下载的是安装程序：**
1. 运行安装程序
2. 选择以下配置：
   - Version: 选择最新版本
   - Architecture: x86_64 (64位系统)
   - Threads: posix
   - Exception: seh
   - Build revision: 0
3. 选择安装路径（建议选择 D:\mingw64，路径不要包含中文）
4. 点击 Next 完成安装

**如果你下载的是压缩包：**
1. 将 mingw64.zip 解压到 D 盘根目录（D:\mingw64）
2. 确保解压后的文件夹结构正确（D:\mingw64\bin 目录应该存在）

### 3. 配置环境变量

1. 打开控制面板 → 系统 → 查看高级系统设置 → 高级 → 环境变量
2. 在系统变量中找到 Path，双击编辑
3. 点击新建，添加 D:\mingw64\bin
4. 点击确定保存所有更改

### 4. 验证安装

1. 打开命令提示符（Win + R → 输入 cmd → 回车）
2. 输入以下命令验证编译器是否安装成功：
   ```cmd
   gcc --version
   g++ --version
   ```
3. 如果显示版本信息，则安装成功

## 二、编译运行项目

### 1. 打开项目目录

在命令提示符中，切换到项目目录：

```cmd
cd d:\VisualStudioGitHub\FileManagerSystem1\FileManagerSystem
```

### 2. 编译项目

使用 g++ 编译项目：

```cmd
g++ -std=c++17 -o FileManager Main.cpp CMDManager.cpp FileSystemCore.cpp PathUtils.cpp TreeNode.cpp TreeNodeType.cpp -lfmt
```

参数说明：
- `-std=c++17`: 使用 C++17 标准
- `-o FileManager`: 生成名为 FileManager 的可执行文件
- 后面是所有需要编译的源文件
- `-lfmt`: 链接 fmt 库（用于格式化输出）

### 3. 运行项目

编译成功后，运行生成的可执行文件：

```cmd
FileManager.exe
```

## 三、可能遇到的问题及解决方案

### 1. 找不到头文件或库文件

如果编译时提示找不到头文件或库文件，可能是因为：
- 路径设置不正确
- 缺少必要的库文件（如 fmt 库）

解决方案：
- 确保所有源文件都在同一目录下
- 如果缺少 fmt 库，可以下载并安装：
  1. 下载 fmt 库：https://fmt.dev/latest/index.html
  2. 将库文件添加到编译命令中

### 2. 编译错误

如果遇到编译错误，仔细查看错误信息，通常会提示具体的错误位置和原因。常见的错误包括：
- 语法错误
- 变量未声明
- 函数调用错误

解决方案：
- 根据错误信息修改代码
- 如果不确定如何解决，可以将错误信息告诉我，我会帮助你分析

### 3. 运行错误

如果运行时出现错误，可能是因为：
- 程序逻辑错误
- 资源文件缺失
- 权限问题

解决方案：
- 检查程序逻辑
- 确保所有必要的资源文件都存在
- 尝试以管理员身份运行程序