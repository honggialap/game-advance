#include "server/actor/headquarter.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pHeadquarter CHeadquarter::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("data");
			world->game_objects[id] = std::make_unique<CHeadquarter>(game, world, id, name);
			world->dictionary[name] = id;

			pHeadquarter headquarter = static_cast<pHeadquarter>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			headquarter->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			headquarter->SetResourcePath(resource_path);
			headquarter->LoadResource();

			return headquarter;
		}

		CHeadquarter::CHeadquarter(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world) 
			, NSEngine::NSActor::CHeadquarter(game, world, id, name) {
		}

		CHeadquarter::~CHeadquarter() {
		}

	}
}