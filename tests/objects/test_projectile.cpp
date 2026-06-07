#include <gtest/gtest.h>

#include <stdexcept>

#include "library.hpp"

using namespace r82labs::learn_with_physics;

TEST(ProjectileTest, RejectsInvalidMass) {
    EXPECT_THROW(Projectile({.mass = 0.0f}), std::invalid_argument);
    EXPECT_THROW(Projectile({.mass = -1.0f}), std::invalid_argument);
    EXPECT_NO_THROW(Projectile({.mass = 0.1f}));
}
