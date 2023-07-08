#ifndef __ENGINE__COMPONENT__LOAD_BY_NETWORKS_H__
#define __ENGINE__COMPONENT__LOAD_BY_NETWORKS_H__

#include "engine/common.h"
#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSComponent {

		class CLoadByNetworks {
		protected:
		public:
			CLoadByNetworks();
			virtual ~CLoadByNetworks() = 0;

			virtual void PackLoad(NSNetworks::CPacket* packet) = 0;
			virtual void UnpackLoad(NSNetworks::CPacket* packet) = 0;
		};
		typedef CLoadByNetworks* pLoadByNetworks;

	}
}

#endif // !__ENGINE__COMPONENT__LOAD_BY_NETWORKS_H__
