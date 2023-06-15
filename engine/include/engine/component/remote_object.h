#pragma once
#ifndef __ENGINE__COMPONENT__REMOTE_OBJECT_H__
#define __ENGINE__COMPONENT__REMOTE_OBJECT_H__

namespace NSEngine {
	namespace NSComponent {

		class CRemoteObject {
		protected:
		public:
			CRemoteObject();
			virtual ~CRemoteObject() = 0;

		};
		typedef CRemoteObject* pRemoteObject;

	}
}

#endif // !__ENGINE__COMPONENT__REMOTE_OBJECT_H__
