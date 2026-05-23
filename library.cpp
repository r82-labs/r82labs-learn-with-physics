#include "library.hpp"

namespace r82labs::learn_with_physics {

    float Slingshot::getLaunchVelocity(const float drawLengthMeters, const float massKg) const {
        if (massKg <= 0.0f) return 0.0f;

        return drawLengthMeters * std::sqrt((efficiency * bandStiffness) / massKg);
    }

    Vector2 Simulator::getPositionAtTime(const Slingshot& slingshot, const Projectile& proj,
                                         const float drawLength, const float angleRadians, const float time) const {

        const float v0 = slingshot.getLaunchVelocity(drawLength, proj.getMass());

        const float v0x = v0 * std::cos(angleRadians);
        const float v0y = v0 * std::sin(angleRadians);

        const float x = v0x * time;
        const float y = (v0y * time) - (0.5f * gravity * time * time);

        return {x, y};
    }

    std::vector<Vector2> Simulator::calculateFullTrajectory(const Slingshot& slingshot, const Projectile& proj,
                                                            const float drawLength, const float angleRadians, const float timeStep) const {
        std::vector<Vector2> trajectory;
        float time = 0.0f;
        Vector2 currentPos;

        do {
            currentPos = getPositionAtTime(slingshot, proj, drawLength, angleRadians, time);

            if (currentPos.y >= 0.0f) {
                trajectory.push_back(currentPos);
            }
            time += timeStep;

        } while (currentPos.y >= 0.0f);

        return trajectory;
    }
}