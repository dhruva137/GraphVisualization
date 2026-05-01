#include <cmath>

#include "VisualGraphNode.h"
#include "VisualGraphEdge.h"

class VisualGraph : public Graph<VisualGraphNode, VisualGraphEdge>
{
    public:
        VisualGraph(int nodeCount, int windowWidth, int windowHeight);

        void VisualDFS();

        void VisualBFS();

        void VisualShortestPath(int source, int target);

        void VisualizeCyclicEdges();

        void UpdateVisualization(float deltaSeconds);
        void SetRevealIntervalSeconds(float seconds);
        float GetRevealIntervalSeconds() const;
        const std::string& GetCurrentModeLabel() const;

        LinkedList<VisualGraphEdge> * VisualizedEdges;

    private:
        Color * _visualColorPalette;
        LinkedList<VisualGraphEdge *> _pendingEdges;
        float _revealTimerSeconds = 0.0f;
        float _revealIntervalSeconds = 0.08f;
        std::string _currentModeLabel = "DFS";

        void InitColorPalette();
        void QueueVisualization(LinkedList<VisualGraphEdge *> edges, Color color, const std::string& modeLabel);
};

VisualGraph::VisualGraph(int nodeCount, int windowWidth, int windowHeight)
{
    VisualizedEdges = new LinkedList<VisualGraphEdge>;

    _nodeCount = nodeCount;

    InitColorPalette();

    _nodes = (VisualGraphNode *) calloc(sizeof(VisualGraphNode), nodeCount);

    _adjLinkList = (LinkedList<VisualGraphEdge *> *) calloc(sizeof(LinkedList<VisualGraphEdge *>), nodeCount);

    for (int i = 0; i < nodeCount; i++)
    {
        _nodes[i] = VisualGraphNode(i, 0, Constants::GET_NODE_COLOR(), Utils::GetRandomVector2(windowWidth, windowHeight));

        _adjLinkList[i] = LinkedList<VisualGraphEdge *>();
    }

    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j ++)
        {
            if (i == j) { continue; }

            float distance = _nodes[i].GetDistance(_nodes[j]);
            float dice = Utils::GetRandomFloat();

            bool canThereBeEdge =
                    (distance < Constants::ADJACENCY_DISTANCE_THRESHOLD && dice < Constants::ADJACENCY_POSSIBLITY) ||
                    (dice < Constants::ADJACENCY_POSSIBLITY_AFTER_EXCEED_THRESHOLD);

            if (canThereBeEdge)
            {
                _nodes[i].SetOutDegree(_nodes[i].GetOutDegree() + 1);

                VisualGraphEdge * edge = new VisualGraphEdge(
                                            &_nodes[i],
                                            &_nodes[j],
                                            Constants::GET_EDGE_COLOR());

                _adjLinkList[i].PushBack(edge);
            }
        }
    }
}

void VisualGraph::SetRevealIntervalSeconds(float seconds)
{
    if (seconds < 0.01f)
    {
        _revealIntervalSeconds = 0.01f;
        return;
    }

    if (seconds > 0.5f)
    {
        _revealIntervalSeconds = 0.5f;
        return;
    }

    _revealIntervalSeconds = seconds;
}

float VisualGraph::GetRevealIntervalSeconds() const
{
    return _revealIntervalSeconds;
}

const std::string& VisualGraph::GetCurrentModeLabel() const
{
    return _currentModeLabel;
}

void VisualGraph::QueueVisualization(LinkedList<VisualGraphEdge *> edges, Color color, const std::string& modeLabel)
{
    VisualizedEdges->Clear();
    _pendingEdges.Clear();
    _revealTimerSeconds = 0.0f;
    _currentModeLabel = modeLabel;

    for (int i = 0; i < edges.Size(); i++)
    {
        edges.ValueAt(i)->SetColor(color);
        _pendingEdges.PushBack(edges.ValueAt(i));
    }
}

void VisualGraph::UpdateVisualization(float deltaSeconds)
{
    _revealTimerSeconds += deltaSeconds;

    while (_revealTimerSeconds >= _revealIntervalSeconds && !_pendingEdges.IsEmpty())
    {
        VisualizedEdges->PushBack(*(_pendingEdges.PopFront()));
        _revealTimerSeconds -= _revealIntervalSeconds;
    }
}

void VisualGraph::VisualDFS()
{
    QueueVisualization(DFS(), Color::Red, "DFS");
}

void VisualGraph::VisualBFS()
{
    QueueVisualization(BFS(), Color::Green, "BFS");
}

void VisualGraph::VisualShortestPath(int source, int target)
{
    QueueVisualization(ShortestPath(source, target), Color::Yellow, "Shortest Path");
}

void VisualGraph::VisualizeCyclicEdges()
{
    QueueVisualization(DetermineCycles(), Color::Magenta, "Cycle Detection");
}

void VisualGraph::InitColorPalette()
{
    _visualColorPalette = (Color *) calloc(sizeof(Color), _nodeCount);

    for (int i = 0; i < _nodeCount; i ++)
    {
        float r = Utils::GetRandomFloat(0, 255);
        float g = Utils::GetRandomFloat(0, 255);
        float b = Utils::GetRandomFloat(0, 255);

        _visualColorPalette[i] = Color(r, g, b, 255);
    }
}
