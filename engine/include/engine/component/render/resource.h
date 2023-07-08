#pragma once
#ifndef __ENGINE__COMPONENT__RESOURCE_H__
#define __ENGINE__COMPONENT__RESOURCE_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CResource
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			std::string resource_path;

		public:
			CResource();
			virtual ~CResource() = 0;

			void SetResourcePath(std::string value);
			std::string GetResourcePath();

			virtual void LoadResource() = 0;
			virtual void UnloadResource() = 0;

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CResource* pResource;

	}
}

#endif // !__ENGINE__COMPONENT__RESOURCE_H__
