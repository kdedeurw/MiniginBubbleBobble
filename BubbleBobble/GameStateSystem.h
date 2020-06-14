#pragma once
#include "Observer.h"
#include "SingletonRef.h"
class GameStateSystem final : public Observer, public SingletonRef<GameStateSystem>
{
public:
	~GameStateSystem() = default;

	void Reset();

	void Render() const;

	void OnNotify(GameObject* pGameObject, int event) override;

private:
	friend class GameStateSystem& SingletonRef<GameStateSystem>::GetInstance();
	GameStateSystem() = default;

	int m_Lives[2]{};
	int m_Scores[2]{};
	const int m_MaxLives = 4;

};