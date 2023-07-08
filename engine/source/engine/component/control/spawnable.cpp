#include "engine/component/control/spawnable.h"

namespace NSEngine {
	namespace NSComponent {

		CSpawnable::CSpawnable() {
		}

		CSpawnable::~CSpawnable() {
		}

		void CSpawnable::SetIsSpawned(bool value) {
			is_spawned = value;
		}

		bool CSpawnable::IsSpawned() {
			return is_spawned;
		}

	}

}