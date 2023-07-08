#pragma once
#ifndef __ENGINE__COMPONENT__INPUT_HANDLER_H__
#define __ENGINE__COMPONENT__INPUT_HANDLER_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CInputHandler {
		protected:
		public:
			CInputHandler();
			virtual ~CInputHandler() = 0;

			virtual void HandleInput(uint32_t tick) = 0;
		};
		typedef CInputHandler* pInputHandler;

	}
}

#endif // !__ENGINE__COMPONENT__INPUT_HANDLER_H__
