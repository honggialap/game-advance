#include "animation.h"

namespace Engine {

	void Animation::LoadTexture(const std::string& filename) {
		texture.loadFromFile(filename);
		texture.setSmooth(true);
		sprite.setTexture(texture);
	}

	void Animation::AddFrame(sf::IntRect texture_rect, float frame_time) {
		frames.push_back(
			std::make_pair(texture_rect, frame_time)
		);
	}

	void Animation::Play(bool loop) {
		frame = 0;
		elapsed_frame_time = 0;
		is_playing = true;
		is_looping = loop;
	}

	void Animation::Stop() {
		frame = 0;
		elapsed_frame_time = 0;
		is_playing = false;
		is_looping = false;
	}

	void Animation::Update(float elapsed) {
		sprite.setPosition(getPosition());

		if (!is_playing) {
			return;
		}

		elapsed_frame_time += elapsed;
		while (elapsed_frame_time > frames[frame].second) {
			elapsed_frame_time -= frames[frame].second;
			frame++;

			if (frame >= frames.size()) {
				frame = 0;
				if (!is_looping) {
					is_playing = false;
					is_looping = false;
				}
			}
		}

		sprite.setTextureRect(frames[frame].first);
	}

	void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite, states);
	}

}