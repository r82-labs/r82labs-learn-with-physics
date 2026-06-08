#include <iostream>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;

int main() {
    Projectile proj({.mass = Mass::from_kilograms(0.2)});
    Slingshot slingshot({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                         .efficiency = Efficiency::from_ratio(0.8)});
    Simulator sim({.slingshot = slingshot,
                   .projectile = proj,
                   .draw_length = Length::from_meters(1.0),
                   .orientation = LaunchOrientation::toward_right(Angle::from_degrees(45.0))});

    const Point position = sim.get_position_at_time({.time = Time::from_seconds(0.5)});
    std::cout << "Position at t=0.5s: (" << position.x << ", " << position.y << ")\n";

    return 0;
}
