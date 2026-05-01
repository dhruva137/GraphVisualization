#pragma once

#include <algorithm>
#include <vector>

#include "TimelineEvent.h"

class TimelinePlayer
{
    public:
        void Load(std::vector<TimelineEvent> events)
        {
            _events = std::move(events);
            _cursor = 0;
            _elapsed = 0.0f;
        }

        void Play() { _isPlaying = true; }
        void Pause() { _isPlaying = false; }
        void TogglePlay() { _isPlaying = !_isPlaying; }

        void SetStepInterval(float seconds)
        {
            _stepIntervalSeconds = std::clamp(seconds, 0.01f, 1.0f);
        }

        bool StepForward(TimelineEvent& outEvent)
        {
            if (_cursor >= static_cast<int>(_events.size())) return false;
            outEvent = _events[_cursor++];
            return true;
        }

        bool StepBackward()
        {
            if (_cursor <= 0) return false;
            _cursor--;
            return true;
        }

        bool Update(float deltaSeconds, TimelineEvent& outEvent)
        {
            if (!_isPlaying) return false;
            _elapsed += deltaSeconds;

            if (_elapsed >= _stepIntervalSeconds)
            {
                _elapsed -= _stepIntervalSeconds;
                return StepForward(outEvent);
            }

            return false;
        }

        TimelineSnapshot Snapshot() const
        {
            return TimelineSnapshot{_cursor, _isPlaying, 1.0f / _stepIntervalSeconds, _events};
        }

    private:
        std::vector<TimelineEvent> _events;
        int _cursor = 0;
        bool _isPlaying = false;
        float _elapsed = 0.0f;
        float _stepIntervalSeconds = 0.08f;
};
