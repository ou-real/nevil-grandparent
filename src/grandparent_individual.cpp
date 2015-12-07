#include "nevil/grandparent_individual.hpp"

nevil::grandparent_individual::grandparent_individual()
  : nevil::individual()
{}

nevil::grandparent_individual::grandparent_individual(size_t chromo_size)
  : nevil::individual(chromo_size)
  , _turned_on_switch_A(0)
  , _turned_on_switch_B(0)
  , _light_power(0)
{
  // Assign values to every gene in the chromosome
  for (int i = 0; i < chromo_size; ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::grandparent_individual::grandparent_individual(const nevil::chromosome &chromo)
  : nevil::individual()
  , _turned_on_switch_A(0)
  , _turned_on_switch_B(0)
  , _light_power(0)
{
  _chromosome = chromo;
}

void nevil::grandparent_individual::set_turned_on_switch(const std::string &name, bool on)
{
  if (name == "A")
    _turned_on_switch_A = on;

  else if (name == "B")
    _turned_on_switch_B = on;
}

void nevil::grandparent_individual::increase_fitness(double fitness)
{
  _fitness += fitness;
  _light_power = std::max(_light_power, fitness);
}

Json::Value nevil::grandparent_individual::json() const
{
  Json::Value data;
  data["switchA"] = _turned_on_switch_A;
  data["switchB"] = _turned_on_switch_B;
  data["lightPower"] = _light_power;
  data["fitness"] = _fitness;
  return data;
}

nevil::grandparent_individual* nevil::grandparent_individual::clone() const 
{
  return new grandparent_individual(_chromosome);
}