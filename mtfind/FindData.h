#pragma once

#include <map>
#include <string>

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
  std::string filename_;
  std::string mask_;
  static void ReadThread(void* arg);
  static void CheckThread(void* arg, void* data);
  FoundData foundData_;
  bool IsMatch(Position& position, std::string data);
public:
  FindData(const char* filename, const char* mask);
  ~FindData();
  void BeginFinding(WaitMode mode);
  const FoundData* GetFound() const;
};

