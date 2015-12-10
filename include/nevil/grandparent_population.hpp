#ifndef _NEVIL_GRANDPARENT_POPULATION_HPP_
#define _NEVIL_GRANDPARENT_POPULATION_HPP_

#include <vector>
#include <algorithm>
#include "nevil/util/parser.hpp"
#include "nevil/grandparent_individual.hpp"
#include "nevil/util/evolution.hpp"

namespace nevil
{
  class grandparent_population
  {
  public:
    grandparent_population();
    explicit grandparent_population(const nevil::args &cl_args);
    grandparent_population(const nevil::grandparent_population &rhs);
    grandparent_population(nevil::grandparent_population &&rhs) noexcept;
    virtual ~grandparent_population();

    size_t size() const;
    nevil::grandparent_individual next_generation();

    nevil::grandparent_population &operator=(const grandparent_population &rhs);
    nevil::grandparent_population &operator=(grandparent_population &&rhs) noexcept;
    nevil::grandparent_individual *operator[](int i);

  protected:
    size_t _population_size;
    size_t _bracket_size;
    double _mutation_rate;
    std::vector <nevil::grandparent_individual *> _individual_list;
  };
}

#endif // _NEVIL_GRANDPARENT_POPULATION_HPP_