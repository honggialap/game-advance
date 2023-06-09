#include "client/actor/game_master.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {
		
		pGameMaster CGameMaster::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CGameMaster>(game, world);
			world->dictionary[name] = id;
			pGameMaster game_master = static_cast<pGameMaster>(world->game_objects[id].get());

			game_master->SetId(id);
			game_master->SetName(name);
			game_master->SetResourcePath(data_path);
			game_master->Load(data_path);

			return game_master;
		}

		CGameMaster::CGameMaster(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CGameMaster(game, world)
			, NSClient::NSCore::CGameObject(game, world) {
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
