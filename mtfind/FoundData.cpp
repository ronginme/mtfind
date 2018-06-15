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

Position::Position(size_t lineNum, size_t columnNum)
{
  this->lineNum = lineNum;
  this->columnNum = columnNum;
}

Position::Position(const Position & src)
{
  lineNum = src.lineNum;
  columnNum = src.columnNum;
}

Position & Position::operator=(const Position & src)
{
  lineNum = src.lineNum;
  columnNum = src.columnNum;
  return *this;
}
