#pragma once
#ifndef __ENGINE__COMPONENT__PLAYER_CONTROL_H__
#define __ENGINE__COMPONENT__PLAYER_CONTROL_H__

#include "engine/common.h"
#include "engine/component/input_handler.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CPlayerControl 
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			bool is_player_controlled = false;
			uint32_t player_id = 0u;

		public:
			CPlayerControl();
			virtual ~CPlayerControl() = 0;

			void AssignPlayerControl(uint32_t player_id_value);
			bool IsPlayerControlled();

			void SetPlayerId(uint32_t value);
			uint32_t GetPlayerId();

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CPlayerControl* pPlayerControl;

	}
}

#endif // !__ENGINE__COMPONENT__PLAYER_CONTROL_H__
