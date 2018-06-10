#pragma once

#include <map>
#include <string>
#include <deque>
#include <fstream>
#include <boost/thread.hpp>

enum WaitMode
{
  NO_WAIT,
  WAIT_ENDING,
};

struct Position
{
  size_t Line;
  size_t Column;
  bool operator<(const Position& src) const;
};

class FoundData
{
private:
  std::map<Position, std::string> foundData_;
public:
  FoundData();
  FoundData(const FoundData& src);
  FoundData& operator=(const FoundData& src);
  ~FoundData();
  size_t GetCount() const;
  std::map<Position, std::string> GetData() const;
  void AddFoundData(Position position, std::string data);
};

class FindData
{
private:
  boost::mutex mtx_;
  std::map<size_t, std::string> buffer_;
  std::string filename_;
  std::string mask_;
  std::ifstream in_;
  static void ReadThread(void* arg);
  static void CheckThread(void* arg);
  static void CheckDispatchThread(void* arg);

  FoundData foundData_;
public:
  FindData(const char* filename, const char* mask);
  ~FindData();
  void BeginFinding(WaitMode mode);
  const FoundData* GetFound() const;
};

class MatchChecker 
{
public:
  static bool IsMatchByMask(std::string mask, Position& position, std::string& str);
};
