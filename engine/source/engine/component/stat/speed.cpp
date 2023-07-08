#include "engine/component/stat/speed.h"

namespace NSEngine {
	namespace NSComponent {

		CSpeed::CSpeed()
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CSpeed::~CSpeed() {
		}

		void CSpeed::SetSpeed(float value) {
			speed = value;
		}

		float CSpeed::GetSpeed() {
			return speed;
		}

		void CSpeed::JsonLoad(nlohmann::json& data) {
			if (data.contains("speed")) {
				float speed_value = data.at("speed");
				SetSpeed(speed_value);
			}
		}

		void CSpeed::PackLoad(NSNetworks::CPacket* packet) {
			float send_speed = GetSpeed();
			*packet << send_speed;
		}

		void CSpeed::UnpackLoad(NSNetworks::CPacket* packet) {
			float receive_speed;
			*packet >> receive_speed;
			SetSpeed(receive_speed);
		}

	}
}
