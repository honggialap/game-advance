#pragma once
#ifndef __ENGINE__COMPONENT__UPDATABLE_H__
#define __ENGINE__COMPONENT__UPDATABLE_H__

#include "engine/common.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CUpdatable 
			: public CDataLoadable	
			, public CNetworksLoadable {
		protected:
			bool is_active;

		public:
			CUpdatable();
			virtual ~CUpdatable() = 0;

			void SetActive(bool value);
			bool IsActive();

			virtual void Update(float elapsed) = 0;

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CUpdatable* pUpdatable;

	}
}

#endif // !__ENGINE__COMPONENT__UPDATABLE_H__
