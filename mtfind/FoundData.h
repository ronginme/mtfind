#pragma once
#include <string>

struct Position
{
  size_t lineNum;
  size_t columnNum;
  Position() {}
  Position(size_t lineNum, size_t columnNum);
  Position(const Position& src);
  Position& operator=(const Position& src);
  bool operator<(const Position& src) const 
  {
    if (this->lineNum == src.lineNum)
      return this->columnNum < src.columnNum;
    else
      return this->lineNum < src.lineNum;
  }
};

struct FoundData
{
  size_t lineNum;
  size_t columnNum;
  std::string data;

  FoundData() {}
  FoundData(size_t lineNum, size_t columnNum, std::string data);
  FoundData(const FoundData& src);
  FoundData& operator=(const FoundData& src);
};

