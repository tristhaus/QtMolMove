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

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>

namespace Backend
{
    using unit = double;

    class Viewport
    {
    public:
        const unit minX;
        const unit maxX;
        const unit minY;
        const unit maxY;
        explicit Viewport(unit minX, unit maxX, unit minY, unit maxY)
            : minX(minX),
              maxX(maxX),
          minY(minY),
          maxY(maxY)
        {}
    };

    class Particle
    {
    public:
        const unsigned int id;
        explicit Particle(unsigned int id)
            : id(id)
        {}
    };

    class Coordinate
    {
    public:
        const unit x;
        const unit y;
        explicit Coordinate(unit x, unit y)
            : x(x),
              y(y)
        {}
    };

    class Frame
    {
    public:
        const std::vector<Coordinate> coordinates;
        explicit Frame(std::vector<Coordinate> coordinates)
            : coordinates(std::move(coordinates))
        {}
    };

    class Trajectory
    {
    private:
        unsigned int particleCount;
        unit particleSize;
        Viewport viewport;
        std::vector<Particle> particles;
        std::vector<Frame> frames;

    public:
        explicit Trajectory(unsigned int particleCount, unit particleSize, Viewport viewport, std::vector<Particle> particles, std::vector<Frame> frames);

        [[nodiscard]] unsigned int ParticleCount() const;
        [[nodiscard]] unit ParticleSize() const;
        [[nodiscard]] Viewport Viewport() const;
        [[nodiscard]] std::vector<Particle> Particles() const;
        [[nodiscard]] std::vector<Frame> Frames() const;
    };
}

#endif // TRAJECTORY_H
