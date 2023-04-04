#include <color.hpp>

namespace raytracing
{

std::ostream& write_color(std::ostream& out, Color pixel_color)
{
    return out << static_cast<int>(pixel_color.r()) << " " << static_cast<int>(pixel_color.g()) << " " << static_cast<int>(pixel_color.b());
}
std::ostream& operator<<(std::ostream& out, Color pixel_color)
{
    return write_color(out, pixel_color);
}

} // namespace raytracing
