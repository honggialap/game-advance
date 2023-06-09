#include "engine/component/player_control.h"

namespace NSEngine {
	namespace NSComponent {

		CPlayerControl::CPlayerControl() {
		}

		CPlayerControl::~CPlayerControl() {
		}

		void CPlayerControl::SetPlayerControl(bool value) {
			is_player_controlled = value;
		}

		bool CPlayerControl::IsPlayerControlled() {
			return is_player_controlled;
		}

		void CPlayerControl::SetPlayerId(uint32_t value) {
			player_id = value;
		}

		uint32_t CPlayerControl::GetPlayerId() {
			return player_id;
		}

	}
}
