#pragma once
#ifndef __ENGINE__COMPONENT__TEAM_H__
#define __ENGINE__COMPONENT__TEAM_H__

#include "engine/common.h"
#include "engine/shared.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CTeam 
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			ETeam team = ETeam::INVALID_TEAM;

		public:
			CTeam();
			virtual ~CTeam() = 0;

			void SetTeam(ETeam value);
			ETeam GetTeam();

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CTeam* pTeam;

	}
}

#endif // !__ENGINE__COMPONENT__TEAM_H__
