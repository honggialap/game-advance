#pragma once
#ifndef __ENGINE__COMPONENT__REMOTE_H__
#define __ENGINE__COMPONENT__REMOTE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CRemote {
		protected:
			bool is_remote = false;

			float previous_x = 0.0f;
			float previous_y = 0.0f;
			
			float latest_x = 0.0f;
			float latest_y = 0.0f;

		public:
			CRemote();
			virtual ~CRemote() = 0;

			void SetRemote(bool value);
			bool IsRemote();

			void SetPrevious(float x, float y);
			void GetPrevious(float& x, float& y);

			void SetLatest(float x, float y);
			void GetLatest(float& x, float& y);

			void UpdateRemote(float x, float y);
			void GetInterpolation(float& x, float& y, float interpolate_value);
		};
		typedef CRemote* pRemote;

	}
}

#endif // !__ENGINE__COMPONENT__REMOTE_H__
