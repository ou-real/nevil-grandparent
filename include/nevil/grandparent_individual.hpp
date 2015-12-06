#ifndef _NAME_GRANDPARENT_INDIVIDUAL_HPP_
#define _NAME_GRANDPARENT_INDIVIDUAL_HPP_

#include <json/json.h>

#include "individual.hpp"
#include "nevil/util/random.hpp"

namespace nevil
{
  class grandparent_individual : public individual
  {
  public:
    grandparent_individual();
    grandparent_individual(size_t chromo_size);
    grandparent_individual(const nevil::chromosome &chromo);

    grandparent_individual* clone() const;
    Json::Value json() const;
    
    bool turn_on_light() const;
    bool gained_fitness() const;

    void increase_fitness(double fitness);
    void set_turned_on_switch (const std::string name, bool on = true);

  protected:
    // Indicates whether this individual activated the switch in a given trial
    bool _turned_on_switch_A;
    bool _turned_on_switch_B;
    // Indicates whether this individual gained fitness.
    double _light_power;
  };
}

#endif // _NAME_GRANDPARENT_INDIVIDUAL_HPP_