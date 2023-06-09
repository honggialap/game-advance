#include "engine/actor/player_tank.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/wall.h"

namespace NSEngine {
	namespace NSActor {

		CPlayerTankRecord::CPlayerTankRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
			, int32_t movement_x, int32_t movement_y
		)
			: NSEngine::NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y)
			, movement_x(movement_x), movement_y(movement_y) {
			actor_type = EActorType::PLAYER_TANK;
		}

		CPlayerTank::CPlayerTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSCore::CGameObject(game, world) {
			type = EActorType::PLAYER_TANK;
		}

		CPlayerTank::~CPlayerTank() {
		}

		void CPlayerTank::Load(std::string data_path) {
			//std::ifstream data_file(data_path);
			//nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_tank1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);

			body_def.type = b2_dynamicBody;
			body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

			body = world->GetPhysics()->CreateBody(&body_def);

			collider.SetAsBox(32.0f / 30, 32.0f / 30);

			fixture_def.shape = &collider;
			fixture_def.density = 100.0f;
			fixture_def.friction = 0.0f;

			fixture_def.filter.categoryBits = ECollisionFilter::FILTER_PLAYER_TANK;
			fixture_def.filter.maskBits
				= ECollisionFilter::FILTER_PLAYER_TANK
				| ECollisionFilter::FILTER_CREEP_TANK
				| ECollisionFilter::FILTER_BULLET
				| ECollisionFilter::FILTER_STRUCTURE
				| ECollisionFilter::FILTER_WALL
				| ECollisionFilter::FILTER_WATER
				//| ECollisionFilter::FILTER_TREE
				| ECollisionFilter::FILTER_PICK_UP
				;

			fixture = body->CreateFixture(&fixture_def);

			movement = sf::Vector2i(0, 0);
			speed = 0.5f;
		}

		void CPlayerTank::Unload() {
			if (body != nullptr) {
				if (fixture != nullptr) {
					body->DestroyFixture(fixture);
					fixture = nullptr;
				}
				world->GetPhysics()->DestroyBody(body);
				body = nullptr;
			}
		}

		void CPlayerTank::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			float velocity_x, velocity_y;
			GetVelocity(velocity_x, velocity_y);

			int32_t movement_x, movement_y;
			GetMovement(movement_x, movement_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CPlayerTankRecord>(
					id,
					position_x, position_y,
					velocity_x, velocity_y,
					movement_x, movement_y
				)
			);
		}

		void CPlayerTank::Deserialize(NSEngine::NSCore::pRecord record) {
			auto tank_record = static_cast<pPlayerTankRecord>(record);
			SetPosition(tank_record->position_x, tank_record->position_y);
			SetVelocity(tank_record->velocity_x, tank_record->velocity_y);
			SetMovement(tank_record->movement_x, tank_record->movement_y);
		}

		void CPlayerTank::HandleInput(uint32_t tick) {
		}

		void CPlayerTank::ExecuteCommand(NSEngine::NSCore::pCommand command) {
			switch (command->command_type) {
			case ECommandType::PLAYER_TANK_MOVE: {
				auto move_command = static_cast<pMoveCommand>(command);
				SetMovement(move_command->x, move_command->y);
				break;
			}

			case ECommandType::PLAYER_TANK_SHOOT: {
				auto shoot_command = static_cast<pShootCommand>(command);
				break;
			}
			}
		}

		void CPlayerTank::Update(float elapsed) {
			b2Vec2 current_movement(
				speed * movement.x / 30.0f,
				speed * movement.y / 30.0f
			);
			body->SetLinearVelocity(current_movement);
		}

		void CPlayerTank::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CPlayerTank::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			if (dynamic_cast<NSEngine::NSActor::pWall>(other)) {
				printf("TANK hit WALL.\n");
			}
		}

		void CPlayerTank::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			if (dynamic_cast<NSEngine::NSActor::pWall>(other)) {
				printf("TANK stop hit WALL.\n");
			}
		}

	}
}
