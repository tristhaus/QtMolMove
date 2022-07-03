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

#include <map>

#include "../Backend/Repository.h"

namespace TestHelper
{
    class MemoryRepository final : public Backend::Repository
    {
    private:
        std::map<std::string, std::shared_ptr<Backend::Trajectory>> store;

    public:
        MemoryRepository() = default;

        /**
         * @reimp
         */
        std::shared_ptr<Backend::Trajectory> Load(std::string identifier) override;

        void Save(std::string identifier, std::shared_ptr<Backend::Trajectory> trajectory);
    };
}

#endif // MEMORYREPOSITORY_H
