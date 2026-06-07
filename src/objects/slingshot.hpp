#pragma once
#include <stdexcept>

namespace r82labs::learn_with_physics {

struct SlingshotConfig {
    Stiffness band_stiffness = Stiffness::from_newtons_per_meter(0.0f);
    Efficiency efficiency = Efficiency::from_ratio(0.75f);
};

class Slingshot {
    const Stiffness band_stiffness;
    const Efficiency efficiency;

   public:
    explicit Slingshot(const SlingshotConfig& config)
        : band_stiffness(config.band_stiffness), efficiency(config.efficiency) {
        if (config.band_stiffness.as_newtons_per_meter() < 0.0f) {
            throw std::invalid_argument("band_stiffness must be non-negative");
        }
        if (config.efficiency.as_ratio() < 0.0f || config.efficiency.as_ratio() > 1.0f) {
            throw std::invalid_argument("efficiency must be between 0 and 1");
        }
    }

    [[nodiscard]] Stiffness get_stiffness() const { return band_stiffness; }
    [[nodiscard]] Efficiency get_efficiency() const { return efficiency; }
};

}  // namespace r82labs::learn_with_physics
