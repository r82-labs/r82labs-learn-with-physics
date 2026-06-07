#pragma once
#include <stdexcept>

namespace r82labs::learn_with_physics {

enum class AngleUnit { radians, degrees };
enum class LaunchDirection { right, left };

struct Point {
    float x;
    float y;
};

struct PointInTime {
    Point position;
    float time;
};

struct ProjectileConfig {
    float mass = 0.0f;
};

class Projectile {
    const float mass;

   public:
    explicit Projectile(const ProjectileConfig& config) : mass(config.mass) {
        if (config.mass <= 0.0f) {
            throw std::invalid_argument("mass must be positive");
        }
    }

    [[nodiscard]] float get_mass() const { return mass; }
};

struct SlingshotConfig {
    float band_stiffness = 0.0f;
    float efficiency = 0.75f;
};

class Slingshot {
    const float band_stiffness;
    const float efficiency;

   public:
    explicit Slingshot(const SlingshotConfig& config)
        : band_stiffness(config.band_stiffness), efficiency(config.efficiency) {
        if (config.band_stiffness < 0.0f) {
            throw std::invalid_argument("band_stiffness must be non-negative");
        }
        if (config.efficiency < 0.0f || config.efficiency > 1.0f) {
            throw std::invalid_argument("efficiency must be between 0 and 1");
        }
    }

    [[nodiscard]] float get_stiffness() const { return band_stiffness; }
    [[nodiscard]] float get_efficiency() const { return efficiency; }
};

struct SimulatorConfig {
    const Slingshot& slingshot;
    const Projectile& projectile;
    float draw_length = 1.0f;
    float angle = 45.0f;
    AngleUnit unit = AngleUnit::radians;
    LaunchDirection direction = LaunchDirection::right;
    float g = 9.81f;
};

struct TimeRequest {
    float time = 0.0f;
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
    [[nodiscard]] float get_time_at_ground() const;
    [[nodiscard]] const Projectile& get_projectile() const { return projectile; }
};
}  // namespace r82labs::learn_with_physics
