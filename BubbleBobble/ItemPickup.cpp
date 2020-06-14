#include "MiniginPCH.h"
#include "ItemPickup.h"
#include "GameObject.h"
#include "GlobalMemoryPools.h"
#include "Events.h"
#include "PhysicsComponent.h"
#include "GameStateSystem.h"
#include <Box2D.h>
#include "ColliderMasks.h"

bool GetContactData(b2Contact* contact, PhysicsComponent*& item, PhysicsComponent*& player)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    //make sure only one of the fixtures was a sensor
    bool sensorA = fixtureA->IsSensor();
    bool sensorB = fixtureB->IsSensor();
    if (!(sensorA ^ sensorB))
        return false;

    PhysicsComponent* entityA = static_cast<PhysicsComponent*>(fixtureA->GetBody()->GetUserData());
    PhysicsComponent* entityB = static_cast<PhysicsComponent*>(fixtureB->GetBody()->GetUserData());

    if (sensorA) { //fixtureB must be an enemy aircraft
        item = entityA;
        player = entityB;
    }
    else { //fixtureA must be an enemy aircraft
        item = entityB;
        player = entityA;
    }
    return true;
}

//main collision call back function
class ItemPickupContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {
        PhysicsComponent* item;
        PhysicsComponent* player;
        if (GetContactData(contact, item, player))
        {
            item->SetActive(false);
            m_pThis->NotifySubject();
        }
    }

    void EndContact(b2Contact* contact)
    {
        PhysicsComponent* item;
        PhysicsComponent* player;
        if (GetContactData(contact, item, player))
        {
            //do nothing
        }
    }

public:
    void SetThis(ItemPickup* pThis) { m_pThis = pThis; };

private:
    ItemPickup* m_pThis{};
};

ItemPickup::ItemPickup()
	: m_Value{}
    , m_Subject{ *GlobalMemoryPools::GetInstance().CreateSubject(1) }
    , m_PickupEvent{}
    , m_pPhysics{}
    , m_pContactListener{}
{}

ItemPickup::~ItemPickup()
{
    m_Subject.RemoveObserver(&GameStateSystem::GetInstance());
}

void ItemPickup::Initialize()
{
    m_pPhysics = m_pGameObject->GetComponent<PhysicsComponent>();
    if (!m_pPhysics)
        throw std::exception("ItemPickup::Initialize > invalid physicscomponent (no physicscomponent found)");

    m_Subject.AddObserver(&GameStateSystem::GetInstance());

    m_pContactListener = new ItemPickupContactListener{};
    m_pContactListener->SetThis(this);

    m_pPhysics->Getb2World().SetContactListener(m_pContactListener);
}

void ItemPickup::Render() const
{}

void ItemPickup::Update()
{
    //TODO: collision update
    //m_Subject.Notify(m_pGameObject, (int)m_PickupEvent);
    //Handled by contact listener
}

void ItemPickup::SetScore(ItemType type)
{
	switch (type)
	{
    case ItemType::Banana:
        m_Value = 100;
        break;
    case ItemType::Melon:
        m_Value = 200;
        break;
    case ItemType::GoldenApple:
        m_Value = 300;
        break;
    case ItemType::Grapes:
        m_Value = 400;
        break;
    case ItemType::Pineapple:
        m_Value = 500;
        break;
    case ItemType::Diamond:
        m_Value = 600;
        break;
    case ItemType::Peach:
        m_Value = 700;
        break;
    case ItemType::RedDiamond:
        m_Value = 800;
        break;
	}

    m_PickupEvent = (Event)((int)Event::event_item_pickup_Banana + (int)type);
}

void ItemPickup::NotifySubject()
{
    m_Subject.Notify(m_pGameObject, (int)m_PickupEvent);
}
