#include "wall.h"
#include "game.h"
#include "world.h"

#include "tank.h"

void Wall::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);
}

void Wall::Unload() {
}

Record* Wall::Serialize() {
	float position_x;
	float position_y;
	GetPosition(position_x, position_y);

	float velocity_x;
	float velocity_y;
	GetVelocity(velocity_x, velocity_y);

	return new WallRecord(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y
	);
}

void Wall::Deserialize(Record* record) {
	auto wall_record = static_cast<WallRecord*>(record);
	SetPosition(wall_record->position_x, wall_record->position_y);
	SetVelocity(wall_record->velocity_x, wall_record->velocity_y);
}

void Wall::HandleInput(uint32_t tick) {
}

void Wall::ExecuteCommand(Command* command) {
}

void Wall::Update(float elapsed) {
}

void Wall::Render(sf::RenderWindow& window) {
}

void Wall::OnCollisionEnter(GameObject* other) {
}

void Wall::OnCollisionExit(GameObject* other) {
}
