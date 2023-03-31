#include "bullet.h"
#include "game.h"
#include "world.h"

void Bullet::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	font.loadFromFile("data/resources/fonts/arial.ttf");

	text.setFont(font);
	text.setString("TESTING FONT");
	text.setFillColor(sf::Color::Red);
	text.setPosition(200, 200);
}

void Bullet::Unload() {
}

void Bullet::Update(float elapsed) {
	// Scene control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
		game->PlayScene(0);
	}
}

void Bullet::Render(sf::RenderWindow& window) {
	window.draw(text);
}

void Bullet::OnCollisionEnter(pGameObject other) {
}

void Bullet::OnCollisionExit(pGameObject other) {
}
