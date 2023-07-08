#include "engine/component/stat/defend_level.h"

namespace NSEngine {
	namespace NSComponent {

		CDefendLevel::CDefendLevel() {
		}

		CDefendLevel::~CDefendLevel() {
		}

		void CDefendLevel::SetDefaultDefendLevel(int32_t value) {
			default_defend_level = value;
		}

		int32_t CDefendLevel::GetDefaultDefendLevel() {
			return default_defend_level;
		}

		void CDefendLevel::SetMaxDefendLevel(int32_t value) {
			max_defend_level = value;
		}

		int32_t CDefendLevel::GetMaxDefendLevel() {
			return max_defend_level;
		}

		void CDefendLevel::SetMinDefendLevel(int32_t value) {
			min_defend_level = value;
		}

		int32_t CDefendLevel::GetMinDefendLevel() {
			return min_defend_level;
		}

		void CDefendLevel::SetDefendLevel(int32_t value) {
			defend_level = value;
			if (defend_level > max_defend_level) {
				defend_level = max_defend_level;
			}
			else if (defend_level < min_defend_level) {
				defend_level = min_defend_level;
			}
		}

		int32_t CDefendLevel::GetDefendLevel() {
			return defend_level;
		}

		void CDefendLevel::IncreaseDefendLevel(int32_t value) {
			defend_level += value;
			if (defend_level > max_defend_level) {
				defend_level = max_defend_level;
			}
		}

		void CDefendLevel::DecreaseDefendLevel(int32_t value) {
			defend_level -= value;
			if (defend_level < min_defend_level) {
				defend_level = min_defend_level;
			}
		}

		void CDefendLevel::ResetDefendLevel() {
			defend_level = default_defend_level;
		}

		void CDefendLevel::JsonLoad(nlohmann::json& data) {
			if (data.contains("defend")) {
				auto& defend_data = data.at("defend");
				int32_t max_defend_value = defend_data.at("max");
				int32_t min_defend_value = defend_data.at("min");
				int32_t default_defend_value = defend_data.at("default");

				SetMaxDefendLevel(max_defend_value);
				SetMinDefendLevel(min_defend_value);
				SetDefaultDefendLevel(default_defend_value);
				ResetDefendLevel();
			}
		}

		void CDefendLevel::PackLoad(NSNetworks::CPacket* packet) {
			int32_t send_max = GetMaxDefendLevel();
			*packet << send_max;

			int32_t send_min = GetMinDefendLevel();
			*packet << send_min;

			int32_t send_default = GetDefaultDefendLevel();
			*packet << send_default;
		}

		void CDefendLevel::UnpackLoad(NSNetworks::CPacket* packet) {
			int32_t receive_max;
			*packet >> receive_max;
			SetMaxDefendLevel(receive_max);

			int32_t receive_min;
			*packet >> receive_min;
			SetMinDefendLevel(receive_min);

			int32_t receive_default;
			*packet >> receive_default;
			SetDefaultDefendLevel(receive_default);

			ResetDefendLevel();
		}

	}
}