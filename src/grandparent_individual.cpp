#include "nevil/grandparent_individual.hpp"

nevil::grandparent_individual::grandparent_individual()
  : nevil::individual()
{}

nevil::grandparent_individual::grandparent_individual(size_t chromo_size)
  : nevil::individual(chromo_size)
  , _turned_on_light_a(0)
  , _turned_on_light_b(0)
  , _light_power(0)
{
  // Assign values to every gene in the chromosome
  for (int i = 0; i < chromo_size; ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::grandparent_individual::grandparent_individual(const std::vector<double> &chromosome)
  : nevil::individual()
  , _turned_on_light_a(0)
  , _turned_on_light_b(0)
  , _light_power(0)
{
  _chromosome = chromosome;
}

void nevil::grandparent_individual::set_turn_on_light_a(bool a)
{
  _turned_on_light_a = a;
}

void nevil::grandparent_individual::set_turn_on_light_b(bool b)
{
  _turned_on_light_b = b;
}

void nevil::grandparent_individual::increase_fitness(double fitness)
{
  _fitness += fitness;
  _light_power = std::max(_light_power, fitness);
}

Json::Value nevil::grandparent_individual::json() const
{
  Json::Value data;
  data["switchA"] = _turned_on_light_a;
  data["switchB"] = _turned_on_light_b;
  data["lightPower"] = _light_power;
  data["fitness"] = _fitness;
  return data;
}

nevil::grandparent_individual* nevil::grandparent_individual::clone() const 
{
  return new grandparent_individual(_chromosome);
}

void nevil::grandparent_individual::mutate(double rate)
{
  assert ((0 <= rate && rate <= 1) && "Mutation rate must be between 0 and 1");
  if (nevil::random::random_double() <= rate)
  {
    int gene_index = nevil::random::random_int() % (_chromosome.size());
    _chromosome[gene_index] = nevil::random::random_int(-15, 15);
  }
}
