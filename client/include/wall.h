#pragma once
#ifndef __CLIENT_WALL_H__
#define __CLIENT_WALL_H__

#include "game_object.h"

namespace Client {

	// Forward declaration
	class GameClient;
	typedef GameClient* pGameClient;
	class World;
	typedef World* pWorld;

	class Wall : public Engine::GameObject {
	protected:
		pGameClient game_client;
		pWorld world;

	protected:
		sf::SoundBuffer sfx_buffer;
		sf::Sound sfx;
		sf::Music music;

	public:
		Wall(Engine::pGame game, Engine::pScene scene);
		~Wall();

	public:
		void Load(std::string data_path) override;
		void Unload() override;

		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;
	};
	typedef Wall* pWall;

}

#endif // !__CLIENT_WALL_H__
