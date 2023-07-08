#include "engine/component/control/direction.h"

namespace NSEngine {
	namespace NSComponent {

		CDirection::CDirection()
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CDirection::~CDirection() {
		}

		void CDirection::SetDirection(bool left, bool up) {
			facing_left = left;
			facing_up = up;
		}

		void CDirection::GetDirection(bool& left, bool& up) {
			left = facing_left;
			up = facing_up;
		}

		void CDirection::SetFacingLeft(bool value) {
			facing_left = value;
		}

		bool CDirection::IsFacingLeft() {
			return facing_left;
		}

		void CDirection::SetFacingUp(bool value) {
			facing_up = value;
		}

		bool CDirection::IsFacingUp() {
			return facing_up;
		}

		void CDirection::JsonLoad(nlohmann::json& data) {
			if (
				data.contains("left")
				&& data.contains("up")
				) {
				bool facing_left_value = data.at("left");
				bool facing_up_value = data.at("up");
				SetDirection(facing_left_value, facing_up_value);
			}
		}

		void CDirection::PackLoad(NSNetworks::CPacket* packet) {
			bool send_facing_left, send_facing_up;
			GetDirection(send_facing_left, send_facing_up);
			*packet << send_facing_left;
			*packet << send_facing_up;
		}

		void CDirection::UnpackLoad(NSNetworks::CPacket* packet) {
			bool receive_facing_left;
			*packet >> receive_facing_left;

			bool receive_facing_up;
			*packet >> receive_facing_up;
			
			SetDirection(receive_facing_left, receive_facing_up);
		}

	}
}
