#include <gtest/gtest.h>

#include <stdexcept>

#include "library.hpp"

using namespace r82labs::learn_with_physics;

TEST(SlingshotTest, PropertyAccessors) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 0.8f});
    EXPECT_FLOAT_EQ(sling.get_stiffness(), 100.0f);
    EXPECT_FLOAT_EQ(sling.get_efficiency(), 0.8f);
}

TEST(SlingshotTest, RejectsNegativeStiffness) {
    EXPECT_THROW(Slingshot({.band_stiffness = -10.0f}), std::invalid_argument);
}

TEST(SlingshotTest, RejectsInvalidEfficiency) {
    EXPECT_THROW(Slingshot({.band_stiffness = 100.0f, .efficiency = -0.1f}), std::invalid_argument);
    EXPECT_THROW(Slingshot({.band_stiffness = 100.0f, .efficiency = 1.1f}), std::invalid_argument);
    EXPECT_NO_THROW(Slingshot({.band_stiffness = 100.0f, .efficiency = 0.0f}));
    EXPECT_NO_THROW(Slingshot({.band_stiffness = 100.0f, .efficiency = 1.0f}));
}
