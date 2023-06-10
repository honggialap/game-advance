#include "engine/actor/bound.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CBound::CBound(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSCore::CGameObject(game, world, id, name)
			, NSEngine::NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::BOUND;
		}

		CBound::~CBound() {
		}

		//void CBound::Load(std::string data_path) {
		//	//std::ifstream data_file(data_path);
		//	//nlohmann::json data = nlohmann::json::parse(data_file);
		//
		//	body_def.type = b2_kinematicBody;
		//	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
		//
		//	body = world->GetPhysics()->CreateBody(&body_def);
		//
		//	collider.SetAsBox(32.0f / 30, 32.0f / 30);
		//
		//	fixture_def.shape = &collider;
		//
		//	fixture_def.filter.categoryBits = ECollisionFilter::FILTER_WALL;
		//	fixture_def.filter.maskBits
		//		= ECollisionFilter::FILTER_PLAYER_TANK
		//		| ECollisionFilter::FILTER_CREEP_TANK
		//		| ECollisionFilter::FILTER_BULLET
		//		//| ECollisionFilter::FILTER_STRUCTURE
		//		//| ECollisionFilter::FILTER_WALL
		//		//| ECollisionFilter::FILTER_WATER
		//		//| ECollisionFilter::FILTER_TREE
		//		//| ECollisionFilter::FILTER_PICK_UP
		//		;
		//
		//	fixture = body->CreateFixture(&fixture_def);
		//}
		//
		//void CBound::Unload() {
		//	if (body != nullptr) {
		//		if (fixture != nullptr) {
		//			body->DestroyFixture(fixture);
		//			fixture = nullptr;
		//		}
		//		world->GetPhysics()->DestroyBody(body);
		//		body = nullptr;
		//	}
		//}

		void CBound::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
		}

		void CBound::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}
