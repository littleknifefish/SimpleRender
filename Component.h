#pragma once
#include "Math/Vector4.h"
#include "GameObject.h"

class GameObject;
class Component
{
public:
  Component();
  ~Component();

  GameObject* Go;

  virtual void Update(float deltaTime);
private:

};

Component::Component()
{
}

Component::~Component()
{
}