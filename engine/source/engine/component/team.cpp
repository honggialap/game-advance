#include "engine/component/team.h"

namespace NSEngine {
	namespace NSComponent {

		CTeam::CTeam() {
		}

		CTeam::~CTeam() {
		}

		void CTeam::SetTeam(ETeam value) {
			team = value;
		}

		ETeam CTeam::GetTeam() {
			return team;
		}

	}
}
