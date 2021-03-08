#pragma once

#include <core/particle.h>
#include <core/particle_engine.h>

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

class ParticleSimulator {
 public:
  ParticleSimulator(const glm::vec2& top_left_corner,
              const size_t& num_pixels_per_side);

  /**
   *
   */
  void Update();

  /**
   *
   * @param radius The desired particle radius
   * @param mass The desired particle mass
   */
  void GenerateRandomParticle(const float& radius, const float& mass, const size_t& type);

  const ParticleEngine& GetParticleEngine() const;

  // Draws the box and all particles.
  void Draw() const;

  // Deletes all particles.
  void Clear();

  /**
   * Increases the velocity of every particle by 10%
   */
  void AccelerateSimulation();

  /**
   * Decreases the velocity of every particle by 10%
   */
  void DeaccelerateSimulation();

 private:
  glm::vec2 top_left_corner_;
  size_t num_pixels_per_side_;
  ParticleEngine particle_engine_;
  const ci::Color kParticleBoxColor = ci::Color::white();

};

}  // namespace visualizer

}  // namespace idealgas
