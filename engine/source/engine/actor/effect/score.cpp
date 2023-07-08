#include "engine/actor/effect/score.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/tank/enemy_tank.h"

namespace NSEngine {
	namespace NSActor {

		CScore::CScore(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
		{
			type = EActorType::SCORE;
		}

		CScore::~CScore() {
		}

		void CScore::AddEnemyTank(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			enemy_tank = dynamic_cast<pEnemyTank>(game_object);
			enemy_tank->AddScoreEffect(GetName());
		}

		void CScore::SetPosition(float value_x, float value_y) {
			x = value_x;
			y = value_y;
		}

		void CScore::GetPosition(float& out_x, float& out_y) {
			out_x = x;
			out_y = y;
		}

		void CScore::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);
		}

		void CScore::UnloadResource() {
		}

		void CScore::Update(float elapsed) {
		}

		void CScore::Render(sf::RenderWindow& window) {
		}

		void CScore::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			std::string enemy_tank_name = enemy_tank->GetName();
			*packet << enemy_tank_name;
		}

		void CScore::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			std::string enemy_tank_name;
			*packet >> enemy_tank_name;
			AddEnemyTank(enemy_tank_name);
		}

	}
}