#ifndef OMEGA_UI_BUTTON_TEXTBUTTON_H
#define OMEGA_UI_BUTTON_TEXTBUTTON_H

#include "omega/gfx/texture/texture.hpp"
#include "omega/ui/button/image_button.hpp"
#include "omega/ui/font.hpp"
#include "omega/util/std.hpp"

namespace omega::ui::button {

using namespace omega::util;
using namespace omega::gfx;

struct TextButtonBuilder {
    std::string text;
    Font *font;
    float width, height;
    glm::vec4 color;
};

class TextButton : public ImageButton {
  public:
    TextButton(float x, float y, float w, float h, std::function<void()> on_click, const TextButtonBuilder &builder);
    virtual ~TextButton() override = default;

    virtual void render() override;

  protected:
    util::sptr<gfx::texture::Texture> text_texture;
    float text_width, text_height;
};

} // namespace omega::ui::button

#endif // OMEGA_UI_BUTTON_TEXTBUTTON_H
