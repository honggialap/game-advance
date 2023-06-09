#include "engine/component/movement.h"

namespace NSEngine {
	namespace NSComponent {

		CMovement::CMovement() {
		}

		CMovement::~CMovement() {
		}

		void CMovement::SetMovement(int32_t x, int32_t y) {
			movement.x = x;
			movement.y = y;
		}

		sf::Vector2i CMovement::GetMovement() {
			return movement;
		}

		void CMovement::GetMovement(int32_t& x, int32_t& y) {
			x = movement.x; y = movement.y;
		}

		void CMovement::SetSpeed(float value) {
			speed = value;
		}

		float CMovement::GetSpeed() {
			return speed;
		}

	}
}
