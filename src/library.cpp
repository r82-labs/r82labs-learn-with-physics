#include "library.hpp"
#include <cmath>
#include <numbers>
#include <limits>

namespace r82labs::learn_with_physics {

    float MathUtils::to_radians(const float angle, const AngleUnit unit) {
        if (unit == AngleUnit::radians) {
            return angle;
        }
        return angle * (std::numbers::pi_v<float> / 180.0f);
    }

    Simulator::Simulator(const Slingshot& slingshot, const Projectile& proj,
                         const float draw_length, const float angle,
                         const AngleUnit unit, const LaunchDirection direction,
                         const float g)
        : gravity(g), projectile(proj), x_velocity_factor(0.0f), y_velocity_factor(0.0f), half_gravity_factor(0.5f * g) {
        const float angle_radians = MathUtils::to_radians(angle, unit);

        constexpr float epsilon = std::numeric_limits<float>::epsilon();
        if (angle_radians < -epsilon || angle_radians > (std::numbers::pi_v<float> / 2.0f + epsilon)) {
            throw std::out_of_range("Launch angle must be between 0 and 90 degrees.");
        }

        const float v0 = draw_length * std::sqrt((slingshot.get_efficiency() * slingshot.get_stiffness()) / projectile.get_mass());
        const float dir_multiplier = (direction == LaunchDirection::right) ? 1.0f : -1.0f;

        x_velocity_factor = v0 * std::cos(angle_radians) * dir_multiplier;
        y_velocity_factor = v0 * std::sin(angle_radians);
    }

    Point Simulator::get_position_at_time(const float time) const {
        return {
            x_velocity_factor * time,
            (y_velocity_factor - half_gravity_factor * time) * time
        };
    }
}
