#include <iostream>
#include "library.hpp"

using namespace r82labs::learn_with_physics;

int main() {
    Projectile proj(0.2f);
    Slingshot slingshot(100.0f, 0.8f);
    Simulator sim(slingshot, proj, 1.0f, 45.0f, AngleUnit::degrees, LaunchDirection::right);

    const Point position = sim.get_position_at_time(0.5f);
    std::cout << "Position at t=0.5s: (" << position.x << ", " << position.y << ")\n";

    return 0;
}
