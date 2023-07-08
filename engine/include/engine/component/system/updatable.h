#pragma once
#ifndef __ENGINE__COMPONENT__UPDATABLE_H__
#define __ENGINE__COMPONENT__UPDATABLE_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CUpdatable 
			: public CLoadByJson	
			, public CLoadByNetworks
		{
		protected:
			bool is_active = false;

		public:
			CUpdatable();
			virtual ~CUpdatable() = 0;

			void SetActive(bool value);
			bool IsActive();

			virtual void Update(float elapsed) = 0;

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CUpdatable* pUpdatable;

	}
}

#endif // !__ENGINE__COMPONENT__UPDATABLE_H__
