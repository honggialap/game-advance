#include "engine/actor/bound.h"
#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CBound::CBound(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::BOUND;
		}

		CBound::~CBound() {
		}

		void CBound::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CBound::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CBound::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
		}

		void CBound::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
		}

	}
}
