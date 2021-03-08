#pragma once
#include <core/particle.h>

#include "cinder/gl/gl.h"

namespace idealgas {
namespace visualizer {

class Histogram {
 public:
  Histogram(const glm::vec2& top_left_corner, const size_t& width_,
            const size_t& length_, const size_t& particle_type,
            const ci::Color& color);

  /**
   * Draws the box for the histogram, then calls draw labels and bars.
   * @param particles The list of particles currently in the simulation
   */
  void Draw(const std::vector<Particle>& particles) const;

 private:
  glm::vec2 top_left_corner_;
  size_t width_;
  size_t length_;
  size_t particle_type_;
  ci::Color color_;

  const float kMargin = 20;
  const float kTickLength = 7;
  const size_t kNumTicksY = 10;
  const size_t kTickIntervalY = 5;
  const size_t kNumTicksX = 20;
  const size_t kTickIntervalX = 1;

  /**
   * Writes the x-axis and y-axis labels on the histogram. Also writes the
   * title.
   */
  void DrawLabels() const;

  /**
   * Draws tick marks and values along the x and y axis with a certain interval
   */
  void DrawAxisTicks() const;

  /**
   * Counts the number of particles that fall into each bin and draws the bars
   * of the histogram.
   * @param particles The list of particles currently in the simulation
   */
  void DrawBars(const std::vector<Particle>& particles) const;

  void DrawNumParticles(const size_t& num_particles) const;
};
}  // namespace visualizer
}  // namespace idealgas