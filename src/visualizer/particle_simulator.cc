#include <cinder/Rand.h>
#include <visualizer/ideal_gas_simulation_app.h>

namespace idealgas {

namespace visualizer {

ParticleSimulator::ParticleSimulator(const glm::vec2& top_left_corner,
                         const size_t& num_pixels_per_side)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side), particle_engine_(ParticleEngine(num_pixels_per_side)) {
}

void ParticleSimulator::Draw() const {
  // Render the particle box.
  ci::gl::color(kParticleBoxColor);
  ci::gl::drawSolidRect(ci::Rectf(
      top_left_corner_,
      top_left_corner_ + ci::vec2(num_pixels_per_side_, num_pixels_per_side_)));
  ci::gl::color(0,0,0); // Black.

  // Gives the box a subtle outline.
  ci::gl::drawStrokedRect(ci::Rectf(
      top_left_corner_,
      top_left_corner_ + ci::vec2(num_pixels_per_side_, num_pixels_per_side_)),1);

  // Render the particles.
  for (const Particle& particle : particle_engine_.GetParticles()) {

    if (particle.GetMass() == kType1Mass) {
      ci::gl::color(kType1Color);
    } else if (particle.GetMass() == kType2Mass) {
      ci::gl::color(kType2Color);
    } else if (particle.GetMass() == kType3Mass) {
      ci::gl::color(kType3Color);
    }

    ci::gl::drawSolidCircle(top_left_corner_ + particle.GetPosition(),
                            particle.GetRadius());
    ci::gl::color(0,0,0); // Black
    ci::gl::drawStrokedCircle(top_left_corner_ + particle.GetPosition(),
                            particle.GetRadius(), 20);
  }
}

void ParticleSimulator::Clear() {
  particle_engine_.Clear();
}

void ParticleSimulator::GenerateRandomParticle(const float& radius, const float& mass, const size_t& type) {
  particle_engine_.GenerateRandomParticle(radius, mass, type);
}

void ParticleSimulator::AccelerateSimulation() {
  particle_engine_.AccelerateParticles();
}

void ParticleSimulator::DeaccelerateSimulation() {
  particle_engine_.DeaccelerateParticles();
}

void ParticleSimulator::Update() {
  particle_engine_.Update();
}

const ParticleEngine& ParticleSimulator::GetParticleEngine() const{
  return particle_engine_;
}

}  // namespace visualizer

}  // namespace idealgas
