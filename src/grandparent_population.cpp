#include "nevil/grandparent_population.hpp"

int nevil::grandparent_population::_individual_counter = 0;

nevil::grandparent_population::grandparent_population() {}

nevil::grandparent_population::grandparent_population(size_t pop_size, bool has_parent, bool has_grandparent, float bracket_ratio, float mutation_rate)
  : _population_size(pop_size)
  , _bracket_size(int(bracket_ratio * pop_size))
  , _mutation_rate(mutation_rate)
{
  _individual_list = std::vector<nevil::grandparent_individual *>(3 * _population_size);
  int genome_size = 38 + (2 * has_grandparent) + (2 * has_grandparent);

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

  std::vector<int> selected_indices = nevil::evolution::tournament_selection(_individual_list.begin(), _individual_list.begin() + _population_size, _population_size, _bracket_size);
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

  _individual_list = new_individuals;

  return best_individual;
}

nevil::grandparent_population &nevil::grandparent_population::operator=(const nevil::grandparent_population &rhs)
{
  for (auto i : _individual_list)
    delete i;
  _population_size = rhs._population_size;
  _mutation_rate = rhs._mutation_rate;
  _bracket_size = rhs._bracket_size;
  _individual_list = std::vector<nevil::grandparent_individual *> (rhs.size());
  for (int i = 0; i < _individual_list.size(); ++i)
    _individual_list[i] = new nevil::grandparent_individual(*rhs._individual_list[i]);

  return (*this);
}

nevil::grandparent_individual* nevil::grandparent_population::operator[](int i)
{
  return _individual_list[i];
}
