#include "engine/component/resource_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		CResourceLoadable::CResourceLoadable()
			: CDataLoadable()
			, CNetworksLoadable() {
		}

		CResourceLoadable::~CResourceLoadable() {
		}

		void CResourceLoadable::SetResourcePath(std::string value) {
			resource_path = value;
		}

		std::string CResourceLoadable::GetResourcePath() {
			return resource_path;
		}

		void CResourceLoadable::LoadData(nlohmann::json& data) {
			if (data.contains("resource_path")) {
				std::string resource_path_value = data.at("resource_path");
				SetResourcePath(resource_path_value);
				LoadResource();
			}
		}

		void CResourceLoadable::PackLoad(NSNetworks::CPacket* packet) {
			*packet << resource_path;
		}

		void CResourceLoadable::UnpackLoad(NSNetworks::CPacket* packet) {
			*packet >> resource_path;
			LoadResource();
		}

	}
}
