#pragma once
#ifndef __SERVER_WORLD_H__
#define __SERVER_WORLD_H__

#include "scene.h"
#include "game_object.h"
#include "game_state.h"
#include "command.h"

#define ACTOR_TYPE_TANK		1
#define ACTOR_TYPE_BULLET	2
#define ACTOR_TYPE_WALL		3

// Forward declaration
class Game;
typedef Game* pGame;

struct GameState {
	uint32_t tick;
	std::map<uint32_t, pGameObjectState> game_objects_state;
};
typedef GameState* pGameState;

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

	uint32_t ready_client_count = 0;
	uint32_t load_client_count = 0;

public:
	uint32_t tick_per_game_state = 4;
	uint32_t tick_per_game_state_count = 0;

	std::map<uint32_t, float> player_ping;

	World(pGame game) : Scene(game) {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	pGameObject CreateGameObject(uint32_t game_object_type,	float position_x, float position_y);

	sf::View& GetCamera();

	b2World* GetPhysics();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	void OnConnect(uint32_t connection_id) override;
	void OnDisconnect(uint32_t connection_id) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;

	void SendLoadPacket();
	void SendStartGamePacket();

	void SendGameStatePacket();
	void RelayMoveCommand(uint32_t sent_client_id, pMoveCommand move_command);

	void SerializeGameState();
	void DeserializeGameState();
};
typedef World* pWorld;

#endif // !__SERVER_WORLD_H__
