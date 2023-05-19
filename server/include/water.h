#pragma once
#ifndef __SERVER_WATER_H__
#define __SERVER_WATER_H__

#include "game_object.h"

struct WaterRecord : public Record {
	WaterRecord(
		uint32_t id, uint32_t type
	) :
		Record(id, type)
	{}
};
typedef std::unique_ptr<WaterRecord> pWaterRecord;

class Water : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	static Water* Create(pGame game, pWorld world, nlohmann::json& data);

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
typedef Water* pWater;

#endif // !__SERVER_WATER_H__
