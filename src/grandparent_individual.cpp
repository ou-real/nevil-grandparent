#include "nevil/grandparent_individual.hpp"

nevil::grandparent_individual::grandparent_individual() {}

nevil::grandparent_individual::grandparent_individual(size_t chromo_size)
  : _gained_fitness(0)
  , _turned_on_light_a(0)
  , _turned_on_light_b(0)
{
  _fitness = 0;
  // Assign values to every gene in the chromosome
  _chromosome = std::vector<double>(chromo_size);
  for (int i = 0; i < chromo_size; ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::grandparent_individual::grandparent_individual(const std::vector<double> &chromosome)
  : _gained_fitness(0)
  , _turned_on_light_a(0)
  , _turned_on_light_b(0)
{
  _fitness = 0;
  _chromosome = chromosome;
}

nevil::grandparent_individual::grandparent_individual(const grandparent_individual &rhs)
  : _gained_fitness(rhs._gained_fitness)
  , _turned_on_light_a(rhs._turned_on_light_a)
  , _turned_on_light_b(rhs._turned_on_light_b)
{
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
}

nevil::grandparent_individual::~grandparent_individual() {}

std::string nevil::grandparent_individual::str() const
{
  return std::string("SA=") + (_turned_on_light_a ? "1" : "0") + ":SB=" + (_turned_on_light_b ? "1" : "0") + ":L=" + std::to_string(_gained_fitness) + ":" + std::to_string(_fitness);
}

void nevil::grandparent_individual::set_turn_on_light_a(bool a)
{
  _turned_on_light_a = a;
}

void nevil::grandparent_individual::set_turn_on_light_b(bool b)
{
  _turned_on_light_b = b;
}

void nevil::grandparent_individual::increase_fitness(int fitness)
{
  _fitness += fitness;
  _gained_fitness = std::max(_gained_fitness, fitness);
}

nevil::grandparent_individual* nevil::grandparent_individual::clone() const 
{
  return new grandparent_individual(_chromosome);
}

void nevil::grandparent_individual::mutate(float rate)
{
  assert (0 <= rate && rate <= 1 && "Mutation rate must be between 0 and 1");
  int gene_index = rand() % (_chromosome.size());
  double r  = ((double) rand() / (RAND_MAX));
  if (r <= rate)
    _chromosome[gene_index] = nevil::random::random_int(-15,15);
}

nevil::grandparent_individual &nevil::grandparent_individual::operator=(const nevil::grandparent_individual &rhs)
{
  _gained_fitness = rhs._gained_fitness;
  _turned_on_light_a = rhs._turned_on_light_a;
  _turned_on_light_b = rhs._turned_on_light_b;
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
  return (*this);
}