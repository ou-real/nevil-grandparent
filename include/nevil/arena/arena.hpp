#ifndef _NEVIL_ARENA_ARENA_HPP_
#define _NEVIL_ARENA_ARENA_HPP_

#include <memory>
#include <vector>
#include "nevil/arena/object.hpp"
#include "nevil/arena/robot.hpp"

namespace nevil
{
  class arena
  {
   public:
    arena();
    arena(int size_x, int size_y, const Enki::Color &color = Enki::Color(0.9, 0.9, 0.9));
    arena(const nevil::arena &rhs);
    arena(nevil::arena &&rhs) noexcept;
    virtual ~arena();

    virtual bool update();
    virtual bool reset();

    Enki::World* get_world() const;
    nevil::arena &operator=(const nevil::arena &rhs);
    nevil::arena &operator=(nevil::arena &&rhs) noexcept;

   protected:
    void _add_object(nevil::object *o);
    void _add_robot(nevil::robot *r);

    std::unique_ptr<Enki::World> _world;
    std::vector<robot*> _robot_vector;
    std::vector<object*> _object_vector;
  };
}
#endif  // _NEVIL_ARENA_ARENA_HPP_
