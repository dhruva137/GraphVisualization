#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../Runtime/TimelineEvent.h"

using AlgorithmParams = std::unordered_map<std::string, std::string>;

class IAlgorithm
{
    public:
        virtual ~IAlgorithm() = default;
        virtual std::string Id() const = 0;
        virtual std::string Name() const = 0;
        virtual bool Validate(const AlgorithmParams& params, std::string& error) const = 0;
        virtual std::vector<TimelineEvent> RunStepwise(const AlgorithmParams& params) = 0;
};

class AlgorithmRegistry
{
    public:
        void Register(IAlgorithm* algorithm)
        {
            _algorithms.push_back(algorithm);
        }

        const std::vector<IAlgorithm*>& All() const
        {
            return _algorithms;
        }

        IAlgorithm* FindById(const std::string& id) const
        {
            for (auto* algorithm : _algorithms)
            {
                if (algorithm->Id() == id)
                {
                    return algorithm;
                }
            }
            return nullptr;
        }

    private:
        std::vector<IAlgorithm*> _algorithms;
};
