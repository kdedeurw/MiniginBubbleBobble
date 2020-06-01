#pragma once
#include "SingletonRef.h"
#include "Timer.h"
#include "GlobalInput.h"
#include "GlobalMemoryPools.h"

class Scene;
class FPS;
class GameState final : public SingletonRef<GameState> //placeholder name
{
public:
	~GameState() = default;

	GameState(const GameState& other) = delete;
	GameState(GameState&& other) = delete;
	GameState& operator=(const GameState& other) = delete;
	GameState& operator=(GameState&& other) = delete;

	float DeltaTime{};
	Scene* pCurrentScene{};
	FPS* pFPS{};
	Timer<high_resolution_clock> Timer{};
	GlobalInput& GlobalInput{ GlobalInput::GetInstance() };
	GlobalMemoryPools& pGlobalMemoryPools{ GlobalMemoryPools::GetInstance() };

private:
	friend static GameState& SingletonRef<GameState>::GetInstance();
	GameState() = default;
};