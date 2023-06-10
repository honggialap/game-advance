#pragma once
#ifndef __ENGINE__COMPONENT__PHYSICS_H__
#define __ENGINE__COMPONENT__PHYSICS_H__

#include "engine/common.h"
#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSComponent {

		class CPhysics {
		protected:
			b2World* physics_world = nullptr;

			b2BodyDef body_def;
			b2Body* body = nullptr;

			b2PolygonShape collider;
			float width = 0.0f;
			float height = 0.0f;

			b2FixtureDef fixture_def;
			b2Fixture* fixture = nullptr;

		public:
			CPhysics(b2World* world);
			virtual ~CPhysics() = 0;

			void CreatePhysics(
				b2BodyType body_type
				, float position_x, float position_y
				, float width, float height
				, uint16_t category_bits
				, uint16_t mask_bits
			);
			void DestroyPhysics();

			void SetPosition(float x, float y);
			void GetPosition(float& x, float& y);

			void SetVelocity(float vx, float vy);
			void GetVelocity(float& vx, float& vy);

			void PackLoadPhysics(NSEngine::NSNetworks::CPacket* packet);
			void UnpackLoadPhysics(NSEngine::NSNetworks::CPacket* packet);

			virtual void OnCollisionEnter(CPhysics* other) = 0;
			virtual void OnCollisionExit(CPhysics* other) = 0;
		};
		typedef CPhysics* pPhysics;

	}
}

#endif // !__ENGINE__COMPONENT__PHYSICS_H__
