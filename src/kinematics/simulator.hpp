#pragma once
#include "core/types.hpp"
#include "objects/projectile.hpp"
#include "objects/slingshot.hpp"

namespace r82labs::learn_with_physics {

struct SimulatorConfig {
    const Slingshot& slingshot;
    const Projectile& projectile;
    Length draw_length = Length::from_meters(1.0);
    LaunchOrientation orientation = LaunchOrientation::toward_right(Angle::from_degrees(45.0));

    Acceleration g = Acceleration::from_meters_per_second_squared(9.81);
};

class Simulator {
    const double gravity;
    const Projectile projectile;
    double x_velocity_factor;
    double y_velocity_factor;
    double half_gravity_factor;

   public:
    explicit Simulator(const SimulatorConfig& config);
    [[nodiscard]] Point get_position_at_time(const TimeRequest& request) const;
    [[nodiscard]] PointInTime get_apex_point_in_time() const;
    [[nodiscard]] Time get_time_at_ground() const;
    [[nodiscard]] const Projectile& get_projectile() const { return projectile; }
};

}  // namespace r82labs::learn_with_physics
