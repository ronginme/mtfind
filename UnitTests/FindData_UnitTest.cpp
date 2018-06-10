#include "pch.h"

#include "../mtfind/Position.h"
#include "../mtfind/Position.cpp"
#include "../mtfind/FoundDataStorage.h"
#include "../mtfind/FoundDataStorage.cpp"
#include "../mtfind/FindData.h"
#include "../mtfind/FindData.cpp"

TEST(FileDataTest, AlterMaskTest) {
  FindData fd("", "?,?,?");
  //EXPECT_TRUE(fd.mask_.compare(""));
}