#include "System.h"
#include "Window.h"
#include "LayerArray.h"
#include "ColliderManager.h"
#include "Player.h"

namespace fz {

	float	System::s_timeScale = 1.0f;

	System& System::GetInstance()
	{
		static System s_system;
		return (s_system);
	}

	void System::Delete()
	{
		System& system = System::GetInstance();
		system.Reset();
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
		system.m_isReset = false;
	}

	void System::SetPause(bool enabled)
	{
		System& system = System::GetInstance();
		system.m_isPause = enabled;
		s_timeScale = (enabled) ? 0.0f : 1.0f;
	}

	void System::SetReset(bool enabled)
	{
		System& system = System::GetInstance();
		system.m_isPlaying = (enabled) ? false : true;
		system.m_isReset = enabled;
	}

	bool System::GetResetStatus()
	{
		System& system = System::GetInstance();
		return (system.m_isReset);
	}

	bool System::IsPaused()
	{
		System& system = System::GetInstance();
		return (system.m_isPause);
	}

	bool System::IsFirstEvent()
	{
		System& system = System::GetInstance();
		return (system.m_isFirstStart);
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
 			float dt = clock.restart().asSeconds() * s_timeScale;
			// 레이어 추가 요청 처리
			m_layerArray->WorkingInsertLayers();

			// 이벤트 루프
			m_window->Event(&eventQueue);

			// Layer 이벤트 전송
			for (auto& event : eventQueue)
			{
				switch (event.get().type)
				{
					// 일시 정지
					case sf::Event::KeyPressed:
					{
						static bool prevPauseFlag = true;
						switch (event.get().key.code)
						{
							case sf::Keyboard::Escape:
								prevPauseFlag = (prevPauseFlag) ? false : true;
								this->SetPause(prevPauseFlag);
								break;
							case sf::Keyboard::Return:
							{
								if (m_isFirstStart)
									m_isFirstStart = false;
								else
								{
									Layer* target = System::FindLayer("Player");
									Player* p = dynamic_cast<Player*>(target);
									if (p != nullptr)
									{
										if (!p->IsAlive())
											this->SetReset(true);
									}
								}
							} break;
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

			// Layer 업데이트
			if (!m_isPause)
			{
				for (auto layer : (*m_layerArray))
				{
					layer->OnUpdate(dt);
				}
			}

			// 삭제 요청된 레이어 정리
			m_layerArray->WorkingGarbage();

			// 충돌 체크
			auto& colManager = ColliderManager::GetInstance();
			for (auto collider1 : colManager)
			{
				for (auto collider2 : colManager)
				{
					(*collider1)->IsCollided(**collider2);
				}
			}

			// 모든 오브젝트 그리기
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

	void System::Reset()
	{
		if (!m_isReset)
			return;

		s_timeScale = 1.0f;
		m_isPlaying = true;
		m_isPause = false;
		m_isReset = false;
		m_isFirstStart = true;
		this->ReleaseLayerArray();
		this->CreateLayerArray();
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
		, m_isPlaying(true)
		, m_isPause(false)
		, m_isReset(false)
		, m_isFirstStart(true)
	{
		this->CreateLayerArray();
	}

	System::~System()
	{
		ReleaseWindow();
		ReleaseLayerArray();
	}

	void System::ReleaseWindow()
	{
		if (m_window != nullptr)
		{
			m_window->Release();
			delete m_window;
			m_window = nullptr;
		}
	}

	void System::CreateLayerArray()
	{
		if (m_layerArray != nullptr)
			return;
		
		m_layerArray = new LayerArray();
	}

	void System::ReleaseLayerArray()
	{
		if (m_layerArray != nullptr)
		{
			delete m_layerArray;
			m_layerArray = nullptr;
		}
	}

} // namespace fz