#pragma once

#include "system/misc/Color.h"

#include <vector>

namespace ForgeEngine
{
    namespace MeshUtils
    {
        std::vector<float> GetPlaneVerticesCoordinates(float scale = 1.f);
        std::vector<float> GetPlaneVerticesCoordinatesTextured(float scale = 1.f);
        std::vector<float> GetPlaneVerticesCoordinatesColored(const Color& color);
        std::vector<unsigned int> GetPlaneVerticesIndexes();

        std::vector<float> GetCubeVerticesCoordinates();
        std::vector<unsigned int> GetCubeVerticesIndexes();

        std::vector<float> GetSphereVerticesCoordinates();
        std::vector<unsigned int> GetSphereVerticesIndexes();
    }
}
