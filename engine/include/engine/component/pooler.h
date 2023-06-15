#pragma once
#ifndef __ENGINE__COMPONENT__POOLER_H__
#define __ENGINE__COMPONENT__POOLER_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CPooler {
		protected:
		public:
			CPooler();
			virtual ~CPooler() = 0;
		};
		typedef CPooler* pPooler;

	}
}

#endif // !__ENGINE__COMPONENT__POOLER_H__
