#include "engine/component/render/remote.h"

namespace NSEngine {
	namespace NSComponent {

		CRemote::CRemote() {
		}

		CRemote::~CRemote() {
		}

		void CRemote::SetRemote(bool value) {
			is_remote = value;
		}

		bool CRemote::IsRemote() {
			return is_remote;
		}

		void CRemote::SetPrevious(float x, float y) {
			previous_x = x;
			previous_y = y;
		}

		void CRemote::GetPrevious(float& x, float& y) {
			x = previous_x;
			y = previous_y;
		}

		void CRemote::SetLatest(float x, float y) {
			latest_x = x;
			latest_y = y;
		}

		void CRemote::GetLatest(float& x, float& y) {
			x = latest_x;
			y = latest_y;
		}

		void CRemote::UpdateRemote(float x, float y) {
			previous_x = latest_x;
			previous_y = latest_y;

			latest_x = x;
			latest_y = y;
		}

		void CRemote::GetInterpolation(float& x, float& y, float interpolate_value) {
			x = previous_x + ((latest_x - previous_x) * interpolate_value);
			y = previous_y + ((latest_y - previous_y) * interpolate_value);
		}

	}
}

