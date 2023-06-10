#include "client/core/world.h"

namespace NSClient {
	namespace NSCore {

		CWorld::CWorld(NSEngine::NSCore::pGame game)
			: NSEngine::NSCore::CWorld(game)
			, game_client(static_cast<NSClient::NSCore::pGame>(game)) {
		}

		CWorld::~CWorld() {
		}

		void CWorld::SetJustGotGameState(bool value) {
			just_got_game_state = value;
		}

		bool CWorld::IsJustGotGameState() {
			return just_got_game_state;
		}

		void CWorld::SetServerTick(uint32_t value) {
			server_tick = value;
		}

		uint32_t CWorld::GetServerTick() {
			return server_tick;
		}

		void CWorld::Load(nlohmann::json& data) {
		}

		void CWorld::Unload() {
		}

	}
}
