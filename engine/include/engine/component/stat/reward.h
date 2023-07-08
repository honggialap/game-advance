#ifndef __ENGINE__COMPONENT__REWARD_H__
#define __ENGINE__COMPONENT__REWARD_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CReward
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			int32_t reward = 0;

		public:
			CReward();
			virtual ~CReward() = 0;

			void SetReward(int32_t value);
			int32_t GetReward();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CReward* pReward;

	}
}

#endif // !__ENGINE__COMPONENT__REWARD_H__
