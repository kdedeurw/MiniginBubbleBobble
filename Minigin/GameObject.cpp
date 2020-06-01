#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components.h"

GameObject::GameObject(Transform& transform)
	: SceneObject{ transform }
	, m_pComponents{}
	, m_pChildren{}
	, m_pParent{}
	, m_pDebug{}
{}

GameObject::~GameObject()
{
	m_pParent = nullptr;
	//delete all children
	for (GameObject* pChild : m_pChildren)
		delete pChild;
	m_pChildren.clear();
	//delete all components
	for (Component* pComponent : m_pComponents)
		delete pComponent;
	m_pComponents.clear();

	delete m_pDebug;
	m_pDebug = nullptr;
}

void GameObject::Initialize()
{}

void GameObject::Update()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->Update();
	}

	for (GameObject* pObject : m_pChildren)
	{
		pObject->Update();
	}
}

void GameObject::Render() const
{
	if (m_pParent)
	{
		for (Component* pComponent : m_pComponents)
		{
			pComponent->Render(&m_pParent->GetTransform());
		}
	}
	else
	{
		for (Component* pComponent : m_pComponents)
		{
			pComponent->Render();
		}
	}

	for (GameObject* pObject : m_pChildren)
	{
		pObject->Render();
	}

	DrawDebug();
}

void GameObject::AddComponent(Component* pComponent)
{
	if (std::find(m_pComponents.begin(), m_pComponents.end(), pComponent) == m_pComponents.end())
	{
		m_pComponents.push_back(pComponent);
		pComponent->m_pGameObject = this;
	}
}

void GameObject::RemoveComponent(Component* pComponent)
{
	const std::vector<Component*>::iterator it = std::find(m_pComponents.begin(), m_pComponents.end(), pComponent);
	if (it != m_pComponents.end())
		m_pComponents.erase(it);
}

void GameObject::AddChildObject(GameObject* pChild)
{
	if (std::find(m_pChildren.begin(), m_pChildren.end(), pChild) == m_pChildren.end())
	{
		m_pChildren.push_back(pChild);
		pChild->m_pParent = this;
	}
}

void GameObject::RemoveChildObject(GameObject* pChild)
{
	const std::vector<GameObject*>::iterator it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);
	if (it != m_pChildren.end())
	{
		m_pChildren.erase(it);
		pChild->m_pParent = nullptr;
	}
}

void GameObject::DrawDebug() const
{
	Vector2 pos{ m_Transform.GetPosition() };
	if (m_pParent)
	{
		const float parentRot = m_pParent->GetTransform().GetRotation() * Math::ToRadians;
		const float sinCalc{ sinf(parentRot) };
		const float cosCalc{ cosf(parentRot) };
		const float newX{ pos.x * cosCalc - pos.y * sinCalc };//store new X, but don't overwrite original yet
		pos.y = pos.y * cosCalc + pos.x * sinCalc;
		pos.x = newX;
		pos += m_pParent->GetTransform().GetPosition();

		//scale += pParentTrans->GetScale(); //inherit scale from parent?
	}
	Renderer::GetInstance().DrawDebug(pos, m_Id);
}