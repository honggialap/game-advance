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

		void CBound::PackLoad(NSEngine::NSNetworks::CPacket* packet) {
		}

		void CBound::UnpackLoad(NSEngine::NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
		}

		void CBound::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
		}

		void CBound::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}
