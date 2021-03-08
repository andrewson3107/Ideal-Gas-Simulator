#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "histogram.h"
#include "particle_simulator.h"

namespace idealgas {
const float kType1Mass = 1;
const float kType2Mass = 5;
const float kType3Mass = 7;
const float kRadius = 5;

namespace visualizer {
const ci::Color kType1Color = ci::Color::hex(0x0000FF); //Blue
const ci::Color kType2Color = ci::Color::hex(0xFF0000); //Red
const ci::Color kType3Color = ci::Color::hex(0x00FF00); //Green

class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  // Creates the window that holds a particle box.
  void draw() override;

  // Calls update on every object in the window.
  void update() override;

  // Sets actions for enter and delete keys. Enter creates a new particle,
  // delete clears all particles.
  void keyDown(ci::app::KeyEvent event) override;

  const size_t kMargin = 50;
  const size_t kWindowWidth = 750;
  const size_t kWindowLength = 1100;
  const size_t kParticleBoxSize = 600;
  const size_t kHistogramWidth = 100;
  const size_t kHistogramLength = 300;

 private:
  ParticleSimulator particle_sim_;
  Histogram histogram1_;
  Histogram histogram2_;
  Histogram histogram3_;
};

}  // namespace visualizer

}  // namespace idealgas
