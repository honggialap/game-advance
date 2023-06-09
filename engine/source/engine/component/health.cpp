#include "engine/component/health.h"

namespace NSEngine {
	namespace NSComponent {

		CHealth::CHealth() {
		}

		CHealth::~CHealth() {
		}

		void CHealth::SetMaxHealth(int32_t value) {
			max_health = value;
		}

		int32_t CHealth::GetMaxHealth() {
			return max_health;
		}

		void CHealth::SetHealth(int32_t value) {
			health = value;
		}

		int32_t CHealth::GetHealth() {
			return health;
		}
		
	}
}
