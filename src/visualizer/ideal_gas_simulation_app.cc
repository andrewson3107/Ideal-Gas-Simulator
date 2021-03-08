#include <visualizer/ideal_gas_simulation_app.h>

#include <random>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : particle_sim_(glm::vec2(kMargin, kMargin * 2), kParticleBoxSize),
      histogram1_(
          glm::vec2(kMargin + kParticleBoxSize + kMargin * 2, kMargin * 3),
          kHistogramWidth, kHistogramLength, 1, kType1Color),
      histogram2_(
          glm::vec2(kMargin + kParticleBoxSize + kMargin * 2, kMargin * 7),
          kHistogramWidth, kHistogramLength, 2, kType2Color),
      histogram3_(
          glm::vec2(kMargin + kParticleBoxSize + kMargin * 2, kMargin * 11),
          kHistogramWidth, kHistogramLength, 3, kType3Color) {
  ci::app::setWindowSize((int)kWindowLength, (int)kWindowWidth);
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  // Generates a random number from 1 to 3
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist3(1,3);
  float mass;
  size_t type;

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_UP:
      particle_sim_.AccelerateSimulation();
      break;

    case ci::app::KeyEvent::KEY_DOWN:
      particle_sim_.DeaccelerateSimulation();
      break;

    case ci::app::KeyEvent::KEY_RETURN:
      // Creates a random particle from the current particle types
      switch (dist3(rng)) {
        case 1:
          mass = kType1Mass;
          type = 1;
          break;
        case 2:
          mass = kType2Mass;
          type = 2;
          break;
        case 3:
          mass = kType3Mass;
          type = 3;
          break;
      }
      particle_sim_.GenerateRandomParticle(kRadius,mass, type);
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      particle_sim_.Clear();
      break;

    case ci::app::KeyEvent::KEY_1:
      particle_sim_.GenerateRandomParticle(kRadius, kType1Mass, 1);
      break;

    case ci::app::KeyEvent::KEY_2:
      particle_sim_.GenerateRandomParticle(kRadius, kType2Mass, 2);
      break;

    case ci::app::KeyEvent::KEY_3:
      particle_sim_.GenerateRandomParticle(kRadius, kType3Mass, 3);
      break;
  }
}

void IdealGasApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  ci::gl::drawStringCentered(
      "Ideal Gas Simulator", glm::vec2(kWindowLength / 2, kMargin / 4),
      ci::Color("Black"), ci::Font("Times New Roman", 50));

  ci::gl::drawStringCentered(
      "Number of particles: " +
          std::to_string(
              particle_sim_.GetParticleEngine().GetParticles().size()),
      glm::vec2(kMargin + kParticleBoxSize / 2, kWindowWidth - kMargin),
      ci::Color("Black"), ci::Font("Times New Roman", 30));

  particle_sim_.Draw();

  std::vector<Particle> particles = particle_sim_.GetParticleEngine().GetParticles();
  histogram1_.Draw(particles);
  histogram2_.Draw(particles);
  histogram3_.Draw(particles);
}

void IdealGasApp::update() {
  particle_sim_.Update();
}


}  // namespace visualizer

}  // namespace idealgas
