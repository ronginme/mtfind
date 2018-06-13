#include "FoundData.h"

FoundData::FoundData(size_t lineNum, size_t columnNum, std::string data)
{
  this->lineNum = lineNum;
  this->columnNum = columnNum;
  this->data = data;
}

FoundData::FoundData(const FoundData & src)
{
  lineNum = src.lineNum;
  columnNum = src.columnNum;
  data = src.data;
}

FoundData & FoundData::operator=(const FoundData & src)
{
  lineNum = src.lineNum;
  columnNum = src.columnNum;
  data = src.data;
  return *this;
}