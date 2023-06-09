#include "client/core/world.h"

namespace NSClient {
	namespace NSCore {

		CWorld::CWorld(NSEngine::NSCore::pGame game)
			: NSEngine::NSCore::CWorld(game)
			, game_client(static_cast<NSClient::NSCore::pGame>(game)) {
		}

		CWorld::~CWorld() {
		}

	}
}
