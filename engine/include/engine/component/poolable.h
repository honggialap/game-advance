#pragma once
#ifndef __ENGINE__COMPONENT__POOLABLE_H__
#define __ENGINE__COMPONENT__POOLABLE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CPoolable {
		protected:
		public:
			CPoolable();
			virtual ~CPoolable() = 0;
		};
		typedef CPoolable* pPoolable;

	}
}

#endif // !__ENGINE__COMPONENT__POOLABLE_H__
