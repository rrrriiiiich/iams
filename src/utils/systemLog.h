#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H

#include <QString>
#include <QDebug>

/**
 * @brief 输出日志信息到控制台
 * @param message 日志消息内容
 * @param file 源文件名
 * @param line 代码行号
 */
void log(const QString &message, const char *file, int line);

/**
 * @brief 系统日志记录器类
 *
 * 用于格式化输出系统日志,支持流式语法
 */
class SystemLogger
{
public:
  /**
   * @brief 构造函数
   * @param file 源文件名
   * @param line 代码行号
   */
  SystemLogger(const char *file, int line);

  /**
   * @brief 析构函数,输出累积的日志信息
   */
  ~SystemLogger();

  /**
   * @brief 重载流式操作符
   * @param message 要追加的日志消息
   * @return SystemLogger& 返回自身引用以支持链式调用
   */
  SystemLogger &operator<<(const QString &message);

private:
  const char *m_file; ///< 源文件名
  int m_line;         ///< 代码行号
  QString m_message;  ///< 累积的日志消息
};

/**
 * @brief 日志宏,用于简化日志调用
 */
#define SYSTEMLog(...) SystemLogger(__FILE__, __LINE__) << (QString(__VA_ARGS__).isEmpty() ? "" : QString(__VA_ARGS__))

#endif // SYSTEMLOG_H
