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
     * @struct Point
     * @brief A simple structure representing a 2D coordinate.
     */
    struct Point {
        float x; ///< The horizontal coordinate.
        float y; ///< The vertical coordinate.
    };

    /**
     * @struct ProjectileConfig
     * @brief Named parameters for constructing a Projectile.
     */
    struct ProjectileConfig {
        float mass = 0.0f; ///< Mass of the projectile in kg.
    };

    /**
     * @class Projectile
     * @brief Represents an object to be launched.
     */
    class Projectile {
        const float mass; ///< Mass of the projectile in kg

    public:
        /**
         * @brief Constructs a Projectile from a configuration.
         * @param config Named projectile configuration.
         * @throws std::invalid_argument if config.mass <= 0.
         */
        explicit Projectile(const ProjectileConfig& config)
            : mass(config.mass) {
            if (config.mass <= 0.0f) {
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
     * @struct SlingshotConfig
     * @brief Named parameters for constructing a Slingshot.
     */
    struct SlingshotConfig {
        float band_stiffness = 0.0f; ///< Stiffness constant of the band (k).
        float efficiency = 0.75f;    ///< Energy transfer efficiency (eta).
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
         * @brief Constructs a new Slingshot object from a configuration.
         * @param config Named slingshot configuration.
         */
        explicit Slingshot(const SlingshotConfig& config)
            : band_stiffness(config.band_stiffness), efficiency(config.efficiency) {
            if (config.band_stiffness < 0.0f) {
                throw std::invalid_argument("band_stiffness must be non-negative");
            }
            if (config.efficiency < 0.0f || config.efficiency > 1.0f) {
                throw std::invalid_argument("efficiency must be between 0 and 1");
            }
        }

        /** @brief Gets the band stiffness in N/m. */
        [[nodiscard]] float get_stiffness() const { return band_stiffness; }
        /** @brief Gets the efficiency factor (0.0 to 1.0). */
        [[nodiscard]] float get_efficiency() const { return efficiency; }
    };

    /**
     * @struct SimulatorConfig
     * @brief Configuration parameters for creating a Simulator.
     */
    struct SimulatorConfig {
        const Slingshot& slingshot;      ///< The Slingshot used for launch.
        const Projectile& projectile;     ///< The Projectile being launched.
        float draw_length = 1.0f;         ///< The draw length in meters.
        float angle = 45.0f;              ///< The launch angle.
        AngleUnit unit = AngleUnit::radians; ///< The unit of the provided angle.
        LaunchDirection direction = LaunchDirection::right; ///< The launch direction.
        float g = 9.81f;                  ///< Gravity in m/s^2.
    };

    /**
     * @struct TimeRequest
     * @brief Named parameter for requesting a position at a specific time.
     */
    struct TimeRequest {
        float time = 0.0f; ///< Time elapsed since launch in seconds.
    };

    /**
     * @class Simulator
     * @brief Handles trajectory calculations for projectiles.
     */
    class Simulator {
        const float gravity;            ///< Acceleration due to gravity (g)
        const Projectile projectile;    ///< The projectile being simulated
        float x_velocity_factor;        ///< Precomputed v0 * cos(theta) * direction
        float y_velocity_factor;        ///< Precomputed v0 * sin(theta)
        float half_gravity_factor;      ///< Precomputed 0.5 * gravity

    public:
        /**
         * @brief Constructs a Simulator for a configured launch.
         * @param config Named simulator configuration.
         */
        explicit Simulator(const SimulatorConfig& config);

        /**
         * @brief Calculates the position of a projectile at a specific time.
         * 
         * Using the precomputed launch state and Horner's method for efficiency:
         * \f[ x(t) = f_x \cdot t \f]
         * \f[ y(t) = (f_y - \frac{1}{2} g \cdot t) \cdot t \f]
         * 
         * @param request Time request with named parameter.
         * @return Point The (x, y) coordinates at time t.
         */
        [[nodiscard]] Point get_position_at_time(const TimeRequest& request) const;

        /**
         * @brief Provides access to the projectile being simulated.
         * @return const Projectile& Reference to the internal projectile.
         */
        [[nodiscard]] const Projectile& get_projectile() const { return projectile; }
    };
}
