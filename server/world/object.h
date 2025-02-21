#ifndef __WORLD_OBJECT_H__
#define __WORLD_OBJECT_H__

#include "world/geo.h"

#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace world {

struct Object {
  std::vector<Vec> vertexs;
  std::vector<Num> hardness;
  Vec pos{};
  Vec vel{};
  Vec acc{};
  Num rad{};
  Num radv{};
  Num rada{};
};

} // namespace world

#endif