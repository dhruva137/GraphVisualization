#include <iomanip>
#include <sstream>

#include "Utils/Resources.h"
#include "DataStructures/Graph/Graph.h"
#include "DataStructures/Graph/VisualGraph/VisualGraph.h"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        try
        {
            Utils::SetRandomSeed(static_cast<unsigned int>(std::stoul(argv[1])));
        }
        catch (...)
        {
            Utils::SetRandomSeed(42u);
        }
    }
    else
    {
        Utils::SetRandomSeed(42u);
    }

    Font font;
    font.loadFromFile("../Resources/Roboto.ttf");

    VisualGraph graph(50, 1500, 800);
    graph.VisualDFS();

    RenderWindow window(VideoMode(1600, 900), "Graph Visualization");
    window.setFramerateLimit(144);

    Clock frameClock;
    Event event;

    while (window.isOpen())
    {
        float deltaSeconds = frameClock.restart().asSeconds();

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Num1) { graph.VisualDFS(); }
                    if (event.key.code == Keyboard::Num2) { graph.VisualBFS(); }
                    if (event.key.code == Keyboard::Num3) { graph.VisualizeCyclicEdges(); }
                    if (event.key.code == Keyboard::Num4) { graph.VisualShortestPath(0, 10); }
                    if (event.key.code == Keyboard::LBracket) { graph.SetRevealIntervalSeconds(graph.GetRevealIntervalSeconds() + 0.01f); }
                    if (event.key.code == Keyboard::RBracket) { graph.SetRevealIntervalSeconds(graph.GetRevealIntervalSeconds() - 0.01f); }
                    break;
            }
        }

        graph.UpdateVisualization(deltaSeconds);

        window.clear(Color(14, 18, 28));

        for (int i = 0; i < graph.GetNodeCount(); i++)
        {
            for (int j = 0; j < graph.GetNodes()[i].GetOutDegree(); j++)
            {
                window.draw(graph.GetAdjLinkList()[i].ValueAt(j)->GetLine(), 2, Lines);
                window.draw(graph.GetAdjLinkList()[i].ValueAt(j)->GetArrow());
            }
        }

        for (int i = 0; i < graph.VisualizedEdges->Size(); i++)
        {
            window.draw(graph.VisualizedEdges->ValueAt(i).GetLine(), 2, Lines);
            window.draw(graph.VisualizedEdges->ValueAt(i).GetArrow());
        }

        for (int i = 0; i < graph.GetNodeCount(); i++)
        {
            window.draw(graph.GetNodes()[i].GetShape());
            Text t;
            t.setFont(font);
            t.setCharacterSize(Constants::NODE_INDEX_CHAR_SIZE);
            t.setFillColor(Constants::GET_NODE_INDEX_TEXT_COLOR());
            t.setString(std::to_string(graph.GetNodes()[i].GetIndex()));
            t.setPosition(graph.GetNodes()[i].GetPosition());
            t.setOrigin(Constants::NODE_RADIUS, Constants::NODE_RADIUS);
            window.draw(t);
        }

        std::stringstream hud;
        hud << "Mode: " << graph.GetCurrentModeLabel() << "  |  Speed: " << std::fixed << std::setprecision(2)
            << graph.GetRevealIntervalSeconds() << " s/edge\n"
            << "1: DFS  2: BFS  3: Cycles  4: ShortestPath(0->10)  [: slower  ]: faster";

        Text info;
        info.setFont(font);
        info.setCharacterSize(18);
        info.setFillColor(Color(220, 235, 255));
        info.setString(hud.str());
        info.setPosition(16, 12);
        window.draw(info);

        window.display();
    }
}
