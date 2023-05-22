#include "tree.h"
#include "game.h"
#include "world.h"

Tree* Tree::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<Tree>();
	world->dictionary[data.at("name")] = id;

	Tree* tree = static_cast<Tree*>(world->game_objects[id].get());
	
	tree->SetGame(game);
	tree->SetWorld(world);
	tree->SetId(id);
	tree->SetType(ACTOR_TREE);
	tree->SetName(data.at("name"));
	tree->SetLayer(data.at("layer"));

	tree->Load(data.at("data_path"));
	tree->SetResourcePath(data.at("data_path"));
	
	tree->SetPosition(data.at("x"), data.at("y"));

	return tree;
}

void Tree::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_tree.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	body_def.type = b2_kinematicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_TREE;

	fixture = body->CreateFixture(&fixture_def);
}

void Tree::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Tree::Serialize(uint32_t tick) {
	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<TreeRecord>(
			id, type
		)
	);
}

void Tree::Deserialize(Record* record) {
	auto tree_record = static_cast<TreeRecord*>(record);
}

void Tree::HandleInput(uint32_t tick) {
}

void Tree::ExecuteCommand(Command* command) {
}

void Tree::Update(float elapsed) {
}

void Tree::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void Tree::OnCollisionEnter(GameObject* other) {
}

void Tree::OnCollisionExit(GameObject* other) {
}