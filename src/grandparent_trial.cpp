#include "nevil/grandparent_trial.hpp"

nevil::grandparent_trial::grandparent_trial()
{}

nevil::grandparent_trial::grandparent_trial(const nevil::args &cl_args)
{
  const int WORLD_SIZE_X = 70;
  const int WORLD_SIZE_Y = 50;

  _population_size = std::stoi(cl_args.at("ps"));
  float bracket_ratio = std::stof(cl_args.at("br"));
  float mutation_rate = std::stof(cl_args.at("mr"));
  bool has_grandparent = (cl_args.at("gp") == "true");
  bool has_parent = (cl_args.at("pr") == "true");

  _arena = nevil::grandparent_arena(WORLD_SIZE_X, WORLD_SIZE_Y, has_parent, has_grandparent);
  _population = nevil::grandparent_population(_population_size, has_parent, has_grandparent, bracket_ratio, mutation_rate);
  _current_index = 0;
}

Enki::World *nevil::grandparent_trial::get_world() const
{
  return _arena.get_world();
}

bool nevil::grandparent_trial::update()
{
  return _arena.update();
}

bool nevil::grandparent_trial::reset()
{
  _arena.set_individuals(_population[_current_index]
    , _population[_current_index + _population_size]
    , _population[_current_index + (2 * _population_size)]);
  ++_current_index;
  return _arena.reset();;
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

Json::Value nevil::grandparent_trial::get_generation_data()
{
  Json::Value generation_info (Json::arrayValue);
  for (int i = 0; i < _population_size; ++i)
  {
    Json::Value family;
    family["child"] = _population[i]->json();
    family["parent"] = _population[i + _population_size]->json();
    family["grandparent"] = _population[i + (2 * _population_size)]->json();
    generation_info.append(family);
  }

  return generation_info;
}
