#ifndef __ENGINE__COMPONENT__SPEED_H__
#define __ENGINE__COMPONENT__SPEED_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CSpeed
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			float speed = 0;

		public:
			CSpeed();
			virtual ~CSpeed() = 0;

			void SetSpeed(float value);
			float GetSpeed();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CSpeed* pSpeed;

	}
}

#endif // !__ENGINE__COMPONENT__SPEED_H__
