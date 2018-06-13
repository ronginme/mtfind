#pragma once

#include "FindData.h"

class SubstringSeeker
{
public:
  static std::deque<FoundData> AllMatchesByMask(std::string mask, FoundData fd);
};

