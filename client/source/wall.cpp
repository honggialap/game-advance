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

void Wall::HandleInput() {
}

void Wall::ExecuteCommand(uint32_t tick) {
}

void Wall::Update(float elapsed) {
}

void Wall::Render(sf::RenderWindow& window) {
}

void Wall::OnCollisionEnter(pGameObject other) {
}

void Wall::OnCollisionExit(pGameObject other) {
}
