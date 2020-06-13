#include "MiniginPCH.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "GlobalInput.h"
#include "GameObject.h"
#include "GameState.h"
#include "RigidBody.h"
#include "PhysicsComponent.h"

Player::Player()
	: m_pSprites{}
    , m_State{}
	, m_Velocity{}
	, spawnTest{}
	, m_pCollision{ RigidBody{} }
	, m_Speed{ 100.f }
	, m_JumpForce{ 200.f }
{}

Player::~Player()
{
	m_pSprites = nullptr;
}

void Player::Initialize()
{
	m_pCollision.CreateBox(Vector2{ m_pGameObject->GetTransform().GetPosition() }, 5.f, Vector2{ 16.f, 16.f }, RigidBody::Type::Dynamic);
}

void Player::Render() const
{
	m_pCollision.DrawDebug();
}

void Player::Update()
{
	KeyboardMouseListener& listener = GlobalInput::GetInstance().KeyboardMouseListener;

	Vector2& pos = m_pGameObject->GetTransform().GetPosition();

	GameState& gs = GameState::GetInstance();

	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;

	//TODO: isGrounded check, return

	if (listener.IsPressed(Key::ArrowLeft))
		m_Velocity.x = -m_Speed;
	else if (listener.IsPressed(Key::ArrowRight))
		m_Velocity.x = m_Speed;

	if (listener.IsPressed(Key::ArrowUp))
		m_Velocity.y = m_JumpForce;

	//TODO: going down platforms

	//TODO: shooting bubbles

	//TODO: checking enemy collision/death

	//pos += m_Velocity * gs.DeltaTime;
	//m_pCollision.SetLinearVelocity(m_Velocity);
	m_pCollision.ApplyLinearImpulse(m_Velocity);

	//pos.y -= 9.81f * gs.DeltaTime;

	pos = m_pCollision.GetPosition();

	if (spawnTest < 5.f)
	{
		spawnTest += gs.DeltaTime;
		m_State = States::Spawn;
	}

	UpdateState();

	m_pSprites->SetStateMultiplier((int)m_State);
}

void Player::SetSprites(SpriteComponent* pComp)
{
	m_pSprites = pComp;
}

void Player::UpdateState()
{
	if (spawnTest >= 5.f)
	{
		m_State = States::Idle;
		m_pSprites->GetSourceRect().y = (int)States::Spawn * 18.f;
	}

	if (m_Velocity.x != 0.f)
		m_State = States::Walk;
	else if (m_Velocity.y > 0.f)
		m_State = States::Jump;

	//if (!m_IsGrounded)
	//	m_State = States::Fall;

	//player : 18h 18w
	//bubble : 18h 18w
	//spawnbubble: 34h 30w

	switch (m_State)
	{
	case Player::States::Idle:
		m_pSprites->SetMaxFrames(2);
		m_pSprites->SetSizes(Vector2{ 18.f, 18.f });
		break;
	case Player::States::Walk:
		m_pSprites->SetMaxFrames(4);
		m_pSprites->SetSizes(Vector2{ 18.f, 18.f });
		break;
	case Player::States::Jump:
		m_pSprites->SetMaxFrames(2);
		m_pSprites->SetSizes(Vector2{ 18.f, 18.f });
		break;
	case Player::States::Fall:
		m_pSprites->SetMaxFrames(2);
		m_pSprites->SetSizes(Vector2{ 18.f, 18.f });
		break;
	case Player::States::Shoot:
		m_pSprites->SetMaxFrames(1);
		m_pSprites->SetSizes(Vector2{ 18.f, 18.f });
		break;
	case Player::States::Die:
		m_pSprites->Reset();
		m_pSprites->SetMaxFrames(6);
		m_pSprites->SetSizes(Vector2{ 18.f, 18.f });
		break;
	case Player::States::Bubble:
		//m_pSprites->Reset();
		m_pSprites->SetMaxFrames(6);
		m_pSprites->SetSizes(Vector2{ 18.f, 18.f });
		break;
	case Player::States::Spawn:
		//m_pSprites->Reset();
		m_pSprites->SetMaxFrames(2);
		m_pSprites->SetSizes(Vector2{ 30.f, 34.f });
		break;
	}
}