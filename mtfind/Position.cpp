#include "Position.h"

bool Position::operator<(const Position & src) const
{
  return Line < src.Line;
}
