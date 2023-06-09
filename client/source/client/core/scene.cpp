#include "client/core/scene.h"
#include "client/core/game.h"

namespace NSClient {
	namespace NSCore {

		CScene::CScene(NSEngine::NSCore::pGame game)
			: NSEngine::NSCore::CScene(game)
			, game_client(static_cast<NSClient::NSCore::pGame>(game)) {
		}

		CScene::~CScene() {
		}

	}
}
