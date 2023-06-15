#pragma once
#ifndef __ENGINE__COMPONENT__NETWORKS_LOADABLE_H__
#define __ENGINE__COMPONENT__NETWORKS_LOADABLE_H__

#include "engine/common.h"
#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSComponent {

		class CNetworksLoadable {
		protected:
		public:
			CNetworksLoadable();
			virtual ~CNetworksLoadable() = 0;

			virtual void PackNetworksLoadPacket(NSEngine::NSNetworks::CPacket* packet) = 0;
			virtual void UnpackNetworksLoadPacket(NSEngine::NSNetworks::CPacket* packet) = 0;
		};
		typedef CNetworksLoadable* pNetworksLoadable;

	}
}

#endif // !__ENGINE__COMPONENT__NETWORKS_LOADABLE_H__
