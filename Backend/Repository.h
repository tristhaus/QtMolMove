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

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "memory"
#include "string"

#include "Trajectory.h"

namespace Backend
{
    /*!
     * \brief The Repository interface provides access to trajectories.
     */
    class Repository
    {
    public:
        /*!
         * \brief Initializes a new instance.
         */
        Repository() = default;
        Repository(const Repository&) = delete;
        Repository(Repository&&) = delete;
        Repository& operator=(const Repository&) = delete;
        Repository& operator=(Repository&&) = delete;
        virtual ~Repository() = default;

        /*!
         * \brief Loads a trajectory from the persistence medium.
         * \param identifier The unique identifier, e.g. a file path or a GUID.
         * \return The corresponding trajectory.
         */
        virtual std::shared_ptr<Trajectory> Load(std::string identifier) = 0;
    };
}

#endif // REPOSITORY_H
