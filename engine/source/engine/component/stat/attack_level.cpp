#include "engine/component/stat/attack_level.h"

namespace NSEngine {
	namespace NSComponent {

		CAttackLevel::CAttackLevel() {
		}

		CAttackLevel::~CAttackLevel() {
		}

		void CAttackLevel::SetDefaultAttackLevel(int32_t value) {
			default_attack_level = value;
		}

		int32_t CAttackLevel::GetDefaultAttackLevel() {
			return default_attack_level;
		}

		void CAttackLevel::SetMaxAttackLevel(int32_t value) {
			max_attack_level = value;
		}

		int32_t CAttackLevel::GetMaxAttackLevel() {
			return max_attack_level;
		}

		void CAttackLevel::SetMinAttackLevel(int32_t value) {
			min_attack_level = value;
		}

		int32_t CAttackLevel::GetMinAttackLevel() {
			return min_attack_level;
		}

		void CAttackLevel::SetAttackLevel(int32_t value) {
			attack_level = value;
			if (attack_level > max_attack_level) {
				attack_level = max_attack_level;
			}
			else if (attack_level < min_attack_level) {
				attack_level = min_attack_level;
			}
		}

		int32_t CAttackLevel::GetAttackLevel() {
			return attack_level;
		}

		void CAttackLevel::IncreaseAttackLevel(int32_t value) {
			attack_level += value;
			if (attack_level > max_attack_level) {
				attack_level = max_attack_level;
			}
		}

		void CAttackLevel::DecreaseAttackLevel(int32_t value) {
			attack_level -= value;
			if (attack_level < min_attack_level) {
				attack_level = min_attack_level;
			}
		}

		void CAttackLevel::ResetAttackLevel() {
			attack_level = default_attack_level;
		}

		void CAttackLevel::JsonLoad(nlohmann::json& data) {
			if (data.contains("attack")) {
				auto& attack_data = data.at("attack");
				int32_t max_attack_value = attack_data.at("max");
				int32_t min_attack_value = attack_data.at("min");
				int32_t default_attack_value = attack_data.at("default");

				SetMaxAttackLevel(max_attack_value);
				SetMinAttackLevel(min_attack_value);
				SetDefaultAttackLevel(default_attack_value);
				ResetAttackLevel();
			}
		}

		void CAttackLevel::PackLoad(NSNetworks::CPacket* packet) {
			int32_t send_max = GetMaxAttackLevel();
			*packet << send_max;

			int32_t send_min = GetMinAttackLevel();
			*packet << send_min;

			int32_t send_default = GetDefaultAttackLevel();
			*packet << send_default;
		}

		void CAttackLevel::UnpackLoad(NSNetworks::CPacket* packet) {
			int32_t receive_max;
			*packet >> receive_max;
			SetMaxAttackLevel(receive_max);

			int32_t receive_min;
			*packet >> receive_min;
			SetMinAttackLevel(receive_min);

			int32_t receive_default;
			*packet >> receive_default;
			SetDefaultAttackLevel(receive_default);

			ResetAttackLevel();
		}

	}
}