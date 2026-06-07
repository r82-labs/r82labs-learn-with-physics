#pragma once
#include <stdexcept>

#include "core/types.hpp"

namespace r82labs::learn_with_physics {

struct ProjectileConfig {
    Mass mass = Mass::from_kilograms(1.0);
};

class Projectile {
    const Mass mass;

   public:
    explicit Projectile(const ProjectileConfig& config) : mass(config.mass) {
        if (mass.get_kilograms() <= 0.0) {
            throw std::invalid_argument("mass must be positive");
        }
    }

    [[nodiscard]] Mass get_mass() const { return mass; }
};

}  // namespace r82labs::learn_with_physics
