#include "engine/actor/tank/bullet.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/tank/base_tank.h"

namespace NSEngine {
	namespace NSActor {

		CBulletRecord::CBulletRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f)
			, velocity_x(0.0f), velocity_y(0.0f) {
			actor_type = EActorType::BULLET;
		}

		CBulletRecord::CBulletRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
		)
			: NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y) {
			actor_type = EActorType::BULLET;
		}

		CBullet::CBullet(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics())	
		{
			type = EActorType::BULLET;
		}

		CBullet::~CBullet() {
		}

		void CBullet::AddBaseTank(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			base_tank = dynamic_cast<pBaseTank>(game_object);
			base_tank->AddBullet(GetName());
		}

		void CBullet::AddImpactEffect(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			impact_effect = dynamic_cast<pImpact>(game_object);
		}

		void CBullet::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			uint32_t texture_id = data.at("texture");
			sf::Texture& texture = game->GetTexture(texture_id);

			for (auto& sprite_data : data.at("sprites")) {
				uint32_t id = sprite_data.at("id");
				int32_t left = sprite_data.at("left");
				int32_t top = sprite_data.at("top");
				int32_t width = sprite_data.at("width");
				int32_t height = sprite_data.at("height");
				float origin_x = sprite_data.at("origin_x");
				float origin_y = sprite_data.at("origin_y");

				sprites[id] = sf::Sprite(
					texture
					, sf::IntRect(left, top, width, height)
				);
				sprites[id].setOrigin(origin_x, origin_y);
			}
		}

		void CBullet::UnloadResource() {
		}

		void CBullet::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			float velocity_x, velocity_y;
			GetVelocity(velocity_x, velocity_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CBulletRecord>(
					id,
					position_x, position_y,
					velocity_x, velocity_y
				)
			);
		}

		void CBullet::Deserialize(NSCore::pRecord record) {
			auto player_bullet = static_cast<pBulletRecord>(record);
			SetPosition(player_bullet->position_x, player_bullet->position_y);
			SetVelocity(player_bullet->velocity_x, player_bullet->velocity_y);
		}

		void CBullet::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto player_bullet_record = static_cast<pBulletRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CBullet::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CBulletRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CBullet::Update(float elapsed) {
		}

		void CBullet::Render(sf::RenderWindow& window) {
			sf::Sprite& sprite = sprites[1001];

			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CBullet::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CBullet::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CBullet::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			std::string base_tank_name = base_tank->GetName();
			*packet << base_tank_name;
		}

		void CBullet::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			std::string base_tank_name;
			*packet >> base_tank_name;
			AddBaseTank(base_tank_name);
		}

	}
}