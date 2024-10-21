#include "ImguiManager.h"
//imgui
#include <windows.h>
#include <gl/GL.h>
#include <tchar.h>

WNDPROC	g_OriginalWndProc;

static void Hook_Renderer_CreateWindow(ImGuiViewport* viewport)
{
	assert(viewport->RendererUserData == NULL);

	// SFML의 창(window) 데이터를 저장하는 구조체
	sf::Window* window = new sf::Window(sf::VideoMode(viewport->Size.x, viewport->Size.y), "ImGui Viewport", sf::Style::Default, sf::ContextSettings(32));
	window->setVerticalSyncEnabled(true);

	viewport->RendererUserData = window;
	viewport->PlatformHandle = window->getSystemHandle(); // 플랫폼 핸들을 SFML 창의 네이티브 핸들로 설정
}

static void Hook_Renderer_DestroyWindow(ImGuiViewport* viewport)
{
	if (viewport->RendererUserData != NULL)
	{
		// RendererUserData는 SFML의 창(window) 객체
		sf::Window* window = (sf::Window*)viewport->RendererUserData;
		delete window; // SFML 창 삭제
		viewport->RendererUserData = NULL;
	}
}

static void Hook_Platform_RenderWindow(ImGuiViewport* viewport, void*)
{
	// SFML의 창에서 OpenGL 컨텍스트를 활성화
	if (sf::Window* window = (sf::Window*)viewport->RendererUserData)
	{
		window->setActive(true); // OpenGL 컨텍스트를 활성화
	}
}

static void Hook_Renderer_SwapBuffers(ImGuiViewport* viewport, void*)
{
	if (sf::Window* window = (sf::Window*)viewport->RendererUserData)
	{
		window->display(); // SFML 창의 버퍼를 스왑
	}
}

LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN && wParam == VK_ESCAPE) {
		PostQuitMessage(0);
		return 0; 
	}

	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam)) {
		return 1; 
	}

	return CallWindowProc(g_OriginalWndProc, hwnd, uMsg, wParam, lParam);
}

namespace fz {

	bool ImGuiManager::s_enableOverviewDockspace = true;
	const sf::Window* ImGuiManager::s_currWindow = nullptr;

	void ImGuiManager::Initialize(const sf::Window& window)
	{
		s_currWindow = &window;
		auto sysHwnd = window.getSystemHandle();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_InitForOpenGL(sysHwnd);
		ImGui_ImplOpenGL3_Init();

		// Win32+GL needs specific hooks for viewport, as there are specific things needed to tie Win32 and GL api.
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
			IM_ASSERT(platform_io.Renderer_CreateWindow == NULL);
			IM_ASSERT(platform_io.Renderer_DestroyWindow == NULL);
			IM_ASSERT(platform_io.Renderer_SwapBuffers == NULL);
			IM_ASSERT(platform_io.Platform_RenderWindow == NULL);
			platform_io.Renderer_CreateWindow = Hook_Renderer_CreateWindow;
			platform_io.Renderer_DestroyWindow = Hook_Renderer_DestroyWindow;
			platform_io.Renderer_SwapBuffers = Hook_Renderer_SwapBuffers;
			platform_io.Platform_RenderWindow = Hook_Platform_RenderWindow;
		}

		// Input Bind
		// 기존 WndProc을 저장
		g_OriginalWndProc = (WNDPROC)GetWindowLongPtr(sysHwnd, GWLP_WNDPROC);
		// 새로운 WndProc을 설정
		SetWindowLongPtr(sysHwnd, GWLP_WNDPROC, (LONG_PTR)CustomWndProc);
	}

	void ImGuiManager::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		//if (s_bEnabledImplot)
		//	ImPlot::DestroyContext();
	}

	void ImGuiManager::Begin()
	{
		if (s_currWindow && s_currWindow->isOpen())
		{
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			if (s_enableOverviewDockspace)
			{
				ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			}
		}
	}

	void ImGuiManager::End()
	{
		auto sysHwnd = s_currWindow->getSystemHandle();
		HDC hdc = GetDC(sysHwnd);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ReleaseDockspace();
	}

	void ImGuiManager::ShowDemo()
	{
		bool show_demo_window = true;
		bool show_another_window = true;
		// ImGui::ShowDemoWindow(&show_demo_window);
		static float f = 0.0f;
		static int counter = 0;

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	void ImGuiManager::ReleaseDockspace()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			// 현재 Win32 컨텍스트를 저장합니다.
			HWND backup_current_context = GetActiveWindow();
			// ImGui 플랫폼 창 업데이트 및 렌더링
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			// 이전 컨텍스트로 복구합니다.
			SetForegroundWindow(backup_current_context);
		}
	}

} // namespace fz
