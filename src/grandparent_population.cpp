#include "nevil/grandparent_population.hpp"
#include <iostream>
nevil::grandparent_population::grandparent_population() 
{}

nevil::grandparent_population::grandparent_population(const nevil::args &cl_args)
  : _population_size(std::stoi(cl_args.at("ps")))
  , _bracket_size(size_t(std::stod(cl_args.at("br")) * _population_size))
  , _mutation_rate(std::stod(cl_args.at("mr")))
  , _individual_list(std::vector<nevil::grandparent_individual *>(3 * _population_size))
{
  // 19 base input (18 camera + 1 bias) => 38 genes
  // If has parents +2 more neuron (4 more genes)
  // Is has grandparents +1 more neuron (2 more genes)
  bool has_parent = (cl_args.at("pr") == "true");
  bool has_grandparent = (cl_args.at("gp") == "true");
  int genome_size = 38 + (4 * has_parent) + (2 * has_grandparent);

  for (int i = 0; i < _population_size; ++i)
  {
    // Creating grandparents
    _individual_list[i + (2 * _population_size)] = new nevil::grandparent_individual(genome_size);

    // Creating parents
    _individual_list[i + _population_size] = _individual_list[i + (2 * _population_size)]->clone();
    _individual_list[i + _population_size]->mutate(_mutation_rate);

    //Creating children
    _individual_list[i] = _individual_list[i + _population_size]->clone();
    _individual_list[i]->mutate(_mutation_rate);
  }
}

nevil::grandparent_population::grandparent_population(const nevil::grandparent_population &rhs)
  : _population_size(rhs._population_size)
  , _bracket_size(rhs._bracket_size)
  , _mutation_rate(rhs._mutation_rate)
  , _individual_list(std::vector<nevil::grandparent_individual *> (rhs.size()))
{
  for (int i = 0; i < _individual_list.size(); ++i)
    _individual_list[i] = new nevil::grandparent_individual(*rhs._individual_list[i]);
}

nevil::grandparent_population::grandparent_population(nevil::grandparent_population &&rhs) noexcept
  : _population_size(rhs._population_size)
  , _bracket_size(rhs._bracket_size)
  , _mutation_rate(rhs._mutation_rate)
{
  std::swap(_individual_list, rhs._individual_list);
}

nevil::grandparent_population::~grandparent_population()
{
  for (auto i : _individual_list)
    delete i;
}

size_t nevil::grandparent_population::size() const
{
  return _individual_list.size();
}

nevil::grandparent_individual nevil::grandparent_population::next_generation()
{

  auto selected_indices = nevil::evolution::tournament_selection(_individual_list.begin(), _individual_list.begin() + _population_size, _population_size, _bracket_size);
  std::vector<nevil::grandparent_individual *> new_individuals(_individual_list.size());

  nevil::grandparent_individual *max_individual = _individual_list[0];

  for (int i = 0; i < _population_size; ++i)
  {
    // Make the parent to be the grandparent
    new_individuals[i + (2 * _population_size)] = _individual_list[selected_indices[i] + _population_size]->clone();

    // Make the children to be the parents
    new_individuals[i + _population_size] = _individual_list[selected_indices[i]]->clone();

    // Finding the best individual
    if ((*_individual_list[i]) > (*max_individual))
      max_individual = _individual_list[i];

    // Cloning and mutating the parent for getting the new children
    new_individuals[i] = _individual_list[selected_indices[i]]->clone();
    new_individuals[i]->mutate(_mutation_rate);
  }

  nevil::grandparent_individual best_individual(*max_individual);
  for (auto i : _individual_list)
    delete i;

  _individual_list = std::move(new_individuals);

  return best_individual;
}

nevil::grandparent_population &nevil::grandparent_population::operator=(const nevil::grandparent_population &rhs)
{
  nevil::grandparent_population tmp(rhs);
  *this = std::move(tmp);
  return *this;
}

nevil::grandparent_population &nevil::grandparent_population::operator=(nevil::grandparent_population &&rhs) noexcept
{
  _population_size = rhs._population_size;
  _bracket_size = rhs._bracket_size;
  _mutation_rate = rhs._mutation_rate;
  std::swap(_individual_list, rhs._individual_list);
  return *this;
}

nevil::grandparent_individual* nevil::grandparent_population::operator[](int i)
{
  return _individual_list[i];
}
