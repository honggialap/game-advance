#pragma once
#ifndef __SERVER_BULLET_H__
#define __SERVER_BULLET_H__

#include "game_object.h"

struct BulletRecord : public Record {
	BulletRecord(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	) :
		Record(
			id,
			type,
			position_x,
			position_y,
			velocity_x,
			velocity_y
		)
	{}
};
typedef std::unique_ptr<BulletRecord> pBulletRecord;

class Bullet : public GameObject {
public:
	Bullet(pGame game, pWorld world, uint32_t id, uint32_t type)
		: GameObject(game, world, id, type) {};

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
typedef Bullet* pBullet;

#endif // !__SERVER_BULLET_H__
