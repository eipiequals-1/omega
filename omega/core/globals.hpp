#ifndef OMEGA_CORE_GLOBALS_HPP
#define OMEGA_CORE_GLOBALS_HPP

#include "omega/core/viewport.hpp"
#include "omega/gfx/sprite_batch.hpp"
#include "omega/gfx/shape_renderer.hpp"
#include "omega/events/input_manager.hpp"
#include "omega/scene/scene.hpp"
#include "omega/util/asset_manager.hpp"

namespace omega::core {

struct Globals {
    Globals(const core::Viewport &vp, const std::string &scene_name = "Scene") : scene(vp, scene_name) {
    }
    // renderer globals
    gfx::SpriteBatch sprite_batch;
    gfx::ShapeRenderer shape_renderer;

    // scene globals
    scene::Scene scene;
    
    // input globals
    events::InputManager input;

    // asset globals
    util::AssetManager asset_manager;
};

} // namespace omega::core

#endif // OMEGA_CORE_GLOBALS_HPP
