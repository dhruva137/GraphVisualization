#include <random>
#include <iomanip>
#include <iostream>
#include "SFML/Graphics.hpp"

class Utils
{
    public:
        static void SetRandomSeed(unsigned int seed)
        {
            Generator() = std::mt19937(seed);
        }

        static float GetRandomFloat(float min = 0, float max = 1)
        {
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(Generator());
        }

        static sf::Vector2f GetRandomVector2(float maxX, float maxY)
        {
            float randX = GetRandomFloat(0, maxX);
            float randY = GetRandomFloat(0, maxY);

            return sf::Vector2f(randX, randY);
        }

    private:
        static std::mt19937& Generator()
        {
            static std::mt19937 generator(std::random_device{}());
            return generator;
        }
};
