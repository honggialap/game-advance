#ifndef __ENGINE__COMPONENT__HEALTH_H__
#define __ENGINE__COMPONENT__HEALTH_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CHealth
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			int32_t health = 0;

		public:
			CHealth();
			virtual ~CHealth() = 0;

			void SetHealth(int32_t value);
			int32_t GetHealth();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CHealth* pHealth;

	}
}

#endif // !__ENGINE__COMPONENT__HEALTH_H__
