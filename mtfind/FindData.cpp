
#include <boost/thread.hpp>
#include <iostream>
#include <fstream>

#include "FindData.h"

void FindData::ReadThread(void * arg)
{
  FindData* obj = (FindData*)arg;
  std::ifstream in(obj->filename_.c_str());
  std::string line;


  while (getline(in, line))
  {
    std::string tmp = line;
    // TODO 
    // 0 if no room in shmem wait.
    // 1 read bytes from file.
    // 2 add bytes to shared memory.
  }
}

void FindData::CheckThread(void * arg, void * data)
{
  // TODO
  // 1 pop bytes from shared memory.
  // 2 check match.
  // 3 if match add foundData.

  FindData* obj = (FindData*)arg;
  std::string line((const char*)data);
  Position pos;
  if (obj->IsMatch(pos, line))
    obj->foundData_.AddFoundData(pos, line);
}

bool FindData::IsMatch(Position& position, std::string data)
{
  position.Line = this->foundData_.GetCount();
  position.Column = 321;
  return true;
}

FindData::FindData(const char * filename, const char * mask)
{
  filename_ = filename;
  mask_ = mask;
}

FindData::~FindData()
{
}

void FindData::BeginFinding(WaitMode mode)
{
  boost::thread readThread{ ReadThread, this };
  if (mode == WAIT_ENDING)
  {
    readThread.join();
  }
}

const FoundData * FindData::GetFound() const
{
  return &foundData_;
}

FoundData::FoundData()
{
}

FoundData::FoundData(const FoundData & src)
{
  std::map<Position, std::string> tmp(src.foundData_);
  foundData_.swap(tmp);
}

FoundData & FoundData::operator=(const FoundData & src)
{
  std::map<Position, std::string> tmp(src.foundData_);
  foundData_.swap(tmp);
  return *this;
}

FoundData::~FoundData()
{
}

size_t FoundData::GetCount() const
{
  return foundData_.size();
}

std::map<Position, std::string> FoundData::GetData() const
{
  std::map<Position, std::string> tmp(foundData_);
  return tmp;
}

void FoundData::AddFoundData(Position position, std::string data)
{
  foundData_.emplace(position, data);
}

bool Position::operator<(const Position & src) const
{
  return Line < src.Line;
}
