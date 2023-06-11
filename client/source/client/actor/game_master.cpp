#include "client/actor/game_master.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {
		
		pGameMaster CGameMaster::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CGameMaster>(game, world, id, name);
			world->dictionary[name] = id;
			
			pGameMaster game_master = static_cast<pGameMaster>(world->game_objects[id].get());
			return game_master;
		}

		CGameMaster::CGameMaster(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CGameMaster(game, world, id, name)
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
