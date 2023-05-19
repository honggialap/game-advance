#pragma once
#ifndef __SERVER_TURRET_BULLET_H__
#define __SERVER_TURRET_BULLET_H__

#include "game_object.h"

struct TurretBulletRecord : public Record {
	float position_x, position_y;
	float velocity_x, velocity_y;

	TurretBulletRecord(
		uint32_t id, uint32_t type,
		float position_x, float position_y,
		float velocity_x, float velocity_y
	) :
		Record(id, type),
		position_x(position_x), position_y(position_y),
		velocity_x(velocity_x), velocity_y(velocity_y)
	{}
};
typedef std::unique_ptr<TurretBulletRecord> pTurretBulletRecord;

class TurretBullet : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	uint32_t team = 0;

public:
	static TurretBullet* Create(pGame game, pWorld world, nlohmann::json& data);

	void SetTeam(uint32_t value) { team = value; }
	uint32_t GetTeam() { return team; }

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
typedef TurretBullet* pTurretBullet;

#endif // !__SERVER_TURRET_BULLET_H__
