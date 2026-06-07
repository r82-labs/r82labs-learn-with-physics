#pragma once
#include <stdexcept>

namespace r82labs::learn_with_physics {

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

}  // namespace r82labs::learn_with_physics
