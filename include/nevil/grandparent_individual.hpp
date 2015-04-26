#ifndef _NAME_GRANDPARENT_INDIVIDUAL_HPP_
#define _NAME_GRANDPARENT_INDIVIDUAL_HPP_

#include "individual.hpp"
#include "nevil/util/random.hpp"
#include <string>

namespace nevil
{
  class grandparent_individual : public individual
  {
  public:
    grandparent_individual();
    grandparent_individual(size_t chromo_size);
    grandparent_individual(const std::vector<double> &chromosome);
    grandparent_individual(const grandparent_individual &rhs);
    virtual ~grandparent_individual();

    grandparent_individual* clone() const;
    void mutate(float rate);
    
    std::string str() const;
    bool turn_on_light() const;
    bool gained_fitness() const;
    nevil::grandparent_individual &operator=(const nevil::grandparent_individual &rhs);

    void increase_fitness(int fitness);
    void set_turn_on_light_a (bool a);
    void set_turn_on_light_b (bool b);

  protected:
    // Indicates whether this individual activated the switch in a given trial
    bool _turned_on_light_a;
    bool _turned_on_light_b;
    // Indicates whether this individual gained fitness.
    int _gained_fitness;
  };
}

#endif // _NAME_GRANDPARENT_INDIVIDUAL_HPP_