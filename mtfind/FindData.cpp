

#include <iostream>
#include <boost/regex.hpp>

#include "FindData.h"

void FindData::ReadThread(void * arg)
{
  FindData* obj = (FindData*)arg;
  obj->in_.open(obj->filename_.c_str());
  if (obj->in_.fail())
  {
    std::cout << "File " << obj->filename_ << " not found." << std::endl;
    return;
  }

  std::string line;
  size_t lineIndex = 0;;
  getline(obj->in_, line);
  while (true)
  {
    {
      boost::lock_guard<boost::mutex> guard(obj->mtx_);
      obj->buffer_.emplace(++lineIndex, line);

      if (obj->in_.eof())
      {
        obj->in_.close();
        break;
      }
      getline(obj->in_, line);
    }
  }
}

void FindData::CheckThread(void * arg)
{
  FindData* obj = (FindData*)arg;

  while (true)
  {
    {
      boost::lock_guard<boost::mutex> guard(obj->mtx_);
      bool isOpened = obj->in_.is_open();
      bool isBufferEmpty = obj->buffer_.empty();

      if (!isOpened && isBufferEmpty)
      {
        break;
      }

      if (!isBufferEmpty)
      {
        auto &item = *(obj->buffer_.rbegin());
        Position pos;
        pos.Line = item.first;
        if (MatchChecker::IsMatchByMask(obj->mask_, pos, item.second))
          obj->foundData_.AddFoundData(pos, item.second);

        obj->buffer_.erase(item.first);
      }
    }
  }
}

void FindData::CheckDispatchThread(void * arg)
{
  FindData* obj = (FindData*)arg;
  boost::thread checkThread{ CheckThread, obj };
  checkThread.join();
}

FindData::FindData(const char * filename, const char * mask)
{
  filename_ = filename;
  mask_ = mask;

  auto pos = mask_.find("?");
  while (pos != std::string::npos)
  {
    mask_ = mask_.replace(pos, pos + 1, ".");
    pos = mask_.find('?', 1);
  }
}

FindData::~FindData()
{
}

void FindData::BeginFinding(WaitMode mode)
{
  boost::thread readThread{ ReadThread, this };
  boost::thread checkDispThread{ CheckDispatchThread, this };
  if (mode == WAIT_ENDING)
  {
    readThread.join();
    checkDispThread.join();
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

bool MatchChecker::IsMatchByMask(std::string mask, Position& position, std::string& str)
{

  std::string Mask = mask;
  std::string Str = str;

  boost::smatch matchResults;
  boost::regex regEx(Mask);

  auto isMatch = boost::regex_search(Str.cbegin(), Str.cend(), matchResults, regEx);
  if (isMatch)
  {
    position.Column = str.find(matchResults.str());
    str = matchResults.str();
  }
  return isMatch;
}
