#include "nevil/grandparent_trial.hpp"

nevil::grandparent_trial::grandparent_trial() {}


nevil::grandparent_trial::grandparent_trial(nevil::args &cl_args)
{
  const int WORLD_SIZE_X = 120;
  const int WORLD_SIZE_Y = 70;

  _population_size = std::stoi(cl_args["ps"]);
  float bracket_ratio = std::stof(cl_args["br"]);
  float mutation_rate = std::stof(cl_args["mr"]);
  bool has_grandparent = (cl_args["gp"] == "true");

  _trial_arena = new nevil::grandparent_arena(WORLD_SIZE_X, WORLD_SIZE_Y, has_grandparent);
  _population = nevil::grandparent_population(_population_size, has_grandparent, bracket_ratio, mutation_rate);
  _current_index = 0;
}

nevil::grandparent_trial::~grandparent_trial() 
{
  delete _trial_arena;
}

Enki::World *nevil::grandparent_trial::get_trial_world()
{
  return _trial_arena->get_world();
}

bool nevil::grandparent_trial::update()
{
  _trial_arena->tick();
  _trial_arena->update();
  return true;
}

bool nevil::grandparent_trial::reset()
{
  _trial_arena->reset();
  // 
  _trial_arena->set_individuals(_population[_current_index]
    , _population[_current_index + _population_size]
    , _population[_current_index + (2 * _population_size)]);
  ++_current_index;
  return true;
}

bool nevil::grandparent_trial::epoch()
{
  _best_individual = _population.next_generation();
  _current_index = 0;

  return true;
}

nevil::grandparent_individual nevil::grandparent_trial::get_best_individual() const
{
  return _best_individual;
}

std::string nevil::grandparent_trial::get_generation_data()
{
  std::string generation_info;
  for (int i = 0; i < _population.size() - 1; ++i)
    generation_info = generation_info + _population[i]->str() + ", ";

  return generation_info + _population[_population.size() - 1]->str();
}
