#include <iostream>
#include "FindData.h"
#include "SubstringSeeker.h"

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
        if (SubstringSeeker::FoundByRegexMask(obj->mask_, pos, item.second))
          obj->foundData_.AddFoundData(pos, item.second);

        obj->buffer_.erase(item.first);
      }
    }
  }
}

void FindData::CheckDispatchThread(void * arg)
{
  FindData* obj = (FindData*)arg;
  const int threadCount = 10;
  boost::thread_group checkGrp;
  for (auto i = 0; i < threadCount; ++i)
    checkGrp.create_thread( boost::bind(CheckThread, obj));

  checkGrp.join_all();
}

void FindData::AlterMaskToRegex()
{
  auto pos = mask_.find("?");
  while (pos != std::string::npos)
  {
    mask_ = mask_.replace(pos, pos + 1, ".");
    pos = mask_.find('?', 1);
  }
}

FindData::FindData(const char * filename, const char * mask)
{
  filename_ = filename;
  mask_ = mask;
  AlterMaskToRegex();
}

FindData::~FindData()
{
  buffer_.clear();
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

const FoundDataStorage * FindData::GetFound() const
{
  return &foundData_;
}