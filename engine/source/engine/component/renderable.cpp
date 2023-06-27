#include "engine/component/renderable.h"

namespace NSEngine {
	namespace NSComponent {

		CRenderable::CRenderable()
			: CDataLoadable()	
			, CNetworksLoadable()
			, layer(0u)
			, is_visible(true) {
		}

		CRenderable::~CRenderable() {
		}

		void CRenderable::SetVisible(bool value) {
			is_visible = value;
		}

		bool CRenderable::IsVisible() {
			return is_visible;
		}

		void CRenderable::SetLayer(uint32_t value) {
			layer = value;
		}

		uint32_t CRenderable::GetLayer() {
			return layer;
		}

		void CRenderable::LoadData(nlohmann::json& data) {
			if (
				data.contains("layer")
				&& data.contains("visible")
				) {
				uint32_t layer_value = data.at("layer");
				SetLayer(layer_value);

				bool visible_value = data.at("visible");
				SetVisible(visible_value);
			}
		}

		void CRenderable::PackLoad(NSNetworks::CPacket* packet) {
			uint32_t send_layer = GetLayer();
			*packet << send_layer;

			bool send_visible = IsVisible();
			*packet << send_visible;
		}

		void CRenderable::UnpackLoad(NSNetworks::CPacket* packet) {
			uint32_t receive_layer;
			*packet >> receive_layer;
			SetLayer(receive_layer);

			bool receive_visible;
			*packet >> receive_visible;
			SetVisible(receive_visible);
		}

	}
}
