#include "engine/component/control/move.h"

namespace NSEngine {
	namespace NSComponent {

		CMove::CMove() {
		}

		CMove::~CMove() {
		}

		void CMove::SetMovement(int32_t x, int32_t y) {
			movement.x = x;
			movement.y = y;
		}

		sf::Vector2i CMove::GetMovement() {
			return movement;
		}

		void CMove::GetMovement(int32_t& x, int32_t& y) {
			x = movement.x; y = movement.y;
		}

	}
}
