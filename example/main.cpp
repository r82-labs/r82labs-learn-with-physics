#include <iostream>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;

int main() {
    Projectile proj({.mass = Mass::from_kilograms(0.2f)});
    Slingshot slingshot({.band_stiffness = Stiffness::from_newtons_per_meter(100.0f),
                         .efficiency = Efficiency::from_ratio(0.8f)});
    Simulator sim({.slingshot = slingshot,
                   .projectile = proj,
                   .draw_length = Length::from_meters(1.0f),
                   .angle = Angle::from_degrees(45.0f),
                   .direction = LaunchDirection::right});

    const Point position = sim.get_position_at_time({.time = Time::from_seconds(0.5f)});
    std::cout << "Position at t=0.5s: (" << position.x.as_meters() << ", " << position.y.as_meters() << ")\n";

    return 0;
}
