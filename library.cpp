#include "library.hpp"
#include <cmath>

namespace r82labs::learn_with_physics {

    float Slingshot::get_launch_velocity(const float draw_length_meters, const float mass_kg) const {
        if (mass_kg <= 0.0f) return 0.0f;

        return draw_length_meters * std::sqrt((efficiency * band_stiffness) / mass_kg);
    }

    Point Simulator::get_position_at_time(const Slingshot& slingshot, const Projectile& proj,
                                         const float draw_length, const float angle_radians, const float time) const {

        const float v0 = slingshot.get_launch_velocity(draw_length, proj.get_mass());

        const float v0_x = v0 * std::cos(angle_radians);
        const float v0_y = v0 * std::sin(angle_radians);

        const float x = v0_x * time;
        const float y = (v0_y * time) - (0.5f * gravity * time * time);

        return {x, y};
    }

    std::vector<Point> Simulator::calculate_full_trajectory(const Slingshot& slingshot, const Projectile& proj,
                                                            const float draw_length, const float angle_radians, const float time_step) const {
        std::vector<Point> trajectory;
        float time = 0.0f;
        Point current_pos;

        do {
            current_pos = get_position_at_time(slingshot, proj, draw_length, angle_radians, time);

            if (current_pos.y >= 0.0f) {
                trajectory.push_back(current_pos);
            }
            time += time_step;

        } while (current_pos.y >= 0.0f);

        return trajectory;
    }
}
