#ifndef _NEVIL_GRANDPARENT_POPULATION_HPP_
#define _NEVIL_GRANDPARENT_POPULATION_HPP_

#include <vector>
#include <algorithm>

#include "nevil/grandparent_individual.hpp"
#include "nevil/util/evolution.hpp"

namespace nevil
{
  class grandparent_population
  {
  public:
    grandparent_population();
    grandparent_population(size_t pop_size, float bracket_ratio ,float mutation_rate);
    virtual ~grandparent_population();

    size_t size() const;
    nevil::grandparent_individual next_generation();

    grandparent_population &operator=(const grandparent_population &rhs);
    grandparent_individual *operator[](int i);

  protected:
    // Number of individuals created so far
    static int _individual_counter;
    size_t _bracket_size;
    float _mutation_rate;
    size_t _population_size;
    std::vector <nevil::grandparent_individual *> _individual_list;

  };
}

#endif // _NEVIL_GRANDPARENT_POPULATION_HPP_