#include <gtest/gtest.h>
#include "library.hpp"
#include <cmath>
#include <numbers>
#include <stdexcept>

using namespace r82labs::learn_with_physics;

TEST(SlingshotTest, LaunchVelocityCalculations) {
    const Slingshot sling(100.0f, 1.0f);

    EXPECT_FLOAT_EQ(sling.get_launch_velocity(1.0f, 1.0f), 10.0f);

    EXPECT_FLOAT_EQ(sling.get_launch_velocity(1.0f, 0.0f), 0.0f);

    const Slingshot weak_sling(100.0f, 0.5f);

    EXPECT_NEAR(weak_sling.get_launch_velocity(1.0f, 1.0f), 7.07106f, 0.0001f);
}

TEST(SimulatorTest, ExactPositionAtTime) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(10.0f);

    auto [x, y] = sim.get_position_at_time(sling, proj, 1.0f, 0.0f, 1.0f);

    EXPECT_FLOAT_EQ(x, 10.0f);

    EXPECT_FLOAT_EQ(y, -5.0f);
}

TEST(SimulatorTest, DegreesSupport) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(10.0f);

    auto pos_deg = sim.get_position_at_time(sling, proj, 1.0f, 90.0f, 1.0f, AngleUnit::degrees);
    auto pos_rad = sim.get_position_at_time(sling, proj, 1.0f, std::numbers::pi / 2.0f, 1.0f, AngleUnit::radians);

    EXPECT_NEAR(pos_deg.x, pos_rad.x, 0.0001f);
    EXPECT_NEAR(pos_deg.y, pos_rad.y, 0.0001f);
    EXPECT_NEAR(pos_deg.x, 0.0f, 0.0001f);
}

TEST(SimulatorTest, DirectionSupport) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(10.0f);

    auto pos_right = sim.get_position_at_time(sling, proj, 1.0f, 0.0f, 1.0f, AngleUnit::degrees, LaunchDirection::right);
    auto pos_left = sim.get_position_at_time(sling, proj, 1.0f, 0.0f, 1.0f, AngleUnit::degrees, LaunchDirection::left);

    EXPECT_FLOAT_EQ(pos_right.x, 10.0f);
    EXPECT_FLOAT_EQ(pos_left.x, -10.0f);
    EXPECT_FLOAT_EQ(pos_right.y, pos_left.y);
}

TEST(SimulatorTest, AngleValidation) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(10.0f);

    // Test bounds
    EXPECT_NO_THROW(sim.get_position_at_time(sling, proj, 1.0f, 0.0f, 1.0f, AngleUnit::degrees));
    EXPECT_NO_THROW(sim.get_position_at_time(sling, proj, 1.0f, 90.0f, 1.0f, AngleUnit::degrees));

    // Test out of range
    EXPECT_THROW(sim.get_position_at_time(sling, proj, 1.0f, -0.1f, 1.0f, AngleUnit::degrees), std::out_of_range);
    EXPECT_THROW(sim.get_position_at_time(sling, proj, 1.0f, 90.1f, 1.0f, AngleUnit::degrees), std::out_of_range);
    EXPECT_THROW(sim.get_position_at_time(sling, proj, 1.0f, 150.0f, 1.0f, AngleUnit::degrees), std::out_of_range);
}

TEST(SimulatorTest, FullTrajectoryBounds) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(10.0f);

    const auto trajectory = sim.calculate_full_trajectory(sling, proj, 1.0f, 45.0f, 0.1f, AngleUnit::degrees, LaunchDirection::left);

    ASSERT_FALSE(trajectory.empty());

    EXPECT_FLOAT_EQ(trajectory.front().x, 0.0f);
    EXPECT_FLOAT_EQ(trajectory.front().y, 0.0f);

   EXPECT_GE(trajectory.back().y, -0.001f);

   for (size_t i = 1; i < trajectory.size(); ++i) {
        EXPECT_LE(trajectory[i].x, 0.0f);
    }
}

TEST(LibraryCoverageTest, AdditionalCoverage) {
    // Cover default efficiency
    const Slingshot default_sling(100.0f);
    EXPECT_NEAR(default_sling.get_launch_velocity(1.0f, 1.0f), 8.66025f, 0.0001f); // sqrt(0.75 * 100)

    // Cover MathUtils with Radians
    EXPECT_FLOAT_EQ(MathUtils::to_radians(1.0f, AngleUnit::radians), 1.0f);
    EXPECT_THROW(MathUtils::to_radians(-0.1f, AngleUnit::radians), std::out_of_range);
    EXPECT_THROW(MathUtils::to_radians(2.0f, AngleUnit::radians), std::out_of_range);

    // Cover Projectile mass getter explicitly
    const Projectile p(5.0f);
    EXPECT_FLOAT_EQ(p.get_mass(), 5.0f);

    // Cover Simulator default constructor
    const Simulator default_sim;
    auto [x, y] = default_sim.get_position_at_time(default_sling, p, 1.0f, 45.0f, 0.1f, AngleUnit::degrees);
    EXPECT_GT(x, 0.0f);
}
