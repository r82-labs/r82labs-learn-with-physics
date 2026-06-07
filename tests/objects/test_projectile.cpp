#include <gtest/gtest.h>

#include <stdexcept>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;

TEST(ProjectileTest, RejectsInvalidMass) {
    EXPECT_THROW(Projectile({.mass = Mass::from_kilograms(0.0f)}), std::invalid_argument);
    EXPECT_THROW(Projectile({.mass = Mass::from_kilograms(-1.0f)}), std::invalid_argument);
    EXPECT_NO_THROW(Projectile({.mass = Mass::from_kilograms(0.1f)}));
}

TEST(ProjectileTest, AcceptsDifferentMassUnits) {
    const Projectile kg_projectile({.mass = Mass::from_kilograms(1.0f)});
    const Projectile g_projectile({.mass = Mass::from_grams(1000.0f)});
    const Projectile lb_projectile({.mass = Mass::from_pounds(2.20462262f)});

    EXPECT_FLOAT_EQ(kg_projectile.get_mass().as_kilograms(), 1.0f);
    EXPECT_FLOAT_EQ(g_projectile.get_mass().as_kilograms(), 1.0f);
    EXPECT_NEAR(lb_projectile.get_mass().as_kilograms(), 1.0f, 1e-6f);
}

TEST(CoreTypesTest, RejectsInvalidLength) {
    EXPECT_THROW(Length::from_meters(0.0f), std::invalid_argument);
    EXPECT_THROW(Length::from_centimeters(-1.0f), std::invalid_argument);
    EXPECT_NO_THROW(Length::from_inches(0.1f));
}

TEST(CoreTypesTest, RejectsNegativeTime) {
    EXPECT_THROW(Time::from_seconds(-0.1f), std::invalid_argument);
    EXPECT_NO_THROW(Time::from_seconds(0.0f));
}
