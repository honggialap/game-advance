#ifndef __ENGINE__COMPONENT__SHOOT_H__
#define __ENGINE__COMPONENT__SHOOT_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CShoot 
			: public CLoadByJson	
			, public CLoadByNetworks
		{
		protected:
			float default_recharge_time = 0.0f;
			float recharge_time = 0.0f;

		public:
			CShoot();
			virtual ~CShoot() = 0;
			
			void SetDefaultRechargeTime(float value);
			float GetDefaultRechargeTime();

			void SetRechargeTime(float value);
			float GetRechargeTime();

			void SetRateOfFire(float rate_of_fire_value);
			void RestartRechargeTime();

			void UpdateRechargeTime(float elapsed);
			bool IsShootable();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CShoot* pShoot;

	}
}

#endif // !__ENGINE__COMPONENT__SHOOT_H__
