#include "engine/actor/wall.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CWallRecord::CWallRecord(uint32_t id)
			: NSEngine::NSCore::CRecord(id) {
			actor_type = EActorType::WALL;
		}

		CWall::CWall(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSCore::CGameObject(game, world, id, name) 
			, NSEngine::NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::WALL;
		}

		CWall::~CWall() {
		}

		void CWall::Load(std::string data_path) {
			//std::ifstream data_file(data_path);
			//nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_wall.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);

			body_def.type = b2_kinematicBody;
			body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

			body = world->GetPhysics()->CreateBody(&body_def);

			collider.SetAsBox(32.0f / 30, 32.0f / 30);

			fixture_def.shape = &collider;
			fixture_def.density = 100.0f;
			fixture_def.friction = 0.0f;

			fixture_def.filter.categoryBits = ECollisionFilter::FILTER_WALL;
			fixture_def.filter.maskBits =
				ECollisionFilter::FILTER_PLAYER_TANK
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

		void CWall::Unload() {
			if (body != nullptr) {
				if (fixture != nullptr) {
					body->DestroyFixture(fixture);
					fixture = nullptr;
				}
				world->GetPhysics()->DestroyBody(body);
				body = nullptr;
			}
		}

		void CWall::PackLoad(NSEngine::NSNetworks::CPacket* packet)
		{
		}

		void CWall::UnpackLoad(NSEngine::NSNetworks::CPacket* packet)
		{
		}

		void CWall::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CWallRecord>(
					id
				)
			);
		}

		void CWall::Deserialize(NSEngine::NSCore::pRecord record) {
			auto wall_record = static_cast<pWallRecord>(record);
		}

		void CWall::PackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto wall_record = static_cast<pWallRecord>(record);
			//*packet << factory_record->a;
		}

		void CWall::UnpackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto wall_record = static_cast<pWallRecord>(record);
			//*packet >> factory_record->a;
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

		void CWall::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
		}

		void CWall::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}
