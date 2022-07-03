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

#include "DiskRepository.h"
#include <filesystem>
#include <fstream>

std::shared_ptr<Backend::Trajectory> Backend::DiskRepository::Load(std::string identifier)
{
    std::filesystem::path path = std::filesystem::u8path(identifier);
    if(!std::filesystem::exists(path))
    {
        throw std::runtime_error((std::string(u8"file \"") + path.string() + std::string(u8"\" does not exist")).c_str());
    }

    std::ifstream ifs;

    try
    {
        ifs.open(path);
    }
    catch (const std::exception& exception)
    {
        throw std::runtime_error((std::string(u8"when opening \"") + path.string() + std::string(u8"\" exception: \"") + exception.what() + std::string(u8"\"")).c_str());
    }

    if(!(ifs.is_open() && ifs.good()))
    {
        throw std::runtime_error((std::string(u8"unable to open stream \"") + path.string() + std::string(u8"\" for reading")).c_str());
    }

    auto trajectory = Deserializer::Deserialize(ifs);

    ifs.close();

    return trajectory;
}
