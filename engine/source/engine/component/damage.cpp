#include "engine/component/damage.h"

namespace NSEngine {
	namespace NSComponent {

		CDamage::CDamage() 
			: CDataLoadable()
			, CNetworksLoadable() {
		}

		CDamage::~CDamage() {
		}

		void CDamage::SetDamage(float value) {
			damage = value;
		}

		float CDamage::GetDamage() {
			return damage;
		}

		void CDamage::LoadData(nlohmann::json& data) {
			if (data.contains("damage")) {
				float damage_value = data.at("damage");
				SetDamage(damage_value);
			}
		}

		void CDamage::PackLoad(NSNetworks::CPacket* packet) {
			float send_damage = GetDamage();
			*packet << send_damage;
		}

		void CDamage::UnpackLoad(NSNetworks::CPacket* packet) {
			float receive_damage;
			*packet >> receive_damage;
			SetDamage(receive_damage);
		}

	}
}
