#include "nevil/grandparent_arena.hpp"

nevil::grandparent_arena::grandparent_arena(int world_size_x, int world_size_y, const Enki::Color &arena_color)
 : nevil::arena(world_size_x, world_size_y, arena_color)
{
  // TODO: Setup your arena with objects
  const double OBJECT_SIZE_X = 6;
  const double OBJECT_SIZE_Y = 0.1;
  const double OBJECT_HEIGHT = 7;
  const double INITIAL_DEGREE = 0;
  const double MASS = -1;

  //switch A
  _add_object(new nevil::switch_object(world_size_x / 2.0
    , 0
    , OBJECT_SIZE_X
    , OBJECT_SIZE_Y
    , OBJECT_HEIGHT
    , MASS
    , 1));
  
  //switch B
  _add_object(new nevil::switch_object(world_size_x / 2.0
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
  _add_robot(new nevil::grandparent_robot(world_size_x / 2.0
    , world_size_y / 2.0
    , INITIAL_DEGREE
    , "child"
    , Enki::Color(0.0, 0.0, 0.5)));

  // Create a robot named parent with 0 degree angle
  _add_robot(new nevil::grandparent_robot(world_size_x * (2 / 3.0)
    , world_size_y / 2.0
    , INITIAL_DEGREE
    , "parent"
    , Enki::Color(0.0, 0.5, 0.0)));

  // Create a robot named grandparent with 0 degree angle
  _add_robot(new nevil::grandparent_robot(world_size_x * (5 / 6.0)
    , world_size_y / 2.0
    , INITIAL_DEGREE
    , "grandparent"
    , Enki::Color(0.5, 0.0, 0.0)));
}

nevil::grandparent_arena::~grandparent_arena() {}

void nevil::grandparent_arena::set_individuals(nevil::grandparent_individual *child
  , nevil::grandparent_individual *parent
  , nevil::grandparent_individual *grandparent)
{
  _robot_vector[0]->set_individual(child);
  _robot_vector[1]->set_individual(parent);
  _robot_vector[2]->set_individual(grandparent);
}

bool nevil::grandparent_arena::update()
{
  //TODO change this 

  // Updating the environment
  for (auto r : _robot_vector)
  {
    // Turning the switches and lights on based on the position of the robots
    if(r->is_at_switch())
    {
      // Turn on everything
      for (auto o : _object_vector)
        o->turn_on();
      break; // Don't need to check the other robots
    }
  }

  // Updating the robots
  for (auto r : _robot_vector)
    r->update(_object_vector);
  return true;
}


  // // Updating the objects
  // bool is_on_switch_a, is_on_switch_b, is_on_light;
  // bool switch_a_active, switch_b_active;
  // _robot_vector[0]->evaluate_position(is_on_switch_a, is_on_switch_b, is_on_light);
  // _robot_vector[1]->evaluate_position(is_on_switch_a, is_on_switch_b, is_on_light);
  // _robot_vector[2]->evaluate_position(is_on_switch_a, is_on_switch_b, is_on_light);

  // // Turning the switches and lights on based on the position of the robots
  // if(is_on_switch_a)
  // {
  //   // Notify system that switch A has been turned on
  //   switch_a_active = true;

  //   // Change the color of the switchA to ON
  //   _object_vector[0]->turn_on();
  //   // Change the color of the lightA to ON
  //   _object_vector[2]->turn_on();

  //   // are these strictly necessary for grandparent simulation?
  //   //if so, let's make them 100% v. 50% success maybe
  //   //if not, we can just use fitness values
  //   pop[index]->setTurnOnLight(true);
  //   pop[index + pop.size()/3]->setTurnOnLight(true);
  //   pop[index + pop.size()*(2/3)]->setTurnOnLight(true);
  // }

  // if(is_on_switch_b)
  // {
  //   // Notify system that switch B has been turned on
  //   switch_b_active = true;

  //   // Change the color of the switchA to ON
  //   _object_vector[1]->turn_on();
  //   // Change the color of the lightA to ON
  //   _object_vector[2]->turn_on();

  //   // are these strictly necessary for grandparent simulation?
  //   //if so, let's make them 100% v. 50% success maybe
  //   //if not, we can just use fitness values
  //   pop[index]->setTurnOnLight(true);
  //   pop[index + pop.size()/3]->setTurnOnLight(true);
  //   pop[index + pop.size()*(2/3)]->setTurnOnLight(true);
  // }


  // if (is_on_light && switch_a_active && switch_b_active) 
  // {
  //   pop[index]->increase_fitness(1);
  //   pop[index]->setGainedFitness(true);
  // } else if (is_on_light && switch_a_active)
  // {
  //   pop[index]->increase_fitness(0.5);
  //   pop[index]->setGainedFitness(true);
  // } else if (is_on_light && switch_b_active)
  // {
  //   pop[index]->increase_fitness(0.5);
  //   pop[index]->setGainedFitness(true);
  // }