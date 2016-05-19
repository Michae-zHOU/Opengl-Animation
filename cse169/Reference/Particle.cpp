//
//  SpringDamper.cpp
//  cse169
//
//  Created by Ziyao Zhou on 4/22/16.
//
//

#include "Particle.h"

void Particle::Update(float deltaTime) {
    // Compute acceleration (Newton’s second law)
    Vector3 Accel=(1.0/Mass) * Force;
    // Compute new position & velocity
    Velocity+=Accel*deltaTime;
    Position+=Velocity*deltaTime;
    // Zero out Force vector
    Force.Zero();
}

// Constructors
Particle::Particle(Vector3 position, Vector3 acceleration)
: m_position(position), m_velocity(0,0,0), m_acceleration(acceleration), m_forceAccumulated(0,0,0), m_normal(0,0,0), m_damping(0.4), m_inverseMass(1), m_stationary(false)
{
}

Particle::Particle(const Particle& particle)
: m_position(particle.getPosition()), m_velocity(particle.getVelocity()), m_acceleration(particle.getAcceleration()), m_forceAccumulated(particle.getForceAccumulated()),
m_normal(particle.getNormal()), m_damping(particle.getDamping()), m_inverseMass(particle.getInverseMass()), m_stationary(particle.getStationary())
{
}

Particle::Particle()
: m_position(0,0,0), m_velocity(0,0,0), m_acceleration(0,0,0), m_forceAccumulated(0,0,0), m_normal(0,0,0), m_damping(0.7), m_inverseMass(1), m_stationary(false)
{
}

Particle& Particle::operator= (const Particle& particle) {
    m_position = particle.getPosition();
    m_velocity = particle.getVelocity();
    m_acceleration = particle.getAcceleration();
    m_forceAccumulated = particle.getForceAccumulated();
    m_normal = particle.getNormal();
    m_damping = particle.getDamping();
    m_inverseMass = particle.getInverseMass();
    m_stationary = particle.getStationary();
    return *this;
}

// Move the Particle forward in time by applying acceleration to the velocity and moving the position by the velocity
void Particle::integrate(float duration)
{
    // If the object is moving forward in time and not stationary
    if ((duration > 0) && (!m_stationary)){
        
        // Move forward by the specified duration
        m_position += m_velocity * duration;
        m_velocity += (m_forceAccumulated * m_inverseMass) * duration;
        
        m_forceAccumulated = Vector3(0,0,0);
        
        m_velocity *= pow(m_damping, duration);
    }
}