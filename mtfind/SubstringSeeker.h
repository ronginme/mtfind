#pragma once

#include "FindData.h"

class SubstringSeeker
{
public:
  static bool FoundByRegexMask(std::string mask, Position& position, std::string& str);
};

