#pragma once
#ifndef __ENGINE__COMPONENT__AI_CONTROL_H__
#define __ENGINE__COMPONENT__AI_CONTROL_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CAIControl {
		protected:
		public:
			CAIControl();
			virtual ~CAIControl() = 0;
		};
		typedef CAIControl* pAIControl;

	}
}

#endif // !__ENGINE__COMPONENT__AI_CONTROL_H__
