#include <iostream>

#include "library.hpp"

using namespace r82labs::learn_with_physics;

int main() {
    Projectile proj({.mass = 0.2f});
    Slingshot slingshot({.band_stiffness = 100.0f, .efficiency = 0.8f});
    Simulator sim({.slingshot = slingshot,
                   .projectile = proj,
                   .draw_length = 1.0f,
                   .angle = 45.0f,
                   .unit = AngleUnit::degrees,
                   .direction = LaunchDirection::right});

    const Point position = sim.get_position_at_time({.time = 0.5f});
    std::cout << "Position at t=0.5s: (" << position.x << ", " << position.y << ")\n";

    return 0;
}
