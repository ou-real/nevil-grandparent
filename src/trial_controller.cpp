#include "nevil/trial_controller.hpp"

nevil::trial_controller::trial_controller() {}

nevil::trial_controller::trial_controller(int id, unsigned seed, const nevil::args &cl_args)
  : _trial_id(id)
{
  srand(seed);

  //Default Values
  _population_size = 80;
  _max_generation_num = 200;
  _max_step_num = 1000;
  std::string trial_name = "GrandparentTrial";
  bool has_parent = false;
  bool has_grandparent = false;
  double mutation_rate = 0.25;
  double bracket_ratio = 0.1;

  // Reading the command line arguments
  nevil::args::const_iterator it;
  nevil::args local_args(cl_args);

  if ((it = local_args.find("xn")) != local_args.end())
    trial_name = it->second;

  if ((it = local_args.find("mg")) != local_args.end())
    _max_generation_num = stoi(it->second);

  if ((it = local_args.find("ms")) != local_args.end())
    _max_step_num = stoi(it->second);

  if ((it = local_args.find("pr")) != local_args.end())
    has_parent = (it->second == "true");
  else
    local_args["pr"] = (has_parent ? "true":"false");

  if ((it = local_args.find("gp")) != local_args.end())
    has_grandparent = (it->second == "true");
  else
    local_args["gp"] = (has_grandparent ? "true":"false");

  if ((it = local_args.find("ps")) != local_args.end())
    _population_size = stoi(it->second);
  else
    local_args["ps"] = std::to_string(_population_size);

  if ((it = local_args.find("br")) != local_args.end())
  {
    bracket_ratio = stof(it->second);
    if (bracket_ratio < 0 || bracket_ratio > 1)
    {
      printf("Bracket ratio must be between 0 and 1. '%.2f' was given.\nTerminating ...", bracket_ratio);
      exit(-1); 
    }
  }
  else
    local_args["br"] = std::to_string(bracket_ratio);

  if ((it = local_args.find("mr")) != local_args.end())
  {
    mutation_rate = stof(it->second);
    if (mutation_rate < 0 || mutation_rate > 1)
    {
      printf("Mutation rate must be between 0 and 1. '%.2f' was given.\nTerminating ...", mutation_rate);
      exit(-1); 
    }
  }
  else
    local_args["mr"] = std::to_string(mutation_rate);

  _trial_json_logger.start_new_file(local_args["xp_path"], "Trial_" + std::to_string(_trial_id) + ".json");
  _generational_data = Json::Value(Json::arrayValue);
  
  // JSON style
  _root["config"]["trialName"] = trial_name;
  _root["config"]["hasParent"] = has_parent;
  _root["config"]["hasGrandparent"] = has_grandparent;
  _root["config"]["randomSeed"] = seed;
  _root["config"]["numberOfGenerations"] = _max_generation_num;
  _root["config"]["numberOfTimesteps"] = _max_step_num;
  _root["config"]["populationSize"] = _population_size;
  _root["config"]["bracketRatio"] = bracket_ratio;
  _root["config"]["mutationRate"] = mutation_rate;

  _trial = nevil::grandparent_trial(local_args);
  _current_generation = 0;
  _current_individual = 0;
  _current_step = 0;
  printf("-Trial %d: starting\n", _trial_id);
  printf("-Trial %d: running generation %d\n", _trial_id, _current_generation);
}

Enki::World *nevil::trial_controller::get_world() const
{
  return _trial.get_world();
}

bool nevil::trial_controller::run()
{
  if (_current_generation < _max_generation_num)
  {
    if (_current_individual < _population_size)
    {
      if (_current_step == 0 && _current_individual != _population_size)
        _trial.reset();

      if (_current_step < _max_step_num)
      {
        _trial.update();
        ++_current_step;
      }
      else
      {
        ++_current_individual;
        _current_step = 0;
      }
    }
    else
    {
      _evaluate();
      ++_current_generation;
      _current_individual = 0;
      _current_step = 0;
      printf("-Trial %d: running generation %d\n", _trial_id, _current_generation);
    }
    return true;
  }

  _end();
  return false;
}

void nevil::trial_controller::_evaluate()
{
  Json::Value data;
  data["generationNumber"] = _current_generation;
  data["individualList"] = _trial.get_generation_data();
  _trial.epoch();
  data["bestIndividual"] = _trial.get_best_individual().json();
  _generational_data.append(data);
}

void nevil::trial_controller::_end()
{
  printf("-Trial %d: finished\n", _trial_id);
  _root["generationalData"] = _generational_data;
  _trial_json_logger.write(_root);
  _trial_json_logger.close_file();
}