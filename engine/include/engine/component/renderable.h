#pragma once
#ifndef __ENGINE__COMPONENT__RENDERABLE_H__
#define __ENGINE__COMPONENT__RENDERABLE_H__

#include "engine/common.h"
#include "engine/component/data_loadable.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSComponent {

		class CRenderable
			: public CDataLoadable
			, public CNetworksLoadable {
		protected:
			bool is_visible;
			uint32_t layer;

		public:
			CRenderable();
			virtual ~CRenderable() = 0;

			void SetVisible(bool value);
			bool IsVisible();

			void SetLayer(uint32_t value);
			uint32_t GetLayer();

			virtual void Render(sf::RenderWindow& window) = 0;

			void LoadData(nlohmann::json& data) final;

			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CRenderable* pRenderable;

	}
}

#endif // !__ENGINE__COMPONENT__RENDERABLE_H__
