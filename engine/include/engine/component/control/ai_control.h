#pragma once
#ifndef __ENGINE__COMPONENT__AI_CONTROL_H__
#define __ENGINE__COMPONENT__AI_CONTROL_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CAIControl
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			uint32_t wave_queue_id = 0u;
			uint32_t seed = 0u;

		public:
			CAIControl();
			virtual ~CAIControl() = 0;

			void SetSeed(uint32_t value);
			uint32_t GetSeed();

			void SetWave(uint32_t value);
			uint32_t GetWave();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CAIControl* pAIControl;

	}
}

#endif // !__ENGINE__COMPONENT__AI_CONTROL_H__
