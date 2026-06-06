#include <gtest/gtest.h>
#include "library.hpp"
#include <cmath>
#include <numbers>
#include <stdexcept>

using namespace r82labs::learn_with_physics;

TEST(SlingshotTest, PropertyAccessors) {
    const Slingshot sling(100.0f, 0.8f);
    EXPECT_FLOAT_EQ(sling.get_stiffness(), 100.0f);
    EXPECT_FLOAT_EQ(sling.get_efficiency(), 0.8f);
}

TEST(SlingshotTest, RejectsNegativeStiffness) {
    EXPECT_THROW(Slingshot(-10.0f), std::invalid_argument);
}

TEST(SlingshotTest, RejectsInvalidEfficiency) {
    EXPECT_THROW(Slingshot(100.0f, -0.1f), std::invalid_argument);
    EXPECT_THROW(Slingshot(100.0f, 1.1f), std::invalid_argument);
    EXPECT_NO_THROW(Slingshot(100.0f, 0.0f));
    EXPECT_NO_THROW(Slingshot(100.0f, 1.0f));
}

TEST(ProjectileTest, RejectsInvalidMass) {
    EXPECT_THROW(Projectile(0.0f), std::invalid_argument);
    EXPECT_THROW(Projectile(-1.0f), std::invalid_argument);
    EXPECT_NO_THROW(Projectile(0.1f));
}

TEST(SimulatorTest, ExactPositionAtTime) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(sling, proj, 1.0f, 0.0f, AngleUnit::radians, LaunchDirection::right, 10.0f);

    auto [x, y] = sim.get_position_at_time(1.0f);

    EXPECT_FLOAT_EQ(x, 10.0f);
    EXPECT_FLOAT_EQ(y, -5.0f);
}

TEST(SimulatorTest, DegreesSupport) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim_deg(sling, proj, 1.0f, 90.0f, AngleUnit::degrees);
    const Simulator sim_rad(sling, proj, 1.0f, std::numbers::pi / 2.0f, AngleUnit::radians);

    auto pos_deg = sim_deg.get_position_at_time(1.0f);
    auto pos_rad = sim_rad.get_position_at_time(1.0f);

    EXPECT_NEAR(pos_deg.x, pos_rad.x, 0.0001f);
    EXPECT_NEAR(pos_deg.y, pos_rad.y, 0.0001f);
    EXPECT_NEAR(pos_deg.x, 0.0f, 0.0001f);
}

TEST(SimulatorTest, DirectionSupport) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim_right(sling, proj, 1.0f, 0.0f, AngleUnit::degrees, LaunchDirection::right);
    const Simulator sim_left(sling, proj, 1.0f, 0.0f, AngleUnit::degrees, LaunchDirection::left);

    auto pos_right = sim_right.get_position_at_time(1.0f);
    auto pos_left = sim_left.get_position_at_time(1.0f);

    EXPECT_FLOAT_EQ(pos_right.x, 10.0f);
    EXPECT_FLOAT_EQ(pos_left.x, -10.0f);
    EXPECT_FLOAT_EQ(pos_right.y, pos_left.y);
}

TEST(SimulatorTest, AngleValidation) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);

    // Test bounds
    EXPECT_NO_THROW(Simulator(sling, proj, 1.0f, 0.0f, AngleUnit::degrees));
    EXPECT_NO_THROW(Simulator(sling, proj, 1.0f, 90.0f, AngleUnit::degrees));

    // Test out of range (Simulator should throw)
    EXPECT_THROW(Simulator(sling, proj, 1.0f, -0.1f, AngleUnit::degrees), std::out_of_range);
    EXPECT_THROW(Simulator(sling, proj, 1.0f, 90.1f, AngleUnit::degrees), std::out_of_range);
    EXPECT_THROW(Simulator(sling, proj, 1.0f, 150.0f, AngleUnit::degrees), std::out_of_range);
}

TEST(SimulatorTest, GetProjectile) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(sling, proj, 1.0f, 0.0f, AngleUnit::radians);
    
    EXPECT_FLOAT_EQ(sim.get_projectile().get_mass(), 1.0f);
}

TEST(LibraryCoverageTest, AdditionalCoverage) {
    // Cover MathUtils with Radians and larger ranges (pure conversion)
    EXPECT_FLOAT_EQ(MathUtils::to_radians(1.0f, AngleUnit::radians), 1.0f);
    EXPECT_FLOAT_EQ(MathUtils::to_radians(180.0f, AngleUnit::degrees), std::numbers::pi_v<float>);
    EXPECT_FLOAT_EQ(MathUtils::to_radians(-90.0f, AngleUnit::degrees), -std::numbers::pi_v<float> / 2.0f);

    // Cover Projectile mass getter explicitly
    const Projectile p(5.0f);
    EXPECT_FLOAT_EQ(p.get_mass(), 5.0f);

    // Cover Simulator configured launch state
    const Slingshot default_sling(100.0f);
    const Simulator default_sim(default_sling, p, 1.0f, 45.0f, AngleUnit::degrees);
    auto [x, y] = default_sim.get_position_at_time(0.1f);
    EXPECT_GT(x, 0.0f);
}
