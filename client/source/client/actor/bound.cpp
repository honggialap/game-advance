#include "client/actor/bound.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pBound CBound::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CBound>(game, world, id, name);
			world->dictionary[name] = id;

			pBound bound = static_cast<pBound>(world->game_objects[id].get());
			return bound;
		}

		CBound::CBound(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			:NSClient::NSCore::CGameObject(game, world)
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