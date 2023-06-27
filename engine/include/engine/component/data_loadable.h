#ifndef __ENGINE__COMPONENT__DATA_LOADABLE_H__
#define __ENGINE__COMPONENT__DATA_LOADABLE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CDataLoadable {
		protected:
		public:
			CDataLoadable();
			virtual ~CDataLoadable() = 0;

			virtual void LoadData(nlohmann::json& data) = 0;
		};
		typedef CDataLoadable* pDataLoadable;

	}
}

#endif // !__ENGINE__COMPONENT__DATA_LOADABLE_H__
