#pragma once

#include <core/particle.h>

#include "cinder/gl/gl.h"

namespace idealgas {
class ParticleEngine {
 public:
  ParticleEngine(const size_t& num_pixels_per_side);
  void Update();

  /**
   * Creates a new particle with random position and velocity constrained by
   * the box size and particle radius.
   * @param radius The particle radius.
   */
  void GenerateRandomParticle(const float& radius, const float& mass,
                              const size_t& type);

  const std::vector<Particle>& GetParticles() const;

  /**
   * Clears all particles.
   */
  void Clear();

  /**
   * Adds a particle to the simulation.
   * @param particle The particle to add.
   */
  void AddParticle(const Particle& particle);

  /**
   * Increases the velocity of every particle by 10%
   */
  void AccelerateParticles();

  /**
   * Decreases the velocity of every particle by 10%
   */
  void DeaccelerateParticles();

 private:
  size_t num_pixels_per_side_;
  std::vector<Particle> particles_;

  /**
   * Calculates the new velocity of a particle post collision.
   * @param particle1 The first particle.
   * @param particle2 The second particle.
   * @return A vector that returns the new velocity of particle1.
   */
  glm::vec2 CalculateParticleCollisionVel(const Particle& particle1,
                                          const Particle& particle2) const;

  /**
   * Checks the position and velocity of each particle. Modifies velocity if the
   * particle has collided with a wall.
   */
  void UpdateVelOnWallCollision();

  /**
   * Checks every possible pair of particles and whether they have collided.
   * Modifies velocity accordingly using a formula.
   */
  void UpdateVelOnParticleCollision();

  /**
   * Helper method that takes two particles and determines if they will collide.
   *
   * @param particle1 The first particle.
   * @param particle2 The second particle.
   * @return True if the particles will collide, false if not.
   */
  bool WillParticlesCollide(const Particle& particle1,
                            const Particle& particle2) const;
};
}  // namespace idealgas