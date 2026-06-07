#include <gtest/gtest.h>

#include <numbers>
#include <stdexcept>

#include "r82labs_learn_with_physics.hpp"

using namespace r82labs::learn_with_physics;

TEST(SimulatorTest, ExactPositionAtTime) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 1.0f});
    const Projectile proj({.mass = Mass::from_kilograms(1.0f)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0f),
                         .angle = Angle::from_radians(0.0f),
                         .direction = LaunchDirection::right,
                         .g = 10.0f});

    auto [x, y] = sim.get_position_at_time({.time = Time::from_seconds(1.0f)});

    EXPECT_FLOAT_EQ(x, 10.0f);
    EXPECT_FLOAT_EQ(y, -5.0f);
}

TEST(SimulatorTest, GroundTimeCalculation) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 1.0f});
    const Projectile proj({.mass = Mass::from_kilograms(1.0f)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0f),
                         .angle = Angle::from_degrees(45.0f),
                         .direction = LaunchDirection::right,
                         .g = 10.0f});

    const Time ground_time = sim.get_time_at_ground();
    EXPECT_GT(ground_time.as_seconds(), 0.0f);

    const Point final_position = sim.get_position_at_time({.time = ground_time});
    EXPECT_NEAR(final_position.y, 0.0f, 1e-4f);
}

TEST(SimulatorTest, ApexCalculation) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 1.0f});
    const Projectile proj({.mass = Mass::from_kilograms(1.0f)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0f),
                         .angle = Angle::from_degrees(45.0f),
                         .direction = LaunchDirection::right,
                         .g = 10.0f});

    const PointInTime apex = sim.get_apex_point_in_time();
    EXPECT_NEAR(apex.time.as_seconds(), 0.70710677f, 1e-4f);
    EXPECT_NEAR(apex.position.x, 5.0f, 1e-4f);
    EXPECT_NEAR(apex.position.y, 2.5f, 1e-4f);
}

TEST(SimulatorTest, DegreesSupport) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 1.0f});
    const Projectile proj({.mass = Mass::from_kilograms(1.0f)});
    const Simulator sim_deg({.slingshot = sling,
                             .projectile = proj,
                             .draw_length = Length::from_meters(1.0f),
                             .angle = Angle::from_degrees(90.0f)});
    const Simulator sim_rad({.slingshot = sling,
                             .projectile = proj,
                             .draw_length = Length::from_meters(1.0f),
                             .angle = Angle::from_radians(std::numbers::pi_v<float> / 2.0f)});

    auto pos_deg = sim_deg.get_position_at_time({.time = Time::from_seconds(1.0f)});
    auto pos_rad = sim_rad.get_position_at_time({.time = Time::from_seconds(1.0f)});

    EXPECT_NEAR(pos_deg.x, pos_rad.x, 0.0001f);
    EXPECT_NEAR(pos_deg.y, pos_rad.y, 0.0001f);
    EXPECT_NEAR(pos_deg.x, 0.0f, 0.0001f);
}

TEST(SimulatorTest, DirectionSupport) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 1.0f});
    const Projectile proj({.mass = Mass::from_kilograms(1.0f)});
    const Simulator sim_right({.slingshot = sling,
                               .projectile = proj,
                               .draw_length = Length::from_meters(1.0f),
                               .angle = Angle::from_degrees(0.0f),
                               .direction = LaunchDirection::right});
    const Simulator sim_left({.slingshot = sling,
                              .projectile = proj,
                              .draw_length = Length::from_meters(1.0f),
                              .angle = Angle::from_degrees(0.0f),
                              .direction = LaunchDirection::left});

    auto pos_right = sim_right.get_position_at_time({.time = Time::from_seconds(1.0f)});
    auto pos_left = sim_left.get_position_at_time({.time = Time::from_seconds(1.0f)});

    EXPECT_FLOAT_EQ(pos_right.x, 10.0f);
    EXPECT_FLOAT_EQ(pos_left.x, -10.0f);
    EXPECT_FLOAT_EQ(pos_right.y, pos_left.y);
}

TEST(SimulatorTest, AngleValidation) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 1.0f});
    const Projectile proj({.mass = Mass::from_kilograms(1.0f)});

    // Test bounds (Explicitly checking 0 and 90 degrees)
    EXPECT_NO_THROW(Simulator({.slingshot = sling,
                               .projectile = proj,
                               .draw_length = Length::from_meters(1.0f),
                               .angle = Angle::from_degrees(0.0f)}));
    EXPECT_NO_THROW(Simulator({.slingshot = sling,
                               .projectile = proj,
                               .draw_length = Length::from_meters(1.0f),
                               .angle = Angle::from_degrees(90.0f)}));
    EXPECT_NO_THROW(Simulator({.slingshot = sling,
                               .projectile = proj,
                               .draw_length = Length::from_meters(1.0f),
                               .angle = Angle::from_radians(0.0f)}));
    EXPECT_NO_THROW(Simulator({.slingshot = sling,
                               .projectile = proj,
                               .draw_length = Length::from_meters(1.0f),
                               .angle = Angle::from_radians(std::numbers::pi_v<float> / 2.0f)}));

    // Test out of range (Simulator should throw)
    EXPECT_THROW(Simulator({.slingshot = sling,
                            .projectile = proj,
                            .draw_length = Length::from_meters(1.0f),
                            .angle = Angle::from_degrees(-0.1f)}),
                 std::out_of_range);
    EXPECT_THROW(Simulator({.slingshot = sling,
                            .projectile = proj,
                            .draw_length = Length::from_meters(1.0f),
                            .angle = Angle::from_degrees(90.1f)}),
                 std::out_of_range);
    EXPECT_THROW(Simulator({.slingshot = sling,
                            .projectile = proj,
                            .draw_length = Length::from_meters(1.0f),
                            .angle = Angle::from_degrees(150.0f)}),
                 std::out_of_range);
}

TEST(SimulatorTest, GetProjectile) {
    const Slingshot sling({.band_stiffness = 100.0f, .efficiency = 1.0f});
    const Projectile proj({.mass = Mass::from_kilograms(1.0f)});
    const Simulator sim({.slingshot = sling,
                         .projectile = proj,
                         .draw_length = Length::from_meters(1.0f),
                         .angle = Angle::from_radians(0.0f)});

    EXPECT_FLOAT_EQ(sim.get_projectile().get_mass().as_kilograms(), 1.0f);
}

TEST(LibraryCoverageTest, AdditionalCoverage) {
    const Projectile p({.mass = Mass::from_kilograms(5.0f)});
    EXPECT_FLOAT_EQ(p.get_mass().as_kilograms(), 5.0f);

    const Slingshot default_sling({.band_stiffness = 100.0f});
    const Simulator default_sim({.slingshot = default_sling,
                                 .projectile = p,
                                 .draw_length = Length::from_meters(1.0f),
                                 .angle = Angle::from_degrees(45.0f)});
    auto [x, y] = default_sim.get_position_at_time({.time = Time::from_seconds(0.1f)});
}
