#include "SubstringSeeker.h"
#include <boost/regex.hpp>


std::deque<FoundData> SubstringSeeker::AllMatchesByMask(std::string mask, FoundData fd)
{
  boost::smatch matchResults;
  boost::regex regEx(mask);
  std::deque<FoundData> res;
  std::string str = fd.data;

  while (boost::regex_search(str, matchResults, regEx))
  {
    for (auto match : matchResults)
    {
      auto str = match.str();
      FoundData tmpFd(fd.lineNum, fd.data.find(str) + 1, str);
      res.push_back(tmpFd);

    }
    str = matchResults.suffix().str();
  }
  return res;
}
