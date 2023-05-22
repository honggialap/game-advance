#include "game_object.h"

GameObject::GameObject(Game* game, World* world)
	: game(game)
	, world(world) 
{}


GameObject::~GameObject() {
}

void GameObject::SetName(std::string value) {
	name = value; 
}

std::string GameObject::GetName() { 
	return name; 
}

void GameObject::SetId(uint32_t value) { 
	id = value; 
}

uint32_t GameObject::GetId() { 
	return id; 
}

void GameObject::SetType(uint32_t value) { 
	type = value; 
}

uint32_t GameObject::GetType() { 
	return type; 
}

void GameObject::SetLayer(uint32_t value) { 
	layer = value; 
}

uint32_t GameObject::GetLayer() { 
	return layer; 
}

void GameObject::SetActive(bool active) { 
	is_active = active; 
}

bool GameObject::IsActive() { 
	return is_active; 
}

void GameObject::Destroy() { 
	is_destroyed = true; 
}

bool GameObject::IsDestroyed() { 
	return is_destroyed; 
}

void GameObject::SetPosition(float x, float y) { 
	body->SetTransform(b2Vec2(x / PIXEL_PER_METER, y / PIXEL_PER_METER), 0); 
}

void GameObject::GetPosition(float& x, float& y) { 
	x = body->GetPosition().x * PIXEL_PER_METER; y = body->GetPosition().y * PIXEL_PER_METER; 
}

void GameObject::SetVelocity(float vx, float vy) { 
	body->SetLinearVelocity(b2Vec2(vx / PIXEL_PER_METER, vy / PIXEL_PER_METER)); 
}

void GameObject::GetVelocity(float& vx, float& vy) { 
	vx = body->GetPosition().x * PIXEL_PER_METER; vy = body->GetPosition().y * PIXEL_PER_METER; 
}
