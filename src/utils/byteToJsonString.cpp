#include "byteToJsonString.h"

QString byteToJsonString(QByteArray data)
{
  QString result = "transfer failed!";
  QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
  if (!jsonDoc.isNull() && jsonDoc.isObject())
  {
    result = QString::fromUtf8(jsonDoc.toJson());
  }
  else
  {
    Log() << "Failed to parse !";
  }
  return result;
}
