#include "SubstringSeeker.h"
#include <boost/regex.hpp>


bool SubstringSeeker::FoundByRegexMask(std::string mask, Position& position, std::string& str)
{
  boost::smatch matchResults;
  boost::regex regEx(mask);

  auto isMatch = boost::regex_search(str.cbegin(), str.cend(), matchResults, regEx);
  if (isMatch)
  {
    position.Column = str.find(matchResults.str()) + 1;
    str = matchResults.str();
  }
  return isMatch;
}