// !!! 废弃 原生qDebug已经实现了很多功能 仅用作学习

#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H

#include <QString>
#include <QDebug>
#include <QVariant>

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

  /**
   * @brief 模板函数，用于处理任何可以转换为QString的类型
   * @tparam T 类型参数
   * @param value 要追加的值
   * @return SystemLogger& 返回自身引用以支持链式调用
   */
  template <typename T>
  SystemLogger &operator<<(const T &value)
  {
    QVariant var(value);
    QString strValue;

    // 检查是否可以转换为QString
    if (var.canConvert<QString>())
    {
      strValue = var.toString();
    }
    else if (var.canConvert<int>())
    {
      strValue = QString::number(var.toInt());
    }
    else if (var.canConvert<double>())
    {
      strValue = QString::number(var.toDouble());
    }
    else if (var.canConvert<qlonglong>())
    {
      strValue = QString::number(var.toLongLong());
    }
    else if (var.canConvert<qulonglong>())
    {
      strValue = QString::number(var.toULongLong());
    }
    else
    {
      // 对于无法直接转换为QString的类型，使用qDebug()输出并转换为QString
      qDebug() << "[SystemLog] ：" << value;
    }

    m_message = m_message.isEmpty() ? strValue : m_message + " " + strValue;

    return *this;
  }

private:
  const char *m_file; ///< 源文件名
  int m_line;         ///< 代码行号
  QString m_message;  ///< 累积的日志消息
};

/**
 * @brief 日志宏,用于简化日志调用
 */
#define Log(...) SystemLogger(__FILE__, __LINE__) << (QString(__VA_ARGS__).isEmpty() ? "" : QString(__VA_ARGS__))

#endif // SYSTEMLOG_H
