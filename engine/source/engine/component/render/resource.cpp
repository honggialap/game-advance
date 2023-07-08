#include "engine/component/render/resource.h"

namespace NSEngine {
	namespace NSComponent {

		CResource::CResource()
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CResource::~CResource() {
		}

		void CResource::SetResourcePath(std::string value) {
			resource_path = value;
		}

		std::string CResource::GetResourcePath() {
			return resource_path;
		}

		void CResource::JsonLoad(nlohmann::json& data) {
			if (data.contains("resource_path")) {
				std::string resource_path_value = data.at("resource_path");
				SetResourcePath(resource_path_value);
				LoadResource();
			}
		}

		void CResource::PackLoad(NSNetworks::CPacket* packet) {
			*packet << resource_path;
		}

		void CResource::UnpackLoad(NSNetworks::CPacket* packet) {
			*packet >> resource_path;
			LoadResource();
		}

	}
}
