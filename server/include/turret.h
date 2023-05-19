#pragma once
#ifndef __SERVER_TURRET_H__
#define __SERVER_TURRET_H__

#include "game_object.h"

struct TurretRecord : public Record {
	TurretRecord(
		uint32_t id, uint32_t type
	) :
		Record(id, type)
	{}
};
typedef std::unique_ptr<TurretRecord> pTurretRecord;

class Turret : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	uint32_t team = 0;

public:
	static Turret* Create(pGame game, pWorld world, nlohmann::json& data);

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
typedef Turret* pTurret;

#endif // !__SERVER_TURRET_H__
