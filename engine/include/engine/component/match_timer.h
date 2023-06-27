#pragma once
#ifndef __ENGINE__COMPONENT__MATCH_TIMER_H__
#define __ENGINE__COMPONENT__MATCH_TIMER_H__

#include "engine/common.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CMatchTimer
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			float match_time = 0.0f;

		public:
			CMatchTimer();
			virtual ~CMatchTimer() = 0;

			void SetMatchTime(float value);
			float GetMatchTime();

			void UpdateMatchTime(float elapsed);
			bool IsMatchTimeUp();

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CMatchTimer* pMatchTimer;

	}
}

#endif // !__ENGINE__COMPONENT__MATCH_TIMER_H__
