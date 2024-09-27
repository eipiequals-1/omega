#ifndef OMEGA_SCENE_ANIMATION_HPP
#define OMEGA_SCENE_ANIMATION_HPP

#include <vector>

#include "omega/util/types.hpp"
namespace omega::scene {

template <typename T>
class Animation {
  public:
    Animation(f32 frame_duration, const std::vector<T> &frames)
        : frame_duration(frame_duration), frames(frames) {}

    i32 get_frame_number(f32 t) {
        i32 frame_number = (i32)(t / frame_duration);
        frame_number = frame_number % frames.size();
        return frame_number;
    }

    T &get_frame(f32 t) {
        return frames[get_frame_number(t)];
    }

  private:
    f32 frame_duration = 0.0f;
    std::vector<T> frames;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_ANIMATION_HPP
