#ifndef OMEGA_SCENE_SYSTEMS_HPP
#define OMEGA_SCENE_SYSTEMS_HPP

#include "omega/math/math.hpp"
#include "omega/scene/components.hpp"

namespace omega::scene {

inline math::mat4 create_model_transform(TransformComponent tc) {
    math::mat4 model{1.0f};

    model = math::rotate(model, tc.rotation, tc.rotation_axis);
    model = math::scale(model, tc.scale);
    model = math::translate(model, tc.position);

    return model;
}

inline math::mat4 create_model_transform(const math::vec3 &pos,
                                         const math::vec3 &rotation_axis,
                                         f32 rot,
                                         const math::vec3 &scale) {
    TransformComponent tc{.position = pos,
                          .rotation_axis = rotation_axis,
                          .rotation = rot,
                          .scale = scale};
    return create_model_transform(tc);
}

} // namespace omega::scene

#endif // OMEGA_SCENE_SYSTEMS_HPP
