#pragma once
#ifndef __ENGINE__COMPONENT__MOVE_H__
#define __ENGINE__COMPONENT__MOVE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CMove {
		protected:
			sf::Vector2i movement;

		public:
			CMove();
			virtual ~CMove() = 0;

			void SetMovement(int32_t x, int32_t y);
			sf::Vector2i GetMovement();
			void GetMovement(int32_t& x, int32_t& y);
		};
		typedef CMove* pMove;

	}
}

#endif // !__ENGINE__COMPONENT__MOVE_H__
