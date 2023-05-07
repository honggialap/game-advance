#include "bullet.h"
#include "game.h"
#include "world.h"

void Bullet::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);
}

void Bullet::Unload() {
}

Record* Bullet::Serialize() {
	float position_x;
	float position_y;
	GetPosition(position_x, position_y);

	float velocity_x;
	float velocity_y;
	GetVelocity(velocity_x, velocity_y);

	return new BulletRecord(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y
	);
}

void Bullet::Deserialize(Record* record) {
	auto bullet_record = static_cast<BulletRecord*>(record);
	SetPosition(bullet_record->position_x, bullet_record->position_y);
	SetVelocity(bullet_record->velocity_x, bullet_record->velocity_y);
}

void Bullet::HandleInput(uint32_t tick) {
}

void Bullet::ExecuteCommand(Command* command) {
}

void Bullet::Update(float elapsed) {
}

void Bullet::Render(sf::RenderWindow& window) {
}

void Bullet::OnCollisionEnter(GameObject* other) {
}

void Bullet::OnCollisionExit(GameObject* other) {
}