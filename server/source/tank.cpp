#include "tank.h"
#include "game.h"
#include "world.h"

void Tank::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/test.png", sf::IntRect(0, 0, 64, 64));
	texture.setSmooth(true);

	sprite.setTexture(texture);
	sprite.setPosition(100, 100);
}

void Tank::Unload() {
}

void Tank::Update(float elapsed) {
}

void Tank::Render(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Tank::OnCollisionEnter(pGameObject other) {
}

void Tank::OnCollisionExit(pGameObject other) {
}
