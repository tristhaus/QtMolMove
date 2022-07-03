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

std::shared_ptr<Backend::Trajectory> TestHelper::MemoryRepository::Load(std::string identifier)
{
    return this->store[identifier];
}

void TestHelper::MemoryRepository::Save(std::string identifier, std::shared_ptr<Backend::Trajectory> trajectory)
{
    this->store[identifier] = std::move(trajectory);
}
