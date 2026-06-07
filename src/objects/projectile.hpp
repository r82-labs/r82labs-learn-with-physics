#pragma once
#include <stdexcept>

namespace r82labs::learn_with_physics {

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

}  // namespace r82labs::learn_with_physics
