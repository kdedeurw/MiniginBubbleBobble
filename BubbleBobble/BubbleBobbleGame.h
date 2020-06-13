#pragma once
#include "MiniginGame.h"

class TextObject;
class GameObject;
struct Vector2;
struct Vector4;
class BubbleBobbleGame final : public dae::MiniginGame
{
public:
	BubbleBobbleGame(const char* pTitle = "BubbleBobble", int w = 640, int h = 480, int msPF = 16);
	~BubbleBobbleGame();

private:
	void LoadGame() override;
	void Update() override;

	GameObject* pBox;

	//unused test content
	void Archive();
	void InputTest(TextObject* pTo);
	void ScaleTest(Vector2& scale);
	GameObject* GetParentChildTest();
	void ParentChildTest(GameObject* pParent);
	void DestRectTest(Vector4& dest);
};