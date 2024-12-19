#include <QDebug>
#include <QFile>

void systemLog(const QString &message, const char *file, int line);

#define SYSTEMLog(message) systemLog(message, __FILE__, __LINE__)
