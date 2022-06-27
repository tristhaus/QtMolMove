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

#include "MemoryRepository.h"

std::shared_ptr<Backend::Trajectory> Backend::MemoryRepository::Load(std::string)
{
    Backend::Viewport viewport(-10.0, 10.0, -10.0, 10.0);

    auto frames = std::vector<Backend::Frame>
    {
            Backend::Frame(std::vector<Backend::Particle> { Backend::Particle(-6.0, 4.0, 1), Backend::Particle( 6.0, -4.0, 2) }),
            Backend::Frame(std::vector<Backend::Particle> { Backend::Particle(-3.0, 4.0, 1), Backend::Particle( 3.0, -4.0, 2) }),
            Backend::Frame(std::vector<Backend::Particle> { Backend::Particle( 3.0, 4.0, 1), Backend::Particle(-3.0, -4.0, 2) }),
            Backend::Frame(std::vector<Backend::Particle> { Backend::Particle( 6.0, 4.0, 1), Backend::Particle(-6.0, -4.0, 2) })
    };

    return std::make_shared<Backend::Trajectory>(2, 1.25, viewport, frames);
}
