#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <vector>
#include <cmath>     // sin, cos
#include "simplerandom.hpp"
#include "heightmap.hpp"
#include "rectangle.hpp"
#include "segment_data.hpp"
#include "utils.hpp"
#include "bounds.hpp"

#define CONT_BASE 1.0 ///< Height limit that separates seas from dry land.
#define INITIAL_SPEED_X 1
#define DEFORMATION_WEIGHT 2

typedef uint32_t ContinentId;

class plate;

class Movement
{
public:
    Movement(SimpleRandom randsource, const WorldDimension& worldDimension);
    void applyFriction(float deformed_mass, float mass);
    void move();
    float velocityOnX() const;
    float velocityOnY() const;
    float velocityOnX(float length) const;
    float velocityOnY(float length) const;
    float dot(float dx_, float dy_) const;
    float relativeUnitVelocityOnX(const Movement& m) const;
    float relativeUnitVelocityOnY(const Movement& m) const;
    float momentum(float mass) const throw() { return mass * velocity; }
    float getVelocity() const { return velocity; };
    float velX() const throw() { return vx; }
    float velY() const throw() { return vy; }
    void collide(plate& thisPlate, plate& p, Movement& thisMovement, Movement& otherMovement, uint32_t wx, uint32_t wy, float coll_mass);
    void decDx(float delta) { dx -= delta; }
    void decDy(float delta) { dy -= delta; }
private:
    SimpleRandom _randsource;
    const WorldDimension _worldDimension;
    float velocity;       ///< Plate's velocity.
    float rot_dir;        ///< Direction of rotation: 1 = CCW, -1 = ClockWise.
    float dx, dy;         ///< X and Y components of plate's acceleration vector.
    float vx, vy;         ///< X and Y components of plate's direction unit vector.
};


#endif