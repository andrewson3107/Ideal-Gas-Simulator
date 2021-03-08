#include <visualizer/histogram.h>
#include <visualizer/ideal_gas_simulation_app.h>

namespace idealgas {
namespace visualizer {

Histogram::Histogram(const glm::vec2 &top_left_corner, const size_t &width,
                     const size_t &length, const size_t &particle_type,
                     const ci::Color &color)
    : top_left_corner_(top_left_corner),
      width_(width),
      length_(length),
      particle_type_(particle_type),
      color_(color) {
}

void Histogram::Draw(const std::vector<Particle> &particles) const {
  ci::gl::color(255, 255, 255);
  ci::gl::drawSolidRect(ci::Rectf(
      top_left_corner_, top_left_corner_ + ci::vec2(length_, width_)));
  ci::gl::color(0, 0, 0);  // Black.

  // Gives the box a subtle outline.
  ci::gl::drawStrokedRect(
      ci::Rectf(top_left_corner_, top_left_corner_ + ci::vec2(length_, width_)),
      1);

  DrawLabels();
  DrawBars(particles);
  // DrawAxisTicks(); // Commented out for performance.
}

void Histogram::DrawLabels() const {
  ci::gl::drawStringCentered(
      "Particle " + std::to_string(particle_type_) + " Speed Distribution",
      glm::vec2(length_ / 2, -kMargin) + top_left_corner_, ci::Color("Black"),
      ci::Font("Times New Roman", 20));

  ci::gl::drawStringCentered(
      "Speed", glm::vec2(length_ / 2, width_ + kMargin) + top_left_corner_,
      ci::Color("Black"), ci::Font("Times New Roman", 25));

  // Rotates the string 90 degrees counter-clockwise
  ci::gl::pushModelMatrix();
  ci::gl::translate(top_left_corner_ + glm::vec2(0, width_));
  ci::gl::rotate((float)(3 * M_PI / 2));
  ci::gl::drawStringCentered("Frequency", glm::vec2(width_ / 2, -kMargin * 2),
                             ci::Color("Black"),
                             ci::Font("Times New Roman", 20));
  ci::gl::popModelMatrix();
}

void Histogram::DrawAxisTicks() const {
  ci::gl::pushModelMatrix();
  ci::gl::translate(top_left_corner_ + glm::vec2(0, width_));
  ci::gl::rotate((float)(3 * M_PI / 2));

  // Draws a little dash after each interval on the y axis.
  for (size_t index = 0; index < kNumTicksY; index++) {
    ci::gl::drawLine(glm::vec2(width_ / kNumTicksY * index, 0),
                     glm::vec2(width_ / kNumTicksY * index, -kTickLength));
  }
  ci::gl::popModelMatrix();

  // Labels each dash with the respective value.
  for (size_t index = 0; index < kNumTicksY; index++) {
    ci::gl::drawStringCentered(
        std::to_string(kTickIntervalY * index),
        top_left_corner_ +
            glm::vec2(-10, width_ - (width_ / kNumTicksY * index) - 5),
        ci::Color("Black"), ci::Font("Times New Roman", 13));
  }

  // Draws a little dash after each interval on the x axis.
  for (size_t index = 0; index <= kNumTicksX; index++) {
    ci::gl::drawLine(
        top_left_corner_ + glm::vec2(length_ / kNumTicksX * index, width_),
        top_left_corner_ +
            glm::vec2(length_ / kNumTicksX * index, width_ + kTickLength));
  }

  // Labels each dash with the respective value.
  for (size_t index = 0; index <= kNumTicksX; index++) {
    ci::gl::drawStringCentered(
        std::to_string(kTickIntervalX * index),
        top_left_corner_ +
            glm::vec2(length_ / kNumTicksX * index, width_ + kTickLength),
        ci::Color("Black"), ci::Font("Times New Roman", 13));
  }
}

void Histogram::DrawBars(const std::vector<Particle> &particles) const {
  std::unordered_map<size_t, size_t> frequency;

  // There are kNumTicksX - 1 or 19 separate bins.
  for (size_t i = 1; i <= kNumTicksX; i++) {
    frequency[i] = 0;  // Initially populate them as 0
  }

  for (const Particle &particle : particles) {
    // Each histogram should only plot particles of it's type
    if (particle.GetType() == particle_type_) {
      // Rounds the magnitude of the velocity upwards. Ex: 2.1 -> 3
      frequency[(size_t)std::ceilf(glm::length(particle.GetVelocity()))]++;
    }
  }

  // Draws each bar
  for (size_t index = 0; index < kNumTicksX; index++) {
    ci::gl::color(color_);

    // index * length_ / kNumTicksX is the tick mark it should be on.
    // width_ / (kNumTicksY*kTickIntervalY) is the pixel amount each particle
    // should add to the bar.
    ci::gl::drawSolidRect(ci::Rectf(
        top_left_corner_ + glm::vec2(index * length_ / kNumTicksX,
                                     width_ - (frequency[index + 1] * width_ /
                                               (kNumTicksY * kTickIntervalY))),
        top_left_corner_ +
            glm::vec2((index + 1) * length_ / kNumTicksX, width_)));
  }

  size_t sum = 0;
  for (size_t i = 1; i <= kNumTicksX; i++) {
    sum += frequency[i];
  }
  DrawNumParticles(sum);

}

void Histogram::DrawNumParticles(const size_t &num_particles) const {
  ci::gl::color(0, 0, 0);
  ci::gl::drawStringCentered(
      "n = " + std::to_string(num_particles),
      top_left_corner_ + glm::vec2(length_ + kMargin, width_ / 2),
      ci::Color("Black"), ci::Font("Times New Roman", 15));
}

}  // namespace visualizer
}  // namespace idealgas
