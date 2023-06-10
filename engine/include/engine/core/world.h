#pragma once
#ifndef __ENGINE__CORE__WORLD_H__
#define __ENGINE__CORE__WORLD_H__

#include "engine/common.h"
#include "engine/shared.h"

#include "engine/core/game.h"
#include "engine/core/game_object.h"

#include "engine/component/updatable.h"
#include "engine/component/renderable.h"
#include "engine/component/commandable.h"
#include "engine/component/recordable.h"
#include "engine/component/physics.h"
#include "engine/component/player_control.h"

namespace NSEngine {
	namespace NSCore {

		class CWorld : public b2ContactListener {
		protected:
			pGame game;

		public:
			b2Vec2 gravity;
			b2World* physics_world = nullptr;

			uint32_t game_object_id = 1000;
			std::map<std::string, uint32_t> dictionary;
			std::map<uint32_t, upGameObject> game_objects;
			std::map<uint32_t, std::vector<upCommand>> commands;
			std::map<uint32_t, std::vector<upRecord>> records;

			uint32_t latest_tick = 0;
			uint32_t tick_per_game_state = 8;
			
			CWorld(pGame game);
			~CWorld();

			virtual void Load(nlohmann::json& data) = 0;
			virtual void Unload() = 0;

			void HandleInput(uint32_t tick);

			void Step(uint32_t tick, float elapsed);

			void Render(sf::RenderWindow& window);

			void TrimCommands(uint32_t threshold);
			void TrimCommands(uint32_t from, uint32_t to);

			void TrimRecords(uint32_t threshold);
			void TrimRecords(uint32_t from, uint32_t to);

			void Serialize(uint32_t tick);
			void Deserialize(uint32_t tick);

			b2World* GetPhysics();
			void BeginContact(b2Contact* contact) override;
			void EndContact(b2Contact* contact) override;
		};
		typedef CWorld* pWorld;

	}
}

#endif // !__ENGINE__CORE__WORLD_H__
