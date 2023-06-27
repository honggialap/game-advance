#include "engine/component/movement.h"

namespace NSEngine {
	namespace NSComponent {

		CMovement::CMovement()
			: CDataLoadable()
			, CNetworksLoadable() {
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

		void CMovement::LoadData(nlohmann::json& data) {
			if (data.contains("speed")) {
				float speed_value = data.at("speed");
				SetSpeed(speed_value);
			}
		}

		void CMovement::PackLoad(NSNetworks::CPacket* packet) {
			float send_speed = GetSpeed();
			*packet << send_speed;
		}

		void CMovement::UnpackLoad(NSNetworks::CPacket* packet) {
			float receive_speed;
			*packet >> receive_speed;
			SetSpeed(receive_speed);
		}

	}
}
