#include "engine/actor/terrain/brick.h"
#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/headquarter.h"

namespace NSEngine {
	namespace NSActor {

		CBrickRecord::CBrickRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::BRICK;
		}

		CBrick::CBrick(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name) 
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::BRICK;
		}

		CBrick::~CBrick() {
		}

		void CBrick::AddHeadquarter(std::string name) {
			is_headquarter_bound = true;
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			headquarter = dynamic_cast<pHeadquarter>(game_object);
			headquarter->AddBrick(GetName());
		}

		void CBrick::LoadResource() {
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

		void CBrick::UnloadResource() {
		}

		void CBrick::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CBrickRecord>(
					id
				)
			);
		}

		void CBrick::Deserialize(NSCore::pRecord record) {
			auto brick_record = static_cast<pBrickRecord>(record);
		}

		void CBrick::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto brick_record = static_cast<pBrickRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CBrick::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CBrickRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CBrick::Update(float elapsed) {
		}

		void CBrick::Render(sf::RenderWindow& window) {
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

		void CBrick::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CBrick::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CBrick::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			*packet << is_headquarter_bound;
			if (is_headquarter_bound) {
				std::string headquarter_name = headquarter->GetName();
				*packet << headquarter_name;
			}
		}

		void CBrick::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			*packet >> is_headquarter_bound;
			if (is_headquarter_bound) {
				std::string headquarter_name;
				*packet >> headquarter_name;
				AddHeadquarter(headquarter_name);
			}
		}

	}
}
