#pragma once
#ifndef __ENGINE__COMPONENT__DAMAGE_H__
#define __ENGINE__COMPONENT__DAMAGE_H__

#include "engine/common.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CDamage 
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			float damage = 0.0f;

		public:
			CDamage();
			virtual ~CDamage() = 0;

			void SetDamage(float value);
			float GetDamage();

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CDamage* pDamage;

	}
}

#endif // !__ENGINE__COMPONENT__DAMAGE_H__
