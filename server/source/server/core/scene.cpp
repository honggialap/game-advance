#include "server/core/scene.h"
#include "server/core/game.h"

namespace NSServer {
	namespace NSCore {

		CScene::CScene(NSEngine::NSCore::pGame game)
			: NSEngine::NSCore::CScene(game)
			, game_server(static_cast<NSServer::NSCore::pGame>(game)) {
		}

		CScene::~CScene() {
		}

	}
}
