#include "engine/actor/headquarter.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/game_master.h"

namespace NSEngine {
	namespace NSActor {

		CHeadquarterRecord::CHeadquarterRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::HEADQUARTER;
		}

		CHeadquarterRecord::CHeadquarterRecord(
			uint32_t id
			, bool is_alive
			, bool is_shovel_activated
			, float shovel_timer
		)
			: NSCore::CRecord(id) 
			, is_alive(is_alive) 
			, is_shovel_activated(is_shovel_activated)
			, shovel_timer(shovel_timer) {
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

		void CHeadquarter::AddGameMaster(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			game_master = dynamic_cast<pGameMaster>(game_object);
			game_master->AddHeadquarter(GetName());
		}

		void CHeadquarter::AddBrick(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			pBrick brick = dynamic_cast<pBrick>(game_object);
			bricks.push_back(brick);
		}

		void CHeadquarter::AddSteel(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			pSteel steel = dynamic_cast<pSteel>(game_object);
			steels.push_back(steel);
		}

		void CHeadquarter::ActivateShovel() {
			if (!is_shovel_activated) {
				for (auto& steel : steels) {
					steel->SetActive(true);
					steel->SetVisible(true);
					steel->SetBodyEnable(true);
					//steel->Reset();
				}

				for (auto& brick : bricks) {
					brick->SetActive(false);
					brick->SetVisible(false);
					brick->SetBodyEnable(false);
				}

				is_shovel_activated = true;
				shovel_timer = shovel_default_timer;
			}

			shovel_timer = shovel_default_timer;
		}

		void CHeadquarter::DeactivateShovel() {
			for (auto& brick : bricks) {
				brick->SetActive(true);
				brick->SetVisible(true);
				brick->SetBodyEnable(true);
				//brick->Reset();
			}

			for (auto& steel : steels) {
				steel->SetActive(false);
				steel->SetVisible(false);
				steel->SetBodyEnable(false);
			}

			is_shovel_activated = false;
		}

		void CHeadquarter::LoadResource() {
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

		void CHeadquarter::UnloadResource() {
		}

		void CHeadquarter::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CHeadquarterRecord>(
					id
					, is_alive
					, is_shovel_activated
					, shovel_timer
				)
			);
		}

		void CHeadquarter::Deserialize(NSCore::pRecord record) {
			auto headquarter_record = static_cast<pHeadquarterRecord>(record);
			is_alive = headquarter_record->is_alive;
			is_shovel_activated = headquarter_record->is_shovel_activated;
			shovel_timer = headquarter_record->shovel_timer;
		}

		void CHeadquarter::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto headquarter_record = static_cast<pHeadquarterRecord>(record);
			*packet << headquarter_record->is_alive;
			*packet << headquarter_record->is_shovel_activated;
			*packet << headquarter_record->shovel_timer;
		}

		NSCore::pRecord CHeadquarter::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CHeadquarterRecord(id);
			*packet >> record->is_alive;
			*packet >> record->is_shovel_activated;
			*packet >> record->shovel_timer;

			return record;
		}

		void CHeadquarter::Update(float elapsed) {
			// Do nothing here...
		}

		void CHeadquarter::Render(sf::RenderWindow& window) {
			uint32_t sprite_id = 1001;
			if (is_alive) sprite_id = 1001;
			else sprite_id = 1002;

			sf::Sprite& sprite = sprites[sprite_id];
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
			// Also do nothing here
		}

		void CHeadquarter::OnCollisionExit(NSComponent::pPhysics other) {
			// And here
		}

		void CHeadquarter::LoadComponents(nlohmann::json& components_data) {
			NSCore::CGameObject::LoadComponents(components_data);

			if (components_data.contains("shovel_time")) {
				float shovel_time = components_data.at("shovel_time");
			}

		}

		void CHeadquarter::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			std::string game_master_name = game_master->GetName();
			*packet << game_master_name;
		}

		void CHeadquarter::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			std::string game_master_name;
			*packet >> game_master_name;
			AddGameMaster(game_master_name);
		}

	}
}