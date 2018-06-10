#include "pch.h"

#include "../mtfind/SubstringSeeker.h"
#include "../mtfind/SubstringSeeker.cpp"

TEST(SubstringSeekerTest, FoundColumnIndexTest) {

  Position pos;
  std::string str = "1";
  SubstringSeeker::FoundByRegexMask("1", pos, str);
  EXPECT_EQ(pos.Column, 1);

  Position pos1;
  std::string str1 = "0 1";
  SubstringSeeker::FoundByRegexMask("1", pos1, str1);
  EXPECT_EQ(pos1.Column, 3);

  Position pos2;
  std::string str2 = "000 a12";
  SubstringSeeker::FoundByRegexMask(".12", pos2, str2);
  EXPECT_EQ(pos2.Column, 5);

  Position pos3;
  std::string str3 = "000 a12";
  SubstringSeeker::FoundByRegexMask("a1.", pos3, str3);
  EXPECT_EQ(pos3.Column, 5);

  Position pos4;
  std::string str4 = "000 a12 a12";
  SubstringSeeker::FoundByRegexMask("a1.", pos4, str4);
  EXPECT_EQ(pos4.Column, 5);
}

TEST(SubstringSeekerTest, FoundStringTest) {

  Position pos;
  std::string str = "1";
  SubstringSeeker::FoundByRegexMask("1", pos, str);
  EXPECT_TRUE(str.compare("1") == 0);

  Position pos1;
  std::string str1 = "0 1";
  SubstringSeeker::FoundByRegexMask("1", pos1, str1);
  EXPECT_TRUE(str1.compare(0, str1.length(), "1") == 0);

  Position pos2;
  std::string str2 = "000 a12";
  SubstringSeeker::FoundByRegexMask(".12", pos2, str2);
  EXPECT_TRUE(str2.compare(0, str2.length(), "a12") == 0);

  Position pos3;
  std::string str3 = "000 a12";
  SubstringSeeker::FoundByRegexMask("a1.", pos3, str3);
  EXPECT_TRUE(str3.compare(0, str3.length(), "a12") == 0);

  Position pos4;
  std::string str4 = "000 a12 a15";
  SubstringSeeker::FoundByRegexMask("a1.", pos4, str4);
  EXPECT_TRUE(str4.compare(0, str4.length(), "a12") == 0);
}