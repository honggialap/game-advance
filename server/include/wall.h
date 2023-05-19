#pragma once
#ifndef __SERVER_WALL_H__
#define __SERVER_WALL_H__

#include "game_object.h"

struct WallRecord : public Record {
	WallRecord(
		uint32_t id, uint32_t type
	) :
		Record(id, type)
	{}
};
typedef std::unique_ptr<WallRecord> pWallRecord;

class Wall : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	static Wall* Create(pGame game, pWorld world, nlohmann::json& data);

	void Load(std::string data_path) override;
	void Unload() override;

	void Serialize(uint32_t tick) override;
	void Deserialize(Record* record) override;

	void HandleInput(uint32_t tick) override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;
};
typedef Wall* pWall;

#endif // !__SERVER_WALL_H__
