//Base includes
#include "MiniginPCH.h"
#include "Minigin.h"
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

dae::Minigin::Minigin()
	: m_GameState{ GameState::GetInstance() }
	, m_SceneManager{ SceneManager::GetInstance() }
	, m_Renderer{ Renderer::GetInstance() }
	, m_ResourceManager{ ResourceManager::GetInstance() }
	, m_GlobalInput{ GlobalInput::GetInstance() }
	, m_GlobalMemoryPools{ GlobalMemoryPools::GetInstance() }
{}

dae::Minigin::~Minigin()
{}

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	m_Renderer.Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame()
{
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
	pGo->GetTransform().SetPosition(320, 200);
	scene.AddObject(pGo);

	Font* pFont = m_ResourceManager.LoadFont("Lingua.otf", 36);
	TextObject* pTo = m_GlobalMemoryPools.CreateTextObject("Programming 4 Assignment", pFont);
	pTo->GetTransform().SetPosition(80, 20);
	scene.AddObject(pTo);
}

void dae::Minigin::Cleanup()
{
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Start()
{
	Initialize();

	// tell the resource manager where he can find the game data
	m_ResourceManager.Init("../Data/");

	LoadGame();
	AddFPSScene();
	GameObject* pParent = ParentChildTest();

	Scene& scene = m_SceneManager.CreateScene("InputTestScene");
	TextObject* pInputTo = m_GlobalMemoryPools.CreateTextObject("", m_ResourceManager.LoadFont("Lingua.otf", 36));
	pInputTo->GetTransform().SetPosition(320, 280);
	pInputTo->SetText("No input");
	scene.AddObject(pInputTo);
	TextObject* pTo = m_GlobalMemoryPools.CreateTextObject("", m_ResourceManager.LoadFont("Lingua.otf", 36));
	pTo->SetText("MouseButtons to change width");
	pTo->GetTransform().SetPosition(0.f, 350.f);
	scene.AddObject(pTo);
	pTo = m_GlobalMemoryPools.CreateTextObject("", m_ResourceManager.LoadFont("Lingua.otf", 36));
	pTo->SetText("Scrollwheel to change height");
	pTo->GetTransform().SetPosition(0.f, 400.f);
	scene.AddObject(pTo);
	pTo = m_GlobalMemoryPools.CreateTextObject("", m_ResourceManager.LoadFont("Lingua.otf", 36));
	pTo->SetText("WASD to move");
	pTo->GetTransform().SetPosition(0.f, 450.f);
	scene.AddObject(pTo);
	GameObject* pGo = m_GlobalMemoryPools.CreateGameObject();
	Texture2DComponent* pTex = m_GlobalMemoryPools.CreateComponent<Texture2DComponent>();
	pTex->SetTexture("logo.png");
	pGo->AddComponent(pTex);
	scene.AddObject(pGo);

	Vector4& dest{ pTex->GetDestRect() };
	//Vector4& src{ pTex->GetSourceRect() };
	Vector2& scale{ pGo->GetTransform().GetScale() };
	float& rot{ pGo->GetTransform().GetRotation() };

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

			InputTest(pInputTo);

			pGo->GetTransform().SetPosition(m_GlobalInput.KeyboardMouseListener.GetMousePos());
			pGo->GetTransform().SetScale(scale);
			pGo->GetTransform().SetRotation(rot);
			Texture2DComponent* pTest = pGo->GetComponent<Texture2DComponent>();

			//DestRect test
			{
				if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::A))
					dest.x -= 1.f;
				else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::D))
					dest.x += 1.f;
				if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::W))
					dest.y -= 1.f;
				else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::S))
					dest.y += 1.f;

				if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::ArrowLeft))
					dest.z -= 1.f;
				else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::ArrowRight))
					dest.z += 1.f;
				if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::ArrowUp))
					dest.w += 1.f;
				else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::ArrowDown))
					dest.w -= 1.f;
			}

			ScaleTest(scale);

			rot += 1.f;

			//pTest->SetSourceRect(src);
			pTest->SetDestRect(dest);

			pParent->GetTransform().SetPosition(m_GlobalInput.KeyboardMouseListener.GetMousePos() + Vector2{ 100.f, 0.f });
			pParent->GetTransform().Rotate(1.f);
			pParent->GetChildren().front()->GetTransform().Rotate(2.f);
			//pParent->GetChildren().front()->GetChildren().front()->GetTransform().Rotate(2.f);

			lag += m_GameState.DeltaTime;
			while(lag >= MsPerFrame)
			{
				m_GameState.DeltaTime = MsPerFrame / 1000.f;
				m_SceneManager.Update();
				lag -= MsPerFrame;
			}
			m_Renderer.Render();
			timer.ResetStartTime();
			
			const auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::Minigin::ForceEnd()
{
	m_IsQuit = true;
}

void dae::Minigin::AddFPSScene() const
{
	Scene& scene = m_SceneManager.CreateScene("FPS");
	GameObject* pGo = m_GlobalMemoryPools.CreateGameObject();
	FPSComponent* pFPS = m_GlobalMemoryPools.CreateComponent<FPSComponent>();
	pGo->AddComponent(pFPS);
	scene.AddObject(pGo);
}

void dae::Minigin::InputTest(TextObject* pTo)
{
	pTo->SetText("No input");
	if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::W))
	{
		pTo->SetText("W");
		if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::A))
			pTo->SetText("W + A");
		else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::D))
			pTo->SetText("W + D");
		pTo->GetTransform().SetPosition(pTo->GetTransform().GetPosition() - Vector3{ 0.f, 1.f });
	}
	else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::S))
	{
		pTo->SetText("S");
		if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::A))
			pTo->SetText("S + A");
		else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::D))
			pTo->SetText("S + D");
		pTo->GetTransform().SetPosition(pTo->GetTransform().GetPosition() + Vector3{ 0.f, 1.f });
	}
	if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::A))
	{
		pTo->SetText("A");
		if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::W))
			pTo->SetText("W + A");
		else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::S))
			pTo->SetText("S + A");
		pTo->GetTransform().SetPosition(pTo->GetTransform().GetPosition() - Vector3{ 1.f, 0.f });
	}
	else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::D))
	{
		pTo->SetText("D");
		if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::W))
			pTo->SetText("W + D");
		else if (m_GlobalInput.KeyboardMouseListener.IsPressed(Key::S))
			pTo->SetText("S + D");
		pTo->GetTransform().SetPosition(pTo->GetTransform().GetPosition() + Vector3{ 1.f, 0.f });
	}
}

void dae::Minigin::ScaleTest(Vector2& scale)
{
	if (m_GlobalInput.KeyboardMouseListener.IsScrollWheelMove(ScrollWheel::Up))
		scale.x += 0.1f;
	else if (m_GlobalInput.KeyboardMouseListener.IsScrollWheelMove(ScrollWheel::Down))
		scale.x -= 0.1f;

	if (m_GlobalInput.KeyboardMouseListener.IsMouseButtonPressed(Mouse::LMB))
		scale.y += 0.1f;
	else if (m_GlobalInput.KeyboardMouseListener.IsMouseButtonPressed(Mouse::RMB))
		scale.y -= 0.1f;
}

GameObject* dae::Minigin::ParentChildTest()
{
	Scene& scene = m_SceneManager.CreateScene("ParentChild");
	GameObject* pParent = m_GlobalMemoryPools.CreateGameObject();
	Texture2DComponent* pTex = m_GlobalMemoryPools.CreateComponent<Texture2DComponent>();
	pTex->SetTexture("logo.png");
	pParent->AddComponent(pTex);
	pParent->GetTransform().SetPosition(100.f, 100.f);
	GameObject* pChild = m_GlobalMemoryPools.CreateGameObject();
	pTex = m_GlobalMemoryPools.CreateComponent<Texture2DComponent>();
	pTex->SetTexture("logo.png");
	pChild->AddComponent(pTex);
	pChild->GetTransform().SetPosition(100.f, 100.f);
	//GameObject* pPivot = m_GlobalMemoryPools.CreateGameObject();
	//pPivot->AddChildObject(pChild);
	//pParent->AddChildObject(pPivot);
	pParent->AddChildObject(pChild);
	pParent->GetTransform().SetRotation(90.f);
	//pParent->GetTransform().SetScale(1.5f, 0.5f);
	//pChild->GetTransform().SetScale(0.5f, 1.5f);
	pChild->GetTransform().SetRotation(180.f);
	scene.AddObject(pParent);
	return pParent;
}