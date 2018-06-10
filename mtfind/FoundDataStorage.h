#pragma once

#include <map>
#include "Position.h"

class FoundDataStorage
{
private:
  std::map<Position, std::string> foundData_;
public:
  FoundDataStorage();
  FoundDataStorage(const FoundDataStorage& src);
  FoundDataStorage& operator=(const FoundDataStorage& src);
  ~FoundDataStorage();

  size_t GetCount() const;
  std::map<Position, std::string> GetData() const;
  void AddFoundData(Position position, std::string data);
};

