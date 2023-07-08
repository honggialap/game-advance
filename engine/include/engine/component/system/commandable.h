#pragma once
#ifndef __ENGINE__COMPONENT__COMMANDABLE_H__
#define __ENGINE__COMPONENT__COMMANDABLE_H__

#include "engine/core/command.h"

namespace NSEngine {
	namespace NSComponent {

		class CCommandable {
		protected:
		public:
			CCommandable();
			virtual ~CCommandable() = 0;

			virtual void ExecuteCommand(NSCore::pCommand command) = 0;
		};
		typedef CCommandable* pCommandable;

	}
}

#endif // !__ENGINE__COMPONENT__COMMANDABLE_H__
