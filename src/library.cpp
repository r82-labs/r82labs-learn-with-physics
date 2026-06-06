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
        return draw_length_meters * std::sqrt((efficiency * band_stiffness) / mass_kg);
    }

    Simulator::Simulator(const Slingshot& slingshot, const Projectile& proj,
                         const float draw_length, const float angle,
                         const AngleUnit unit, const LaunchDirection direction,
                         const float g)
        : gravity(g), x_velocity_factor(0.0f), y_velocity_factor(0.0f), dir_multiplier(1.0f) {
        const float angle_radians = MathUtils::to_radians(angle, unit);
        const float v0 = slingshot.get_launch_velocity(draw_length, proj.get_mass());

        x_velocity_factor = v0 * std::cos(angle_radians);
        y_velocity_factor = v0 * std::sin(angle_radians);
        dir_multiplier = (direction == LaunchDirection::right) ? 1.0f : -1.0f;
    }

    Point Simulator::get_position_at_time(const float time) const {
        const float x = dir_multiplier * x_velocity_factor * time;
        const float y = (y_velocity_factor * time) - (0.5f * gravity * time * time);
        return {x, y};
    }
}
