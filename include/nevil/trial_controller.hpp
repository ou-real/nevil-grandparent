#ifndef _NEVIL_TRIAL_CONTROLLER_HPP_
#define _NEVIL_TRIAL_CONTROLLER_HPP_

#include <iostream>
#include <string>
#include <time.h>
#include <enki/Types.h>

#include "grandparent_trial.hpp"
#include "util/logger.hpp"
#include "util/parser.hpp"

#ifdef GUI
  #include "nevil/gui/view.hpp"
#endif

namespace nevil
{
  class trial_controller
  {
  public:
    trial_controller();
    trial_controller(int id, unsigned seed, args&);
    ~trial_controller();

    void run();
    Enki::World *get_trial_world();

  protected:
    void _simulate();
    void _evaluate();
    void _end();

    nevil::grandparent_trial *_trial;
    nevil::logger _trial_logger;
    int _trial_id;

    #ifdef GUI
      view *_viewer;
    #endif

    //simulation variables
    int _max_step_num;
    int _population_size;
    int _max_generation_num;
    int _current_generation;
  };
}

#endif // _NEVIL_TRIAL_CONTROLLER_HPP_