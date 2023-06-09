#pragma once
#ifndef __ENGINE__COMPONENT__TEAM_H__
#define __ENGINE__COMPONENT__TEAM_H__

#include "engine/common.h"
#include "engine/shared.h"

namespace NSEngine {
	namespace NSComponent {

		class CTeam {
		protected:
			ETeam team = ETeam::INVALID_TEAM;

		public:
			CTeam();
			virtual ~CTeam() = 0;

			void SetTeam(ETeam value);
			ETeam GetTeam();
		};

	}
}

#endif // !__ENGINE__COMPONENT__TEAM_H__
