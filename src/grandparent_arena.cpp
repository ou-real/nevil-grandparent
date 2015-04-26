#include "nevil/grandparent_arena.hpp"

nevil::grandparent_arena::grandparent_arena(int world_size_x, int world_size_y, bool has_grandparent, const Enki::Color &arena_color)
 : nevil::arena(world_size_x, world_size_y, arena_color)
 , _has_grandparent(has_grandparent)
{
  // TODO: Setup your arena with objects
  const double OBJECT_SIZE_X = 6;
  const double OBJECT_SIZE_Y = 0.1;
  const double OBJECT_HEIGHT = 7;
  const double INITIAL_DEGREE = 0;
  const double MASS = -1;

  //switch A
  _add_object(new nevil::switch_object(world_size_x * (5/ 8.0)
    , 0
    , OBJECT_SIZE_X
    , OBJECT_SIZE_Y
    , OBJECT_HEIGHT
    , MASS
    , 1));
  
  //switch B
  _add_object(new nevil::switch_object(world_size_x * (5/ 8.0)
    , world_size_y
    , OBJECT_SIZE_X
    , OBJECT_SIZE_Y
    , OBJECT_HEIGHT
    , MASS
    , 1));
  
  //light
  _add_object(new nevil::light(0
    , world_size_y / 2.0
    , OBJECT_SIZE_Y
    , OBJECT_SIZE_X
    , OBJECT_HEIGHT
    , MASS
    , 0.01));

  //--robots--
  // Create a robot named child with 0 degree angle
  _add_robot(new nevil::grandparent_robot(world_size_x / 4.0
    , world_size_y / 2.0
    , INITIAL_DEGREE
    , _has_grandparent
    , "child"
    , Enki::Color(0.0, 0.0, 0.5)));

  // Create a robot named parent with 0 degree angle
  _add_robot(new nevil::grandparent_robot(world_size_x / 2.0
    , world_size_y / 2.0
    , INITIAL_DEGREE
    , _has_grandparent
    , "parent"
    , Enki::Color(0.0, 0.5, 0.0)));

  // Create a robot named grandparent with 0 degree angle
  if (_has_grandparent)
  {
    _add_robot(new nevil::grandparent_robot(world_size_x * (3 / 4.0)
      , world_size_y / 2.0
      , INITIAL_DEGREE
      , _has_grandparent
      , "grandparent"
      , Enki::Color(0.5, 0.0, 0.0)));
  }
}

nevil::grandparent_arena::~grandparent_arena() {}

void nevil::grandparent_arena::set_individuals(nevil::grandparent_individual *child
  , nevil::grandparent_individual *parent
  , nevil::grandparent_individual *grandparent)
{
  _robot_vector[0]->set_individual(child);
  _robot_vector[1]->set_individual(parent);
  if (_has_grandparent)
    _robot_vector[2]->set_individual(grandparent);
}

bool nevil::grandparent_arena::update()
{
  // Updating the environment
  for (auto r : _robot_vector)
  {
    // Turning the switches and lights on based on the position of the robots
    if(r->is_at_switch())
    {
      // If the robot is at the left switch
      if (r->pos.y < _trial_world->w/2)
        _object_vector[0]->turn_on();
      // The robot is at the right switch
      else
        _object_vector[1]->turn_on();
      // Turn on the light
      _object_vector[2]->turn_on();
    }
  }

  // Updating the robots
  for (auto r : _robot_vector)
    r->update(_object_vector);
  return true;
}