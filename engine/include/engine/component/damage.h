#pragma once
#ifndef __ENGINE__COMPONENT__DAMAGE_H__
#define __ENGINE__COMPONENT__DAMAGE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CDamage {
		protected:
			uint32_t damage;

		public:
			CDamage();
			virtual ~CDamage() = 0;

			void SetDamage(uint32_t value);
			uint32_t GetDamage();
		};
		typedef CDamage* pDamage;

	}
}

#endif // !__ENGINE__COMPONENT__DAMAGE_H__
