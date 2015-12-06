#include "nevil/grandparent_arena.hpp"

nevil::grandparent_arena::grandparent_arena()
  : nevil::arena()
{}

nevil::grandparent_arena::grandparent_arena(int world_size_x, int world_size_y,bool has_parent, bool has_grandparent)
 : nevil::arena(world_size_x, world_size_y)
 , _has_parent(has_parent)
 , _has_grandparent(has_grandparent)
{
  //switch A
  _add_object("switch A", new nevil::switch_object(world_size_x * (5/ 8.0), 0));
  
  //switch B
  _add_object("switch B", new nevil::switch_object(world_size_x * (5/ 8.0), world_size_y));
  
  //light
  _add_object("light", new nevil::light(0, world_size_y / 2.0, 6, 0.1));

  //--robots--
  // Create a robot named child with 0 degree angle
  _add_robot(new nevil::grandparent_robot(world_size_x / 4.0
    , world_size_y / 2.0
    , INITIAL_DEGREE
    , _has_parent
    , _has_grandparent
    , "child"
    , Enki::Color(0.0, 0.0, 0.5)));

  // Create a robot named parent with 0 degree angle
  if (_has_parent)
  {
    _add_robot(new nevil::grandparent_robot(world_size_x / 2.0
      , world_size_y / 2.0
      , INITIAL_DEGREE
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
      , INITIAL_DEGREE
      , _has_parent
      , _has_grandparent
      , "grandparent"
      , Enki::Color(0.5, 0.0, 0.0)));
  }
}

void nevil::grandparent_arena::set_individuals(nevil::grandparent_individual *child
  , nevil::grandparent_individual *parent
  , nevil::grandparent_individual *grandparent)
{
  _robot_vector[0]->set_individual(child);
  if (_has_parent)
    _robot_vector[1]->set_individual(parent);
  if (_has_grandparent)
    _robot_vector[2]->set_individual(grandparent);
}

bool nevil::grandparent_arena::update()
{
  nevil::arena::update();
  // Updating the environment
  for (auto r : _robot_vector)
  {
    // Turning the switches and lights on based on the position of the robots
    if(r->is_at(_objects["switch A"], OFF))
    {
      _objects["switch A"]->turn_on();
      _objects["light"]->turn_on();
    }

    if(r->is_at(_objects["switch B"], OFF))
    {
      _objects["switch B"]->turn_on();
      _objects["light"]->turn_on();
    }
  }

  // Updating the robots
  for (auto r : _robot_vector)
    r->update(_object_vector);
  return true;
}