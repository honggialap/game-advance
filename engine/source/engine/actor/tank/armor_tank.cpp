#include "engine/actor/tank/armor_tank.h"
#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/game_master.h"
#include "engine/actor/terrain/brick.h"

namespace NSEngine {
	namespace NSActor {

		CArmorTankRecord::CArmorTankRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f)
			, velocity_x(0.0f), velocity_y(0.0f)
			, movement_x(0), movement_y(0) {
			actor_type = EActorType::ARMOR_TANK;
		}

		CArmorTankRecord::CArmorTankRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
			, int32_t movement_x, int32_t movement_y
		)
			: NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y)
			, movement_x(movement_x), movement_y(movement_y) {
			actor_type = EActorType::ARMOR_TANK;
		}

		CArmorTank::CArmorTank(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CEnemyTank(game, world, id, name) {
			type = EActorType::ARMOR_TANK;
		}

		CArmorTank::~CArmorTank() {
		}

		void CArmorTank::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			uint32_t texture_id = data.at("tank_texture");
			sf::Texture& texture = game->GetTexture(texture_id);

			for (auto& tank_sprite_data : data.at("tank_sprites")) {
				uint32_t id = tank_sprite_data.at("id");
				int32_t left = tank_sprite_data.at("left");
				int32_t top = tank_sprite_data.at("top");
				int32_t width = tank_sprite_data.at("width");
				int32_t height = tank_sprite_data.at("height");
				float origin_x = tank_sprite_data.at("origin_x");
				float origin_y = tank_sprite_data.at("origin_y");

				tank_sprites[id] = sf::Sprite(
					texture
					, sf::IntRect(left, top, width, height)
				);
				tank_sprites[id].setOrigin(origin_x, origin_y);
			}
		}

		void CArmorTank::UnloadResource() {
		}

		void CArmorTank::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			float velocity_x, velocity_y;
			GetVelocity(velocity_x, velocity_y);

			int32_t movement_x, movement_y;
			GetMovement(movement_x, movement_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CArmorTankRecord>(
					id,
					position_x, position_y,
					velocity_x, velocity_y,
					movement_x, movement_y
				)
			);
		}

		void CArmorTank::Deserialize(NSCore::pRecord record) {
			auto armor_tank_record = static_cast<pArmorTankRecord>(record);
			SetPosition(armor_tank_record->position_x, armor_tank_record->position_y);
			SetVelocity(armor_tank_record->velocity_x, armor_tank_record->velocity_y);
			SetMovement(armor_tank_record->movement_x, armor_tank_record->movement_y);
		}

		void CArmorTank::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto armor_tank_record = static_cast<pArmorTankRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CArmorTank::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CArmorTankRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CArmorTank::ExecuteCommand(NSCore::pCommand command) {
			switch (command->command_type) {
			case ECommandType::TANK_MOVE: {
				auto move_command = static_cast<pMoveCommand>(command);
				SetMovement(move_command->x, move_command->y);
				break;
			}

			case ECommandType::TANK_SHOOT: {
				auto shoot_command = static_cast<pShootCommand>(command);
				break;
			}
			}
		}

		void CArmorTank::Update(float elapsed) {
			b2Vec2 current_movement(
				speed * movement.x / 30.0f,
				speed * movement.y / 30.0f
			);
			body->SetLinearVelocity(current_movement);
		}

		void CArmorTank::Render(sf::RenderWindow& window) {
			sf::Sprite& sprite = tank_sprites[1001];

			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CArmorTank::OnCollisionEnter(NSComponent::pPhysics other) {
			if (dynamic_cast<NSActor::pBrick>(other)) {
				printf("TANK hit WALL.\n");
			}
		}

		void CArmorTank::OnCollisionExit(NSComponent::pPhysics other) {
			if (dynamic_cast<NSActor::pBrick>(other)) {
				printf("TANK stop hit WALL.\n");
			}
		}

	}
}
