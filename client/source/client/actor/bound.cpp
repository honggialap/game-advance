#include "client/actor/bound.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pBound CBound::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CBound>(game, world);
			world->dictionary[name] = id;
			pBound bound = static_cast<pBound>(world->game_objects[id].get());

			bound->SetId(id);
			bound->SetName(name);
			bound->SetResourcePath(data_path);
			bound->Load(data_path);

			return bound;
		}

		CBound::CBound(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CBound(game, world)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CBound::~CBound() {
		}

		void CBound::Load(std::string data_path) {
			NSEngine::NSActor::CBound::Load(data_path);
		}

		void CBound::Unload() {
			NSEngine::NSActor::CBound::Unload();
		}

		void CBound::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CBound::OnCollisionEnter(other);
		}

		void CBound::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CBound::OnCollisionExit(other);
		}

	}
}