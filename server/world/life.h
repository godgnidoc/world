#ifndef __WORLD_LIFE_H__
#define __WORLD_LIFE_H__

#include "world/geo.h"
#include "world/object.h"
#include <vector>

namespace world {

struct Region {
  size_t begin;
  size_t size;
}

struct Brain {
  /**
   * 主要脑容量，混合存储指令和记忆
   */
  std::vector<Num> memory;

  Region instinct;
}

struct Eye : virtual public Brain {
  /**
   * 视觉输入区的起始位置与尺寸
   */
  Region vision;
};

struct Ear : virtual public Brain {
  /**
   * 听觉输入区的起始位置与尺寸
   */
  Region hear;
};

struct Body : virtual public Brain, public Object {
  /**
   * 身体输入区的起始位置与尺寸
   */
  Region body;
};

struct Foot : virtual public Brain {
  /**
   * 移动冲动
   */
  Region move;
};

struct Mouth : virtual public Brain {
  /**
   * 啃咬冲动
   */
  Region bite;
};

struct Life : public Body, public Eye, public Ear, public Foot, public Mouth {};

} // namespace world

#endif