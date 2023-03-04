#pragma once
#ifndef __PONG_SCENE_H__
#define __PONG_SCENE_H__

#include "Common.h"

class Scene {
protected:
	sf::View camera;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	sf::Text text;

	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	sf::Music music;

public:
	void Load() {
		camera.reset(sf::FloatRect(0, 0, 800, 600));

		texture.loadFromFile("data/test.png",sf::IntRect(0, 0, 64, 64));
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

	void Update(float elapsed) {
		// Camera movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			camera.move(sf::Vector2f(0, -0.001f) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			camera.move(sf::Vector2f(0, 0.001f) * elapsed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			camera.move(sf::Vector2f(-0.001f, 0) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			camera.move(sf::Vector2f(0.001f, 0) * elapsed);
		}

		// Sprite movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			sprite.move(sf::Vector2f(0, -0.005f) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			sprite.move(sf::Vector2f(0, 0.005f) * elapsed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			sprite.move(sf::Vector2f(-0.005f, 0) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			sprite.move(sf::Vector2f(0.005f, 0) * elapsed);
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
	}

	void Render(sf::RenderWindow& window) {
		window.setView(camera);
		
		window.draw(sprite);
		window.draw(text);
	}
};



#endif // !__PONG_SCENE_H__
