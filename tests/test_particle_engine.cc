#include <core/particle_engine.h>

#include <catch2/catch.hpp>

using idealgas::Particle;
using idealgas::ParticleEngine;

TEST_CASE("Particle collisions") {
  SECTION("Particles are travelling towards each other") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(5, 5), glm::vec2(2, 1), 5, 1, 1);
    Particle particle2(glm::vec2(10, 5), glm::vec2(-2, -1), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.AddParticle(particle2);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(1.2, 2.6));
    REQUIRE(particle_handler.GetParticles()[1].GetVelocity() ==
            glm::vec2(-1.2, -0.6));
  }

  SECTION("Particles are travelling away from each other") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(10, 5), glm::vec2(-2, 1), 5, 1, 1);
    Particle particle2(glm::vec2(10, 4), glm::vec2(2, 0), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.AddParticle(particle2);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(-2, 1));
    REQUIRE(particle_handler.GetParticles()[1].GetVelocity() ==
            glm::vec2(2, 0));
  }

  SECTION("Particles stacked on top of each other") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(10, 5), glm::vec2(-2, 1), 5, 1, 1);
    Particle particle2(glm::vec2(10, 5), glm::vec2(2, 0), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.AddParticle(particle2);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(-2, 1));
    REQUIRE(particle_handler.GetParticles()[1].GetVelocity() ==
            glm::vec2(2, 0));
  }

  SECTION("Particles stacked and zero velocity") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(10, 5), glm::vec2(0, 0), 5, 1, 1);
    Particle particle2(glm::vec2(10, 5), glm::vec2(0, 0), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.AddParticle(particle2);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(0, 0));
    REQUIRE(particle_handler.GetParticles()[1].GetVelocity() ==
            glm::vec2(0, 0));
  }

  SECTION("Particles of different mass") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(5, 5), glm::vec2(2, 1), 5, 5, 3);
    Particle particle2(glm::vec2(10, 5), glm::vec2(-2, -1), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.AddParticle(particle2);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity().x == Approx(1.73333f));
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity().y == Approx(1.53333f));
    REQUIRE(particle_handler.GetParticles()[1].GetVelocity().x == Approx(-0.66667f));
    REQUIRE(particle_handler.GetParticles()[1].GetVelocity().y == Approx(-1.66667f));
  }

  SECTION("3 Particles in area") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(5, 5), glm::vec2(2, 0), 5, 1, 1);
    Particle particle2(glm::vec2(10, 5), glm::vec2(-2, 0), 5, 1, 1);
    Particle particle3(glm::vec2(12, 12), glm::vec2(0, 1), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.AddParticle(particle2);
    particle_handler.AddParticle(particle3);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(-2, 0));
    REQUIRE(particle_handler.GetParticles()[1].GetVelocity() ==
            glm::vec2(2, 0));
  }

  SECTION("Erroneous wall collision") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(10, 5), glm::vec2(3, 4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(3, 4));
  }

  SECTION("Upper wall collision") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(10, 5), glm::vec2(3, -4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(3, 4));
  }

  SECTION("Lower wall collision") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(50, 745), glm::vec2(3, 4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(3, -4));
  }

  SECTION("Left wall collision") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(5, 50), glm::vec2(-3, 4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(3, 4));
  }

  SECTION("Right wall collision") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(745, 50), glm::vec2(3, 4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(-3, 4));
  }

  SECTION("Upper left corner") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(5, 5), glm::vec2(-3, -4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(3, 4));
  }

  SECTION("Upper right corner") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(745, 5), glm::vec2(3, -4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(-3, 4));
  }

  SECTION("Lower left corner") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(5, 745), glm::vec2(-3, 4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(3, -4));
  }

  SECTION("Lower right corner") {
    ParticleEngine particle_handler(750);
    Particle particle1(glm::vec2(745, 745), glm::vec2(3, 4), 5, 1, 1);
    particle_handler.AddParticle(particle1);
    particle_handler.Update();
    REQUIRE(particle_handler.GetParticles()[0].GetVelocity() ==
            glm::vec2(-3, -4));
  }
}

TEST_CASE("Particle movement") {
  Particle particle(glm::vec2(5, 5), glm::vec2(5, 5), 5, 1, 1);
  particle.UpdatePosition();
  REQUIRE(particle.GetPosition() == glm::vec2(10, 10));
  REQUIRE(particle.GetVelocity() == glm::vec2(5, 5));
}

TEST_CASE("Clear") {
  ParticleEngine particle_handler(750);
  Particle particle1(glm::vec2(5, 5), glm::vec2(2, 1), 5, 1, 1);
  Particle particle2(glm::vec2(10, 5), glm::vec2(-2, -1), 5, 1, 1);
  Particle particle3(glm::vec2(10, 5), glm::vec2(-2, -1), 5, 1, 1);
  particle_handler.AddParticle(particle1);
  particle_handler.AddParticle(particle2);
  particle_handler.AddParticle(particle3);
  REQUIRE(particle_handler.GetParticles().size() == 3);
  particle_handler.Clear();
  REQUIRE(particle_handler.GetParticles().size() == 0);
}

TEST_CASE("Generating Random Particles") {
  ParticleEngine particle_handler(750);

  SECTION("Velocity is less than radius") {
    for (size_t count = 0; count < 50; count++) {
      particle_handler.GenerateRandomParticle(5, 1, 1);
      REQUIRE(particle_handler.GetParticles()[0].GetVelocity().x < 5);
      REQUIRE(particle_handler.GetParticles()[0].GetVelocity().y < 5);
      particle_handler.Clear();
    }
  }

  SECTION("Particles only spawn inside box") {
    for (size_t count = 0; count < 50; count++) {
      particle_handler.GenerateRandomParticle(5, 1, 1);
      REQUIRE(particle_handler.GetParticles()[0].GetPosition().x < 750);
      REQUIRE(particle_handler.GetParticles()[0].GetPosition().y < 750);
      particle_handler.Clear();
    }
  }
}
