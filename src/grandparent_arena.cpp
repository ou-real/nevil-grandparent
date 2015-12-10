#include "nevil/grandparent_arena.hpp"

nevil::grandparent_arena::grandparent_arena()
  : nevil::arena()
{}

nevil::grandparent_arena::grandparent_arena(const nevil::args &cl_args)
 : nevil::arena(std::stod(cl_args.at("wx")), std::stod(cl_args.at("wy")))
 , _has_parent(cl_args.at("pr") == "true")
 , _has_grandparent(cl_args.at("gp") == "true")
{

  Enki::Color switch_off_color(0.4, 0.0, 1.0);
  Enki::Color switch_on_color(0.9, 1.0, 1.0);

  //switch A
  _add_object("switch A", new nevil::switch_object(
    _world->w * (5/ 8.0)  // x coordinate
    , 0                      // y coordinate
    , 6                      // size x
    , 0.1                    // size y
    , 7                      // height
    , switch_off_color       // Off color
    , switch_on_color));     // On color
  
  //switch B
  _add_object("switch B", new nevil::switch_object(
    _world->w * (5/ 8.0)  // x coordinate
    , _world->h           // y coordinate
    , 6                      // size x
    , 0.1                    // size y
    , 7                      // height
    , switch_off_color       // Off color
    , switch_on_color));     // On color
  
  //light
  _add_object("light", new nevil::light(0, _world->h / 2.0, 0.1, 6));

  //--robots--
  // Create a robot named child with 0 degree angle
  _add_robot(new nevil::grandparent_robot(_world->w / 4.0
    , _world->h / 2.0
    , 0
    , _has_parent
    , _has_grandparent
    , "child"
    , Enki::Color(0.0, 0.0, 0.5)
    , std::stod(cl_args.at("childSpeed"))));

  // Create a robot named parent with 0 degree angle
  if (_has_parent)
  {
    _add_robot(new nevil::grandparent_robot(_world->w / 2.0
      , _world->h / 2.0
      , 0
      , _has_parent
      , _has_grandparent
      , "parent"
      , Enki::Color(0.0, 0.5, 0.0)
      , std::stod(cl_args.at("parentSpeed"))));
  }

  // Create a robot named grandparent with 0 degree angle
  if (_has_grandparent)
  {
    _add_robot(new nevil::grandparent_robot(_world->w * (3 / 4.0)
      , _world->h / 2.0
      , 0
      , _has_parent
      , _has_grandparent
      , "grandparent"
      , Enki::Color(0.9, 0.0, 0.0)
      , std::stod(cl_args.at("grandparentSpeed"))));
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
