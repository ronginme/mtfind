#pragma once
#include <string>

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

