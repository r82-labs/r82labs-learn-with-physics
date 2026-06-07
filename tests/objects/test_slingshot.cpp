#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;
using namespace testing;

TEST(SlingshotTest, PropertyAccessors) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0f),
                           .efficiency = Efficiency::from_ratio(0.8f)});
    EXPECT_FLOAT_EQ(sling.get_stiffness().as_newtons_per_meter(), 100.0f);
    EXPECT_FLOAT_EQ(sling.get_efficiency().as_ratio(), 0.8f);
}

TEST(SlingshotTest, StiffnessUnitConversion) {
    const Stiffness stiffness_kN = Stiffness::from_kilonewtons_per_meter(0.12f);
    EXPECT_NEAR(stiffness_kN.as_newtons_per_meter(), 120.0f, 1e-3f);

    const Stiffness stiffness_lbf_in = Stiffness::from_pounds_force_per_inch(10.0f);
    EXPECT_NEAR(stiffness_lbf_in.as_newtons_per_meter(), 1751.26771f, 1e-3f);

    const Stiffness stiffness_lbf_ft = Stiffness::from_pounds_force_per_foot(1.0f);
    EXPECT_NEAR(stiffness_lbf_ft.as_newtons_per_meter(), 14.593903f, 1e-6f);
}

TEST(EfficiencyTest, RejectsInvalidRatios) {
    EXPECT_THAT([]() { Efficiency::from_ratio(-0.1f); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("between 0 and 1")));
                
    EXPECT_THAT([]() { Efficiency::from_ratio(1.1f); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("between 0 and 1")));

    EXPECT_NO_THROW(Efficiency::from_ratio(0.0f));
    EXPECT_NO_THROW(Efficiency::from_ratio(1.0f));
}

TEST(SlingshotTest, RejectsNegativeStiffness) {
    EXPECT_THAT([]() { Slingshot({.band_stiffness = Stiffness::from_newtons_per_meter(-10.0f)}); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("must be non-negative")));
}
