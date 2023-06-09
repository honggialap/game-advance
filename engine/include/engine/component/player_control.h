#pragma once
#ifndef __ENGINE__COMPONENT__PLAYER_CONTROL_H__
#define __ENGINE__COMPONENT__PLAYER_CONTROL_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CPlayerControl {
		protected:
			bool is_player_controlled;
			uint32_t player_id;

		public:
			CPlayerControl();
			virtual ~CPlayerControl() = 0;

			void SetPlayerControl(bool value);
			bool IsPlayerControlled();

			void SetPlayerId(uint32_t value);
			uint32_t GetPlayerId();

			virtual void HandleInput(uint32_t tick) = 0;
		};
		typedef CPlayerControl* pPlayerControl;

	}
}

#endif // !__ENGINE__COMPONENT__PLAYER_CONTROL_H__
