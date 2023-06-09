#pragma once
#ifndef __ENGINE__COMPONENT__UPDATABLE_H__
#define __ENGINE__COMPONENT__UPDATABLE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CUpdatable {
		protected:
		public:
			CUpdatable();
			virtual ~CUpdatable() = 0;

			virtual void Update(float elapsed) = 0;
		};
		typedef CUpdatable* pUpdatable;

	}
}

#endif // !__ENGINE__COMPONENT__UPDATABLE_H__
