#include "engine/actor/factory.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CFactoryRecord::CFactoryRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, a(0.0f) {
			actor_type = EActorType::FACTORY;
		}

		CFactoryRecord::CFactoryRecord(
			uint32_t id
			, float a
		)
			: NSCore::CRecord(id) 
			, a(a) {
			actor_type = EActorType::FACTORY;
		}

		CFactory::CFactory(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::FACTORY;
		}

		CFactory::~CFactory() {
		}

		void CFactory::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_factory1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CFactory::UnloadResource() {
		}

		void CFactory::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CFactoryRecord>(
					id
				)
			);
		}

		void CFactory::Deserialize(NSCore::pRecord record) {
			auto factory_record = static_cast<pFactoryRecord>(record);
		}

		void CFactory::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto factory_record = static_cast<pFactoryRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CFactory::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CFactoryRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CFactory::Update(float elapsed) {
		}

		void CFactory::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CFactory::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CFactory::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CFactory::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
			PackLoadResource(packet);
		}

		void CFactory::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
			UnpackLoadResource(packet);
		}

	}
}