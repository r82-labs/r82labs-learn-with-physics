#include <gtest/gtest.h>
#include "library.hpp"

using namespace r82labs::learn_with_physics;

TEST(SlingshotTest, LaunchVelocityCalculations) {
    const Slingshot sling(100.0f, 1.0f);

    EXPECT_FLOAT_EQ(sling.getLaunchVelocity(1.0f, 1.0f), 10.0f);

    EXPECT_FLOAT_EQ(sling.getLaunchVelocity(1.0f, 0.0f), 0.0f);

    const Slingshot weakSling(100.0f, 0.5f);

    EXPECT_NEAR(weakSling.getLaunchVelocity(1.0f, 1.0f), 7.07106f, 0.0001f);
}

TEST(SimulatorTest, ExactPositionAtTime) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(10.0f);

    auto [x, y] = sim.getPositionAtTime(sling, proj, 1.0f, 0.0f, 1.0f);

    EXPECT_FLOAT_EQ(x, 10.0f);

    EXPECT_FLOAT_EQ(y, -5.0f);
}

TEST(SimulatorTest, FullTrajectoryBounds) {
    const Slingshot sling(100.0f, 1.0f);
    const Projectile proj(1.0f);
    const Simulator sim(10.0f);

    const auto trajectory = sim.calculateFullTrajectory(sling, proj, 1.0f, M_PI / 2.0f, 0.1f);

    ASSERT_FALSE(trajectory.empty());

    EXPECT_FLOAT_EQ(trajectory.front().x, 0.0f);
    EXPECT_FLOAT_EQ(trajectory.front().y, 0.0f);

   EXPECT_GE(trajectory.back().y, 0.0f);

   for (const auto& point : trajectory) {
        EXPECT_NEAR(point.x, 0.0f, 0.0001f);
    }
}