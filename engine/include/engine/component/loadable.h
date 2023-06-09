#pragma once
#ifndef __ENGINE__COMPONENT__LOADABLE_H__
#define __ENGINE__COMPONENT__LOADABLE_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CLoadable {
		protected:
			std::string resource_path;

		public:
			CLoadable();
			virtual ~CLoadable() = 0;

			void SetResourcePath(std::string value);
			std::string GetResourcePath();

			virtual void Load(std::string data_path) = 0;
			virtual void Unload() = 0;
		};
		typedef CLoadable* pLoadable;

	}
}

#endif // !__ENGINE__COMPONENT__LOADABLE_H__
