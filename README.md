# QT 智慧农业监控系统 iams

## 简介

个人正在接受学校安排的粤嵌物联网传输层实训，因此使用这个仓库来存放我的代码。

QT 版本为 5.14.2，使用 vscode 编写代码，使用qmake进行编译，使用 QtCreator 进行 UI 设计 与新建各种组件。

仓库内容不仅限于粤嵌的实训内容，还进行了各种拓展。

可供学习使用。

免责声明：个人并不熟悉 c++ 与 QT，只在实训开始时才开始接触，主要擅长的是JavaScript生态，因此可能会出现一些错误。

## 如何运行

1. 安装 QT 开发环境，参考 [链接](https://download.qt.io/archive/qt/5.14/5.14.2/)
2. 克隆仓库
3. 运行
   - 在 QtCreator 中打开 iams.pro 文件直接运行
   - 在 VSCode 中打开
     1. 需要修改 [c_cpp_properties.json](.vscode/c_cpp_properties.json) 文件，将 Qt 的路径替换为你的 Qt 路径
     2. 需要修改 [launch.json](.vscode/launch.json) 文件，将 Qt 的路径替换为你的 Qt 路径
     3. 之后选择 终端 -> 运行任务 选择要运行的任务即可，任务定义在 [tasks.json](.vscode/tasks.json) 文件中
