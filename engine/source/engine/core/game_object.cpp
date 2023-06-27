#include "engine/core/game_object.h"
#include "engine/core/world.h"

#include "engine/component/updatable.h"

#include "engine/component/physics.h"
#include "engine/component/recordable.h"
#include "engine/component/commandable.h"

#include "engine/component/input_handler.h"
#include "engine/component/ai_control.h"
#include "engine/component/player_control.h"

#include "engine/component/resource_loadable.h"
#include "engine/component/remote_object.h"

#include "engine/component/renderable.h"
#include "engine/component/sprite.h"
#include "engine/component/animation.h"

#include "engine/component/match_timer.h"
#include "engine/component/health.h"
#include "engine/component/damage.h"
#include "engine/component/movement.h"
#include "engine/component/team.h"

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
			, is_destroyed(false) {
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

		void CGameObject::Destroy() {
			is_destroyed = true;
		}

		bool CGameObject::IsDestroyed() {
			return is_destroyed;
		}

		bool CGameObject::AddParent(std::string parent_name_value) {
			// Check if the parent game object exist.
			if (world->dictionary.find(parent_name_value) == world->dictionary.end()) {
				return false;
			}

			// Retrive parent
			uint32_t parent_id = world->dictionary[parent_name_value];
			pGameObject parent = world->game_objects[parent_id].get();

			// Check if parent accepting the child.
			if (!parent->AddChild(name)) {
				return false;
			}

			parent_name = parent_name_value;
			return true;
		}

		bool CGameObject::RemoveParent() {
			// Check if the parent game object exist.
			if (world->dictionary.find(parent_name) == world->dictionary.end()) {
				return false;
			}

			// Retrive parent
			uint32_t parent_id = world->dictionary[parent_name];
			pGameObject parent = world->game_objects[parent_id].get();

			// Check if parent disowning the child.
			if (!parent->RemoveChild(name)) {
				return false;
			}

			parent_name = "";
			return true;
		}

		bool CGameObject::ChangeParent(std::string new_parent_name_value) {
			// Check if the new parent game object exist.
			if (world->dictionary.find(new_parent_name_value) == world->dictionary.end()) {
				return false;
			}

			if (!RemoveParent()) {
				return false;
			}

			if (!AddParent(new_parent_name_value)) {
				return false;
			}

			return true;
		}

		CGameObject* CGameObject::GetParent() {			
			// Check if the child game object exist.
			if (world->dictionary.find(parent_name) == world->dictionary.end()) {
				return nullptr;
			}

			// Retrive parent
			uint32_t parent_id = world->dictionary[parent_name];
			pGameObject parent = world->game_objects[parent_id].get();
			return parent;
		}

		bool CGameObject::AddChild(std::string child_name_value) {
			// Check if the child game object exist.
			if (world->dictionary.find(child_name_value) == world->dictionary.end()) {
				return false;
			}
			
			// Check if the child game object already added.
			for (auto& child_name : children_name) {
				if (child_name.compare(child_name_value) == 0) {
					return false;
				}
			}

			children_name.push_back(child_name_value);
			return true;
		}

		bool CGameObject::RemoveChild(std::string child_name_value) {
			// Check if the child game object exist.
			if (world->dictionary.find(child_name_value) == world->dictionary.end()) {
				return false;
			}

			// Check if the child game object are added.
			bool found_child_with_name = false;
			for (auto& child_name : children_name) {
				if (child_name.compare(child_name_value) == 0) {
					found_child_with_name = true;
				}
			}
			if (!found_child_with_name) {
				return false;
			}

			// Deletion
			auto it = std::find(children_name.begin(), children_name.end(), child_name_value);
			if (it != children_name.end()) {
				children_name.erase(it);
				return true;
			}

			return false;
		}

		pGameObject CGameObject::GetChild(std::string child_name_value) {
			// Check if the child game object exist.
			if (world->dictionary.find(child_name_value) == world->dictionary.end()) {
				return nullptr;
			}

			uint32_t child_id = world->dictionary[child_name_value];
			pGameObject child = world->game_objects[child_id].get();
			return child;
		}

		void CGameObject::LoadComponents(nlohmann::json& components_data) {

			// Physics
			if (dynamic_cast<NSComponent::pPhysics>(this)) {
				auto component = dynamic_cast<NSComponent::pPhysics>(this);
				component->LoadData(components_data);
			}

			// Player Control
			if (dynamic_cast<NSComponent::pPlayerControl>(this)) {
				auto component = dynamic_cast<NSComponent::pPlayerControl>(this);
				component->LoadData(components_data);
			}

			// Resource Loadable
			if (dynamic_cast<NSComponent::pResourceLoadable>(this)) {
				auto component = dynamic_cast<NSComponent::pResourceLoadable>(this);
				component->LoadData(components_data);
			}

			// Renderable
			if (dynamic_cast<NSComponent::pRenderable>(this)) {
				auto component = dynamic_cast<NSComponent::pRenderable>(this);
				component->LoadData(components_data);
			}

			// Health
			if (dynamic_cast<NSComponent::pHealth>(this)) {
				auto component = dynamic_cast<NSComponent::pHealth>(this);
				component->LoadData(components_data);
			}

			// Damage
			if (dynamic_cast<NSComponent::pDamage>(this)) {
				auto component = dynamic_cast<NSComponent::pDamage>(this);
				component->LoadData(components_data);
			}

			// Match Timer
			if (dynamic_cast<NSComponent::pMatchTimer>(this)) {
				auto component = dynamic_cast<NSComponent::pMatchTimer>(this);
				component->LoadData(components_data);
			}

			// Team
			if (dynamic_cast<NSComponent::pTeam>(this)) {
				auto component = dynamic_cast<NSComponent::pTeam>(this);
				component->LoadData(components_data);
			}

			// TEMPLATE
			//if (dynamic_cast<NSComponent::>(this)) {
			//	auto component = dynamic_cast<NSComponent::>(this);
			//	component->LoadData(components_data);
			//}

		}

		void CGameObject::PackLoadPacket(NSNetworks::CPacket* packet) {
			std::string send_parent_name = parent_name;
			*packet << parent_name;

			if (dynamic_cast<NSComponent::pDamage>(this)) {
				auto damage_component = dynamic_cast<NSComponent::pDamage>(this);
				damage_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pHealth>(this)) {
				auto health_component = dynamic_cast<NSComponent::pHealth>(this);
				health_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pMatchTimer>(this)) {
				auto match_timer_component = dynamic_cast<NSComponent::pMatchTimer>(this);
				match_timer_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pMovement>(this)) {
				auto movement_component = dynamic_cast<NSComponent::pMovement>(this);
				movement_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pPhysics>(this)) {
				auto physics_component = dynamic_cast<NSComponent::pPhysics>(this);
				physics_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pPlayerControl>(this)) {
				auto player_control_component = dynamic_cast<NSComponent::pPlayerControl>(this);
				player_control_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pRenderable>(this)) {
				auto renderable_component = dynamic_cast<NSComponent::pRenderable>(this);
				renderable_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pResourceLoadable>(this)) {
				auto resource_loadable_component = dynamic_cast<NSComponent::pResourceLoadable>(this);
				resource_loadable_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pTeam>(this)) {
				auto team_component = dynamic_cast<NSComponent::pTeam>(this);
				team_component->PackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pUpdatable>(this)) {
				auto updatable_component = dynamic_cast<NSComponent::pUpdatable>(this);
				updatable_component->PackLoad(packet);
			}
			
		}

		void CGameObject::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			std::string receive_parent_name;
			*packet >> parent_name;
			AddParent(parent_name);

			if (dynamic_cast<NSComponent::pDamage>(this)) {
				auto damage_component = dynamic_cast<NSComponent::pDamage>(this);
				damage_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pHealth>(this)) {
				auto health_component = dynamic_cast<NSComponent::pHealth>(this);
				health_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pMatchTimer>(this)) {
				auto match_timer_component = dynamic_cast<NSComponent::pMatchTimer>(this);
				match_timer_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pMovement>(this)) {
				auto movement_component = dynamic_cast<NSComponent::pMovement>(this);
				movement_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pPhysics>(this)) {
				auto physics_component = dynamic_cast<NSComponent::pPhysics>(this);
				physics_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pPlayerControl>(this)) {
				auto player_control_component = dynamic_cast<NSComponent::pPlayerControl>(this);
				player_control_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pRenderable>(this)) {
				auto renderable_component = dynamic_cast<NSComponent::pRenderable>(this);
				renderable_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pResourceLoadable>(this)) {
				auto resource_loadable_component = dynamic_cast<NSComponent::pResourceLoadable>(this);
				resource_loadable_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pTeam>(this)) {
				auto team_component = dynamic_cast<NSComponent::pTeam>(this);
				team_component->UnpackLoad(packet);
			}

			if (dynamic_cast<NSComponent::pUpdatable>(this)) {
				auto updatable_component = dynamic_cast<NSComponent::pUpdatable>(this);
				updatable_component->UnpackLoad(packet);
			}

		}
	}
}
