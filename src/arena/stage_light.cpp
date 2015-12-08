#include "nevil/arena/stage_light.hpp"

const Enki::Color nevil::stage_light::DEFAULT_OFF_COLOR = Enki::Color(0.5, 0.5, 0.0);
const Enki::Color nevil::stage_light::DEFAULT_ON_COLOR = Enki::Color(0.8, 1.0, 0.0);
const Enki::Color nevil::stage_light::DEFAULT_FULL_ON_COLOR = Enki::Color(1.0, 1.0, 0.0);

nevil::stage_light::stage_light()
  : nevil::object()
{}

nevil::stage_light::stage_light(int x, int y, double size_x, double size_y
  , double height, const Enki::Color &off_color, const Enki::Color &on_color)
  : nevil::object(x, y, size_x, size_y, height, off_color, on_color)
{}

void nevil::stage_light::turn_off()
{
  setColor(_off_color);
  set_on_color(stage_light::DEFAULT_ON_COLOR);
  _state = OFF;
}