#pragma once
#include "Core.h"
#include "Event.h"

namespace fz {

    class EventQueue
    {
        using iter = std::vector<Event>::iterator;
        using const_iter = std::vector<Event>::const_iterator;

    public:
        explicit EventQueue();
        virtual ~EventQueue();

        void        push(const sf::Event& event);
        bool        empty() const;
        int         size() const;
        iter        begin();
        iter        end();

    private:
        std::vector<Event>  m_eventQueue;
    };

} // namespace fz