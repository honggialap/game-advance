#include "engine/component/match_timer.h"

namespace NSEngine {
	namespace NSComponent {

		CMatchTimer::CMatchTimer()
			: CDataLoadable()
			, CNetworksLoadable() {
		}

		CMatchTimer::~CMatchTimer() {
		}

		void CMatchTimer::SetMatchTime(float value) {
			match_time = value;
		}

		float CMatchTimer::GetMatchTime() {
			return match_time;
		}

		void CMatchTimer::UpdateMatchTime(float elapsed) {
			match_time -= elapsed;
		}

		bool CMatchTimer::IsMatchTimeUp() {
			return match_time <= 0.0f;
		}

		void CMatchTimer::LoadData(nlohmann::json& data) {
			if (data.contains("match_time")) {
				float match_time_value = data.at("match_time");
				SetMatchTime(match_time_value);
			}
		}

		void CMatchTimer::PackLoad(NSNetworks::CPacket* packet) {
			float send_match_time = GetMatchTime();
			*packet << send_match_time;
		}

		void CMatchTimer::UnpackLoad(NSNetworks::CPacket* packet) {
			float receive_match_time;
			*packet >> receive_match_time;
			SetMatchTime(receive_match_time);
		}

	}
}