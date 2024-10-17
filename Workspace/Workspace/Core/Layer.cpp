#include "Layer.h"
#include "LayerArray.h"
#include "Collider.h"
#include "ColliderManager.h"

namespace fz {

    unsigned int Layer::s_numOfLayers = 0;

    Layer::Layer()
        : m_body(nullptr)
    {
        s_numOfLayers++;
    }

    Layer::~Layer()
    {
        s_numOfLayers--;
        if (m_body)
        {
            auto& manager = GetColliderManager();
            // TODO: Manager에서 제거
            int target = ColliderFind(m_body);
            if (target != -1)
                manager.erase(manager.begin() + target);
            m_body->Activate(false, "", nullptr);
            delete m_body;
            m_body = nullptr;
        }
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

    void Layer::OnCollide(Layer* pLayer, const std::string& className)
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

    bool Layer::IsActivatedCollider() const
    {
        if (m_body)
            return (m_body->IsActivated());
        else
            return (false);
    }

    void Layer::ActivateCollider(bool flags, const std::string& className)
    {
        if (this->IsActivatedCollider())
            return;

        auto& manager = GetColliderManager();
        if (flags)
        {
            if (m_body == nullptr)
                m_body = new Collider();
            m_body->Activate(flags, className, this);
            // TODO: Collider Manager에 등록
            // ...
            manager.push_back(m_body);
        }
        else
        {
            // TODO: Collider Manager에 해제
            // ...
            if (m_body)
            {
                int target = ColliderFind(m_body);
                if (target != -1)
                    manager.erase(manager.begin() + target);
                m_body->Activate(flags, "", nullptr);
                delete m_body;
                m_body = nullptr;
            }
        }
    }

    void Layer::SetCollider(int x, int y, int rect, int right)
    {
        m_body->Set(x, y, rect, right);
    }

} // namespace fz
