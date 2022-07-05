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

#ifndef TESTREPOSITORY_H
#define TESTREPOSITORY_H

#include "../Backend/Repository.h"

namespace TestHelper
{
    /*!
     * @brief The TestRepository class is a fake repo
              in that it only produces one fixed trajectory
              with the maximum number of steps set.
     */
    class TestRepository final : public Backend::Repository
    {
        unsigned int numberFrames;

    public:
        /*!
         * \brief Initializes a new instance.
         * \param numberFrames The number of frames in the trajectory provided by the Load method.
         */
        explicit TestRepository(unsigned int numberFrames);

        /*!
         * @reimp
         */
        std::shared_ptr<Backend::Trajectory> Load(std::string) override;
    };
}

#endif // TESTREPOSITORY_H
