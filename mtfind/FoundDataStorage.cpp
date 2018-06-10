#include "FoundDataStorage.h"


FoundDataStorage::FoundDataStorage()
{
}

FoundDataStorage::FoundDataStorage(const FoundDataStorage & src)
{
  std::map<Position, std::string> tmp(src.foundData_);
  foundData_.swap(tmp);
}

FoundDataStorage & FoundDataStorage::operator=(const FoundDataStorage & src)
{
  std::map<Position, std::string> tmp(src.foundData_);
  foundData_.swap(tmp);
  return *this;
}

FoundDataStorage::~FoundDataStorage()
{
}

size_t FoundDataStorage::GetCount() const
{
  return foundData_.size();
}

std::map<Position, std::string> FoundDataStorage::GetData() const
{
  std::map<Position, std::string> tmp(foundData_);
  return tmp;
}

void FoundDataStorage::AddFoundData(Position position, std::string data)
{
  foundData_.emplace(position, data);
}
