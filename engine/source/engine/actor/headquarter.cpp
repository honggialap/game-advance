#include "engine/actor/headquarter.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CHeadquarterRecord::CHeadquarterRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::HEADQUARTER;
		}

		CHeadquarter::CHeadquarter(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name) 
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::HEADQUARTER;
		}

		CHeadquarter::~CHeadquarter() {
		}

		void CHeadquarter::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_headquarter1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CHeadquarter::UnloadResource() {
		}

		void CHeadquarter::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CHeadquarterRecord>(
					id
				)
			);
		}

		void CHeadquarter::Deserialize(NSCore::pRecord record) {
			auto headquarter_record = static_cast<pHeadquarterRecord>(record);
		}

		void CHeadquarter::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto headquarter_record = static_cast<pHeadquarterRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CHeadquarter::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CHeadquarterRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CHeadquarter::Update(float elapsed) {
		}

		void CHeadquarter::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CHeadquarter::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CHeadquarter::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}