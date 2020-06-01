#pragma once
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
namespace dae
{
	class Minigin
	{
	public:
		Minigin();
		~Minigin();

		void Start();
		void ForceEnd();

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		bool m_IsQuit = false;

		//decided to leave these as singletons
		GameState& m_GameState; //waste of time and code bc singleton and everything in it is a singleton apart from DeltaTime
		SceneManager& m_SceneManager;
		Renderer& m_Renderer;
		ResourceManager& m_ResourceManager;
		GlobalInput& m_GlobalInput;
		GlobalMemoryPools& m_GlobalMemoryPools;
		//the above wastes extra space bc they're singletons anyway

		//functions
		void Initialize();
		void LoadGame();
		void Cleanup();

		void AddFPSScene() const;
		void InputTest(TextObject* pTo);
		void ScaleTest(Vector2& scale);
		GameObject* ParentChildTest();
	};
}