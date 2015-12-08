#ifndef _NEVIL_ARENA_STAGE_LIGHT_HPP_
#define _NEVIL_ARENA_STAGE_LIGHT_HPP_

#include "nevil/arena/object.hpp"

namespace nevil
{
  class stage_light : public object
  {
   public:
    stage_light();
    stage_light(int x, int y, double size_x = 6
      , double size_y = 0.1, double height = 7
      , const Enki::Color &off_color = DEFAULT_OFF_COLOR
      , const Enki::Color &on_color = DEFAULT_ON_COLOR);

    virtual void turn_off();
    
    static const Enki::Color DEFAULT_OFF_COLOR;
    static const Enki::Color DEFAULT_ON_COLOR;
    static const Enki::Color DEFAULT_FULL_ON_COLOR;
  };
}

#endif  // _NEVIL_ARENA_STAGE_LIGHT_HPP_
