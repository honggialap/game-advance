#include "engine/actor/wall.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CWallRecord::CWallRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::WALL;
		}

		CWall::CWall(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name) 
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::WALL;
		}

		CWall::~CWall() {
		}

		void CWall::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_wall.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CWall::UnloadResource() {
		}

		void CWall::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CWallRecord>(
					id
				)
			);
		}

		void CWall::Deserialize(NSCore::pRecord record) {
			auto wall_record = static_cast<pWallRecord>(record);
		}

		void CWall::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto wall_record = static_cast<pWallRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CWall::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CWallRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CWall::Update(float elapsed) {
		}

		void CWall::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CWall::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CWall::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}
