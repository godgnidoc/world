#ifndef __WORLD_H__
#define __WORLD_H__

#include "world/object.h"
#include <map>

namespace world {

struct World {
  std::map<size_t, Object> objects;

  void Update(Num dt) {
    for (auto& [id, obj] : objects) {
      obj.Update(dt);
    }
  }
};

} // namespace world

#endif