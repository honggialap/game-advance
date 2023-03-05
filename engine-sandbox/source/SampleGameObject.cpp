#include "SampleGameObject.h"

SampleGameObject::SampleGameObject(pGame game, pScene scene) : GameObject(game, scene){
	sample_game = static_cast<pSampleGame>(game);
	sample_world_scene = static_cast<pSampleWorldScene>(scene);
}

SampleGameObject::~SampleGameObject(){
}

void SampleGameObject::Load(){
	texture.loadFromFile("data/test.png", sf::IntRect(0, 0, 64, 64));
	texture.setSmooth(true);

	sprite.setTexture(texture);
	sprite.setPosition(100, 100);

	font.loadFromFile("data/arial.ttf");

	text.setFont(font);
	text.setString("TESTING FONT");
	text.setFillColor(sf::Color::Red);
	text.setPosition(200, 200);

	sfx_buffer.loadFromFile("data/sfx.wav");
	sfx.setBuffer(sfx_buffer);

	music.openFromFile("data/audio.wav");
}

void SampleGameObject::Unload() {
}

void SampleGameObject::Update(float elapsed){

	// Camera movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sample_world_scene->GetCamera().move(sf::Vector2f(0, -1.0f) * elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sample_world_scene->GetCamera().move(sf::Vector2f(0, 1.0f) * elapsed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sample_world_scene->GetCamera().move(sf::Vector2f(-1.0f, 0) * elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sample_world_scene->GetCamera().move(sf::Vector2f(1.0f, 0) * elapsed);
	}

	// Sprite movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		sprite.move(sf::Vector2f(0, -1.0f) * elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		sprite.move(sf::Vector2f(0, 1.0f) * elapsed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		sprite.move(sf::Vector2f(-1.0f, 0) * elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		sprite.move(sf::Vector2f(1.0f, 0) * elapsed);
	}

	// Sound control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		sfx.play();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		music.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		music.stop();
	}

	// Scene control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
		game->PlayScene(0);
	}
}

void SampleGameObject::Render(sf::RenderWindow& window){
	window.draw(sprite);
	window.draw(text);
}
