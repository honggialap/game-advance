#pragma once
#ifndef __ENGINE__COMPONENT__POWER_LEVEL_H__
#define __ENGINE__COMPONENT__POWER_LEVEL_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CPowerLevel
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			int32_t default_power_level = 0;
			int32_t min_power_level = 0;
			int32_t max_power_level = 0;
			int32_t power_level = 0;

		public:
			CPowerLevel();
			virtual ~CPowerLevel() = 0;

			void SetDefaultPowerLevel(int32_t value);
			int32_t GetDefaultPowerLevel();

			void SetMinPowerLevel(int32_t value);
			int32_t GetMinPowerLevel();

			void SetMaxPowerLevel(int32_t value);
			int32_t GetMaxPowerLevel();

			void SetPowerLevel(int32_t value);
			int32_t GetPowerLevel();

			void IncreasePowerLevel(int32_t value);
			void DecreasePowerLevel(int32_t value);
			void ResetPowerLevel();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CPowerLevel* pPowerLevel;

	}
}

#endif // !__ENGINE__COMPONENT__POWER_LEVEL_H__
