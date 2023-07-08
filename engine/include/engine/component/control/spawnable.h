#ifndef __ENGINE__COMPONENT__SPAWNABLE_H__
#define __ENGINE__COMPONENT__SPAWNABLE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CSpawnable {
		protected:
			bool is_spawned = false;

		public:
			CSpawnable();
			virtual ~CSpawnable() = 0;

			void SetIsSpawned(bool value);
			bool IsSpawned();

			virtual void Spawn() = 0;
			virtual void Despawn() = 0;
		};
		typedef CSpawnable* pSpawnable;

	}
}

#endif // !__ENGINE__COMPONENT__SPAWNABLE_H__
