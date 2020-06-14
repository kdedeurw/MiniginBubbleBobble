#pragma once
#include "Component.h"
#include "Subject.h"
#include "Types.h"

enum class Event;
class PhysicsComponent;
class ItemPickupContactListener;
class ItemPickup : public Component
{
public:
	ItemPickup();
	~ItemPickup();

	virtual void Initialize() override;
	virtual void Render() const override;
	virtual void Update() override;

	void SetScore(ItemType type);
	void NotifySubject();

private:
	int m_Value;
	Subject& m_Subject;
	Event m_PickupEvent;
	PhysicsComponent* m_pPhysics;
	ItemPickupContactListener* m_pContactListener;
};
