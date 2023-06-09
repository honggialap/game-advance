#pragma once
#ifndef __ENGINE__COMPONENT__HEALTH_H__
#define __ENGINE__COMPONENT__HEALTH_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CHealth {
		protected:
			int32_t max_health;
			int32_t health;

		public:
			CHealth();
			virtual ~CHealth() = 0;

			void SetMaxHealth(int32_t value);
			int32_t GetMaxHealth();

			void SetHealth(int32_t value);
			int32_t GetHealth();
		};
		typedef CHealth* pHealth;

	}
}

#endif // !__ENGINE__COMPONENT__HEALTH_H__
