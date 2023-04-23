#include "bullet.h"
#include "game.h"
#include "world.h"

void Bullet::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);
}

void Bullet::Unload() {
}

pGameObjectState Bullet::Serialize() {
	float position_x;
	float position_y;
	GetPosition(position_x, position_y);

	float velocity_x;
	float velocity_y;
	GetVelocity(velocity_x, velocity_y);

	return new BulletState(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y
	);
}

void Bullet::Deserialize(pGameObjectState game_object_state) {
	auto bullet_state = static_cast<pBulletState>(game_object_state);
	SetPosition(bullet_state->position_x, bullet_state->position_y);
	SetVelocity(bullet_state->velocity_x, bullet_state->velocity_y);
}

void Bullet::ExecuteCommand(uint32_t tick) {
}

void Bullet::Update(float elapsed) {
}

void Bullet::Render(sf::RenderWindow& window) {
}

void Bullet::OnCollisionEnter(pGameObject other) {
}

void Bullet::OnCollisionExit(pGameObject other) {
}
