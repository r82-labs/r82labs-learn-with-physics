#pragma once
#include "core/types.hpp"
#include "objects/projectile.hpp"
#include "objects/slingshot.hpp"

namespace r82labs::learn_with_physics {

struct SimulatorConfig {
    const Slingshot& slingshot;
    const Projectile& projectile;
    Length draw_length = Length::from_meters(1.0f);
    Angle angle = Angle::from_radians(45.0f);
    LaunchDirection direction = LaunchDirection::right;
    float g = 9.81f;
};

class Simulator {
    const float gravity;
    const Projectile projectile;
    float x_velocity_factor;
    float y_velocity_factor;
    float half_gravity_factor;

   public:
    explicit Simulator(const SimulatorConfig& config);
    [[nodiscard]] Point get_position_at_time(const TimeRequest& request) const;
    [[nodiscard]] PointInTime get_apex_point_in_time() const;
    [[nodiscard]] Time get_time_at_ground() const;
    [[nodiscard]] const Projectile& get_projectile() const { return projectile; }
};

}  // namespace r82labs::learn_with_physics
