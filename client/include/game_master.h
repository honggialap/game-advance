#pragma once
#ifndef __CLIENT_GAME_MASTER_H__
#define __CLIENT_GAME_MASTER_H__

#include "client_game_object.h"

class GameMaster : public ClientGameObject {
public:
	GameMaster(Game* game, World* world);
	~GameMaster();

	static GameMaster* Create(
		pGame game, pWorld world,
		std::string name,
		float position_x, float position_y,
		uint32_t layer,
		std::string data_path
	);

	void Load(std::string data_path) override;
	void Unload() override;

	void HandleInput(uint32_t tick) override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;
};
typedef GameMaster* pGameMaster;

#endif // !__CLIENT_GAME_MASTER_H__
