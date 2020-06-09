//Base includes
#include "MiniginPCH.h"
#include "MiniginGame.h"
#include <chrono>
#include <thread>
#include "Transform.h"
#include "GlobalInput.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"

//Project includes
#include "Timer.h"
#include "Components.h"
#include "GameState.h"

using namespace std;
using namespace std::chrono;

dae::MiniginGame::MiniginGame(const char* pTitle, int w, int h, int msPF)
	: m_GameState{ GameState::GetInstance() }
	, m_SceneManager{ SceneManager::GetInstance() }
	, m_Renderer{ Renderer::GetInstance() }
	, m_ResourceManager{ ResourceManager::GetInstance() }
	, m_GlobalInput{ GlobalInput::GetInstance() }
	, m_GlobalMemoryPools{ GlobalMemoryPools::GetInstance() }
	, m_WindowInfo{ pTitle, w, h, msPF }
{
	//TODO: re-fix
	m_GameState.WindowWidth = w;
	m_GameState.WindowHeight = h;
}

dae::MiniginGame::~MiniginGame()
{}

void dae::MiniginGame::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		m_WindowInfo.pTitle,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_WindowInfo.Width,
		m_WindowInfo.Height,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	m_Renderer.Init(m_pWindow);
}

/**
 * Code constructing the scene world starts here
 */
void dae::MiniginGame::LoadGame()
{
	// tell the resource manager where he can find the game data
	m_ResourceManager.Init("../Data/");

	Scene& scene = m_SceneManager.CreateScene("Demo");

	GameObject* pGo = m_GlobalMemoryPools.CreateGameObject();
	Texture2DComponent* pTex = m_GlobalMemoryPools.CreateComponent<Texture2DComponent>();
	pTex->SetTexture("background.jpg");
	pGo->AddComponent(pTex);
	pGo->GetTransform().SetPosition(320, 240);
	scene.AddObject(pGo);

	pGo = m_GlobalMemoryPools.CreateGameObject();
	pTex = m_GlobalMemoryPools.CreateComponent<Texture2DComponent>();
	pGo->AddComponent(pTex);
	pTex->SetTexture("logo.png");
	pGo->GetTransform().SetPosition(320, 280);
	scene.AddObject(pGo);

	Font* pFont = m_ResourceManager.LoadFont("Lingua.otf", 36);
	TextObject* pTo = m_GlobalMemoryPools.CreateTextObject("Programming 4 Assignment", pFont);
	pTo->GetTransform().SetPosition(80, 440);
	scene.AddObject(pTo);

	AddFPSScene();
}

void dae::MiniginGame::Cleanup()
{
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void dae::MiniginGame::Start()
{
	Initialize();
	LoadGame();

	{
		float lag{};
		Timer<high_resolution_clock> timer{}; //start point automatically resets to Time::Now();
		while (!m_IsQuit)
		{
			//forced sleeptime
			//TODO: fix this goddamn time issue
			this_thread::sleep_for(16ms);
			//process all input
			m_GlobalInput.KeyboardMouseListener.ProcessInput();
			m_GlobalInput.ControllerListener.ProcessInput();
			m_IsQuit = m_GlobalInput.KeyboardMouseListener.IsQuit();
			//force quit
			m_IsQuit = m_GlobalInput.KeyboardMouseListener.IsPressed(Key::Escape);
			//get Time::Now()
			const auto currentTime = high_resolution_clock::now();
			//set global deltatime
			m_GameState.DeltaTime = timer.GetElapsedTime<float, milliseconds>();

			lag += m_GameState.DeltaTime;
			while(lag >= m_WindowInfo.MsPerFrame)
			{
				m_GameState.DeltaTime = m_WindowInfo.MsPerFrame / 1000.f;
				m_SceneManager.Update();
				lag -= m_WindowInfo.MsPerFrame;
			}
			m_Renderer.Render();
			timer.ResetStartTime();
			
			const auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(m_WindowInfo.MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::MiniginGame::ForceEnd()
{
	m_IsQuit = true;
}

void dae::MiniginGame::AddFPSScene(float x, float y) const
{
	Scene& scene = m_SceneManager.CreateScene("FPS");
	GameObject* pGo = m_GlobalMemoryPools.CreateGameObject();
	FPSComponent* pFPS = m_GlobalMemoryPools.CreateComponent<FPSComponent>();
	pGo->AddComponent(pFPS);
	pGo->GetTransform().SetPosition(x, y);
	scene.AddObject(pGo);
}