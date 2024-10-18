#include "System.h"
#include "Window.h"
#include "LayerArray.h"
#include "ColliderManager.h"

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

	void System::DetachLayer(Layer* pLayer)
	{
		System& system = System::GetInstance();
		system.m_layerArray->RemoveLayer(pLayer);
		pLayer->OnDetach();
	}

	void System::DetachOverlay(Layer* ppOverlay)
	{
		System& system = System::GetInstance();
		system.m_layerArray->RemoveOverlay(ppOverlay);
		ppOverlay->OnDetach();
	}

	Layer* System::FindLayer(const std::string& className)
	{
		System& system = System::GetInstance();
		Layer* target = nullptr;
		for (auto layer : *system.m_layerArray)
		{
			if (className == layer->GetName())
			{
				target = layer;
				break;
			}
		}
		return (target);
	}

	void System::ExitProgram()
	{
		System& system = System::GetInstance();
		system.m_isPlaying = false;
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
		while (m_isPlaying && m_window->IsOpen())
		{
			EventQueue eventQueue;
			static float timeScale = 1.0f;
 			float dt = clock.restart().asSeconds() * timeScale;
			// ���̾� �߰� ��û ó��
			m_layerArray->WorkingInsertLayers();

			// �̺�Ʈ ����
			m_window->Event(&eventQueue);

			// Layer �̺�Ʈ ����
			for (auto& event : eventQueue)
			{
				switch (event.get().type)
				{
					// �Ͻ� ����
					case sf::Event::KeyPressed:
					{
						switch (event.get().key.code)
						{
						case sf::Keyboard::Return:
							m_isPause = (m_isPause == false) ? true : false;
							timeScale = (timeScale == 0.0f) ? 1.0f : 0.0f;
							break;
						}
					}
				}

				if (!m_isPause)
				{
					for (auto layer : (*m_layerArray))
					{
						if (!event.empty())
							layer->OnEvent(event);
						else
							break;
					}
				}
			} // for (auto& event : eventQueue)

			// Layer ������Ʈ
			if (!m_isPause)
			{
				for (auto layer : (*m_layerArray))
				{
					layer->OnUpdate(dt);
				}
			}

			// ���� ��û�� ���̾� ����
			m_layerArray->WorkingGarbage();

			// �浹 üũ
			auto& colManager = ColliderManager::GetInstance();
			for (auto collider1 : colManager)
			{
				for (auto collider2 : colManager)
				{
					(*collider1)->IsCollided(**collider2);
				}
			}

			// ��� ������Ʈ �׸���
			auto& device = m_window->GetHandle();
			device.clear();
			for (auto layer : (*m_layerArray))
			{
				layer->OnDraw(device);
			}
			for (auto layer : (*m_layerArray))
			{
				layer->OnUI(device);
			}
			for (auto collider : colManager)
			{
				if ((*collider)->IsDisplay())
				{
					auto& rect = (*collider)->GetBox();
					device.draw(rect);
				}
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
		, m_isPause(false)
		, m_isPlaying(true)
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