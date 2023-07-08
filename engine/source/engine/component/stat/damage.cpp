#include "engine/component/stat/damage.h"

namespace NSEngine {
	namespace NSComponent {

		CDamage::CDamage() 
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CDamage::~CDamage() {
		}

		void CDamage::SetDamage(int32_t value) {
			damage = value;
		}

		int32_t CDamage::GetDamage() {
			return damage;
		}

		void CDamage::JsonLoad(nlohmann::json& data) {
			if (data.contains("damage")) {
				int32_t damage_value = data.at("damage");
				SetDamage(damage_value);
			}
		}

		void CDamage::PackLoad(NSNetworks::CPacket* packet) {
			int32_t send_damage = GetDamage();
			*packet << send_damage;
		}

		void CDamage::UnpackLoad(NSNetworks::CPacket* packet) {
			int32_t receive_damage;
			*packet >> receive_damage;
			SetDamage(receive_damage);
		}

	}
}
