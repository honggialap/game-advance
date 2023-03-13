#pragma once
#ifndef __ENGINE_ANIMATION_H__
#define __ENGINE_ANIMATION_H__

#include "SFML/Graphics.hpp"

namespace Engine {

	class Animation : public sf::Transformable, public sf::Drawable {
	protected:
		sf::Texture texture;
		sf::Sprite sprite;
		std::vector<std::pair<sf::IntRect, float>> frames;
		bool is_looping;
		bool is_playing;
		
		int frame;
		float elapsed_frame_time;

	public:
		void LoadTexture(const std::string& filename);
		void AddFrame(sf::IntRect texture_rect, float frame_time);

		void Play(bool loop = false);
		void Stop();

		void Update(float elapsed);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};

}

#endif // !__ENGINE_ANIMATION_H__
