#include "engine/component/loadable.h"

namespace NSEngine {
	namespace NSComponent {

		CLoadable::CLoadable() {
		}

		CLoadable::~CLoadable() {
		}

		void CLoadable::SetResourcePath(std::string value) {
			resource_path = value;
		}

		std::string CLoadable::GetResourcePath() {
			return resource_path;
		}

	}
}
