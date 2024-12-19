#include "systemLog.h"

void log(const QString &message, const char *file, int line)
{
    QString fileName = QString(file).split('\\').last().split('.').first();
    QString debugMessage = QString("[%1:%2] %3").arg(fileName, QString::number(line), message);
    qDebug().noquote() << debugMessage;
}

SystemLogger::SystemLogger(const char *file, int line) : m_file(file), m_line(line), m_message("")
{
}

SystemLogger::~SystemLogger()
{
    log(m_message, m_file, m_line);
}

SystemLogger &SystemLogger::operator<<(const QString &message)
{
    m_message = m_message.isEmpty() ? message : m_message + " " + message;
    return *this;
}

#define SYSTEMLog(...) SystemLogger(__FILE__, __LINE__) << (QString(__VA_ARGS__).isEmpty() ? "" : QString(__VA_ARGS__))
