#ifndef _NEVIL_GRANDPARENT_ARENA_HPP_
#define _NEVIL_GRANDPARENT_ARENA_HPP_

#include "nevil/arena/arena.hpp"
#include "nevil/arena/light.hpp"
#include "nevil/arena/switch.hpp"

#include "nevil/grandparent_individual.hpp"
#include "nevil/grandparent_robot.hpp"


namespace nevil
{
  class grandparent_arena : public arena
  {
  public:
    grandparent_arena(int size_x, int size_y, const Enki::Color &arena_color = Enki::Color(0.9, 0.9, 0.9));
    virtual ~grandparent_arena();

    void set_individuals(nevil::grandparent_individual *child
      , nevil::grandparent_individual *parent
      , nevil::grandparent_individual *grandparent);
    bool update();
  };
}
#endif // _NEVIL_GRANDPARENT_ARENA_HPP_
