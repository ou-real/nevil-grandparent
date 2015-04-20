#ifndef _NEVIL_GRANDPARENT_TRIAL_HPP_
#define _NEVIL_GRANDPARENT_TRIAL_HPP_


#include "nevil/trial.hpp"

#include "nevil/grandparent_population.hpp"
#include "nevil/grandparent_arena.hpp"
#include "nevil/util/logger.hpp"
#include "util/parser.hpp"


namespace nevil
{
  class grandparent_trial : public trial
  {
  public:
    grandparent_trial();
    grandparent_trial(nevil::args &cl_args);
    virtual ~grandparent_trial();
    
    bool reset();
    bool update();
    bool epoch();
    nevil::grandparent_individual get_best_individual() const;
    std::string get_generation_data();
    Enki::World *get_trial_world();


  protected:
    int _population_size;
    int _current_index;

    nevil::grandparent_individual _best_individual;
    nevil::grandparent_arena *_trial_arena;
    nevil::grandparent_population _population;
  };
}

#endif // _NEVIL_GRANDPARENT_TRIAL_HPP_