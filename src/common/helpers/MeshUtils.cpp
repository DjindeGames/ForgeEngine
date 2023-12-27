#include "MeshUtils.h"

namespace ForgeEngine
{
    namespace MeshUtils
    {
        std::vector<float> GetPlaneVerticesCoordinates(float scale/* = 1.f*/)
        {
            return std::vector<float>
            {
                /******************SOUTH WEST*******************/
                -scale / 2.f, 0.f, -scale / 2.f,
                /******************NORTH WEST*******************/
                -scale / 2.f, 0.f, scale / 2.f,
                /******************NORTH EAST*******************/
                scale / 2.f, 0.f, scale / 2.f,
                /******************SOUTH EAST*******************/
                scale / 2.f, 0.f, -scale / 2.f
            };
        }

        std::vector<float> GetPlaneVerticesCoordinatesTextured(float scale/* = 1.f*/)
        {
            return std::vector<float>
            {
                    // positions       // texture coords
                -scale / 2.f, 0.f, -scale / 2.f, scale, scale, // top right
                -scale / 2.f, 0.f,  scale / 2.f, scale, 0.f, // bottom right
                 scale / 2.f, 0.f,  scale / 2.f, 0.f, 0.f, // bottom left
                 scale / 2.f, 0.f, -scale / 2.f, 0.f, scale  // top left 
            };
        }

        std::vector<float> GetPlaneVerticesCoordinatesColored(const Color& color)
        {
            return std::vector<float>
            {
                // positions       // texture coords
               -0.5f, 0.f, -0.5f, color.GetRRatio(), color.GetGRatio(), color.GetBRatio(), color.GetA(), // top right
               -0.5f, 0.f,  0.5f, color.GetRRatio(), color.GetGRatio(), color.GetBRatio(), color.GetA(), // bottom right
                0.5f, 0.f,  0.5f, color.GetRRatio(), color.GetGRatio(), color.GetBRatio(), color.GetA(), // bottom left
                0.5f, 0.f, -0.5f, color.GetRRatio(), color.GetGRatio(), color.GetBRatio(), color.GetA() // top left 
            };
        }

        std::vector<unsigned int> GetPlaneVerticesIndexes()
        {
            return  std::vector<unsigned int>
            {
                0, 1, 3,
                1, 2, 3
            };
        }

        std::vector<float> GetCubeVerticesCoordinates()
        {
            return std::vector<float>
            {
                /******************SIDE FRONT*******************/
                 0.5f,  0.5f, 0.5f,
                 0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f,  0.5f, 0.5f,
                /******************SIDE RIGHT*******************/
                 0.5f,  0.5f,-0.5f,
                 0.5f, -0.5f,-0.5f,
                 0.5f, -0.5f, 0.5f,
                 0.5f,  0.5f, 0.5f,
                 /******************SIDE BACK********************/
                -0.5f,  0.5f,-0.5f,
                -0.5f, -0.5f,-0.5f,
                 0.5f, -0.5f,-0.5f,
                 0.5f,  0.5f,-0.5f,
                /******************SIDE LEFT********************/
                -0.5f,  0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f,-0.5f,
                -0.5f,  0.5f,-0.5f,
                /******************TOP**************************/
                 0.5f, 0.5f, -0.5f,
                 0.5f, 0.5f,  0.5f,
                -0.5f, 0.5f,  0.5f,
                -0.5f, 0.5f, -0.5f, 
                /******************BOTTOM***********************/
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                 0.5f, -0.5f,  0.5f,
                 0.5f, -0.5f, -0.5f
            };
        }

        std::vector<unsigned int> GetCubeVerticesIndexes()
        {
            return  std::vector<unsigned int>
            {
                /******************SIDE FRONT*******************/
                0, 1, 3,
                1, 2, 3,
                /******************SIDE RIGHT*******************/
                4, 5, 7,
                5, 6, 7,
                /******************SIDE BACK********************/
                8, 9, 11,
                9, 10, 11,
                /******************SIDE LEFT********************/
                12, 13, 15,
                13, 14, 15,
                /******************TOP**************************/
                16, 17, 19,
                17, 18, 19,
                /******************BOTTOM***********************/
                20, 21, 23,
                21, 22, 23
            };
        }

        std::vector<float> GetSphereVerticesCoordinates()
        {
            return std::vector<float>();
        }

        std::vector<unsigned int> GetSphereVerticesIndexes()
        {
            return std::vector<unsigned int>();
        }
    }
}