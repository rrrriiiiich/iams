#include "byteToJsonString.h"

QString byteToJsonString(QByteArray data)
{
  QString result;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
  if (!jsonDoc.isNull() && jsonDoc.isObject())
  {
    result = QString::fromUtf8(jsonDoc.toJson());
    return result;
  }
  else
  {
    SYSTEMLog() << "Failed to parse !";
  }
}
