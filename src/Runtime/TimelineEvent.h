#pragma once

#include <string>
#include <vector>

enum class TimelineEventType
{
    NodeDiscovered,
    EdgeRelaxed,
    FrontierPush,
    FrontierPop,
    ComponentClosed,
    Note
};

struct TimelineEvent
{
    TimelineEventType type = TimelineEventType::Note;
    int stepIndex = 0;
    int source = -1;
    int target = -1;
    float weight = 0.0f;
    std::string label;
};

struct TimelineSnapshot
{
    int cursor = 0;
    bool isPlaying = false;
    float playbackSpeed = 1.0f;
    std::vector<TimelineEvent> events;
};
