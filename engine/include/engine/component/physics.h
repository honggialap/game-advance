#pragma once
#ifndef __ENGINE__COMPONENT__PHYSICS_H__
#define __ENGINE__COMPONENT__PHYSICS_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSComponent {

		class CPhysics {
		protected:
			b2BodyDef body_def;
			b2Body* body = nullptr;
			b2PolygonShape collider;
			b2FixtureDef fixture_def;
			b2Fixture* fixture = nullptr;

		public:
			CPhysics();
			virtual ~CPhysics() = 0;

			void SetPosition(float x, float y);
			void GetPosition(float& x, float& y);

			void SetVelocity(float vx, float vy);
			void GetVelocity(float& vx, float& vy);

			virtual void OnCollisionEnter(CPhysics* other) = 0;
			virtual void OnCollisionExit(CPhysics* other) = 0;
		};
		typedef CPhysics* pPhysics;

	}
}

#endif // !__ENGINE__COMPONENT__PHYSICS_H__
