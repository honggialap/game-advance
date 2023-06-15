#include "server/actor/wall.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pWall CWall::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CWall>(game, world, id, name);
			world->dictionary[name] = id;

			pWall wall = static_cast<pWall>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			wall->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			wall->SetResourcePath(resource_path);
			wall->LoadResource();

			return wall;
		}

		CWall::CWall(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CWall(game, world, id, name) {
		}

		CWall::~CWall() {
		}

	}
}
