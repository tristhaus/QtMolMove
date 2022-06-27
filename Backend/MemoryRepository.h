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

#ifndef MEMORYREPOSITORY_H
#define MEMORYREPOSITORY_H

#include "Repository.h"
namespace Backend
{
    /**
     * @brief The MemoryRepository class is a fake repo in that it only produces one fixed trajectory.
     */
    class MemoryRepository final : public Repository
    {
    public:
        MemoryRepository() = default;

        /**
         * @reimp
         */
        std::shared_ptr<Trajectory> Load(std::string) override;
    };
}

#endif // MEMORYREPOSITORY_H
