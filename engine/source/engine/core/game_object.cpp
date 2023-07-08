#include "engine/core/game_object.h"
#include "engine/core/world.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/physics.h"
#include "engine/component/system/recordable.h"
#include "engine/component/system/commandable.h"
#include "engine/component/system/input_handler.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/remote.h"
#include "engine/component/render/resource.h"

#include "engine/component/control/player_control.h"
#include "engine/component/control/ai_control.h"
#include "engine/component/control/spawnable.h"
#include "engine/component/control/direction.h"
#include "engine/component/control/move.h"
#include "engine/component/control/shoot.h"

#include "engine/component/stat/team.h"
#include "engine/component/stat/power_level.h"
#include "engine/component/stat/attack_level.h"
#include "engine/component/stat/defend_level.h"
#include "engine/component/stat/health.h"
#include "engine/component/stat/damage.h"
#include "engine/component/stat/speed.h"
#include "engine/component/stat/reward.h"

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
			, name(name)
		{
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

		void CGameObject::LoadComponents(nlohmann::json& components_data) {

			//system - updatable
			if (dynamic_cast<NSComponent::pUpdatable>(this)) {
				auto component = dynamic_cast<NSComponent::pUpdatable>(this);
				component->JsonLoad(components_data);
			}

			//system - physics
			if (dynamic_cast<NSComponent::pPhysics>(this)) {
				auto component = dynamic_cast<NSComponent::pPhysics>(this);
				component->JsonLoad(components_data);
			}

			//render - renderable
			if (dynamic_cast<NSComponent::pRenderable>(this)) {
				auto component = dynamic_cast<NSComponent::pRenderable>(this);
				component->JsonLoad(components_data);
			}

			//render - resource
			if (dynamic_cast<NSComponent::pResource>(this)) {
				auto component = dynamic_cast<NSComponent::pResource>(this);
				component->JsonLoad(components_data);
			}

			//control - player_control
			if (dynamic_cast<NSComponent::pPlayerControl>(this)) {
				auto component = dynamic_cast<NSComponent::pPlayerControl>(this);
				component->JsonLoad(components_data);
			}

			//control - ai_control
			if (dynamic_cast<NSComponent::pAIControl>(this)) {
				auto component = dynamic_cast<NSComponent::pAIControl>(this);
				component->JsonLoad(components_data);
			}

			//control - direction
			if (dynamic_cast<NSComponent::pDirection>(this)) {
				auto component = dynamic_cast<NSComponent::pDirection>(this);
				component->JsonLoad(components_data);
			}
			
			//control - shoot
			if (dynamic_cast<NSComponent::pShoot>(this)) {
				auto component = dynamic_cast<NSComponent::pShoot>(this);
				component->JsonLoad(components_data);
			}

			//stat - team
			if (dynamic_cast<NSComponent::pTeam>(this)) {
				auto component = dynamic_cast<NSComponent::pTeam>(this);
				component->JsonLoad(components_data);
			}
			
			//stat - power_level
			if (dynamic_cast<NSComponent::pPowerLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pPowerLevel>(this);
				component->JsonLoad(components_data);
			}
			
			//stat - attack_level
			if (dynamic_cast<NSComponent::pAttackLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pAttackLevel>(this);
				component->JsonLoad(components_data);
			}

			//stat - defend_level
			if (dynamic_cast<NSComponent::pDefendLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pDefendLevel>(this);
				component->JsonLoad(components_data);
			}

			//stat - health.h"
			if (dynamic_cast<NSComponent::pHealth>(this)) {
				auto component = dynamic_cast<NSComponent::pHealth>(this);
				component->JsonLoad(components_data);
			}

			//stat - damage.h"
			if (dynamic_cast<NSComponent::pDamage>(this)) {
				auto component = dynamic_cast<NSComponent::pDamage>(this);
				component->JsonLoad(components_data);
			}

			//stat - speed.h"
			if (dynamic_cast<NSComponent::pSpeed>(this)) {
				auto component = dynamic_cast<NSComponent::pSpeed>(this);
				component->JsonLoad(components_data);
			}

			//stat - reward.h"
			if (dynamic_cast<NSComponent::pReward>(this)) {
				auto component = dynamic_cast<NSComponent::pReward>(this);
				component->JsonLoad(components_data);
			}

			// TEMPLATE
			//if (dynamic_cast<NSComponent::>(this)) {
			//	auto component = dynamic_cast<NSComponent::>(this);
			//	component->JsonLoad(components_data);
			//}

		}

		void CGameObject::PackLoadPacket(NSNetworks::CPacket* packet) {

			//system - updatable
			if (dynamic_cast<NSComponent::pUpdatable>(this)) {
				auto component = dynamic_cast<NSComponent::pUpdatable>(this);
				component->PackLoad(packet);
			}

			//system - physics
			if (dynamic_cast<NSComponent::pPhysics>(this)) {
				auto component = dynamic_cast<NSComponent::pPhysics>(this);
				component->PackLoad(packet);
			}

			//render - renderable
			if (dynamic_cast<NSComponent::pRenderable>(this)) {
				auto component = dynamic_cast<NSComponent::pRenderable>(this);
				component->PackLoad(packet);
			}

			//render - resource
			if (dynamic_cast<NSComponent::pResource>(this)) {
				auto component = dynamic_cast<NSComponent::pResource>(this);
				component->PackLoad(packet);
			}

			//control - player_control
			if (dynamic_cast<NSComponent::pPlayerControl>(this)) {
				auto component = dynamic_cast<NSComponent::pPlayerControl>(this);
				component->PackLoad(packet);
			}

			//control - ai_control
			if (dynamic_cast<NSComponent::pAIControl>(this)) {
				auto component = dynamic_cast<NSComponent::pAIControl>(this);
				component->PackLoad(packet);
			}

			//control - direction
			if (dynamic_cast<NSComponent::pDirection>(this)) {
				auto component = dynamic_cast<NSComponent::pDirection>(this);
				component->PackLoad(packet);
			}

			//control - shoot
			if (dynamic_cast<NSComponent::pShoot>(this)) {
				auto component = dynamic_cast<NSComponent::pShoot>(this);
				component->PackLoad(packet);
			}

			//stat - team
			if (dynamic_cast<NSComponent::pTeam>(this)) {
				auto component = dynamic_cast<NSComponent::pTeam>(this);
				component->PackLoad(packet);
			}

			//stat - power_level
			if (dynamic_cast<NSComponent::pPowerLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pPowerLevel>(this);
				component->PackLoad(packet);
			}

			//stat - attack_level
			if (dynamic_cast<NSComponent::pAttackLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pAttackLevel>(this);
				component->PackLoad(packet);
			}

			//stat - defend_level
			if (dynamic_cast<NSComponent::pDefendLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pDefendLevel>(this);
				component->PackLoad(packet);
			}

			//stat - health.h"
			if (dynamic_cast<NSComponent::pHealth>(this)) {
				auto component = dynamic_cast<NSComponent::pHealth>(this);
				component->PackLoad(packet);
			}

			//stat - damage.h"
			if (dynamic_cast<NSComponent::pDamage>(this)) {
				auto component = dynamic_cast<NSComponent::pDamage>(this);
				component->PackLoad(packet);
			}

			//stat - speed.h"
			if (dynamic_cast<NSComponent::pSpeed>(this)) {
				auto component = dynamic_cast<NSComponent::pSpeed>(this);
				component->PackLoad(packet);
			}

			//stat - reward.h"
			if (dynamic_cast<NSComponent::pReward>(this)) {
				auto component = dynamic_cast<NSComponent::pReward>(this);
				component->PackLoad(packet);
			}

			// TEMPLATE
			//if (dynamic_cast<NSComponent::>(this)) {
			//	auto component = dynamic_cast<NSComponent::>(this);
			//	component->PackLoad(components_data);
			//}
			
		}

		void CGameObject::UnpackLoadPacket(NSNetworks::CPacket* packet) {

			//system - updatable
			if (dynamic_cast<NSComponent::pUpdatable>(this)) {
				auto component = dynamic_cast<NSComponent::pUpdatable>(this);
				component->UnpackLoad(packet);
			}

			//system - physics
			if (dynamic_cast<NSComponent::pPhysics>(this)) {
				auto component = dynamic_cast<NSComponent::pPhysics>(this);
				component->UnpackLoad(packet);
			}

			//render - renderable
			if (dynamic_cast<NSComponent::pRenderable>(this)) {
				auto component = dynamic_cast<NSComponent::pRenderable>(this);
				component->UnpackLoad(packet);
			}

			//render - resource
			if (dynamic_cast<NSComponent::pResource>(this)) {
				auto component = dynamic_cast<NSComponent::pResource>(this);
				component->UnpackLoad(packet);
			}

			//control - player_control
			if (dynamic_cast<NSComponent::pPlayerControl>(this)) {
				auto component = dynamic_cast<NSComponent::pPlayerControl>(this);
				component->UnpackLoad(packet);
			}

			//control - ai_control
			if (dynamic_cast<NSComponent::pAIControl>(this)) {
				auto component = dynamic_cast<NSComponent::pAIControl>(this);
				component->UnpackLoad(packet);
			}

			//control - direction
			if (dynamic_cast<NSComponent::pDirection>(this)) {
				auto component = dynamic_cast<NSComponent::pDirection>(this);
				component->UnpackLoad(packet);
			}

			//control - shoot
			if (dynamic_cast<NSComponent::pShoot>(this)) {
				auto component = dynamic_cast<NSComponent::pShoot>(this);
				component->UnpackLoad(packet);
			}

			//stat - team
			if (dynamic_cast<NSComponent::pTeam>(this)) {
				auto component = dynamic_cast<NSComponent::pTeam>(this);
				component->UnpackLoad(packet);
			}

			//stat - power_level
			if (dynamic_cast<NSComponent::pPowerLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pPowerLevel>(this);
				component->UnpackLoad(packet);
			}

			//stat - attack_level
			if (dynamic_cast<NSComponent::pAttackLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pAttackLevel>(this);
				component->UnpackLoad(packet);
			}

			//stat - defend_level
			if (dynamic_cast<NSComponent::pDefendLevel>(this)) {
				auto component = dynamic_cast<NSComponent::pDefendLevel>(this);
				component->UnpackLoad(packet);
			}

			//stat - health.h"
			if (dynamic_cast<NSComponent::pHealth>(this)) {
				auto component = dynamic_cast<NSComponent::pHealth>(this);
				component->UnpackLoad(packet);
			}

			//stat - damage.h"
			if (dynamic_cast<NSComponent::pDamage>(this)) {
				auto component = dynamic_cast<NSComponent::pDamage>(this);
				component->UnpackLoad(packet);
			}

			//stat - speed.h"
			if (dynamic_cast<NSComponent::pSpeed>(this)) {
				auto component = dynamic_cast<NSComponent::pSpeed>(this);
				component->UnpackLoad(packet);
			}

			//stat - reward.h"
			if (dynamic_cast<NSComponent::pReward>(this)) {
				auto component = dynamic_cast<NSComponent::pReward>(this);
				component->UnpackLoad(packet);
			}

			// TEMPLATE
			//if (dynamic_cast<NSComponent::>(this)) {
			//	auto component = dynamic_cast<NSComponent::>(this);
			//	component->UnpackLoad(components_data);
			//}

		}
	}
}
