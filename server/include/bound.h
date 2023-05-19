#pragma once
#ifndef __SERVER_BOUND_H__
#define __SERVER_BOUND_H__

#include "game_object.h"

struct BoundRecord : public Record {
	BoundRecord(
		uint32_t id, uint32_t type
	) : 
		Record(id, type)
	{}
};
typedef std::unique_ptr<BoundRecord> pBoundRecord;

class Bound : public GameObject {
public:
	static Bound* Create(pGame game, pWorld world, nlohmann::json& data);

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
typedef Bound* pBound;

#endif // !__SERVER_BOUND_H__
