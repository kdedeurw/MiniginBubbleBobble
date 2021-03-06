#pragma once
#include "PhysicsComponent.h"
#include "Vectors.h"

class b2Body;
class RigidBodyComponent : public PhysicsComponent
{
public:
	enum class Type
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

	void CreateBox(const Vector2& pos, float m, const Vector2& dim, Type type = Type::Static);
	void CreatePolygon(const Vector2& pos, float m, const std::vector<Vector2>& points, Type type = Type::Static);
	void CreateCircle(const Vector2& pos, float m, float r, Type type = Type::Static);
	void SetType(Type type);

	//only applies force in center
	void ApplyForce(const Vector2& force);
	void ApplyTorque(float t);
	void SetMass(float m);
	void SetLinearVelocity(const Vector2& vel);
	void SetAngularVelocity(float w);

private:
	b2Body* m_pBody;
	Vector2 m_Dim;

	void Create(const Vector2& pos, Type type);

	void DrawDebug() const;
};