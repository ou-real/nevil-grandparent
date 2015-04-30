#include "nevil/grandparent_population.hpp"

int nevil::grandparent_population::_individual_counter = 0;

nevil::grandparent_population::grandparent_population() {}

nevil::grandparent_population::grandparent_population(size_t pop_size, bool has_grandparent, float bracket_ratio, float mutation_rate)
  : _population_size(pop_size)
  , _bracket_size(int(bracket_ratio * pop_size))
  , _mutation_rate(mutation_rate)
{
  _individual_list = std::vector<nevil::grandparent_individual *>(3 * _population_size);
  for (int i = 0; i < _population_size; ++i)
  {
    // Creating grandparents
    _individual_list[i + (2 * _population_size)] = new nevil::grandparent_individual(has_grandparent ? 44 : 42);

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
  std::vector<nevil::grandparent_individual *> children(_individual_list.begin(), _individual_list.begin() + _population_size);
  // Only sort the children
  std::sort(children.begin(), children.end(), [](nevil::grandparent_individual *a, nevil::grandparent_individual *b) {
    return (*b) < (*a);
  });

  nevil::grandparent_individual best_individual(*children[0]);

  // tournament part
  auto selected_individuals = nevil::evolution::tournament_selection(children, _population_size, _bracket_size);

  for (int i = 0; i < _population_size; ++i)
  {
    // Delete grandparent
    delete _individual_list[i + (2 * _population_size)];
    // Make the parent to be the grandparent
    _individual_list[i + (2 * _population_size)] = _individual_list[i + _population_size]->clone();

    // Make the children to be the parents
    delete _individual_list[i + _population_size];
    _individual_list[i + _population_size] = selected_individuals[i]->clone();

    // Cloning and mutating the parent for getting the new children
    delete _individual_list[i];
    _individual_list[i] = selected_individuals[i]->clone();
    _individual_list[i]->mutate(_mutation_rate);
    delete selected_individuals[i];
  }

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
