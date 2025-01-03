// !!! 废弃 原生qDebug已经实现了很多功能 仅用作学习

#include "Logger.h"

void log(const QString &message, const char *file, int line)
{
    QString fileName = QString(file).split('\\').last().split('.').first();
    QString debugMessage = QString("[%1:%2] %3").arg(fileName, QString::number(line), message);
    qDebug().noquote() << debugMessage;
}

Logger::Logger(const char *file, int line) : m_file(file), m_line(line), m_message("")
{
}

Logger::~Logger()
{
    log(m_message, m_file, m_line);
}

Logger &Logger::operator<<(const QString &message)
{
    m_message = m_message.isEmpty() ? message : m_message + " " + message;
    return *this;
}
