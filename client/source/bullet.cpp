#include "bullet.h"
#include "game.h"
#include "world.h"

void Bullet::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);
}

void Bullet::Unload() {
}

void Bullet::Update(float elapsed) {
}

void Bullet::Render(sf::RenderWindow& window) {
}

void Bullet::OnCollisionEnter(pGameObject other) {
}

void Bullet::OnCollisionExit(pGameObject other) {
}
