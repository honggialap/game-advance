#include "engine/actor/terrain/tree.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CTree::CTree(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
		{
			type = EActorType::TREE;
		}

		CTree::~CTree() {
		}

		void CTree::SetPosition(float value_x, float value_y) {
			x = value_x;
			y = value_y;
		}

		void CTree::GetPosition(float& out_x, float out_y) {
			out_x = x;
			out_y = y;
		}

		void CTree::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			uint32_t texture_id = data.at("texture");
			sf::Texture& texture = game->GetTexture(texture_id);

			auto& sprite_data = data.at("sprite");
			int32_t left = sprite_data.at("left");
			int32_t top = sprite_data.at("top");
			int32_t width = sprite_data.at("width");
			int32_t height = sprite_data.at("height");
			float origin_x = sprite_data.at("origin_x");
			float origin_y = sprite_data.at("origin_y");
			sprite = sf::Sprite(
				texture
				, sf::IntRect(left, top, width, height)
			);
			sprite.setOrigin(origin_x, origin_y);
		}

		void CTree::UnloadResource() {
		}

		void CTree::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

	}
}
