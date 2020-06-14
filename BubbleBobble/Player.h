#pragma once
#include "Component.h"
#include "Vectors.h"
//TODO: remove
#include "RigidBody.h"

//Unity-style layout
//component is monobehaviour
//using composition

class SpriteComponent;
class RigidBody;
class Player : public Component
{
public:
	Player();
	~Player();

	virtual void Initialize() override;
	virtual void Render() const override;
	virtual void Update() override;

	void SetSprites(SpriteComponent* pComp);

	enum class States
	{
		Idle,
		Walk,
		Jump,
		Fall,
		Shoot,
		Die,
		Bubble,
		Spawn,
	};
	enum class Playables
	{
		Bub,
		Bob,
		Maita,
	};
	void SetCharacter(Playables character);
	Playables GetCharacter() const;

protected:
	Playables m_Player;
	float m_Speed;
	float m_JumpForce;
	SpriteComponent* m_pSprites;
	States m_State;
	Vector2 m_Velocity; //temp
	RigidBody m_pCollision;

	float spawnTest;

	void UpdateState();

};

