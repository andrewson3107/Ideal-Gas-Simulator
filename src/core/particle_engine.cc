#include <cinder/Rand.h>
#include <core/particle_engine.h>

namespace idealgas {

ParticleEngine::ParticleEngine(const size_t& num_pixels_per_side)
    : num_pixels_per_side_(num_pixels_per_side) {
  // Sets a random seed.
  ci::Rand::randomize();
}

void ParticleEngine::Update() {
  // Moves each particle.
  for (Particle& particle : particles_) {
    particle.UpdatePosition();
  }
  UpdateVelOnWallCollision();
  if (particles_.size() > 1) {
    UpdateVelOnParticleCollision();
  }
}

void ParticleEngine::UpdateVelOnWallCollision() {
  for (Particle& particle : particles_) {
    float x_pos = particle.GetPosition().x;
    float y_pos = particle.GetPosition().y;
    float x_vel = particle.GetVelocity().x;
    float y_vel = particle.GetVelocity().y;
    float radius = particle.GetRadius();

    // The particle cannot be within the size of the radius to any wall.
    // Additionally, the particle must be travelling in the direction of the
    // wall. This is determined by the velocity being > or < 0.
    if (x_pos - radius <= 0 && x_vel < 0) {
      particle.SetVelocity(glm::vec2(-particle.GetVelocity().x, particle.GetVelocity().y));
    } else if (x_pos + radius >= num_pixels_per_side_ && x_vel > 0) {
      particle.SetVelocity(glm::vec2(-particle.GetVelocity().x, particle.GetVelocity().y));
    }

    if (y_pos - radius <= 0 && y_vel < 0) {
      particle.SetVelocity(glm::vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
    } else if (y_pos + radius >= num_pixels_per_side_ && y_vel > 0) {
      particle.SetVelocity(glm::vec2(particle.GetVelocity().x, -particle.GetVelocity().y));
    }
  }
}

void ParticleEngine::GenerateRandomParticle(const float& radius, const float& mass, const size_t& type) {
  // RandFloat(a,b) generates a random float in [a,b).
  glm::vec2 pos_vec =
      glm::vec2(ci::randFloat(1, (float)num_pixels_per_side_ - 1),
                ci::randFloat(1, (float)num_pixels_per_side_ - 1));

  // RandPosNegFloat(a,b) generates a random float in [a,b) and [-a,-b).
  glm::vec2 vel_vec = glm::vec2(ci::randPosNegFloat(0, radius),
                                ci::randPosNegFloat(0, radius));

  particles_.push_back(Particle(pos_vec, vel_vec, radius, mass, type));
}

void ParticleEngine::UpdateVelOnParticleCollision() {
  for (size_t index = 0; index < particles_.size() - 1; index++) {
    Particle& particle1 = particles_[index];
    for (size_t index2 = index + 1; index2 < particles_.size(); index2++) {
      Particle& particle2 = particles_[index2];

      if (WillParticlesCollide(particle1, particle2)) {
        glm::vec2 new_vel1 =
            CalculateParticleCollisionVel(particle1, particle2);

        glm::vec2 new_vel2 =
            CalculateParticleCollisionVel(particle2, particle1);

        particle1.SetVelocity(new_vel1);
        particle2.SetVelocity(new_vel2);
      }

    }
  }
}

bool ParticleEngine::WillParticlesCollide(const Particle& particle1,
                                           const Particle& particle2) const {
  return ((glm::distance(particle1.GetPosition(), particle2.GetPosition()) <=
           (particle1.GetRadius() + particle2.GetRadius())) &&
          (glm::dot((particle1.GetVelocity() - particle2.GetVelocity()),
                    (particle1.GetPosition() - particle2.GetPosition())) < 0));
}

glm::vec2 ParticleEngine::CalculateParticleCollisionVel(
    const Particle& particle1, const Particle& particle2) const {
  return particle1.GetVelocity() - (2 * particle2.GetMass()) / (particle1.GetMass() + particle2.GetMass()) *
         (glm::dot((particle1.GetVelocity() - particle2.GetVelocity()),
                   (particle1.GetPosition() - particle2.GetPosition()))) /
             (glm::pow(
                 glm::length(particle1.GetPosition() - particle2.GetPosition()),
                 2)) *
             (particle1.GetPosition() - particle2.GetPosition());
}

void ParticleEngine::AddParticle(const Particle& particle) {
  particles_.push_back(particle);
}

const std::vector<Particle>& ParticleEngine::GetParticles() const {
  return particles_;
}

void ParticleEngine::Clear() {
  particles_.clear();
}

void ParticleEngine::AccelerateParticles() {
  for (Particle& particle : particles_) {

    if (particle.GetVelocity().x < 0) {
      particle.SetVelocity(particle.GetVelocity() + glm::vec2(0.1 * particle.GetVelocity().x, 0));
    } else if (particle.GetVelocity().x > 0) {
      particle.SetVelocity(particle.GetVelocity() + glm::vec2(0.1 * particle.GetVelocity().x, 0));
    }

    if (particle.GetVelocity().y < 0) {
      particle.SetVelocity(particle.GetVelocity() + glm::vec2(0, 0.1 * particle.GetVelocity().y));
    } else if (particle.GetVelocity().y > 0) {
      particle.SetVelocity(particle.GetVelocity() + glm::vec2(0, 0.1 * particle.GetVelocity().y));
    }

  }
}

void ParticleEngine::DeaccelerateParticles() {
  for (Particle& particle : particles_) {

    if (particle.GetVelocity().x < 0) {
      particle.SetVelocity(particle.GetVelocity() - glm::vec2(0.1 * particle.GetVelocity().x, 0));
    } else if (particle.GetVelocity().x > 0) {
      particle.SetVelocity(particle.GetVelocity() - glm::vec2(0.1 * particle.GetVelocity().x, 0));
    }

    if (particle.GetVelocity().y < 0) {
      particle.SetVelocity(particle.GetVelocity() - glm::vec2(0, 0.1 * particle.GetVelocity().y));
    } else if (particle.GetVelocity().y > 0) {
      particle.SetVelocity(particle.GetVelocity() - glm::vec2(0, 0.1 * particle.GetVelocity().y));
    }

  }
}

}  // namespace idealgas
