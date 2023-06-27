#include "engine/component/player_control.h"

namespace NSEngine {
	namespace NSComponent {

		CPlayerControl::CPlayerControl()
			: CDataLoadable()
			, CNetworksLoadable() {
		}

		CPlayerControl::~CPlayerControl() {
		}

		void CPlayerControl::AssignPlayerControl(uint32_t player_id_value) {
			if (player_id == player_id_value) {
				is_player_controlled = true;
			}
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

		void CPlayerControl::LoadData(nlohmann::json& data) {
			if (data.contains("player_id")) {
				uint32_t player_id_value = data.at("player_id");
				SetPlayerId(player_id_value);
			}
		}

		void CPlayerControl::PackLoad(NSNetworks::CPacket* packet) {
			uint32_t send_player_id = GetPlayerId();
			*packet << send_player_id;
		}

		void CPlayerControl::UnpackLoad(NSNetworks::CPacket* packet) {
			uint32_t receive_player_id;
			*packet >> receive_player_id;
			SetPlayerId(receive_player_id);
		}

	}
}
