#pragma once
#ifndef __SERVER_POWER_UP_H__
#define __SERVER_POWER_UP_H__

#include "game_object.h"

struct PowerUpRecord : public Record {
	float position_x, position_y;

	PowerUpRecord(
		uint32_t id, uint32_t type,
		float position_x, float position_y
	) :
		Record(id, type),
		position_x(position_x), position_y(position_y)
	{}
};
typedef std::unique_ptr<PowerUpRecord> pPowerUpRecord;

class PowerUp : public GameObject {
public:
	sf::Texture texture;
	sf::Sprite sprite;

	static PowerUp* Create(pGame game, pWorld world, nlohmann::json& data);

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
typedef PowerUp* pPowerUp;

#endif // !__SERVER_POWER_UP_H__
