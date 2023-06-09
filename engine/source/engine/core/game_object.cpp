#include "engine/core/game_object.h"

namespace NSEngine {
	namespace NSCore {

		CGameObject::CGameObject(pGame game, pWorld world)
			: game(game)
			, world(world) {
		}

		CGameObject::~CGameObject() {
		}

		void CGameObject::SetName(std::string value) {
			name = value;
		}

		std::string CGameObject::GetName() {
			return name;
		}

		void CGameObject::SetId(uint32_t value) {
			id = value;
		}

		uint32_t CGameObject::GetId() {
			return id;
		}

		void CGameObject::SetType(EActorType value) {
			type = value;
		}

		EActorType CGameObject::GetType() {
			return type;
		}

		void CGameObject::SetActive(bool value) {
			is_active = value;
		}

		bool CGameObject::IsActive() {
			return is_active;
		}

		void CGameObject::Destroy() {
			is_destroyed = true;
		}

		bool CGameObject::IsDestroyed() {
			return is_destroyed;
		}

	}
}
