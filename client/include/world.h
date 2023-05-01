#pragma once
#ifndef __CLIENT_WORLD_H__
#define __CLIENT_WORLD_H__

#include "scene.h"
#include "game_object.h"

#define ACTOR_TYPE_TANK		1
#define ACTOR_TYPE_BULLET	2
#define ACTOR_TYPE_WALL		3

// Forward declaration
class Game;
typedef Game* pGame;

class World : public Scene, public b2ContactListener {
protected:
	enum State {
		Loading,
		Run
	};
	State state = Loading;

	sf::View camera;
	sf::Font font;
	sf::Text text;

	b2Vec2 gravity;
	b2World* physics_world = nullptr;

	uint32_t game_object_id = 1000;
	std::map<uint32_t, std::shared_ptr<GameObject>> game_objects;

public:
	pCommands commands;

	bool just_got_game_state = false;
	uint32_t server_tick = 0;
	uint32_t ack_tick = 0;

	uint32_t latest_tick = 0;
	uint32_t processing_tick = 0;

	bool ready_sent = false;

	bool ping_sent = false;
	uint32_t ping_tick = 0;

	World(pGame game) : Scene(game) {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	pGameObject CreateGameObject(uint32_t game_object_type, float position_x, float position_y);

	sf::View& GetCamera();

	b2World* GetPhysics();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	void OnConnect() override;
	void OnDisconnect() override;
	void OnConnectFail() override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;

	void SendReadyPacket();
	void SendLoadPacket();
	void SendPingPacket();
};
typedef World* pWorld;

#endif // !__CLIENT_WORLD_H__
