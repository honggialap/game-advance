#pragma once
#ifndef __ENGINE__COMPONENT__PHYSICS_H__
#define __ENGINE__COMPONENT__PHYSICS_H__

#include "engine/common.h"
#include "engine/component/interface/load_by_json.h"
#include "engine/component/interface/load_by_networks.h"

namespace NSEngine {
	namespace NSComponent {

		class CPhysics
			: public CLoadByJson
			, public CLoadByNetworks
		{
		protected:
			b2World* physics_world = nullptr;
			b2Body* body = nullptr;
			float width = 0.0f;
			float height = 0.0f;
			float offset_x = 0.0f;
			float offset_y = 0.0f;

		public:
			CPhysics(b2World* world);
			virtual ~CPhysics() = 0;

			void SetBodyEnable(bool value);
			bool IsBodyEnabled();

			void SetPosition(float x, float y);
			void GetPosition(float& x, float& y);

			void SetVelocity(float vx, float vy);
			void GetVelocity(float& vx, float& vy);

			void ChangeSize(float width, float height, float offset_x, float offset_y);

			virtual void OnCollisionEnter(CPhysics* other) = 0;
			virtual void OnCollisionExit(CPhysics* other) = 0;

			void JsonLoad(nlohmann::json& data) final;
			void PackLoad(NSNetworks::CPacket* packet) final;
			void UnpackLoad(NSNetworks::CPacket* packet) final;
		};
		typedef CPhysics* pPhysics;

	}
}

#endif // !__ENGINE__COMPONENT__PHYSICS_H__
