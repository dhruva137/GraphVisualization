#pragma once

#include <algorithm>
#include <chrono>
#include <unordered_set>
#include <vector>

#include "AlgorithmNewsItem.h"

class IngestionService
{
    public:
        void UpsertBatch(const std::vector<AlgorithmNewsItem>& batch)
        {
            for (const auto& item : batch)
            {
                if (_ids.count(item.id) > 0)
                {
                    continue;
                }

                _ids.insert(item.id);
                _items.push_back(item);
            }

            std::sort(_items.begin(), _items.end(), [](const AlgorithmNewsItem& a, const AlgorithmNewsItem& b)
            {
                return a.score > b.score;
            });

            _lastUpdateEpochSeconds = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        }

        std::vector<AlgorithmNewsItem> Top(int count) const
        {
            if (count <= 0) return {};
            if (count >= static_cast<int>(_items.size())) return _items;
            return std::vector<AlgorithmNewsItem>(_items.begin(), _items.begin() + count);
        }

        long long LastUpdateEpochSeconds() const
        {
            return _lastUpdateEpochSeconds;
        }

    private:
        std::vector<AlgorithmNewsItem> _items;
        std::unordered_set<std::string> _ids;
        long long _lastUpdateEpochSeconds = 0;
};
