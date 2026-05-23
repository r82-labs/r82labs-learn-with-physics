#pragma once
#include <vector>

namespace r82labs::learn_with_physics {

    struct Vector2 {
        float x, y;
    };

    class Slingshot {
        float bandStiffness;
        float efficiency;

    public:
        explicit Slingshot(float k, float eff = 0.75f)
            : bandStiffness(k), efficiency(eff) {}

        float getLaunchVelocity(float drawLengthMeters, float massKg) const;
    };

    class Projectile {
        float mass;

    public:
        explicit Projectile(const float m) : mass(m) {}
        float getMass() const { return mass; }
    };

    class Simulator {
        float gravity;

    public:
        explicit Simulator(float g = 9.81f) : gravity(g) {}

        Vector2 getPositionAtTime(const Slingshot& slingshot, const Projectile& proj,
                                  float drawLength, float angleRadians, float time) const;

        std::vector<Vector2> calculateFullTrajectory(const Slingshot& slingshot, const Projectile& proj,
                                                     float drawLength, float angleRadians, float timeStep) const;
    };
}