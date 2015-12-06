#ifndef _NEVIL_GRANDPARENT_ROBOT_HPP_
#define _NEVIL_GRANDPARENT_ROBOT_HPP_


#include "nevil/arena/robot.hpp"
#include "nevil/robot_controller/basic_feedforward_nn.hpp"
#include "nevil/grandparent_individual.hpp"

namespace nevil
{
  class grandparent_robot : public robot
  {
  public:
    grandparent_robot();
    grandparent_robot(double x, double y, double angle, bool has_parent
      , bool has_grandparent, const std::string &robot_name, const Enki::Color &color);

    nevil::grandparent_robot *clone() const;
    bool update(const nevil::object_list &objects);
    void set_individual(nevil::individual *i);

  protected:
    bool _has_parent;
    bool _has_grandparent;
    nevil::grandparent_individual *_individual;
    nevil::basic_feedforward_nn _neural_network;
  };
}



#endif // _NEVIL_GRANDPARENT_ROBOT_HPP_