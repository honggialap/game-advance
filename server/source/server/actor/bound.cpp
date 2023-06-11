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

			auto& physics_data = data.at("physics");
			bound->CreatePhysics(physics_data);

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