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

#include "../Backend/Deserializer.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <regex>
#include <sstream>

#ifndef TST_DESERIALIZER_H
#define TST_DESERIALIZER_H

TEST(BackendTest, DeserializationShallWorkCorrectly) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    const char * json = u8R"foo(
{
    "Version": 1,
    "Size": 0.5,
    "Viewport": {
        "MinX": -10.0,
        "MaxX": 10.0,
        "MinY": -11.0,
        "MaxY": 11.0
    },
    "Particles": [
        {
            "Id": 1
        },
        {
            "Id": 2
        }
    ],
    "Frames": [
        [
            {
                "X": 0.1,
                "Y": -0.3
            },
            {
                "X": 0.4,
                "Y": 0.6
            }
        ],
        [
            {
                "X": 0.2,
                "Y": -0.4
            },
            {
                "X": 0.5,
                "Y": 0.7
            }
        ],
        [
            {
                "X": 0.3,
                "Y": -0.5
            },
            {
                "X": 0.6,
                "Y": 0.8
            }
        ]
    ]
}
)foo";

    std::stringstream ss;
    ss << json;

    // Act
    std::shared_ptr<Backend::Trajectory> result = Backend::Deserializer::Deserialize(ss);

    // Assert
    EXPECT_NEAR(0.5, result->ParticleSize(), 0.001);

    auto viewport = result->Viewport();
    EXPECT_NEAR(-10.0, viewport.minX, 0.001);
    EXPECT_NEAR( 10.0, viewport.maxX, 0.001);
    EXPECT_NEAR(-11.0, viewport.minY, 0.001);
    EXPECT_NEAR( 11.0, viewport.maxY, 0.001);

    auto particles = result->Particles();
    EXPECT_EQ(1, particles[0].id);
    EXPECT_EQ(2, particles[1].id);

    auto frames = result->Frames();
    EXPECT_NEAR(0.1, frames[0].coordinates[0].x, 0.001);
    EXPECT_NEAR(-0.3, frames[0].coordinates[0].y, 0.001);
    EXPECT_NEAR(0.4, frames[0].coordinates[1].x, 0.001);
    EXPECT_NEAR(0.6, frames[0].coordinates[1].y, 0.001);

    EXPECT_NEAR(0.2, frames[1].coordinates[0].x, 0.001);
    EXPECT_NEAR(-0.4, frames[1].coordinates[0].y, 0.001);
    EXPECT_NEAR(0.5, frames[1].coordinates[1].x, 0.001);
    EXPECT_NEAR(0.7, frames[1].coordinates[1].y, 0.001);

    EXPECT_NEAR(0.3, frames[2].coordinates[0].x, 0.001);
    EXPECT_NEAR(-0.5, frames[2].coordinates[0].y, 0.001);
    EXPECT_NEAR(0.6, frames[2].coordinates[1].x, 0.001);
    EXPECT_NEAR(0.8, frames[2].coordinates[1].y, 0.001);
}

TEST(BackendTest, DeserializationShallThrowOnUnparseableInput) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    const char * json = u8R"foo(
{
    "Version": 1,
    "Size": 0.5,
    "Viewport": {
        "MinX": -10.0,
        "MaxX": 10.0,
        "MinY": -11.0,
        "MaxY": 11.0
)foo";

    std::stringstream ss;
    ss << json;

    // Act, Assert
    EXPECT_THROW({ auto result = Backend::Deserializer::Deserialize(ss); }, std::runtime_error); //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
}

TEST(BackendTest, DeserializationShallThrowOnSchemaViolation) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    const char * json = u8R"foo(
{
    "Version": 1,
    "Size": 0.5,
    "Viewport": {
        "MinX": -10.0,
        "MaxX": 10.0,
        "MinY": -11.0,
        "MaxY": 11.0
    }
}
)foo";

    std::stringstream ss;
    ss << json;

    // Act, Assert
    EXPECT_THROW({ auto result = Backend::Deserializer::Deserialize(ss); }, std::runtime_error); //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
}

TEST(BackendTest, DeserializationShallThrowOnInvalidVersion) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    const char * json = u8R"foo(
{
    "Version": 23,
    "Size": 0.5,
    "Viewport": {
        "MinX": -10.0,
        "MaxX": 10.0,
        "MinY": -11.0,
        "MaxY": 11.0
    },
    "Particles": [
        {
            "Id": 1
        },
        {
            "Id": 2
        }
    ],
    "Frames": [
        [
            {
                "X": 0.1,
                "Y": -0.3
            },
            {
                "X": 0.4,
                "Y": 0.6
            }
        ],
        [
            {
                "X": 0.2,
                "Y": -0.4
            },
            {
                "X": 0.5,
                "Y": 0.7
            }
        ],
        [
            {
                "X": 0.3,
                "Y": -0.5
            },
            {
                "X": 0.6,
                "Y": 0.8
            }
        ]
    ]
}
)foo";

    std::stringstream ss;
    ss << json;

    // Act, Assert
    EXPECT_THROW({ auto result = Backend::Deserializer::Deserialize(ss); }, std::runtime_error); //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
}

TEST(BackendTest, DeserializationShallThrowOnParticleNumberMismatch) //NOLINT (cert-err58-cpp, cppcoreguidelines-avoid-non-const-global-variables, cppcoreguidelines-owning-memory, fuchsia-statically-constructed-objects, misc-definitions-in-headers)
{
    // Arrange
    const char * json = u8R"foo(
{
    "Version": 1,
    "Size": 0.5,
    "Viewport": {
        "MinX": -10.0,
        "MaxX": 10.0,
        "MinY": -11.0,
        "MaxY": 11.0
    },
    "Particles": [
        {
            "Id": 1
        },
        {
            "Id": 2
        }
    ],
    "Frames": [
        [
            {
                "X": 0.1,
                "Y": -0.3
            },
            {
                "X": 0.4,
                "Y": 0.6
            }
        ],
        [
            {
                "X": 0.3,
                "Y": -0.5
            }
        ]
    ]
}
)foo";

    std::stringstream ss;
    ss << json;

    // Act, Assert
    EXPECT_THROW({ auto result = Backend::Deserializer::Deserialize(ss); }, std::runtime_error); //NOLINT(cppcoreguidelines-avoid-goto, hicpp-avoid-goto)
}

#endif // TST_DESERIALIZER_H
