#include "engine/actor/tank/basic_tank.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CBasicTankRecord::CBasicTankRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f)
			, velocity_x(0.0f), velocity_y(0.0f) {
			actor_type = EActorType::BASIC_TANK;
		}

		CBasicTankRecord::CBasicTankRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
		)
			: NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y) {
			actor_type = EActorType::BASIC_TANK;
		}

		CBasicTank::CBasicTank(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CEnemyTank(game, world, id, name)
		{
			type = EActorType::BASIC_TANK;
		}

		CBasicTank::~CBasicTank() {
		}

		void CBasicTank::LoadResource() {
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

		void CBasicTank::UnloadResource() {
		}

		void CBasicTank::Serialize(uint32_t tick) {
			float position_x;
			float position_y;
			GetPosition(position_x, position_y);

			float velocity_x;
			float velocity_y;
			GetVelocity(velocity_x, velocity_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CBasicTankRecord>(
					id,
					position_x, position_y,
					velocity_x, velocity_y
				)
			);
		}

		void CBasicTank::Deserialize(NSCore::pRecord record) {
			auto basic_tank_record = static_cast<pBasicTankRecord>(record);
			SetPosition(basic_tank_record->position_x, basic_tank_record->position_y);
			SetVelocity(basic_tank_record->velocity_x, basic_tank_record->velocity_y);
		}

		void CBasicTank::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto basic_tank_record = static_cast<pBasicTankRecord>(record);
			*packet << basic_tank_record->position_x;
			*packet << basic_tank_record->position_y;
			*packet << basic_tank_record->velocity_x;
			*packet << basic_tank_record->velocity_y;
		}

		NSCore::pRecord CBasicTank::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CBasicTankRecord(id);

			*packet >> record->position_x;
			*packet >> record->position_y;
			*packet >> record->velocity_x;
			*packet >> record->velocity_y;

			return record;
		}

		void CBasicTank::ExecuteCommand(NSCore::pCommand command) {
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

		void CBasicTank::Update(float elapsed) {
			b2Vec2 current_movement(
				speed * movement.x / 30.0f,
				speed * movement.y / 30.0f
			);
			body->SetLinearVelocity(current_movement);
		}

		void CBasicTank::Render(sf::RenderWindow& window) {
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

		void CBasicTank::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CBasicTank::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}