把我的分支合并到你们的分支 然后在你们的分支提交修改 不要在我的分支提交!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# FileManagerSystem 项目说明

## 项目概览
`FileManagerSystem` 是一个基于 C++ 的终端文件管理模拟器，通过命令行交互在内存中动态维护一棵目录/文件树。项目以 `C:` 作为虚拟根目录，用户可使用类 CMD 命令体验目录切换、文件夹/文件创建与删除等操作，主要用于演示树形数据结构与路径解析的综合应用。

## 核心模块
- `Main.cpp`：程序入口，仅启动 `CMDManager::Run()`。
- `CMDManager`：命令调度中心。负责：
  - 解析用户输入，将指令拆分为 token。
  - 维护命令表（`mkdir/md`、`create/touch`、`delete/del`、`goto/cd`、`cls/clear`、`help`、`quit`）。
  - 控制终端刷新与输出缓存（`CONTENT`），并与 `FileManager` 交互。
- `FileManager`：文件系统内核。职责：
  - 管理当前目录、路径映射（`pathMap`）、以及根节点 `C:`。
  - 提供目录/文件创建、删除、跳转等接口，并把执行结果回传给 `CMDManager`。
  - 借助 `DirectoryNode`/`FileNode` 操作树结构，确保路径唯一性。
- `TreeNode / DirectoryNode / FileNode`：
  - `TreeNode` 抽象出节点公共信息（名称、路径、类型、大小）。
  - `DirectoryNode` 维护子节点列表，支持增删与展示（格式化输出表格）。
  - `FileNode` 代表具体文件，结合扩展名决定 `TreeNodeType`。
- `TreeNodeType`：集中定义受支持的文件类型及扩展名映射，便于展示与类型判断。
- `PathUtils`：路径工具库，实现连接、规范化（含 `.`、`..` 处理）、拆分、扩展名提取、绝对路径判断等功能，是跨模块复用的基础组件。

## 运行方式
1. 使用 Visual Studio 或 `msbuild` 生成 `FileManagerSystem.sln`。
2. 运行可执行文件后，终端会提示输入命令，常用示例：
   - `md projects`：在当前目录创建文件夹。
   - `create report.txt`：在当前目录创建文件。
   - `create design.docx C:\work`：在指定路径创建文件（自动解析绝对/相对路径）。
   - `cd ..` 或 `cd C:\work`：切换目录。
   - `delete C:\work\report.txt`：删除文件或目录。
   - `help`：查看命令一览。
3. 所有结构均保存在内存，不会操作真实磁盘；输入 `quit` 结束程序。

## 数据结构与路径策略
- 每个节点在 `DirectoryNode::AddChild` 时会注册到 `FileManager::pathMap`，实现 O(1) 级别的路径查询、删除与跳转。
- `PathUtils::normalize` 统一处理分隔符、`..`、`.` 与冗余反斜杠，确保命令输入的健壮性。
- `FileManager` 会在所有路径入口调用 `getAbsolutePath()`，允许用户混用绝对、相对与根相对（`\foo`）写法。

## 与同类实现的差异对比
| 维度 | FileManagerSystem | 同类实现（如直接操作真实文件系统的 CLI / 简化脚本方案） |
| --- | --- | --- |
| 效率 | 完全驻留内存，`pathMap` 查找为 O(1)，命令执行即时返回；不涉及磁盘 IO，核心逻辑测试成本低。 | 真实 CLI 需落盘并触发权限校验，脚本方案常缺少索引结构；对大量节点操作时更容易受磁盘/系统调度影响。 |
| 效果 | 通过 `DirectoryNode::Show()` 格式化输出、命令别名和路径自动规范化，体验接近 CMD，同时便于教学演示。 | 真实 CLI 功能全但难以调试内部状态；脚本 demo 往往输出简单、不支持多类型展示，交互反馈有限。 |
| 作用 | 聚焦树结构、路径解析与命令分发的教学示例，可安全复现边界场景，兼具实验与原型搭建用途。 | 实际文件管理器更偏向生产使用，无法在不影响磁盘的前提下随意实验；脚本示例通常只覆盖局部概念，难以串联完整流程。 |
| 优势 | 模块化清晰（命令层/核心层/数据结构/工具层），`TreeNodeType` 丰富展示信息，易扩展出新命令或持久化方案。 | 传统 CLI 改动成本高；脚本方案耦合度大、类型体系单一，二次开发或嵌入其他项目的难度更高。 |

## 扩展建议
- 引入持久化层：将树结构序列化到文件，支持下次启动恢复。
- 丰富命令集：如 `rename`、`copy`、`move`、`tree`、`search` 等。
- 增加权限与尺寸模拟：为文件写入虚拟大小或权限位，增强展示信息。
- 编写单元测试：对 `PathUtils`、`TreeNode`、`FileManager` 等核心逻辑进行自动化验证。

## 文件结构（关键部分）
```
FileManagerSystem1/
├─ FileManagerSystem.sln
└─ FileManagerSystem/
   ├─ Main.cpp
   ├─ CMDManager.{h,cpp}
   ├─ FileManager.{h,cpp}
   ├─ PathUtils.{h,cpp}
   ├─ TreeNode.{h,cpp}
   └─ TreeNodeType.{h,cpp}
```

通过上述模块协作，项目展示了一个轻量、可扩展的命令行文件系统模拟实现，可作为学习 C++ 面向对象设计与命令解析的示例工程。

