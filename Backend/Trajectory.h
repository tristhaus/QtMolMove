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

    /*!
     * \brief The Viewport class defines the visible part of the coordinate system
     *        to be used to display the trajectory.
     */
    class Viewport
    {
    public:
        /*!
         * \brief minX The lowest visible x-value.
         */
        const unit minX;

        /*!
         * \brief maxX The highest visible x-value.
         */
        const unit maxX;

        /*!
         * \brief minY The lowest visible y-value.
         */
        const unit minY;

        /*!
         * \brief maxY The highest visible y-value.
         */
        const unit maxY;

        /*!
         * \brief Initializes a new instance from the given limits.
         * \param minX The lowest visible x-value.
         * \param maxX The highest visible x-value.
         * \param minY The lowest visible y-value.
         * \param maxY The highest visible y-value.
         */
        explicit Viewport(unit minX, unit maxX, unit minY, unit maxY)
            : minX(minX),
              maxX(maxX),
              minY(minY),
              maxY(maxY)
        {}
    };

    /*!
     * \brief The Particle class collects properties of an individual particle.
     */
    class Particle
    {
    public:
        /*!
         * \brief id Describes the identity of the particle.
         */
        const unsigned int id;

        /*!
         * \brief Initializes a new instance.
         * \param id The numeric identity of the particle.
         */
        explicit Particle(unsigned int id)
            : id(id)
        {}
    };

    /*!
     * \brief The Coordinate class wraps the 2D coordinates of a particle.
     */
    class Coordinate
    {
    public:
        /*!
         * \brief x The x-coordinate of the particle.
         */
        const unit x;

        /*!
         * \brief y The y-coordinate of the particle.
         */
        const unit y;

        /*!
         * \brief Initializes a new instance.
         * \param x The x-coordinate of the particle.
         * \param y The y-coordinate of the particle.
         */
        explicit Coordinate(unit x, unit y)
            : x(x),
              y(y)
        {}
    };

    /*!
     * \brief The Frame class collects the coordinates of all present particles at one point in time.
     */
    class Frame
    {
    public:
        /*!
         * \brief coordinates The list of coordinates.
         */
        const std::vector<Coordinate> coordinates;

        /*!
         * \brief Initializes a new instance.
         * \param coordinates The list of coordinates.
         */
        explicit Frame(std::vector<Coordinate> coordinates)
            : coordinates(std::move(coordinates))
        {}
    };

    /*!
     * \brief The Trajectory class collects the particles and their coordinates
     *        along with other relevant information for the display.
     */
    class Trajectory
    {
    private:
        unit particleSize;
        Viewport viewport;
        std::vector<Particle> particles;
        std::vector<Frame> frames;

    public:
        /*!
         * \brief Initializes a new instance.
         * \param particleSize The size of each of the particles.
         * \param viewport The relevant viewing window.
         * \param particles The list of particles.
         * \param frames The list of frames.
         */
        explicit Trajectory(unit particleSize, Viewport viewport, std::vector<Particle> particles, std::vector<Frame> frames);

        /*!
         * \brief ParticleCount Gets the number of particles.
         * \return The number of particles.
         */
        [[nodiscard]] unsigned int ParticleCount() const;

        /*!
         * \brief ParticleSize Gets the size of each of the particles.
         * \return The size of each of the particles.
         */
        [[nodiscard]] unit ParticleSize() const;

        /*!
         * \brief Viewport Gets the relevant viewing window.
         * \return The relevant viewing window.
         */
        [[nodiscard]] Viewport Viewport() const;

        /*!
         * \brief Particles Gets the list of particles.
         * \return The list of particles.
         */
        [[nodiscard]] std::vector<Particle> Particles() const;

        /*!
         * \brief Frames Gets the list of frames.
         * \return The list of frames.
         */
        [[nodiscard]] std::vector<Frame> Frames() const;
    };
}

#endif // TRAJECTORY_H
