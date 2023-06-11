#include "engine/component/physics.h"

namespace NSEngine {
	namespace NSComponent {

		CPhysics::CPhysics(b2World* physics_world)
			: physics_world(physics_world) {
		}

		CPhysics::~CPhysics() {
			DestroyPhysics();
			physics_world = nullptr;
		}

		void CPhysics::CreatePhysics(nlohmann::json& physics_data){
			b2BodyType body_type = b2BodyType(physics_data.at("body_type"));
			float position_x = float(physics_data.at("x"));
			float position_y = float(physics_data.at("y"));
			float width = float(physics_data.at("width"));
			float height = float(physics_data.at("height"));
			uint16_t category_bits = uint16_t(physics_data.at("category_bits"));
			uint16_t mask_bits = uint16_t(physics_data.at("mask_bits"));
			CreatePhysics(body_type, position_x, position_y, width, height, category_bits, mask_bits);
		}

		void CPhysics::CreatePhysics(
			b2BodyType body_type
			, float position_x, float position_y
			, float width, float height
			, uint16_t category_bits, uint16_t mask_bits
		){
			body_def.type = body_type;
			body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

			body = physics_world->CreateBody(&body_def);
			body->SetTransform(b2Vec2(position_x / PIXEL_PER_METER, position_y / PIXEL_PER_METER), 0);

			collider.SetAsBox(width / PIXEL_PER_METER, height / PIXEL_PER_METER);
			this->width = width;
			this->height = height;

			fixture_def.shape = &collider;

			fixture_def.filter.categoryBits = category_bits;
			fixture_def.filter.maskBits = mask_bits;

			fixture = body->CreateFixture(&fixture_def);
		}

		void CPhysics::DestroyPhysics(){
			if (body != nullptr) {
				if (fixture != nullptr) {
					body->DestroyFixture(fixture);
					fixture = nullptr;
				}
				physics_world->DestroyBody(body);
				body = nullptr;
			}
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

		void CPhysics::PackLoadPhysics(NSEngine::NSNetworks::CPacket* packet) {
			uint32_t body_type = uint32_t(body_def.type);
			*packet << body_type;

			float position_x, position_y;
			GetPosition(position_x, position_y);
			*packet << position_x << position_y;

			float width = this->width;
			float height = this->height;
			*packet << width << height;

			uint16_t category_bits = fixture_def.filter.categoryBits;
			*packet << category_bits;

			uint16_t mask_bits = fixture_def.filter.maskBits;
			*packet << mask_bits;
		}

		void CPhysics::UnpackLoadPhysics(NSEngine::NSNetworks::CPacket* packet) {
			uint32_t body_type;
			*packet >> body_type;

			float position_x, position_y;
			*packet >> position_x >> position_y;

			float width, height;
			*packet >> width >> height;

			uint16_t category_bits;
			*packet >> category_bits;

			uint16_t mask_bits;
			*packet >> mask_bits;

			CreatePhysics(
				b2BodyType(body_type)
				, position_x, position_y
				, width, height
				, category_bits
				, mask_bits
			);
		}

	}
}
