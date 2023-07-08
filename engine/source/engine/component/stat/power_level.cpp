#include "engine/component/stat/power_level.h"

namespace NSEngine {
	namespace NSComponent {

		CPowerLevel::CPowerLevel() {
		}

		CPowerLevel::~CPowerLevel() {
		}

		void CPowerLevel::SetDefaultPowerLevel(int32_t value) {
			default_power_level = value;
		}

		int32_t CPowerLevel::GetDefaultPowerLevel() {
			return default_power_level;
		}

		void CPowerLevel::SetMaxPowerLevel(int32_t value) {
			max_power_level = value;
		}

		int32_t CPowerLevel::GetMaxPowerLevel() {
			return max_power_level;
		}

		void CPowerLevel::SetMinPowerLevel(int32_t value) {
			min_power_level = value;
		}

		int32_t CPowerLevel::GetMinPowerLevel() {
			return min_power_level;
		}

		void CPowerLevel::SetPowerLevel(int32_t value) {
			power_level = value;
			if (power_level > max_power_level) {
				power_level = max_power_level;
			}
			else if (power_level < min_power_level) {
				power_level = min_power_level;
			}
		}

		int32_t CPowerLevel::GetPowerLevel() {
			return power_level;
		}

		void CPowerLevel::IncreasePowerLevel(int32_t value) {
			power_level += value;
			if (power_level > max_power_level) {
				power_level = max_power_level;
			}
		}

		void CPowerLevel::DecreasePowerLevel(int32_t value) {
			power_level -= value;
			if (power_level < min_power_level) {
				power_level = min_power_level;
			}
		}

		void CPowerLevel::ResetPowerLevel() {
			power_level = default_power_level;
		}

		void CPowerLevel::JsonLoad(nlohmann::json& data) {
			if (data.contains("power")) {
				auto& power_data = data.at("power");
				int32_t max_power_value = power_data.at("max");
				int32_t min_power_value = power_data.at("min");
				int32_t default_power_value = power_data.at("default");

				SetMaxPowerLevel(max_power_value);
				SetMinPowerLevel(min_power_value);
				SetDefaultPowerLevel(default_power_value);
				ResetPowerLevel();
			}
		}

		void CPowerLevel::PackLoad(NSNetworks::CPacket* packet) {
			int32_t send_max = GetMaxPowerLevel();
			*packet << send_max;

			int32_t send_min = GetMinPowerLevel();
			*packet << send_min;

			int32_t send_default = GetDefaultPowerLevel();
			*packet << send_default;
		}

		void CPowerLevel::UnpackLoad(NSNetworks::CPacket* packet) {
			int32_t receive_max;
			*packet >> receive_max;
			SetMaxPowerLevel(receive_max);

			int32_t receive_min;
			*packet >> receive_min;
			SetMinPowerLevel(receive_min);

			int32_t receive_default;
			*packet >> receive_default;
			SetDefaultPowerLevel(receive_default);

			ResetPowerLevel();
		}

	}
}