#pragma once

#include <queue>
#include <string>

#include "EventDTO.h"

class EventStreamServer
{
    public:
        void Publish(const TimelineEvent& event)
        {
            _outbox.push(EventDTO::ToJson(event));
        }

        bool HasPending() const
        {
            return !_outbox.empty();
        }

        std::string PopNext()
        {
            if (_outbox.empty()) return "";
            std::string payload = _outbox.front();
            _outbox.pop();
            return payload;
        }

    private:
        std::queue<std::string> _outbox;
};
