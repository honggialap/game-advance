#include "bullet.h"
#include "game.h"
#include "world.h"

pGameObjectState Bullet::Serialize() {
	return new BulletState(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y
	);
}

bool Bullet::Deserialize(pGameObjectState game_object_state) {
	if (!static_cast<pBulletState>(game_object_state)) {
		return false;
	}

	pBulletState state = static_cast<pBulletState>(game_object_state);
	position_x = state->position_x;
	position_y = state->position_y;
	velocity_x = state->velocity_x;
	velocity_y = state->velocity_y;

	return true;
}

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
