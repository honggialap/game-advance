#include "engine/actor/headquarter.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CHeadquarterRecord::CHeadquarterRecord(uint32_t id)
			: NSEngine::NSCore::CRecord(id) {
			actor_type = EActorType::HEADQUARTER;
		}

		CHeadquarter::CHeadquarter(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSCore::CGameObject(game, world, id, name) 
			, NSEngine::NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::HEADQUARTER;
		}

		CHeadquarter::~CHeadquarter() {
		}

		void CHeadquarter::Load(std::string data_path) {
			//std::ifstream data_file(data_path);
			//nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_headquarter1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);

			body_def.type = b2_kinematicBody;
			body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

			body = world->GetPhysics()->CreateBody(&body_def);

			collider.SetAsBox(32.0f / 30, 32.0f / 30);

			fixture_def.shape = &collider;
			fixture_def.density = 100.0f;
			fixture_def.friction = 0.0f;

			fixture_def.filter.categoryBits = ECollisionFilter::FILTER_STRUCTURE;
			fixture_def.filter.maskBits
				= ECollisionFilter::FILTER_PLAYER_TANK
				| ECollisionFilter::FILTER_CREEP_TANK
				| ECollisionFilter::FILTER_BULLET
				//| ECollisionFilter::FILTER_STRUCTURE
				//| ECollisionFilter::FILTER_WALL
				//| ECollisionFilter::FILTER_WATER
				//| ECollisionFilter::FILTER_TREE
				//| ECollisionFilter::FILTER_PICK_UP
				;

			fixture = body->CreateFixture(&fixture_def);
		}

		void CHeadquarter::Unload() {
			if (body != nullptr) {
				if (fixture != nullptr) {
					body->DestroyFixture(fixture);
					fixture = nullptr;
				}
				world->GetPhysics()->DestroyBody(body);
				body = nullptr;
			}
		}

		void CHeadquarter::PackLoad(NSEngine::NSNetworks::CPacket* packet) {
		}

		void CHeadquarter::UnpackLoad(NSEngine::NSNetworks::CPacket* packet) {
		}

		void CHeadquarter::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CHeadquarterRecord>(
					id
				)
			);
		}

		void CHeadquarter::Deserialize(NSEngine::NSCore::pRecord record) {
			auto headquarter_record = static_cast<pHeadquarterRecord>(record);
		}

		void CHeadquarter::PackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto headquarter_record = static_cast<pHeadquarterRecord>(record);
			//*packet << factory_record->a;
		}

		void CHeadquarter::UnpackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto game_master_record = static_cast<pHeadquarterRecord>(record);
			//*packet >> factory_record->a;
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

		void CHeadquarter::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
		}

		void CHeadquarter::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}