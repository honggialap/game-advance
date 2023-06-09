#include "engine/component/damage.h"

namespace NSEngine {
	namespace NSComponent {

		CDamage::CDamage() {
		}

		CDamage::~CDamage() {
		}

		void CDamage::SetDamage(uint32_t value) {
			damage = value;
		}

		uint32_t CDamage::GetDamage() {
			return damage;
		}

	}
}
