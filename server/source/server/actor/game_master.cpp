#include "server/actor/game_master.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pGameMaster CGameMaster::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			
			world->game_objects[id] = std::make_unique<CGameMaster>(game, world, id, name);
			world->dictionary[name] = id;
			pGameMaster game_master = static_cast<pGameMaster>(world->game_objects[id].get());

			std::string resource_path = data.at("resource_path");
			game_master->SetResourcePath(resource_path);
			
			game_master->Load(resource_path);

			return game_master;
		}

		CGameMaster::CGameMaster(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CGameMaster(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CGameMaster::~CGameMaster() {
		}

		void CGameMaster::Load(std::string data_path) {
			NSEngine::NSActor::CGameMaster::Load(data_path);
		}

		void CGameMaster::Unload() {
			NSEngine::NSActor::CGameMaster::Unload();
		}

		void CGameMaster::Update(float elapsed) {
		}

	}
}
