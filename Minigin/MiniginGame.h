#pragma once
#include "WindowInfo.h" //allowed to be included
struct SDL_Window;

class GameState;
class SceneManager;
class Renderer;
class ResourceManager;
class GlobalInput;
class GlobalMemoryPools;
class TextObject;
struct Vector2;
class GameObject;
enum class Key;
class b2World; //box2d
namespace dae
{
	class MiniginGame
	{
	public:
		MiniginGame(const char* pTitle = "Minigin", int w = 640, int h = 480, int msPF = 16);
		virtual ~MiniginGame();

		void Start();
		void ForceQuit();

	protected:
		bool m_IsQuit = false;

		//decided to leave these as singletons
		GameState& m_GameState; //waste of time and code bc singleton and everything in it is a singleton apart from DeltaTime
		SceneManager& m_SceneManager;
		Renderer& m_Renderer;
		ResourceManager& m_ResourceManager;
		GlobalInput& m_GlobalInput;
		GlobalMemoryPools& m_GlobalMemoryPools;
		WindowInfo m_WindowInfo;
		//the above wastes extra space bc they're singletons anyway

		//override me! (Don't forget to set ResourceManager's DataPath)
		virtual void LoadGame();
		//override me for extra functionality in the main update loop (debugging purposes)
		virtual void Update() {};
		//override me for extra functionality in the main update loop (debugging purposes)
		virtual void Render() {};

		void AddFPSScene(float x = 0, float y = 480) const;
		void SetForceQuitKey(Key key);

	private:
		Key m_QuitKey;
		SDL_Window* m_pWindow = nullptr;

		void InitializeSDL();
		void Initialize();
		void Cleanup();
	};
}