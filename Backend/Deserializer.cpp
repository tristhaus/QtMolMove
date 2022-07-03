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

#include <sstream>
#include <stdexcept>

#include "../Include/rapidjson/istreamwrapper.h"
#include "../Include/rapidjson/schema.h"
#include "../Include/rapidjson/stringbuffer.h"
#include "Deserializer.h"

std::shared_ptr<Backend::Trajectory> Backend::Deserializer::Deserialize(std::istream & is)
{
    const std::string schemaData = u8R"foo(
{
  "$schema": "https://json-schema.org/draft-04/schema",
  "$id": "https://github.com/tristhaus/QtMolMove/blob/trunk/trajectory.schema.json",
  "title": "Trajectory",
  "description": "A trajectory for QtMolMove.",
  "version": 1,
  "type": "object",
  "properties": {
    "Version": {
      "description": "The schema version",
      "type": "integer",
      "minimum": 1
    },
    "Size": {
      "description": "The uniform display size of the particles",
      "type": "number"
    },
    "Viewport": {
      "description": "The viewport to be used for the display",
      "type": "object",
      "properties": {
        "MinX": {
          "description": "The left edge of the viewport",
          "type": "number"
        },
        "MaxX": {
          "description": "The right edge of the viewport",
          "type": "number"
        },
        "MinY": {
          "description": "The bottom edge of the viewport",
          "type": "number"
        },
        "MaxY": {
          "description": "The top edge of the viewport",
          "type": "number"
        }
      },
      "required": [
        "MinX",
        "MaxX",
        "MinY",
        "MaxY"
      ]
    },
    "Particles": {
      "description": "Descriptions of the particles. Order must match Frames[] objects",
      "type": "array",
      "items": {
        "description": "Description of one particle",
        "type": "object",
        "properties": {
          "Id": {
            "description": "The identity of a particle. Particles with the same Id will have the same color",
            "type": "integer",
            "minimum": 0,
            "maximum": 19
          }
        },
        "required": [
          "Id"
        ]
      },
      "minItems": 1
    },
    "Frames": {
      "description": "The collection of frames to display",
      "type": "array",
      "items": {
        "description": "One frame containing coordinate descriptions for each particle",
        "type": "array",
        "items": {
          "description": "A coordinate description for the matching particle",
          "type": "object",
          "properties": {
            "X": {
              "description": "The x-coordinate for a particle",
              "type": "number"
            },
            "Y": {
              "description": "The y-coordinate for a particle",
              "type": "number"
            }
          },
          "required": [
            "X",
            "Y"
          ]
        },
        "minItems": 1
      },
      "minItems": 1
    }
  },
  "required": [
    "Version",
    "Size",
    "Viewport",
    "Particles",
    "Frames"
  ]
}
)foo";

    rapidjson::IStreamWrapper isw(is);

    rapidjson::GenericDocument<rapidjson::UTF8<char>> document;
    if (document.ParseStream(isw).HasParseError())
    {
        throw std::runtime_error(u8"input does not parse");
    }

    rapidjson::Document schemaDocument;
    if (schemaDocument.Parse(schemaData.c_str()).HasParseError()) {
        throw std::logic_error(u8"schema does not parse");
    }
    rapidjson::SchemaDocument schema(schemaDocument);

    rapidjson::SchemaValidator validator(schema);
    if (!document.Accept(validator)) {
        std::stringstream ss;
        ss << "input does not validate against schema\n";

        rapidjson::StringBuffer sb;
        validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
        ss << "Invalid schema: " << sb.GetString() << "\n";
        sb.Clear();

        ss << "Invalid keyword: " << validator.GetInvalidSchemaKeyword() << "\n";

        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
        ss << "Invalid document: " << sb.GetString() << "\n";

        std::string error;
        ss >> error;

        throw std::runtime_error(error);
    }

    if (!(document.HasMember(KeyVersion) && document[KeyVersion].IsInt() && document[KeyVersion].GetInt() == 1))
    {
        throw std::runtime_error(u8"no valid version found");
    }

    auto size = ParseSize(document[KeySize]);
    auto viewport = ParseViewport(document[KeyViewport]);
    auto particles = ParseParticles(document[KeyParticles]);
    auto frames = ParseFrames(document[KeyFrames], static_cast<const unsigned int>(particles.size()));

    return std::make_shared<Trajectory>(static_cast<unsigned int>(particles.size()), size, viewport, particles, frames);
}

Backend::unit Backend::Deserializer::ParseSize(rapidjson::GenericValue<rapidjson::UTF8<char>>& sizeValue)
{
    return unit(sizeValue.GetDouble());
}

Backend::Viewport Backend::Deserializer::ParseViewport(rapidjson::GenericValue<rapidjson::UTF8<char>>& viewportValue)
{
    auto minX = unit(viewportValue[KeyMinX].GetDouble());
    auto maxX = unit(viewportValue[KeyMaxX].GetDouble());
    auto minY = unit(viewportValue[KeyMinY].GetDouble());
    auto maxY = unit(viewportValue[KeyMaxY].GetDouble());

    return Viewport(minX, maxX, minY, maxY);
}

std::vector<Backend::Particle> Backend::Deserializer::ParseParticles(rapidjson::GenericValue<rapidjson::UTF8<char>>& particlesValue)
{
    auto particlesArray = particlesValue.GetArray();

    std::vector<Backend::Particle> particles;

    for (auto const & particleValue : particlesArray)
    {
        particles.emplace_back(Particle(particleValue[KeyId].GetInt()));
    }

    return particles;
}

std::vector<Backend::Frame> Backend::Deserializer::ParseFrames(rapidjson::GenericValue<rapidjson::UTF8<char>>& framesValue, const unsigned int & particles)
{
    auto framesArray = framesValue.GetArray();

    std::vector<Backend::Frame> frames;

    for (auto const & frameValue : framesArray)
    {
        auto frameArray = frameValue.GetArray();

        if (frameArray.Size() != particles)
        {
            throw std::runtime_error(u8"incorrect number of particles in frame");
        }

        std::vector<Coordinate> coordinates;

        for (auto const & coordinate : frameArray)
        {
            auto x = unit(coordinate[KeyX].GetDouble());
            auto y = unit(coordinate[KeyY].GetDouble());

            coordinates.emplace_back(Coordinate(x, y));
        }

        frames.emplace_back(coordinates);
    }

    return frames;
}
