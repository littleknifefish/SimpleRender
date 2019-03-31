#include "GameObject.h"

void GameObject::AddComponent(Component* com) {
  com->Go = this;
  m_Comp.push_back(com);
}

vector<Component*>& GameObject::GetComponents() {
  return m_Comp;
}

int GameObject::RemoveComponent(Component* com) {
  std::vector<Component*>::iterator it = m_Comp.begin();
  while (it != m_Comp.end())
  {
    if (*it == com)
    {
      m_Comp.erase(it);
      return 0;
    }
    it++;
  }
  return 1;
}