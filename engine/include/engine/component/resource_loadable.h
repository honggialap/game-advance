#pragma once
#ifndef __ENGINE__COMPONENT__RESOURCE_LOADABLE_H__
#define __ENGINE__COMPONENT__RESOURCE_LOADABLE_H__

#include "engine/common.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CResourceLoadable
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			std::string resource_path;

		public:
			CResourceLoadable();
			virtual ~CResourceLoadable() = 0;

			void SetResourcePath(std::string value);
			std::string GetResourcePath();

			virtual void LoadResource() = 0;
			virtual void UnloadResource() = 0;

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CResourceLoadable* pResourceLoadable;

	}
}

#endif // !__ENGINE__COMPONENT__RESOURCE_LOADABLE_H__
