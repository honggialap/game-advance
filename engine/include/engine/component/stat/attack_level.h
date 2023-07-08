#pragma once
#ifndef __ENGINE__COMPONENT__ATTACK_LEVEL_H__
#define __ENGINE__COMPONENT__ATTACK_LEVEL_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CAttackLevel
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			int32_t default_attack_level = 0;
			int32_t min_attack_level = 0;
			int32_t max_attack_level = 0;
			int32_t attack_level = 0;

		public:
			CAttackLevel();
			virtual ~CAttackLevel() = 0;

			void SetDefaultAttackLevel(int32_t value);
			int32_t GetDefaultAttackLevel();

			void SetMinAttackLevel(int32_t value);
			int32_t GetMinAttackLevel();

			void SetMaxAttackLevel(int32_t value);
			int32_t GetMaxAttackLevel();

			void SetAttackLevel(int32_t value);
			int32_t GetAttackLevel();

			void IncreaseAttackLevel(int32_t value);
			void DecreaseAttackLevel(int32_t value);
			void ResetAttackLevel();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CAttackLevel* pAttackLevel;

	}
}

#endif // !__ENGINE__COMPONENT__ATTACK_LEVEL_H__
