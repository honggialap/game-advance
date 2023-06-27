#pragma once
#ifndef __ENGINE__COMPONENT__ANIMATION_H__
#define __ENGINE__COMPONENT__ANIMATION_H__

#include "engine/common.h"
#include "engine/component/sprite.h"

namespace NSEngine {
	namespace NSComponent {

		class CAnimation
			: public CSprite {
		protected:
		public:
			CAnimation();
			virtual ~CAnimation() = 0;
		};
		typedef CAnimation* pAnimation;

	}
}

#endif // !__ENGINE__COMPONENT__ANIMATION_H__
