#include "wall.h"
#include "game.h"
#include "world.h"

#include "tank.h"

pGameObjectState Wall::Serialize() {
	return new WallState(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y
	);
}

bool Wall::Deserialize(pGameObjectState game_object_state) {
	if (!static_cast<pWallState>(game_object_state)) {
		return false;
	}

	pWallState state = static_cast<pWallState>(game_object_state);
	position_x = state->position_x;
	position_y = state->position_y;
	velocity_x = state->velocity_x;
	velocity_y = state->velocity_y;

	return true;
}

void Wall::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

}

void Wall::Unload() {

}

void Wall::Update(float elapsed) {

}

void Wall::Render(sf::RenderWindow& window) {

}

void Wall::OnCollisionEnter(pGameObject other) {

}

void Wall::OnCollisionExit(pGameObject other) {

}
