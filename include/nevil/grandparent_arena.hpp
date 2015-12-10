#ifndef _NEVIL_GRANDPARENT_ARENA_HPP_
#define _NEVIL_GRANDPARENT_ARENA_HPP_

#include "nevil/util/parser.hpp"
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
    grandparent_arena();
    explicit grandparent_arena(const nevil::args &cl_args);

    void set_individuals(nevil::grandparent_individual *child
      , nevil::grandparent_individual *parent
      , nevil::grandparent_individual *grandparent);
    bool update();

  protected:
    bool _has_parent;
    bool _has_grandparent;
  };
}
#endif // _NEVIL_GRANDPARENT_ARENA_HPP_
