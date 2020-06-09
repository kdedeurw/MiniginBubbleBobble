#pragma once
#include "Component.h"
#include "Vectors.h"

class RigidBodyComponent : public Component
{
public:
	enum class State
	{
		Static,
		Kinematic,
		Dynamic,
	};

	RigidBodyComponent();
	~RigidBodyComponent();

	virtual void Initialize() override;
	virtual void Render() const override;
	virtual void Update() override;

	void SetStatic();
	void SetKinematic();
	void SetDynamic();

private:
	float m_Mass;
	Vector2 m_Velocity;
};