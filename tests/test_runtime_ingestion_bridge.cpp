#include <cassert>
#include <vector>

#include "../src/Runtime/TimelinePlayer.h"
#include "../src/Ingestion/IngestionService.h"
#include "../src/Bridge/EventStreamServer.h"

int main()
{
    TimelinePlayer player;
    std::vector<TimelineEvent> events = {
        {TimelineEventType::NodeDiscovered, 0, 0, -1, 0.0f, "start"},
        {TimelineEventType::FrontierPush, 1, 0, 1, 1.0f, "push"}
    };

    player.Load(events);
    player.Play();
    player.SetStepInterval(0.01f);

    TimelineEvent e;
    bool emitted = player.Update(0.02f, e);
    assert(emitted);
    assert(e.stepIndex == 0);

    IngestionService service;
    service.UpsertBatch({
        {"a", "arxiv", "A", "u1", "2026-01-01", {"graph"}, 3.0f},
        {"b", "github", "B", "u2", "2026-01-02", {"flow"}, 5.0f},
        {"a", "arxiv", "A-dup", "u1", "2026-01-01", {"graph"}, 9.0f}
    });

    auto top = service.Top(2);
    assert(top.size() == 2);
    assert(top[0].id == "b");

    EventStreamServer stream;
    TimelineEvent ev{TimelineEventType::EdgeRelaxed, 2, 1, 2, 2.5f, "relax"};
    stream.Publish(ev);
    assert(stream.HasPending());
    auto payload = stream.PopNext();
    assert(!payload.empty());

    return 0;
}
