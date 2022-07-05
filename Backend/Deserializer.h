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

#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <memory>
#include <string>

#include "../Include/rapidjson/document.h"
#include "../Include/rapidjson/rapidjson.h"

#include "Trajectory.h"

namespace Backend
{
    /*!
     * \brief The Deserializer class deserializes a certain JSON format into a trajectory.
     *        The class is static.
     */
    class Deserializer
    {
    private:
        constexpr static const char * const KeyVersion = u8"Version";
        constexpr static const char * const KeySize = u8"Size";
        constexpr static const char * const KeyViewport = u8"Viewport";
        constexpr static const char * const KeyMinX = u8"MinX";
        constexpr static const char * const KeyMaxX = u8"MaxX";
        constexpr static const char * const KeyMinY = u8"MinY";
        constexpr static const char * const KeyMaxY = u8"MaxY";
        constexpr static const char * const KeyParticles = u8"Particles";
        constexpr static const char * const KeyId = u8"Id";
        constexpr static const char * const KeyFrames = u8"Frames";
        constexpr static const char * const KeyX = u8"X";
        constexpr static const char * const KeyY = u8"Y";
    public:
        Deserializer() = delete;
        /*!
         * \brief Deserializes a given stream containing a JSON per schema into a trajectory.
         * \param is The input stream.
         * \return The corresponding trajectory.
         */
        static std::shared_ptr<Trajectory> Deserialize(std::istream & is);
    private:
        static unit ParseSize(rapidjson::GenericValue<rapidjson::UTF8<char>> & sizeValue); // NOLINT(google-runtime-references)
        static Viewport ParseViewport(rapidjson::GenericValue<rapidjson::UTF8<char>> & viewportValue); // NOLINT(google-runtime-references)
        static std::vector<Particle> ParseParticles(rapidjson::GenericValue<rapidjson::UTF8<char>> & particlesValue); // NOLINT(google-runtime-references)
        static std::vector<Frame> ParseFrames(rapidjson::GenericValue<rapidjson::UTF8<char>> & framesValue, const unsigned int & particles); // NOLINT(google-runtime-references)
    };
}

#endif // DESERIALIZER_H
