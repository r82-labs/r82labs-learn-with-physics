#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;
using namespace testing;

TEST(ProjectileTest, RejectsInvalidMass) {
    EXPECT_THAT([]() { Projectile({.mass = Mass::from_kilograms(0.0)}); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("mass must be positive")));

    EXPECT_THAT([]() { Projectile({.mass = Mass::from_kilograms(-1.0)}); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("mass must be positive")));

    EXPECT_NO_THROW(Projectile({.mass = Mass::from_kilograms(0.1)}));
}

TEST(ProjectileTest, AcceptsDifferentMassUnits) {
    const Projectile kg_projectile({.mass = Mass::from_kilograms(1.0)});
    const Projectile g_projectile({.mass = Mass::from_grams(1000.0)});
    const Projectile lb_projectile({.mass = Mass::from_pounds(2.20462262)});

    EXPECT_NEAR(kg_projectile.get_mass().get_kilograms(), 1.0, 1e-4);
    EXPECT_NEAR(g_projectile.get_mass().get_kilograms(), 1.0, 1e-4);
    EXPECT_NEAR(lb_projectile.get_mass().get_kilograms(), 1.0, 1e-6);
}

TEST(CoreTypesTest, RejectsInvalidLength) {
    EXPECT_THAT([]() { Length::from_meters(0.0); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("length must be positive")));

    EXPECT_THAT([]() { Length::from_centimeters(-1.0); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("length must be positive")));

    EXPECT_NO_THROW(Length::from_inches(0.1));
}

TEST(CoreTypesTest, RejectsNegativeTime) {
    EXPECT_THAT([]() { Time::from_seconds(-0.1); },
                ThrowsMessage<std::invalid_argument>(HasSubstr("time cannot be negative")));

    EXPECT_NO_THROW(Time::from_seconds(0.0));
}

TEST(CoreTypesTest, AngleGetters) {
    const Angle a = Angle::from_degrees(45.0);
    EXPECT_NEAR(a.get_radians(), 0.78539816339744828, 1e-4);
}

TEST(CoreTypesTest, AngleValidation) {
    EXPECT_NO_THROW(Angle::from_degrees(0.0));
    EXPECT_NO_THROW(Angle::from_degrees(90.0));

    EXPECT_THAT([]() { Angle::from_degrees(-0.1); },
                ThrowsMessage<std::out_of_range>(HasSubstr("between 0 and 90 degrees")));

    EXPECT_THAT([]() { Angle::from_degrees(90.1); },
                ThrowsMessage<std::out_of_range>(HasSubstr("between 0 and 90 degrees")));
}

TEST(CoreTypesTest, LaunchOrientation) {
    const Angle a45 = Angle::from_degrees(45.0);
    const LaunchOrientation right = LaunchOrientation::toward_right(a45);
    const LaunchOrientation left = LaunchOrientation::toward_left(a45);

    EXPECT_NEAR(right.get_radians(), 0.78539816339744828, 1e-4);
    EXPECT_NEAR(left.get_radians(), 2.3561944901923448, 1e-4);
}
