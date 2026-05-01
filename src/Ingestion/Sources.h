#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "AlgorithmNewsItem.h"

class IngestionSources
{
    public:
        static std::string ArxivQueryUrl(const std::string& q, int maxResults = 25)
        {
            std::stringstream ss;
            ss << "http://export.arxiv.org/api/query?search_query=all:" << q
               << "&start=0&max_results=" << maxResults
               << "&sortBy=submittedDate&sortOrder=descending";
            return ss.str();
        }

        static std::string CrossrefQueryUrl(const std::string& q, int rows = 20)
        {
            std::stringstream ss;
            ss << "https://api.crossref.org/works?query=" << q << "&sort=published&order=desc&rows=" << rows;
            return ss.str();
        }

        static std::string GithubRepoQueryUrl(const std::string& q)
        {
            std::stringstream ss;
            ss << "https://api.github.com/search/repositories?q=" << q << "&sort=updated&order=desc";
            return ss.str();
        }

        static std::vector<AlgorithmNewsItem> MergeAndRank(const std::vector<AlgorithmNewsItem>& input)
        {
            std::vector<AlgorithmNewsItem> out = input;
            for (auto& item : out)
            {
                item.score = item.score + 1.0f;
            }
            return out;
        }
};
