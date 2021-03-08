#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {
class Particle {
 public:
  Particle(glm::vec2 initial_pos, glm::vec2 initial_vel, float radius,
           float mass, size_t type);

  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  const float& GetRadius() const;
  const float& GetMass() const;
  const size_t& GetType() const;
  void SetVelocity(const glm::vec2& vel);

  /**
   * Updates the position of the particle by adding the velocity vector to the
   * position vector.
   */
  void UpdatePosition();

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  float radius_;
  float mass_;
  size_t type_;
};
}  // namespace idealgas