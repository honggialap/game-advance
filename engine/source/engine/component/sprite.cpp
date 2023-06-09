#include "engine/component/sprite.h"

namespace NSEngine {
	namespace NSComponent {

		CSprite::CSprite(){
		}

		CSprite::~CSprite(){
		}

		void CSprite::SetLayer(uint32_t value) {
			layer = value;
		}

		uint32_t CSprite::GetLayer() {
			return layer;
		}

	}
}
