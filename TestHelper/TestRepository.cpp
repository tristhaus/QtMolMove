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

#include <stdexcept>

#include "TestRepository.h"

TestHelper::TestRepository::TestRepository(unsigned int numberFrames)
    : numberFrames(numberFrames)
{
    if (numberFrames == 0U)
    {
        throw std::logic_error("must have at least one frame");
    }
}

std::shared_ptr<Backend::Trajectory> TestHelper::TestRepository::Load(std::string)
{
    Backend::Viewport viewport(-10.0, 10.0, -10.0, 10.0);

    auto particles = std::vector<Backend::Particle>
    {
            Backend::Particle(1),
            Backend::Particle(2)
    };

    std::vector<Backend::Frame> frames;

    if (numberFrames < 2U)
    {
        auto frame = Backend::Frame(std::vector<Backend::Coordinate>
                                    { Backend::Coordinate(-6.0, 4.0),
                                      Backend::Coordinate( 6.0, -4.0) });
        frames.push_back(frame);
    }
    else
    {
        for (unsigned int frameIndex = 0; frameIndex < numberFrames; ++frameIndex)
        {
            auto frame = Backend::Frame(std::vector<Backend::Coordinate>
                                        { Backend::Coordinate(-6.0 + frameIndex * 12.0 / (numberFrames - 1), 4.0),
                                          Backend::Coordinate( 6.0 - frameIndex * 12.0 / (numberFrames - 1), -4.0) });
            frames.push_back(frame);
        }
    }

    return std::make_shared<Backend::Trajectory>(2, 1.25, viewport, particles, frames);
}
