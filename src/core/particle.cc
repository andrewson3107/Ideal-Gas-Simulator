#include <core/particle.h>

namespace idealgas {

Particle::Particle(glm::vec2 initial_pos, glm::vec2 initial_vel, float radius,
                   float mass, size_t type)
    : position_(initial_pos), velocity_(initial_vel), radius_(radius), mass_(mass),
      type_(type) {
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

const glm::vec2& Particle::GetPosition() const{
  return position_;
}

const glm::vec2& Particle::GetVelocity() const{
  return velocity_;
}

const float& Particle::GetRadius() const{
  return radius_;
}

const float& Particle::GetMass() const {
  return mass_;
}

void Particle::SetVelocity(const glm::vec2& vel) {
  velocity_ = vel;
}
const size_t& Particle::GetType() const {
  return type_;
}

}  // namespace idealgas