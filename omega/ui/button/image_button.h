#ifndef OMEGA_UI_BUTTON_IMAGEBUTTON_H
#define OMEGA_UI_BUTTON_IMAGEBUTTON_H

#include "omega/gfx/texture/texture.h"
#include "omega/ui/button/button.h"
#include "omega/util/util.h"

namespace omega::ui::button {

class ImageButton : public Button {
  public:
    ImageButton(f32 x, f32 y, f32 w, f32 h, std::function<void()> on_click);
    virtual ~ImageButton() override;

    virtual void render() override;
    virtual void set_focus_texture(Texture *focus) { this->focus = focus; }
    virtual void set_unfocus_texture(Texture *un_focus) { this->un_focus = un_focus; }

  protected:
    Texture *focus;
    Texture *un_focus;
};

} // namespace omega::ui::button

#endif // OMEGA_UI_BUTTON_IMAGEBUTTON_H