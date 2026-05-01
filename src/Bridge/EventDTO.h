#pragma once

#include <sstream>
#include <string>

#include "../Runtime/TimelineEvent.h"

class EventDTO
{
    public:
        static std::string ToJson(const TimelineEvent& event)
        {
            std::stringstream ss;
            ss << "{"
               << "\"stepIndex\":" << event.stepIndex << ","
               << "\"source\":" << event.source << ","
               << "\"target\":" << event.target << ","
               << "\"weight\":" << event.weight << ","
               << "\"label\":\"" << event.label << "\""
               << "}";
            return ss.str();
        }
};
