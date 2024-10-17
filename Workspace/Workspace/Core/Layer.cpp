#include "Layer.h"

namespace fz {

    unsigned int Layer::s_numOfLayers = 0;

    Layer::Layer()
    {
        s_numOfLayers++;
    }

    Layer::~Layer()
    {
        s_numOfLayers--;
    }

    void Layer::OnAttach()
    {
        // Empty
    }

    void Layer::OnDetach()
    {
        // Empty
    }

    void Layer::OnEvent(Event& event)
    {
        // Empty
    }

    void Layer::OnUpdate(float dt)
    {
        // Empty
    }

    void Layer::OnDraw(sf::RenderWindow& device)
    {
        // Empty
    }

    void Layer::OnUI(sf::RenderWindow& device)
    {
        // Empty
    }

    std::string Layer::GetName() const
    {
        return ("null");
    }

    unsigned int Layer::GetCount()
    {
        return (s_numOfLayers);
    }

} // namespace fz
