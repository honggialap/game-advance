#include "engine/component/stat/team.h"

namespace NSEngine {
	namespace NSComponent {

		CTeam::CTeam() 
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CTeam::~CTeam() {
		}

		void CTeam::SetTeam(ETeam value) {
			team = value;
		}

		ETeam CTeam::GetTeam() {
			return team;
		}

		void CTeam::JsonLoad(nlohmann::json& data) {
			if (data.contains("team")) {
				uint32_t team_value = data.at("team");
				SetTeam(ETeam(team_value));
			}
		}

		void CTeam::PackLoad(NSNetworks::CPacket* packet) {
			uint32_t send_team = uint32_t(team);
			*packet << send_team;
		}

		void CTeam::UnpackLoad(NSNetworks::CPacket* packet) {
			uint32_t receive_team;
			*packet >> receive_team;
			SetTeam(NSEngine::ETeam(receive_team));
		}

	}
}
