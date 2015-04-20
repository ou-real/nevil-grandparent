#include "nevil/grandparent_robot.hpp"

nevil::grandparent_robot::grandparent_robot(double x, double y, double angle, const std::string &robot_name, const Enki::Color &color)
: robot(x, y, angle, robot_name, color)
{
  _neural_network = nevil::basic_feedforward_nn(19, 2);
}

nevil::grandparent_robot::~grandparent_robot() {}

void nevil::grandparent_robot::set_individual(nevil::individual *i)
{
  _individual = dynamic_cast<grandparent_individual *> (i);
  _neural_network.set_weights(_individual->get_chromosome());
}

bool nevil::grandparent_robot::update(const std::vector<object *> &objects)
{
  // Get the sensor information
  std::vector<double> inputs = _get_sensor_inputs();

  if (is_at_switch())
    _individual->set_turn_on_light(true);

  if (is_at_light())
    _individual->increase_fitness(1);

  // TODO Do stuff according to child, parent, grandparent

  // Add the bias input
  inputs.push_back(1);
  // Evaluate the neural network
  std::vector <double> output = _neural_network.update(inputs);
  // Pass the output of each NN and convert it to motor velocities
  _set_wheels_speed(output);
  return true;
}