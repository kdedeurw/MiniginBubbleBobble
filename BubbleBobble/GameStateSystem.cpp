#include "MiniginPCH.h"
#include "GameStateSystem.h"
#include "Events.h"
#include "GameObject.h"
#include "Player.h"

void GameStateSystem::Reset()
{
	m_Lives[0] = m_MaxLives;
	m_Lives[1] = m_MaxLives;
	m_Scores[0] = 0;
	m_Scores[1] = 0;
}

void GameStateSystem::Render() const
{}

void GameStateSystem::OnNotify(GameObject* pGameObject, int event)
{
	const Player::Playables character = pGameObject->GetComponent<Player>()->GetCharacter();
	const bool id{ character != Player::Playables::Bub };
	switch ((Event)event)
	{
	case Event::event_die:
		--m_Lives[id];
		//versus: maita doesn't permanently die
		break;
	case Event::event_item_pickup_Banana:
		m_Scores[id] += 100;
		break;
	case Event::event_item_pickup_Melon:
		m_Scores[id] += 200;
		break;
	case Event::event_item_pickup_GoldenApple:
		m_Scores[id] += 300;
		break;
	case Event::event_item_pickup_Grapes:
		m_Scores[id] += 400;
		break;
	case Event::event_item_pickup_Pineapple:
		m_Scores[id] += 500;
		break;
	case Event::event_item_pickup_Diamond:
		m_Scores[id] += 600;
		break;
	case Event::event_item_pickup_Peach:
		m_Scores[id] += 700;
		break;
	case Event::event_item_pickup_RedDiamond:
		m_Scores[id] += 800;
		break;
	}
}