#include "engine/component/stat/health.h"

namespace NSEngine {
	namespace NSComponent {

		CHealth::CHealth()
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CHealth::~CHealth() {
		}

		void CHealth::SetHealth(int32_t value) {
			health = value;
		}

		int32_t CHealth::GetHealth() {
			return health;
		}

		void CHealth::JsonLoad(nlohmann::json& data) {
			if (data.contains("health")) {
				int32_t health_value = data.at("health");
				SetHealth(health_value);
			}
		}

		void CHealth::PackLoad(NSNetworks::CPacket* packet) {
			int32_t send_health = GetHealth();
			*packet << send_health;
		}

		void CHealth::UnpackLoad(NSNetworks::CPacket* packet) {
			int32_t receive_health;
			*packet >> receive_health;
			SetHealth(receive_health);
		}

	}
}
