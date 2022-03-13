#ifndef _LIBGL2D_CORE_ANIMATION_H_
#define _LIBGL2D_CORE_ANIMATION_H_

#include <vector>

#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/gfx/texture/texture_region.h"

namespace libGL2D {

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

}  // namespace libGL2D

#endif  // _LIBGL2D_CORE_ANIMATION_H_