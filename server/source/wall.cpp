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

pGameObjectState Wall::Serialize() {
	float position_x;
	float position_y;
	GetPosition(position_x, position_y);

	float velocity_x;
	float velocity_y;
	GetVelocity(velocity_x, velocity_y);

	return new WallState(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y
	);
}

void Wall::Deserialize(pGameObjectState game_object_state) {
	auto wall_state = static_cast<pWallState>(game_object_state);
	SetPosition(wall_state->position_x, wall_state->position_y);
	SetVelocity(wall_state->velocity_x, wall_state->velocity_y);
}

void Wall::ExecuteCommand(pCommand command) {
}

void Wall::Update(float elapsed) {
}

void Wall::Render(sf::RenderWindow& window) {
}

void Wall::OnCollisionEnter(pGameObject other) {
}

void Wall::OnCollisionExit(pGameObject other) {
}
