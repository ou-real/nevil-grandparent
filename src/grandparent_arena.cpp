#include "nevil/grandparent_arena.hpp"

nevil::grandparent_arena::grandparent_arena()
  : nevil::arena()
{}

nevil::grandparent_arena::grandparent_arena(int world_size_x, int world_size_y,bool has_parent, bool has_grandparent)
 : nevil::arena(world_size_x, world_size_y)
 , _has_parent(has_parent)
 , _has_grandparent(has_grandparent)
{

  Enki::Color switch_A_off_color(0.4, 0.0, 1.0);
  Enki::Color switch_A_on_color(0.9, 1.0, 1.0);

  Enki::Color switch_B_off_color(0.6, 0.0, 1.0);
  Enki::Color switch_B_on_color(0.9, 0.5, 1.0);

  //switch A
  _add_object("switch A", new nevil::switch_object(
    world_size_x * (5/ 8.0)  // x coordinate
    , 0                      // y coordinate
    , 6                      // size x
    , 0.1                    // size y
    , 7                      // height
    , switch_A_off_color     // Off color
    , switch_A_on_color));   // On color
  
  //switch B
  _add_object("switch B", new nevil::switch_object(
    world_size_x * (5/ 8.0)  // x coordinate
    , world_size_y           // y coordinate
    , 6                      // size x
    , 0.1                    // size y
    , 7                      // height
    , switch_B_off_color     // Off color
    , switch_B_on_color));   // On color

  //light
  _add_object("light", new nevil::light(0, world_size_y / 2.0, 0.1, 6));

  //--robots--
  // Create a robot named child with 0 degree angle
  _add_robot(new nevil::grandparent_robot(world_size_x / 4.0
    , world_size_y / 2.0
    , 0
    , _has_parent
    , _has_grandparent
    , "child"
    , Enki::Color(0.0, 0.0, 0.5)));

  // Create a robot named parent with 0 degree angle
  if (_has_parent)
  {
    _add_robot(new nevil::grandparent_robot(world_size_x / 2.0
      , world_size_y / 2.0
      , 0
      , _has_parent
      , _has_grandparent
      , "parent"
      , Enki::Color(0.0, 0.5, 0.0)));
  }

  // Create a robot named grandparent with 0 degree angle
  if (_has_grandparent)
  {
    _add_robot(new nevil::grandparent_robot(world_size_x * (3 / 4.0)
      , world_size_y / 2.0
      , 0
      , _has_parent
      , _has_grandparent
      , "grandparent"
      , Enki::Color(0.9, 0.0, 0.0)));
  }
}

void nevil::grandparent_arena::set_individuals(nevil::grandparent_individual *child
  , nevil::grandparent_individual *parent
  , nevil::grandparent_individual *grandparent)
{
  _robots[0]->set_individual(child);
  if (_has_parent)
    _robots[1]->set_individual(parent);
  if (_has_grandparent)
    _robots[2]->set_individual(grandparent);
}

bool nevil::grandparent_arena::update()
{
  nevil::arena::update();
  // Updating the robots
  for (auto r : _robots)
    r->update(_objects);
  return true;
}
