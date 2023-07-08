#include "engine/component/system/physics.h"

namespace NSEngine {
	namespace NSComponent {

		CPhysics::CPhysics(b2World* physics_world)
			: CLoadByJson()
			, CLoadByNetworks()
			, physics_world(physics_world) 
		{
		}

		CPhysics::~CPhysics() {
			if (body) {
				physics_world->DestroyBody(body);
				body = nullptr;
			}
			physics_world = nullptr;
		}

		void CPhysics::SetBodyEnable(bool value) {
			body->SetEnabled(value);
		}

		bool CPhysics::IsBodyEnabled() {
			return body->IsEnabled();
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

		void CPhysics::ChangeSize(float width, float height, float offset_x, float offset_y) {
			b2PolygonShape collider;
			this->width = width;
			this->height = height;
			this->offset_x = offset_x;
			this->offset_y = offset_y;
			
			b2Vec2 offset = b2Vec2(offset_x / PIXEL_PER_METER, offset_x / PIXEL_PER_METER);
			collider.SetAsBox(
				(width / 2.0f) / PIXEL_PER_METER
				, (height / 2.0f) / PIXEL_PER_METER
				, offset
				, 0
			);

			auto old_fixture = body->GetFixtureList();

			b2FixtureDef new_fixture_def;
			new_fixture_def.shape = &collider;
			new_fixture_def.filter.categoryBits = old_fixture->GetFilterData().categoryBits;
			new_fixture_def.filter.maskBits = old_fixture->GetFilterData().maskBits;

			body->DestroyFixture(old_fixture);
			body->CreateFixture(&new_fixture_def);
		}

		void CPhysics::JsonLoad(nlohmann::json& data) {
			if (data.contains("physics")) {
				auto& physics_data = data.at("physics");

				b2BodyDef body_def;
				body_def.type = b2BodyType(physics_data.at("body_type"));
				body_def.bullet = bool(physics_data.at("bullet"));
				body_def.fixedRotation = true;
				body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

				b2PolygonShape collider;
				width = float(physics_data.at("width"));
				height = float(physics_data.at("height"));
				offset_x = float(physics_data.at("offset_x"));
				offset_y = float(physics_data.at("offset_y"));

				b2Vec2 offset = b2Vec2(offset_x / PIXEL_PER_METER, offset_y / PIXEL_PER_METER);

				collider.SetAsBox(
					(width / 2.0f) / PIXEL_PER_METER
					, (height / 2.0f) / PIXEL_PER_METER
					, offset
					, 0
				);

				b2FixtureDef fixture_def;
				fixture_def.shape = &collider;
				fixture_def.isSensor = bool(physics_data.at("sensor"));
				fixture_def.filter.categoryBits = uint16_t(physics_data.at("category_bits"));
				fixture_def.filter.maskBits = uint16_t(physics_data.at("mask_bits"));

				body = physics_world->CreateBody(&body_def);
				body->CreateFixture(&fixture_def);
			}
		}

		void CPhysics::PackLoad(NSNetworks::CPacket* packet) {
			uint32_t body_type = uint32_t(body->GetType());
			*packet << body_type;

			*packet << width << height;

			uint16_t category_bits = body->GetFixtureList()->GetFilterData().categoryBits;
			*packet << category_bits;

			uint16_t mask_bits = body->GetFixtureList()->GetFilterData().maskBits;
			*packet << mask_bits;

			float position_x, position_y;
			GetPosition(position_x, position_y);
			*packet << position_x << position_y;
		}

		void CPhysics::UnpackLoad(NSNetworks::CPacket* packet) {
			uint32_t body_type;
			*packet >> body_type;

			b2BodyDef body_def;
			body_def.type = b2BodyType(body_type);
			body_def.fixedRotation = true;
			body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

			float width, height;
			*packet >> width >> height;

			b2PolygonShape collider;
			collider.SetAsBox(
				(width / 2.0f) / PIXEL_PER_METER
				, (height / 2.0f) / PIXEL_PER_METER
			);

			uint16_t category_bits;
			*packet >> category_bits;

			uint16_t mask_bits;
			*packet >> mask_bits;

			b2FixtureDef fixture_def;
			fixture_def.shape = &collider;
			fixture_def.filter.categoryBits = category_bits;
			fixture_def.filter.maskBits = mask_bits;

			body = physics_world->CreateBody(&body_def);
			body->CreateFixture(&fixture_def);

			float position_x, position_y;
			*packet >> position_x >> position_y;
			SetPosition(position_x, position_y);
		}

	}
}
