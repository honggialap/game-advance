#pragma once
#ifndef __ENGINE__COMPONENT__RENDERABLE_H__
#define __ENGINE__COMPONENT__RENDERABLE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CRenderable {
		protected:
		public:
			CRenderable();
			virtual ~CRenderable() = 0;

			virtual void Render(sf::RenderWindow& window) = 0;
		};
		typedef CRenderable* pRenderable;

	}
}

#endif // !__ENGINE__COMPONENT__RENDERABLE_H__
