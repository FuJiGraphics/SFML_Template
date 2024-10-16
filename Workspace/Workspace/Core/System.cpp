#include "System.h"
#include "Window.h"
#include "LayerArray.h"

namespace fz {

	System* System::s_system = nullptr;

	System& System::GetInstance()
	{
		if (s_system == nullptr)
		{
			s_system = new System();
		}
		return (*s_system);
	}

	void System::Delete()
	{
		if (s_system != nullptr)
		{
			delete s_system;
			s_system = nullptr;
		}
	}

	void System::AttachLayer(Layer* pLayer)
	{
		System& system = System::GetInstance();
		system.m_layerArray->InsertLayer(pLayer);
		pLayer->OnAttach();
	}

	void System::AttachOverlay(Layer* pOverlay)
	{
		System& system = System::GetInstance();
		system.m_layerArray->InsertOverlay(pOverlay);
		pOverlay->OnAttach();
	}

	void System::CreateWindow(int width, int height, const char* title)
	{
		if (m_window != nullptr)
			return;

		m_window = new Window(width, height, title);
		m_window->Create();
		m_width = width;
		m_height = height;
	}

	void System::Run()
	{
		sf::Clock clock;
		while (m_window->IsOpen())
		{
			EventQueue eventQueue;
			float dt = clock.restart().asSeconds();

			// �̺�Ʈ ����
			m_window->Event(&eventQueue);

			// Layer �̺�Ʈ ����
			for (auto& event : eventQueue)
			{
				for (auto layer : (*m_layerArray))
				{
					if (!event.empty())
						layer->OnEvent(event);
					else
						break;
				}
			}

			// Layer ������Ʈ
			for (auto layer : (*m_layerArray))
			{
				layer->OnUpdate(dt);
			}

			// Layer ������Ʈ
			auto& device = m_window->GetHandle();
			device.clear();
			for (auto layer : (*m_layerArray))
			{
				layer->OnDraw(device);
			}
			device.display();

		}
	}

	int System::GetWidth()
	{
		return (m_width);
	}

	int System::GetHeight()
	{
		return (m_height);
	}

	sf::RenderWindow& System::GetDevice()
	{
		return (m_window->GetHandle());
	}

	System::System()
		: m_window(nullptr)
		, m_layerArray(nullptr)
		, m_width(0)
		, m_height(0)
	{
		m_layerArray = new LayerArray();
	}

	System::~System()
	{
		if (m_window != nullptr)
		{
			m_window->Release();
			delete m_window;
			m_window = nullptr;
		}
		if (m_layerArray != nullptr)
		{
			delete m_layerArray;
			m_layerArray = nullptr;
		}
	}

} // namespace fz