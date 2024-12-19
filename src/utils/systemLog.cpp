#include "systemLog.h"

void systemLog(const QString &message, const char *file, int line)
{
    QString fileName = QString(file).split('\\').last().split('.').first();
    QString debugMessage = QString("[%1:%2] %3").arg(fileName, QString::number(line), message);
    qDebug().noquote() << debugMessage;
}

#define SYSTEMLog(message) systemLog(message, __FILE__, __LINE__)
