#include "engine/core/game_object.h"

namespace NSEngine {
	namespace NSCore {

		CGameObject::CGameObject(
			pGame game
			, pWorld world
			, uint32_t id
			, std::string name
		)
			: game(game)
			, world(world) 
			, id(id)
			, name(name) {
			type = EActorType::INVALID_ACTOR;
		}

		CGameObject::~CGameObject() {
		}

		std::string CGameObject::GetName() {
			return name;
		}

		uint32_t CGameObject::GetId() {
			return id;
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
