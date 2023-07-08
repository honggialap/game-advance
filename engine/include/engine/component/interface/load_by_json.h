#ifndef __ENGINE__COMPONENT__LOAD_BY_JSON_H__
#define __ENGINE__COMPONENT__LOAD_BY_JSON_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CLoadByJson {
		protected:
		public:
			CLoadByJson();
			virtual ~CLoadByJson() = 0;

			virtual void JsonLoad(nlohmann::json& data) = 0;
		};
		typedef CLoadByJson* pLoadByJson;

	}
}

#endif // !__ENGINE__COMPONENT__LOAD_BY_JSON_H__
