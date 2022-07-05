/*
 * This file is part of QtMolMove.
 *
 * QtMolMove is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtMolMove is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtMolMove.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Trajectory.h"

#include <utility>

Backend::Trajectory::Trajectory(
        Backend::unit particleSize,
        Backend::Viewport viewport,
        std::vector<Particle> particles,
        std::vector<Frame> frames)
    : particleSize(particleSize),
      viewport(viewport),
      particles(std::move(particles)),
      frames(std::move(frames))
{
}

unsigned int Backend::Trajectory::ParticleCount() const
{
    return static_cast<unsigned int>(this->particles.size());
}

Backend::unit Backend::Trajectory::ParticleSize() const
{
    return this->particleSize;
}

Backend::Viewport Backend::Trajectory::Viewport() const
{
    return this->viewport;
}

std::vector<Backend::Particle> Backend::Trajectory::Particles() const
{
    return this->particles;
}

std::vector<Backend::Frame> Backend::Trajectory::Frames() const
{
    return this->frames;
}
