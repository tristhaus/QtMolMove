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

#include "Deserializer.h"
#include "Repository.h"

#ifndef DISKREPOSITORY_H
#define DISKREPOSITORY_H

namespace Backend
{
    /*!
     * \brief The DiskRepository class allows to deserialize a trajectory from disk.
     *        The identifier is thus a file path.
     */
    class DiskRepository final : public Repository
    {
    public:
        /*!
         * \brief Initializes a new instance.
         */
        DiskRepository() = default;

        /*!
         * \reimp
         */
        std::shared_ptr<Trajectory> Load(std::string identifier) override;
    };
}

#endif // DISKREPOSITORY_H
