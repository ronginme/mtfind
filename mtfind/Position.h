#pragma once

struct Position
{
  size_t Line;
  size_t Column;
  bool operator<(const Position& src) const;
};

