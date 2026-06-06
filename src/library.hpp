#pragma once
#include <vector>
#include <stdexcept>

/**
 * @namespace r82labs::learn_with_physics
 * @brief Core physics simulation components for slingshot mechanics.
 */
namespace r82labs::learn_with_physics {

    /**
     * @enum AngleUnit
     * @brief Units for angular measurements.
     */
    enum class AngleUnit {
        radians, ///< Angle in radians.
        degrees  ///< Angle in degrees.
    };

    /**
     * @enum LaunchDirection
     * @brief Directions for the launch.
     */
    enum class LaunchDirection {
        right, ///< Launch towards positive X.
        left   ///< Launch towards negative X.
    };

    /**
     * @class MathUtils
     * @brief Utility functions for physical and mathematical calculations.
     */
    class MathUtils {
    public:
        /**
         * @brief Converts an angle to radians.
         * @param angle The input angle value.
         * @param unit The unit of the input angle.
         * @return float The angle value in radians.
         */
        [[nodiscard]] static float to_radians(float angle, AngleUnit unit);
    };

    /**
     * @struct Point
     * @brief A simple structure representing a 2D coordinate.
     */
    struct Point {
        float x; ///< The horizontal coordinate.
        float y; ///< The vertical coordinate.
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
         * @throws std::invalid_argument if m <= 0.
         */
        explicit Projectile(float m) : mass(m) {
            if (m <= 0.0f) {
                throw std::invalid_argument("mass must be positive");
            }
        }
        
        /**
         * @brief Gets the mass of the projectile.
         * @return float Mass in kg.
         */
        [[nodiscard]] float get_mass() const { return mass; }
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
            : band_stiffness(k), efficiency(eff) {
            if (k < 0.0f) {
                throw std::invalid_argument("band_stiffness must be non-negative");
            }
            if (eff < 0.0f || eff > 1.0f) {
                throw std::invalid_argument("efficiency must be between 0 and 1");
            }
        }

        /** @brief Gets the band stiffness in N/m. */
        [[nodiscard]] float get_stiffness() const { return band_stiffness; }
        /** @brief Gets the efficiency factor (0.0 to 1.0). */
        [[nodiscard]] float get_efficiency() const { return efficiency; }
    };

    /**
     * @class Simulator
     * @brief Handles trajectory calculations for projectiles.
     */
    class Simulator {
        const float gravity;            ///< Acceleration due to gravity (g)
        const Projectile projectile;    ///< The projectile being simulated
        float x_velocity_factor;        ///< Precomputed v0 * cos(theta)
        float y_velocity_factor;        ///< Precomputed v0 * sin(theta)
        float dir_multiplier;           ///< Direction multiplier for x

    public:
        /**
         * @brief Constructs a Simulator for a configured launch.
         * @param slingshot The Slingshot used for launch.
         * @param proj The Projectile being launched.
         * @param draw_length The draw length in meters.
         * @param angle The launch angle.
         * @param unit The unit of the provided angle (defaults to radians).
         * @param direction The launch direction (defaults to right).
         * @param g Gravity in \f$ m/s^2 \f$ (defaults to 9.81).
         */
        Simulator(const Slingshot& slingshot, const Projectile& proj,
                  float draw_length, float angle,
                  AngleUnit unit = AngleUnit::radians,
                  LaunchDirection direction = LaunchDirection::right,
                  float g = 9.81f);

        /**
         * @brief Calculates the position of a projectile at a specific time.
         * 
         * Using the precomputed launch state:
         * \f[ x(t) = (v_0\cos\theta) t \f]
         * \f[ y(t) = (v_0\sin\theta) t - \frac{1}{2} g t^2 \f]
         * 
         * @param time Time elapsed since launch in seconds.
         * @return Point The (x, y) coordinates at time t.
         */
        [[nodiscard]] Point get_position_at_time(float time) const;

        /**
         * @brief Provides access to the projectile being simulated.
         * @return const Projectile& Reference to the internal projectile.
         */
        [[nodiscard]] const Projectile& get_projectile() const { return projectile; }
    };
}
