#include "wall.h"
#include "game.h"
#include "world.h"

#include "player_tank.h"

Wall* Wall::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<Wall>();
	world->dictionary[data.at("name")] = id;

	Wall* wall = static_cast<Wall*>(world->game_objects[id].get());

	wall->SetGame(game);
	wall->SetWorld(world);
	wall->SetId(id);
	wall->SetType(ACTOR_WALL);
	wall->SetName(data.at("name"));
	wall->SetLayer(data.at("layer"));

	wall->Load(data.at("data_path"));
	wall->SetResourcePath(data.at("data_path"));

	wall->SetPosition(data.at("x"), data.at("y"));

	return wall;
}

void Wall::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_wall.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	body_def.type = b2_kinematicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_WALL;
	fixture_def.filter.maskBits =
		FILTER_PLAYER_TANK
		| FILTER_CREEP_TANK
		| FILTER_BULLET
		//| FILTER_STRUCTURE
		//| FILTER_WALL
		//| FILTER_WATER
		//| FILTER_TREE
		//| FILTER_PICK_UP
		;

	fixture = body->CreateFixture(&fixture_def);
}

void Wall::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Wall::Serialize(uint32_t tick) {
	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<WallRecord>(
			id, type
		)
	);
}

void Wall::Deserialize(Record* record) {
	auto wall_record = static_cast<WallRecord*>(record);
}

void Wall::HandleInput(uint32_t tick) {
}

void Wall::ExecuteCommand(Command* command) {
}

void Wall::Update(float elapsed) {
}

void Wall::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void Wall::OnCollisionEnter(GameObject* other) {
}

void Wall::OnCollisionExit(GameObject* other) {
}
