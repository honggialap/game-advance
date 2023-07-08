#ifndef __ENGINE__COMPONENT__DIRECTION_H__
#define __ENGINE__COMPONENT__DIRECTION_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CDirection 
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			bool facing_left = false;
			bool facing_up = false;

		public:
			CDirection();
			virtual ~CDirection() = 0;

			void SetDirection(bool left, bool up);
			void GetDirection(bool& left, bool& up);

			void SetFacingLeft(bool value);
			bool IsFacingLeft();

			void SetFacingUp(bool value);
			bool IsFacingUp();
			
			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CDirection* pDirection;

	}
}




#endif // !__ENGINE__COMPONENT__DIRECTION_H__
