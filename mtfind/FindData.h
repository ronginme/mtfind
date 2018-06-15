#pragma once

#include <map>
#include <deque>
#include <fstream>
#include <boost/thread.hpp>

#include "FoundData.h"

enum WaitMode
{
  NO_WAIT,
  WAIT_ENDING,
};

class FindData
{
private:
  boost::mutex mtx_;
  size_t threadCount_;
  std::map<Position, std::string> foundData_;
  std::ifstream in_;
  std::string filename_;
  std::string mask_;

  static void ReadThread(FindData * obj);
  static void CheckThread(FindData * obj, std::deque<FoundData> * data);

  void AlterMaskToRegex();
public:
  FindData(const char* filename, const char* mask);
  ~FindData();
  void BeginFinding(WaitMode mode);
  const std::map<Position, std::string> & GetFound() const;
};
