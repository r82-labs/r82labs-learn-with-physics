#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;
using namespace testing;

TEST(SlingshotTest, PropertyAccessors) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                           .efficiency = Efficiency::from_ratio(0.8)});
    EXPECT_NEAR(sling.get_stiffness().get_newtons_per_meter(), 100.0, 1e-4);
    EXPECT_NEAR(sling.get_efficiency().get_ratio(), 0.8, 1e-4);
}

TEST(SlingshotTest, StiffnessUnitConversion) {
    const Stiffness stiffness_kN = Stiffness::from_kilonewtons_per_meter(0.12);
    EXPECT_NEAR(stiffness_kN.get_newtons_per_meter(), 120.0, 1e-3);

    const Stiffness stiffness_lbf_in = Stiffness::from_pounds_force_per_inch(10.0);
    EXPECT_NEAR(stiffness_lbf_in.get_newtons_per_meter(), 1751.26771, 1e-3);

    const Stiffness stiffness_lbf_ft = Stiffness::from_pounds_force_per_foot(1.0);
    EXPECT_NEAR(stiffness_lbf_ft.get_newtons_per_meter(), 14.593903, 1e-6);
}

TEST(EfficiencyTest, RejectsInvalidRatios) {
    EXPECT_THAT([]() { Efficiency::from_ratio(-0.1); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("between 0 and 1")));

    EXPECT_THAT([]() { Efficiency::from_ratio(1.1); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("between 0 and 1")));

    EXPECT_NO_THROW(Efficiency::from_ratio(0.0));
    EXPECT_NO_THROW(Efficiency::from_ratio(1.0));
}

TEST(SlingshotTest, RejectsNegativeStiffness) {
    EXPECT_THAT([]() { Slingshot({.band_stiffness = Stiffness::from_newtons_per_meter(-10.0)}); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("must be non-negative")));
}
