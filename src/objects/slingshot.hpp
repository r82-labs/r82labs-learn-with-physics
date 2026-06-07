#pragma once
#include <stdexcept>

#include "core/types.hpp"

namespace r82labs::learn_with_physics {

struct SlingshotConfig {
    Stiffness band_stiffness = Stiffness::from_newtons_per_meter(0.0);
    Efficiency efficiency = Efficiency::from_ratio(0.75);
};

class Slingshot {
    const Stiffness band_stiffness;
    const Efficiency efficiency;

   public:
    explicit Slingshot(const SlingshotConfig& config)
        : band_stiffness(config.band_stiffness), efficiency(config.efficiency) {
        if (config.band_stiffness.get_newtons_per_meter() < 0.0) {
            throw std::invalid_argument("band_stiffness must be non-negative");
        }
    }

    [[nodiscard]] Stiffness get_stiffness() const { return band_stiffness; }
    [[nodiscard]] Efficiency get_efficiency() const { return efficiency; }
};

}  // namespace r82labs::learn_with_physics
