#include "engine/component/control/shoot.h"

namespace NSEngine {
	namespace NSComponent {

		CShoot::CShoot()
			: CLoadByJson()
			, CLoadByNetworks()
		{
		}

		CShoot::~CShoot() {
		}

		void CShoot::SetDefaultRechargeTime(float value) {
			default_recharge_time = value;
		}

		float CShoot::GetDefaultRechargeTime() {
			return default_recharge_time;
		}

		void CShoot::SetRechargeTime(float value) {
			recharge_time = value;
		}

		float CShoot::GetRechargeTime() {
			return recharge_time;
		}

		void CShoot::SetRateOfFire(float rate_of_fire_value) {
			default_recharge_time = 1000.0f / rate_of_fire_value;
		}

		void CShoot::RestartRechargeTime() {
			recharge_time = default_recharge_time;
		}

		void CShoot::UpdateRechargeTime(float elapsed) {
			if (recharge_time >= 0.0f) {
				recharge_time -= elapsed;
			}
		}

		bool CShoot::IsShootable() {
			return recharge_time <= 0.0f;
		}

		void CShoot::JsonLoad(nlohmann::json& data) {
			if (data.contains("rate_of_fire")) {
				float rate_of_fire_value = data.at("rate_of_fire");
				SetRateOfFire(rate_of_fire_value);
				RestartRechargeTime();
			}
		}

		void CShoot::PackLoad(NSNetworks::CPacket* packet) {
			float send_default_recharge_time = GetDefaultRechargeTime();
			*packet << send_default_recharge_time;
		}

		void CShoot::UnpackLoad(NSNetworks::CPacket* packet) {
			float receive_default_recharge_time;
			*packet >> receive_default_recharge_time;
			SetDefaultRechargeTime(receive_default_recharge_time);
			RestartRechargeTime();
		}

	}
}