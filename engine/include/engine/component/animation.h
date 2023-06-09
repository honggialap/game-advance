#pragma once
#ifndef __ENGINE__COMPONENT__ANIMATION_H__
#define __ENGINE__COMPONENT__ANIMATION_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CAnimation {
		protected:
		public:
			CAnimation();
			virtual ~CAnimation() = 0;
		};
		typedef CAnimation* pAnimation;

	}
}

#endif // !__ENGINE__COMPONENT__ANIMATION_H__
