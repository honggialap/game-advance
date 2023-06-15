#include "server/actor/factory.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pFactory CFactory::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CFactory>(game, world, id, name);
			world->dictionary[name] = id;

			pFactory factory = static_cast<pFactory>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			factory->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			factory->SetResourcePath(resource_path);
			factory->LoadResource();

			return factory;
		}

		CFactory::CFactory(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CFactory(game, world, id, name) {
		}

		CFactory::~CFactory() {
		}

	}
}
