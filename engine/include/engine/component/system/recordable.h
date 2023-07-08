#pragma once
#ifndef __ENGINE__COMPONENT__RECORDABLE_H__
#define __ENGINE__COMPONENT__RECORDABLE_H__

#include "engine/core/record.h"
#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSComponent {

		class CRecordable {
		protected:
		public:
			CRecordable();
			virtual ~CRecordable() = 0;

			virtual void Serialize(uint32_t tick) = 0;
			virtual void Deserialize(NSCore::pRecord record) = 0;

			virtual void PackRecord(
				NSNetworks::CPacket* packet
				, NSCore::pRecord record
			) = 0;

			virtual NSCore::pRecord UnpackRecord(
				NSNetworks::CPacket* packet
			) = 0;
		};
		typedef CRecordable* pRecordable;

	}
}

#endif // !__ENGINE__COMPONENT__RECORDABLE_H__