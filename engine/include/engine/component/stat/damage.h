#ifndef __ENGINE__COMPONENT__DAMAGE_H__
#define __ENGINE__COMPONENT__DAMAGE_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CDamage
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			int32_t damage = 0;

		public:
			CDamage();
			virtual ~CDamage() = 0;

			void SetDamage(int32_t value);
			int32_t GetDamage();

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CDamage* pDamage;

	}
}

#endif // !__ENGINE__COMPONENT__DAMAGE_H__
