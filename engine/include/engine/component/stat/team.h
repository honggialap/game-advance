#pragma once
#ifndef __ENGINE__COMPONENT__TEAM_H__
#define __ENGINE__COMPONENT__TEAM_H__

#include "engine/common.h"
#include "engine/shared.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CTeam 
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			ETeam team = ETeam::INVALID_TEAM;

		public:
			CTeam();
			virtual ~CTeam() = 0;

			void SetTeam(ETeam value);
			ETeam GetTeam();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CTeam* pTeam;

	}
}

#endif // !__ENGINE__COMPONENT__TEAM_H__
