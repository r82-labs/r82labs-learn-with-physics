#pragma once
#include <vector>

/**
 * @namespace r82labs::learn_with_physics
 * @brief Core physics simulation components for slingshot mechanics.
 */
namespace r82labs::learn_with_physics {

    /**
     * @struct Point
     * @brief A simple structure representing a 2D coordinate.
     */
    struct Point {
        float x; ///< The horizontal coordinate.
        float y; ///< The vertical coordinate.
    };

    /**
     * @class Slingshot
     * @brief Models a physical slingshot with specific stiffness and efficiency.
     */
    class Slingshot {
        const float band_stiffness; ///< Stiffness constant of the band (k)
        const float efficiency;     ///< Energy transfer efficiency (eta)

    public:
        /**
         * @brief Constructs a new Slingshot object.
         * @param k The band stiffness in N/m.
         * @param eff The efficiency factor (0.0 to 1.0).
         */
        explicit Slingshot(float k, float eff = 0.75f)
            : band_stiffness(k), efficiency(eff) {}

        /**
         * @brief Calculates the launch velocity of a projectile.
         * 
         * The velocity is calculated using the formula:
         * \f[ v = d \sqrt{\frac{\eta k}{m}} \f]
         * where \f$ d \f$ is the draw length, \f$ \eta \f$ is efficiency,
         * \f$ k \f$ is stiffness, and \f$ m \f$ is mass.
         * 
         * @param draw_length_meters Distance the band is pulled back.
         * @param mass_kg Mass of the projectile being launched.
         * @return float The resulting launch velocity in m/s.
         */
        float get_launch_velocity(float draw_length_meters, float mass_kg) const;
    };

    /**
     * @class Projectile
     * @brief Represents an object to be launched.
     */
    class Projectile {
        const float mass; ///< Mass of the projectile in kg

    public:
        /**
         * @brief Constructs a Projectile with a specific mass.
         * @param m Mass in kilograms.
         */
        explicit Projectile(float m) : mass(m) {}
        
        /**
         * @brief Gets the mass of the projectile.
         * @return float Mass in kg.
         */
        float get_mass() const { return mass; }
    };

    /**
     * @class Simulator
     * @brief Handles trajectory calculations for projectiles.
     */
    class Simulator {
        const float gravity; ///< Acceleration due to gravity (g)

    public:
        /**
         * @brief Constructs a Simulator with a specific gravity constant.
         * @param g Gravity in \f$ m/s^2 \f$ (defaults to 9.81).
         */
        explicit Simulator(float g = 9.81f) : gravity(g) {}

        /**
         * @brief Calculates the position of a projectile at a specific time.
         * 
         * Using standard projectile motion equations:
         * \f[ x(t) = v_0 \cos(\theta) t \f]
         * \f[ y(t) = v_0 \sin(\theta) t - \frac{1}{2} g t^2 \f]
         * 
         * @param slingshot The Slingshot used for launch.
         * @param proj The Projectile being simulated.
         * @param draw_length The draw length in meters.
         * @param angle_radians Launch angle in radians.
         * @param time Time elapsed since launch in seconds.
         * @return Point The (x, y) coordinates at time t.
         */
        Point get_position_at_time(const Slingshot& slingshot, const Projectile& proj,
                                  float draw_length, float angle_radians, float time) const;

        /**
         * @brief Calculates the full flight trajectory until the projectile hits the ground.
         * @param slingshot The Slingshot used for launch.
         * @param proj The Projectile being simulated.
         * @param draw_length The draw length in meters.
         * @param angle_radians Launch angle in radians.
         * @param time_step Time interval between trajectory points.
         * @return std::vector<Point> A sequence of points representing the flight path.
         */
        std::vector<Point> calculate_full_trajectory(const Slingshot& slingshot, const Projectile& proj,
                                                     float draw_length, float angle_radians, float time_step) const;
    };
}
