#ifndef LIBGL2D_CORE_ANIMATION_H
#define LIBGL2D_CORE_ANIMATION_H

#include <vector>

#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/gfx/texture/texture_region.h"

namespace libgl {

template <class T>
class Animation {
   public:
	Animation(const std::vector<T>& textures, float ms_per_frame) : timer_(0), ms_per_frame_(ms_per_frame) {
	}

	void Update(float dt) {
		timer_ += dt;
	}

	T& Get() {
		size_t tex_idx = ((int)timer_) % textures_.size();
		return textures_[tex_idx];
	}

   private:
	std::vector<T> textures_;
	float timer_;
	float ms_per_frame_;
};

}  // namespace libgl

#endif  // LIBGL2D_CORE_ANIMATION_H