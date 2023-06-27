#include "engine/component/updatable.h"

namespace NSEngine {
	namespace NSComponent {

		CUpdatable::CUpdatable()
			: CDataLoadable()
			, CNetworksLoadable()
			, is_active(true) {
		}

		CUpdatable::~CUpdatable() {
		}

		void CUpdatable::SetActive(bool value) {
			is_active = value;
		}

		bool CUpdatable::IsActive() {
			return is_active;
		}

		void CUpdatable::LoadData(nlohmann::json& data) {
			if (data.contains("active")) {
				bool active_value = data.at("active");
				SetActive(active_value);
			}
		}

		void CUpdatable::PackLoad(NSNetworks::CPacket* packet) {
			bool send_active = IsActive();
			*packet << send_active;
		}

		void CUpdatable::UnpackLoad(NSNetworks::CPacket* packet) {
			bool receive_active;
			*packet >> receive_active;
			SetActive(receive_active);
		}

	}
}
