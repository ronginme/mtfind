#include <iostream>
#include "FindData.h"
#include "SubstringSeeker.h"

#define THREADCOUNT 20
#define QUEUELENGTH 200000

void FindData::ReadThread(FindData * obj)
{
  obj->in_.open(obj->filename_.c_str());
  if (obj->in_.fail())
  {
    std::cout << "File " << obj->filename_ << " not found." << std::endl;
    return;
  }

  std::string line;
  std::deque<FoundData> buffer;
  size_t lineIndex = 0;
  boost::thread threads[THREADCOUNT];
  obj->threadCount_ = 0;

  while (!getline(obj->in_, line).eof())
  {
    {
      boost::lock_guard<boost::mutex> guard(obj->mtx_);
      buffer.push_back(FoundData(++lineIndex, 0, line));
    }

    if (buffer.size() >= QUEUELENGTH && obj->threadCount_ < THREADCOUNT)
    {
      (threads[obj->threadCount_++] = boost::thread(CheckThread, obj, &buffer));
    }
  }
  obj->in_.close();

  if (!buffer.empty())
  {
    boost::thread th{ CheckThread , obj, &buffer };
    while(!buffer.empty())
      boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
  }
}

void FindData::CheckThread(FindData * obj, std::deque<FoundData> * data)
{
  std::deque<FoundData> fileData;
  {
    boost::lock_guard<boost::mutex> guard(obj->mtx_);
    fileData = *data;
    data->clear();
  }

  for (auto data : fileData)
  {
    auto res = SubstringSeeker::AllMatchesByMask(obj->mask_, data);
    for (auto r : res)
    {
      boost::lock_guard<boost::mutex> guard(obj->mtx_);
      obj->foundData_.emplace(Position(r.lineNum, r.columnNum),r.data);
    }
  }
  --obj->threadCount_;
}

void FindData::AlterMaskToRegex()
{
  auto pos = mask_.find("?");
  while (pos != std::string::npos)
  {
    mask_[pos] = '.';
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
}

void FindData::BeginFinding(WaitMode mode)
{
  boost::thread readThread{ ReadThread, this };
  if (mode == WAIT_ENDING)
  {
    readThread.join();
  }
}

const std::map<Position, std::string> & FindData::GetFound() const
{
  return foundData_;
}