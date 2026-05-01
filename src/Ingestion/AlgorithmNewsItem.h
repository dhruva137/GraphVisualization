#pragma once

#include <string>
#include <vector>

struct AlgorithmNewsItem
{
    std::string id;
    std::string source;
    std::string title;
    std::string url;
    std::string publishedAtIso;
    std::vector<std::string> tags;
    float score = 0.0f;
};
