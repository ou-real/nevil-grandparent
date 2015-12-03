#include "nevil/grandparent_robot.hpp"

nevil::grandparent_robot::grandparent_robot()
  : robot()
{}

  // Need 19 inputs for self-care
  // To assign roles of parent-child we need two more neurons
  // To assign grandparent we need 3 more neurons  
nevil::grandparent_robot::grandparent_robot(double x, double y, double angle, bool has_parent, bool has_grandparent, const std::string &robot_name, const Enki::Color &color)
  : robot(x, y, angle, robot_name, color, 18)
  , _has_parent(has_parent)
  , _has_grandparent(has_grandparent)
  , _neural_network(nevil::basic_feedforward_nn(19 + (2 * _has_parent) + _has_grandparent, 2))
{}

void nevil::grandparent_robot::set_individual(nevil::individual *i)
{
  _individual = dynamic_cast<grandparent_individual *> (i);
  _neural_network.set_weights(_individual->get_chromosome());
}

nevil::grandparent_robot *nevil::grandparent_robot::clone() const
{
  // Need to fix this
  return new nevil::grandparent_robot();
}

bool nevil::grandparent_robot::update(const std::vector<object *> &objects)
{
  // Get the sensor information
  std::vector<double> inputs = _get_camera_inputs();

  if (is_at_switch())
  {
    if (this->pos.y < (objects[0]->pos.y + 10) && !objects[0]->is_on())
      _individual->set_turn_on_light_a(true);
    else if (!objects[1]->is_on())
      _individual->set_turn_on_light_b(true);
  }

  if (is_at_light())
  {
    // If both switches are on add 1 fitness
    if (objects[0]->is_on() && objects[1]->is_on())
      _individual->increase_fitness(1);
    // Else give 0.5 fitness because only one of the switches are on.
    else
      _individual->increase_fitness(0.5);
  }

    // Add the bias input
  inputs.push_back(1);

  if (_robot_name == "child")
  {
    if (_has_parent)
    {
      inputs.push_back(1);
      inputs.push_back(0);
    }
    if (_has_grandparent)
      inputs.push_back(0);
  }
  else if (_robot_name == "parent")
  {
    inputs.push_back(0);
    inputs.push_back(1);
    if (_has_grandparent)
      inputs.push_back(0);
  }
  else if (_robot_name == "grandparent")
  {
    inputs.push_back(0);
    inputs.push_back(0);
    inputs.push_back(1);
  }

  // Evaluate the neural network
  auto output = _neural_network.update(inputs);
  // if (_robot_name == "child")
  // {
  //   output[0] /= 2;
  //   output[1] /= 2;
  // }
  // Pass the output of each NN and convert it to motor velocities
  _set_wheels_speed(output[0], output[1]);
  return true;
}