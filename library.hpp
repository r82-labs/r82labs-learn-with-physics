#pragma once
#include <vector>

namespace r82labs::learn_with_physics {

    struct Point {
        float x, y;
    };

    class Slingshot {
        const float band_stiffness;
        const float efficiency;

    public:
        explicit Slingshot(const float k, const float eff = 0.75f)
            : band_stiffness(k), efficiency(eff) {}

        float get_launch_velocity(float draw_length_meters, float mass_kg) const;
    };

    class Projectile {
        const float mass;

    public:
        explicit Projectile(const float m) : mass(m) {}
        float get_mass() const { return mass; }
    };

    class Simulator {
        const float gravity;

    public:
        explicit Simulator(const float g = 9.81f) : gravity(g) {}

        Point get_position_at_time(const Slingshot& slingshot, const Projectile& proj,
                                  const float draw_length, const float angle_radians, const float time) const;

        std::vector<Point> calculate_full_trajectory(const Slingshot& slingshot, const Projectile& proj,
                                                     const float draw_length, const float angle_radians, const float time_step) const;
    };
}
