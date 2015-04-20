#include "nevil/grandparent_individual.hpp"

nevil::grandparent_individual::grandparent_individual() {}

nevil::grandparent_individual::grandparent_individual(size_t chromo_size)
  : _parent_uuid("NONE")
  , _gained_fitness(false)
  , _turned_on_light(false)
{
  _fitness = 0;
  // Assign values to every gene in the chromosome
  _chromosome = std::vector<double>(chromo_size);
  for (int i = 0; i < chromo_size; ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::grandparent_individual::grandparent_individual(const std::vector<double> &chromosome)
  : _parent_uuid("NONE")
  , _gained_fitness(false)
  , _turned_on_light(false)
{
  _fitness = 0;
  _chromosome = chromosome;
}

nevil::grandparent_individual::grandparent_individual(const grandparent_individual &rhs)
  : _uuid(rhs._uuid)
  , _parent_uuid(rhs._parent_uuid)
  , _gained_fitness(rhs._gained_fitness)
  , _turned_on_light(rhs._turned_on_light)
{
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
}

nevil::grandparent_individual::~grandparent_individual() {}

const std::string &nevil::grandparent_individual::get_uuid() const
{
  return _uuid;
}

const std::string &nevil::grandparent_individual::get_parent_uuid() const
{
  return _parent_uuid;
}

std::string nevil::grandparent_individual::str() const
{
  return _parent_uuid + ":" + _uuid + ":S=" + (_turned_on_light ? "1" : "0") + ":L=" + (_gained_fitness ? "1" : "0") + ":" +std::to_string(_fitness);
}

void nevil::grandparent_individual::set_id(int id)
{
  _uuid = std::to_string(id);
}

void nevil::grandparent_individual::set_turn_on_light(bool b)
{
  _turned_on_light = b;
}

void nevil::grandparent_individual::increase_fitness(int fitness)
{
  _fitness += fitness;
  _gained_fitness = true;
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
  _uuid = rhs._uuid;
  _parent_uuid = rhs._parent_uuid;
  _gained_fitness = rhs._gained_fitness;
  _turned_on_light = rhs._turned_on_light;
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
  return (*this);
}