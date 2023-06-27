#pragma once
#ifndef __ENGINE__COMPONENT__HEALTH_H__
#define __ENGINE__COMPONENT__HEALTH_H__

#include "engine/common.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CHealth 
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			bool is_alive = false;
			float max_health = 0.0f;
			float health = 0.0f;

		public:
			CHealth();
			virtual ~CHealth() = 0;

			void ActivateHealth(float max_health_value);
			void Heal(float healing_value);
			void Damaged(float damaged_value);
			void BoostMaxHealth(float boost_value);
			bool IsAlive();

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CHealth* pHealth;

	}
}

#endif // !__ENGINE__COMPONENT__HEALTH_H__
