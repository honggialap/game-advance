#pragma once
#ifndef __ENGINE__COMPONENT__MOVEMENT_H__
#define __ENGINE__COMPONENT__MOVEMENT_H__

#include "engine/common.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CMovement
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			sf::Vector2i movement;
			float speed;

		public:
			CMovement();
			virtual ~CMovement() = 0;

			void SetMovement(int32_t x, int32_t y);
			sf::Vector2i GetMovement();
			void GetMovement(int32_t& x, int32_t& y);

			void SetSpeed(float value);
			float GetSpeed();

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CMovement* pMovement;

	}
}

#endif // !__ENGINE__COMPONENT__MOVEMENT_H__
