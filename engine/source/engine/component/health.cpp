#include "engine/component/health.h"

namespace NSEngine {
	namespace NSComponent {

		CHealth::CHealth()
			: CDataLoadable()
			, CNetworksLoadable() {
		}

		CHealth::~CHealth() {
		}

		void CHealth::ActivateHealth(float max_health_value) {
			is_alive = true;
			max_health = max_health_value;
			health = max_health_value;
		}

		void CHealth::Heal(float healing_value) {
			if (is_alive) {
				health += healing_value;
				if (health > max_health) {
					health = max_health;
				}
			}
		}

		void CHealth::Damaged(float damaged_value) {
			if (is_alive) {
				health -= damaged_value;
				if (health <= 0.0f) {
					health = 0.0f;
					is_alive = false;
				}
			}
		}

		void CHealth::BoostMaxHealth(float boost_value) {
			if (is_alive) {
				max_health += boost_value;
				health += boost_value;
			}
		}

		bool CHealth::IsAlive() {
			return is_alive;
		}

		void CHealth::LoadData(nlohmann::json& data) {
			if (data.contains("health")) {
				float health_value = data.at("health");
				ActivateHealth(health_value);
			}
		}

		void CHealth::PackLoad(NSNetworks::CPacket* packet)	{
			float send_health = max_health;
			*packet << max_health;
		}

		void CHealth::UnpackLoad(NSNetworks::CPacket* packet) {
			float receive_health;
			*packet >> receive_health;
			ActivateHealth(receive_health);
		}
		
	}
}
