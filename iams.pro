# 添加核心、图形界面和窗口小部件模块
QT += core gui widgets

# 启用 C++17 标准
CONFIG += c++17

# 在 Windows 平台上，设置编译器选项以支持 UTF-8 编码
win32-msvc*:QMAKE_CXXFLAGS += /utf-8

# 注释掉了设置应用程序清单文件的代码，该文件用于指定 Windows 应用程序的属性，如管理员权限和 UI 访问权限
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

# 指定源文件路径
SOURCES += \
    src/main.cpp \
    src/iams.cpp \
    src/second.cpp

# 自动包含 src 目录下的所有头文件
HEADERS += \
    $$files($$PWD/src/*.h)

# 指定 UI 文件路径
FORMS += $$PWD/src/iams.ui \
    src/second.ui

# 设置默认的部署规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

# 如果目标路径不为空，则将可执行文件安装到目标路径
!isEmpty(target.path): INSTALLS += target

# 指定资源文件路径
RESOURCES += \
    pic.qrc
