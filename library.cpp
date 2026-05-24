#include "library.hpp"
#include <cmath>

namespace r82labs::learn_with_physics {

    float MathUtils::to_radians(const float angle, const AngleUnit unit) {
        float angle_radians = angle;
        if (unit == AngleUnit::degrees) {
            angle_radians = angle * (std::numbers::pi_v<float> / 180.0f);
        }

        if (angle_radians < 0.0f || angle_radians > (std::numbers::pi_v<float> / 2.0f + 0.0001f)) {
            throw std::out_of_range("Angle must be between 0 and 90 degrees (0 and PI/2 radians).");
        }

        return angle_radians;
    }

    float Slingshot::get_launch_velocity(const float draw_length_meters, const float mass_kg) const {
        if (mass_kg <= 0.0f) return 0.0f;
        
        // v = d * sqrt(eta * k / m)
        return draw_length_meters * std::sqrt((efficiency * band_stiffness) / mass_kg);
    }

    Point Simulator::get_position_at_time(const Slingshot& slingshot, const Projectile& proj,
                                        const float draw_length, const float angle, const float time,
                                        const AngleUnit unit, const LaunchDirection direction) const {
        
        const float angle_radians = MathUtils::to_radians(angle, unit);
        const float v0 = slingshot.get_launch_velocity(draw_length, proj.get_mass());
        
        const float dir_multiplier = (direction == LaunchDirection::right) ? 1.0f : -1.0f;
        
        const float x = dir_multiplier * v0 * std::cos(angle_radians) * time;
        const float y = (v0 * std::sin(angle_radians) * time) - (0.5f * gravity * time * time);
        
        return {x, y};
    }

    std::vector<Point> Simulator::calculate_full_trajectory(const Slingshot& slingshot, const Projectile& proj,
                                                          const float draw_length, const float angle, const float time_step,
                                                          const AngleUnit unit, const LaunchDirection direction) const {
        std::vector<Point> trajectory;
        float time = 0.0f;
        Point current_pos{};

        do {
            current_pos = get_position_at_time(slingshot, proj, draw_length, angle, time, unit, direction);

            if (current_pos.y >= -0.001f) {
                trajectory.push_back(current_pos);
            }
            time += time_step;

        } while (current_pos.y >= 0.0f);

        return trajectory;
    }
}
