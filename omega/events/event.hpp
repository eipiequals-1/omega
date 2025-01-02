#ifndef OMEGA_EVENTS_EVENT_HPP
#define OMEGA_EVENTS_EVENT_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

namespace omega::events {

using Event = SDL_Event;

/**
 * Describes possible events
 */
enum class EventType {
    quit = SDL_EVENT_QUIT,
    display_first = SDL_EVENT_DISPLAY_FIRST,
    window_resized = SDL_EVENT_WINDOW_RESIZED,
    display_last = SDL_EVENT_DISPLAY_LAST,
    key_down = SDL_EVENT_KEY_DOWN,
    key_up = SDL_EVENT_KEY_UP,
    mouse_button_down = SDL_EVENT_MOUSE_BUTTON_DOWN,
    mouse_button_up = SDL_EVENT_MOUSE_BUTTON_UP,
    mouse_wheel = SDL_EVENT_MOUSE_WHEEL,
    text_input = SDL_EVENT_TEXT_INPUT,
    text_editing = SDL_EVENT_TEXT_EDITING
};

/**
 * Represents the type of mouse
 */
enum class MouseButton {
    mouse_left = SDL_BUTTON_LEFT,
    mouse_center = SDL_BUTTON_MIDDLE,
    mouse_right = SDL_BUTTON_RIGHT
};

/**
 * Represents all the Keys
 */
enum class Key {
    k_escape = SDL_SCANCODE_ESCAPE,
    k_enter = SDL_SCANCODE_RETURN,
    k_space = SDL_SCANCODE_SPACE,
    k_backspace = SDL_SCANCODE_BACKSPACE,
    k_delete = SDL_SCANCODE_DELETE,
    k_tab = SDL_SCANCODE_TAB,
    k_left = SDL_SCANCODE_LEFT,
    k_right = SDL_SCANCODE_RIGHT,
    k_up = SDL_SCANCODE_UP,
    k_down = SDL_SCANCODE_DOWN,
    k_minus = SDL_SCANCODE_MINUS,
    k_plus = SDL_SCANCODE_EQUALS,

    k_l_shift = SDL_SCANCODE_LSHIFT,

    k_0 = SDL_SCANCODE_0,
    k_1 = SDL_SCANCODE_1,
    k_2 = SDL_SCANCODE_2,
    k_3 = SDL_SCANCODE_3,
    k_4 = SDL_SCANCODE_4,
    k_5 = SDL_SCANCODE_5,
    k_6 = SDL_SCANCODE_6,
    k_7 = SDL_SCANCODE_7,
    k_8 = SDL_SCANCODE_8,
    k_9 = SDL_SCANCODE_9,

    k_a = SDL_SCANCODE_A,
    k_b = SDL_SCANCODE_B,
    k_c = SDL_SCANCODE_C,
    k_d = SDL_SCANCODE_D,
    k_e = SDL_SCANCODE_E,
    k_f = SDL_SCANCODE_F,
    k_g = SDL_SCANCODE_G,
    k_h = SDL_SCANCODE_H,
    k_i = SDL_SCANCODE_I,
    k_j = SDL_SCANCODE_J,
    k_k = SDL_SCANCODE_K,
    k_l = SDL_SCANCODE_L,
    k_m = SDL_SCANCODE_M,
    k_n = SDL_SCANCODE_N,
    k_o = SDL_SCANCODE_O,
    k_p = SDL_SCANCODE_P,
    k_q = SDL_SCANCODE_Q,
    k_r = SDL_SCANCODE_R,
    k_s = SDL_SCANCODE_S,
    k_t = SDL_SCANCODE_T,
    k_u = SDL_SCANCODE_U,
    k_v = SDL_SCANCODE_V,
    k_w = SDL_SCANCODE_W,
    k_x = SDL_SCANCODE_X,
    k_y = SDL_SCANCODE_Y,
    k_z = SDL_SCANCODE_Z,

    k_l_ctrl = SDL_SCANCODE_LCTRL,

};

} // namespace omega::events

#endif // OMEGA_EVENTS_EVENT_HPP
