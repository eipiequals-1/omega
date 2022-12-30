#ifndef EDITOR_PANELS_SCENEHIERARCHY_H
#define EDITOR_PANELS_SCENEHIERARCHY_H

#include "omega/scene/components.h"
#include "omega/scene/entity.h"
#include "omega/scene/scene.h"
#include "omega/util/std.h"

namespace omega {

class SceneHierarchy {
  public:
    SceneHierarchy(util::sptr<scene::Scene> scene);
    ~SceneHierarchy();

    void render();

  private:
    void draw_entity_node(scene::Entity ent);

    util::sptr<scene::Scene> scene;

    scene::Entity selected_entity{};
};

} // namespace omega

#endif // EDITOR_PANELS_SCENEHIERARCHY_H