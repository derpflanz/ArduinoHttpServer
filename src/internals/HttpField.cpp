#include "HttpField.h"
#include "Debug.h"

const char* ArduinoHttpServer::HttpField::SEPERATOR = ": ";

ArduinoHttpServer::HttpField::HttpField(const char* fieldLine) :
   m_type(TYPE_NOT_SUPPORTED),
   m_value()
{

   DEBUG_PRINT("Parsing HTTP field: ");
   DEBUG_PRINTLN(fieldLine);

   String fieldStr(fieldLine);
   int fieldSepIndex( fieldStr.indexOf(SEPERATOR) );

   if( fieldSepIndex < 1 )
   {
      m_type = TYPE_NOT_SUPPORTED;
   }
   else
   {
      m_value = fieldStr.substring(fieldSepIndex + strlen(SEPERATOR));
      String typeStr = fieldStr.substring(0, fieldSepIndex);
      determineType(typeStr);

   }
}

ArduinoHttpServer::HttpField::HttpField() :
   m_type(TYPE_NOT_SUPPORTED),
   m_value()
{
}

ArduinoHttpServer::HttpField::~HttpField()
{

}

void ArduinoHttpServer::HttpField::determineType(const String& typeStr)
{
   if (typeStr.equalsIgnoreCase("Content-Type"))
   {
      m_type = TYPE_CONTENT_TYPE;
   }
   else if (typeStr.equalsIgnoreCase("Content-Length"))
   {
      m_type = TYPE_CONTENT_LENGTH;
   }
   else if (typeStr.equalsIgnoreCase("User-Agent"))
   {
      m_type = TYPE_USER_AGENT;
   }
}

ArduinoHttpServer::HttpField& ArduinoHttpServer::HttpField::operator=(const ArduinoHttpServer::HttpField& other)
{
   m_type = other.m_type;
   m_value = other.m_value;
}

const ArduinoHttpServer::HttpField::TypeEnum ArduinoHttpServer::HttpField::getType() const
{
   return m_type;
}
