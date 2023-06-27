#pragma once
#ifndef __ENGINE__COMPONENT__SPRITE_H__
#define __ENGINE__COMPONENT__SPRITE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CSprite {
		protected:
			sf::Texture texture;
			sf::Sprite sprite;

		public:
			CSprite();
			virtual ~CSprite() = 0;
		};
		typedef CSprite* pSprite;

	}
}

#endif // !__ENGINE__COMPONENT__SPRITE_H__
