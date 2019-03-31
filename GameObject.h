#pragma once
#include <vector>
#include "Component.h"

using namespace std;

class Component;
class GameObject
{
public:
  GameObject();
  ~GameObject();


  void AddComponent(Component* com);

  vector<Component*>& GetComponents();

  int RemoveComponent(Component* com);
private:
  vector<Component*> m_Comp;
};

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}