#pragma once
#ifndef __ENGINE__COMPONENT__DEFEND_LEVEL_H__
#define __ENGINE__COMPONENT__DEFEND_LEVEL_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CDefendLevel
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			int32_t default_defend_level = 0;
			int32_t min_defend_level = 0;
			int32_t max_defend_level = 0;
			int32_t defend_level = 0;

		public:
			CDefendLevel();
			virtual ~CDefendLevel() = 0;

			void SetDefaultDefendLevel(int32_t value);
			int32_t GetDefaultDefendLevel();

			void SetMinDefendLevel(int32_t value);
			int32_t GetMinDefendLevel();

			void SetMaxDefendLevel(int32_t value);
			int32_t GetMaxDefendLevel();

			void SetDefendLevel(int32_t value);
			int32_t GetDefendLevel();

			void IncreaseDefendLevel(int32_t value);
			void DecreaseDefendLevel(int32_t value);
			void ResetDefendLevel();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CDefendLevel* pDefendLevel;

	}
}

#endif // !__ENGINE__COMPONENT__DEFEND_LEVEL_H__
