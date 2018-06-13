#pragma once

#include <queue>
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
  std::deque<FoundData> foundData_;
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
  const std::deque<FoundData> & GetFound() const;
};
