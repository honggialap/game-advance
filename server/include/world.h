#pragma once
#ifndef __SERVER_WORLD_H__
#define __SERVER_WORLD_H__

#include "scene.h"
#include "game_object.h"

#define ACTOR_TYPE_TANK		1
#define ACTOR_TYPE_BULLET	2
#define ACTOR_TYPE_WALL		3

// Forward declaration
class Game;
typedef Game* pGame;

class World : public Scene, b2ContactListener {
protected:
	sf::View camera;

	b2Vec2 gravity;
	b2World* physics_world = nullptr;

	uint32_t game_object_id = 1000;
	std::map<uint32_t, std::shared_ptr<GameObject>> gameObjects;

public:
	World(pGame game) : Scene(game) {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	pGameObject CreateGameObject(unsigned int game_object_type);

	sf::View& GetCamera();

	b2World* GetPhysics();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	void OnConnect(uint32_t connection_id) override;
	void OnDisconnect(uint32_t connection_id) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};
typedef World* pWorld;

#endif // !__SERVER_WORLD_H__
