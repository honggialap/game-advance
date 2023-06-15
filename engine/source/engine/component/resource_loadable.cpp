#include "engine/component/resource_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		CResourceLoadable::CResourceLoadable() {
		}

		CResourceLoadable::~CResourceLoadable() {
		}

		void CResourceLoadable::SetResourcePath(std::string value) {
			resource_path = value;
		}

		std::string CResourceLoadable::GetResourcePath() {
			return resource_path;
		}

		void CResourceLoadable::PackLoadResource(NSEngine::NSNetworks::CPacket* packet) {
			*packet << resource_path;
		}

		void CResourceLoadable::UnpackLoadResource(NSEngine::NSNetworks::CPacket* packet) {
			*packet >> resource_path;
			LoadResource();
		}

	}
}
