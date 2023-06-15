#pragma once
#ifndef __ENGINE__COMPONENT__RESOURCE_LOADABLE_H__
#define __ENGINE__COMPONENT__RESOURCE_LOADABLE_H__

#include "engine/common.h"
#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSComponent {

		class CResourceLoadable {
		protected:
			std::string resource_path;

		public:
			CResourceLoadable();
			virtual ~CResourceLoadable() = 0;

			void SetResourcePath(std::string value);
			std::string GetResourcePath();

			void PackLoadResource(NSEngine::NSNetworks::CPacket* packet);
			void UnpackLoadResource(NSEngine::NSNetworks::CPacket* packet);

			virtual void LoadResource() = 0;
			virtual void UnloadResource() = 0;
		};
		typedef CResourceLoadable* pResourceLoadable;

	}
}

#endif // !__ENGINE__COMPONENT__RESOURCE_LOADABLE_H__
