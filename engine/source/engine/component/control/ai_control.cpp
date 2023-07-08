#include "engine/component/control/ai_control.h"

namespace NSEngine {
	namespace NSComponent {

		CAIControl::CAIControl() {
		}

		CAIControl::~CAIControl() {
		}

		void CAIControl::SetSeed(uint32_t value) {
			seed = value;
		}

		uint32_t CAIControl::GetSeed() {
			return seed;
		}

		void CAIControl::SetWave(uint32_t value) {
			wave_queue_id = value;
		}

		uint32_t CAIControl::GetWave() {
			return wave_queue_id;
		}

		void CAIControl::JsonLoad(nlohmann::json& data) {
			if (
				data.contains("ai_seed")
				&& data.contains("wave_id")
				) {
				uint32_t ai_seed_value = data.at("ai_seed");
				SetSeed(ai_seed_value);

				uint32_t wave_id_value = data.at("wave_id");
				SetWave(wave_id_value);
			}
		}

		void CAIControl::PackLoad(NSNetworks::CPacket* packet) {
			uint32_t send_seed_value = GetSeed();
			*packet << send_seed_value;

			uint32_t send_wave_value = GetWave();
			*packet << send_wave_value;
		}

		void CAIControl::UnpackLoad(NSNetworks::CPacket* packet) {
			uint32_t receive_seed_value;
			*packet >> receive_seed_value;
			SetSeed(receive_seed_value);

			uint32_t receive_wave_value;
			*packet >> receive_wave_value;
			SetWave(receive_wave_value);
		}

	}
}