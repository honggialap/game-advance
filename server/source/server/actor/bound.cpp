#include "server/actor/bound.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pBound CBound::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CBound>(game, world, id, name);
			world->dictionary[name] = id;

			pBound bound = static_cast<pBound>(world->game_objects[id].get());

			auto& physics = data.at("physics");
			b2BodyType body_type = b2BodyType(physics.at("body_type"));
			float position_x = float(physics.at("x"));
			float position_y = float(physics.at("y"));
			float width = float(physics.at("width"));
			float height = float(physics.at("height"));
			uint16_t category_bits = uint16_t(physics.at("category_bits"));
			uint16_t mask_bits = uint16_t(physics.at("mask_bits"));
			bound->CreatePhysics(body_type, position_x, position_y, width, height, category_bits, mask_bits);

			return bound;
		}

		CBound::CBound(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSServer::NSCore::CGameObject(game, world) 
			, NSEngine::NSActor::CBound(game, world, id, name) {
		}

		CBound::~CBound() {
		}

		void CBound::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CBound::OnCollisionEnter(other);
		}

		void CBound::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CBound::OnCollisionExit(other);
		}
	
	}
}