#pragma once

#include <fstream>
#include <boost/thread.hpp>
#include "FoundDataStorage.h"

enum WaitMode
{
  NO_WAIT,
  WAIT_ENDING,
};

class FindData
{
private:
  boost::mutex mtx_;
  std::map<size_t, std::string> buffer_;
  std::string filename_;
  std::string mask_;
  std::ifstream in_;
  FoundDataStorage foundData_;

  static void ReadThread(void* arg);
  static void CheckThread(void* arg);
  static void CheckDispatchThread(void* arg);

  void AlterMaskToRegex();
public:
  FindData(const char* filename, const char* mask);
  ~FindData();
  void BeginFinding(WaitMode mode);
  const FoundDataStorage* GetFound() const;
};
