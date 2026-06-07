#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numbers>
#include <stdexcept>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;
using namespace testing;

TEST(SimulatorTest, ExactPositionAtTime) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                           .efficiency = Efficiency::from_ratio(1.0)});
    const Projectile proj({.mass = Mass::from_kilograms(1.0)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0),
                         .orientation = LaunchOrientation::toward_right(Angle::from_degrees(0.0)),
                         .g = Acceleration::from_meters_per_second_squared(10.0)});

    auto [x, y] = sim.get_position_at_time({.time = Time::from_seconds(1.0)});

    EXPECT_NEAR(x, 10.0, 1e-4);
    EXPECT_NEAR(y, -5.0, 1e-4);
}

TEST(SimulatorTest, GroundTimeCalculation) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                           .efficiency = Efficiency::from_ratio(1.0)});
    const Projectile proj({.mass = Mass::from_kilograms(1.0)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0),
                         .orientation = LaunchOrientation::toward_right(Angle::from_degrees(45.0)),
                         .g = Acceleration::from_meters_per_second_squared(10.0)});

    const Time ground_time = sim.get_time_at_ground();
    EXPECT_GT(ground_time.get_seconds(), 0.0);

    const Point final_position = sim.get_position_at_time({.time = ground_time});
    EXPECT_NEAR(final_position.y, 0.0, 1e-4);
}

TEST(SimulatorTest, ApexCalculation) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                           .efficiency = Efficiency::from_ratio(1.0)});
    const Projectile proj({.mass = Mass::from_kilograms(1.0)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0),
                         .orientation = LaunchOrientation::toward_right(Angle::from_degrees(45.0)),
                         .g = Acceleration::from_meters_per_second_squared(10.0)});

    const PointInTime apex = sim.get_apex_point_in_time();
    EXPECT_NEAR(apex.time.get_seconds(), 0.70710677, 1e-4);
    EXPECT_NEAR(apex.position.x, 5.0, 1e-4);
    EXPECT_NEAR(apex.position.y, 2.5, 1e-4);
}

TEST(SimulatorTest, DirectionSupport) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                           .efficiency = Efficiency::from_ratio(1.0)});
    const Projectile proj({.mass = Mass::from_kilograms(1.0)});
    const Simulator sim_right(
        {.slingshot = sling,
         .projectile = proj,
         .draw_length = Length::from_meters(1.0),
         .orientation = LaunchOrientation::toward_right(Angle::from_degrees(0.0))});
    const Simulator sim_left(
        {.slingshot = sling,
         .projectile = proj,
         .draw_length = Length::from_meters(1.0),
         .orientation = LaunchOrientation::toward_left(Angle::from_degrees(0.0))});

    auto pos_right = sim_right.get_position_at_time({.time = Time::from_seconds(1.0)});
    auto pos_left = sim_left.get_position_at_time({.time = Time::from_seconds(1.0)});

    EXPECT_NEAR(pos_right.x, 10.0, 1e-4);
    EXPECT_NEAR(pos_left.x, -10.0, 1e-4);
    EXPECT_NEAR(pos_right.y, pos_left.y, 1e-4);
}

TEST(SimulatorTest, AngleValidation) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                           .efficiency = Efficiency::from_ratio(1.0)});
    const Projectile proj({.mass = Mass::from_kilograms(1.0)});

    // Test bounds (Explicitly checking 0 and 90 degrees)
    EXPECT_NO_THROW(
        Simulator({.slingshot = sling,
                   .projectile = proj,
                   .draw_length = Length::from_meters(1.0),
                   .orientation = LaunchOrientation::toward_right(Angle::from_degrees(0.0))}));
    EXPECT_NO_THROW(
        Simulator({.slingshot = sling,
                   .projectile = proj,
                   .draw_length = Length::from_meters(1.0),
                   .orientation = LaunchOrientation::toward_right(Angle::from_degrees(90.0))}));

    // Test out of range (Angle factory should throw)
    EXPECT_THAT([&]() { Angle::from_degrees(-0.1); },
                ThrowsMessage<std::out_of_range>(HasSubstr("between 0 and 90 degrees")));

    EXPECT_THAT([&]() { Angle::from_degrees(90.1); },
                ThrowsMessage<std::out_of_range>(HasSubstr("between 0 and 90 degrees")));
}

TEST(SimulatorTest, GetProjectile) {
    const Slingshot sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0),
                           .efficiency = Efficiency::from_ratio(1.0)});
    const Projectile proj({.mass = Mass::from_kilograms(1.0)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0),
                         .orientation = LaunchOrientation::toward_right(Angle::from_degrees(0.0))});

    EXPECT_NEAR(sim.get_projectile().get_mass().get_kilograms(), 1.0, 1e-4);
}

TEST(LibraryCoverageTest, AdditionalCoverage) {
    const Projectile p({.mass = Mass::from_kilograms(5.0)});
    EXPECT_NEAR(p.get_mass().get_kilograms(), 5.0, 1e-4);

    const Slingshot default_sling({.band_stiffness = Stiffness::from_newtons_per_meter(100.0)});
    const Simulator default_sim(
        {.slingshot = default_sling,
         .projectile = p,
         .draw_length = Length::from_meters(1.0),
         .orientation = LaunchOrientation::toward_right(Angle::from_degrees(45.0))});
    auto [x, y] = default_sim.get_position_at_time({.time = Time::from_seconds(0.1)});
}
