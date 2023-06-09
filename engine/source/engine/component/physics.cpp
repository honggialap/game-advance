#include "engine/component/physics.h"

namespace NSEngine {
	namespace NSComponent {

		CPhysics::CPhysics() {
		}

		CPhysics::~CPhysics() {
		}

		void CPhysics::SetPosition(float x, float y) {
			body->SetTransform(b2Vec2(x / PIXEL_PER_METER, y / PIXEL_PER_METER), 0);
		}

		void CPhysics::GetPosition(float& x, float& y) {
			x = body->GetPosition().x * PIXEL_PER_METER; y = body->GetPosition().y * PIXEL_PER_METER;
		}

		void CPhysics::SetVelocity(float vx, float vy) {
			body->SetLinearVelocity(b2Vec2(vx / PIXEL_PER_METER, vy / PIXEL_PER_METER));
		}

		void CPhysics::GetVelocity(float& vx, float& vy) {
			vx = body->GetPosition().x * PIXEL_PER_METER; vy = body->GetPosition().y * PIXEL_PER_METER;
		}

	}
}
