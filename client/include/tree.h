#pragma once
#ifndef __CLIENT_TREE_H__
#define __CLIENT_TREE_H__

#include "client_game_object.h"

class Tree : public ClientGameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Tree(Game* game, World* world);
	~Tree();

	static Tree* Create(
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
typedef Tree* pTree;

#endif // !__CLIENT_TREE_H__