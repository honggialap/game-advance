#include "engine/component/stat/reward.h"

namespace NSEngine {
	namespace NSComponent {

		CReward::CReward()
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CReward::~CReward() {
		}

		void CReward::SetReward(int32_t value) {
			reward = value;
		}

		int32_t CReward::GetReward() {
			return reward;
		}

		void CReward::JsonLoad(nlohmann::json& data) {
			if (data.contains("reward")) {
				int32_t reward_value = data.at("reward");
				SetReward(reward_value);
			}
		}

		void CReward::PackLoad(NSNetworks::CPacket* packet) {
			int32_t send_reward = GetReward();
			*packet << send_reward;
		}

		void CReward::UnpackLoad(NSNetworks::CPacket* packet) {
			int32_t receive_reward;
			*packet >> receive_reward;
			SetReward(receive_reward);
		}

	}
}
