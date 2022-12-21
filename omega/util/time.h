#ifndef OMEGA_UTIL_TIME_H
#define OMEGA_UTIL_TIME_H

#include "omega/util/std.h"

#include <SDL2/SDL.h>

namespace omega::util {

class Time {
  public:
    static void init() {
        // start = SDL_GetTicks() / 1000.0f;
    }

    /**
     * @return the time since the initialization of the SDL library in milliseconds
     */
    static float get_time_millis() {
        return SDL_GetTicks();
    }

    /**
     * @return the time since the initialization of the SDL library in seconds
     */
    static float get_time() {
        return get_time_millis() / 1000.0f;
    }

    /**
     * Add a time event to be tracked
     * @param seconds
     * @param callback is called when the timer completes, passes the elapsed time since the timer ended as arg
     */
    static void add_timer(float seconds, std::function<void(float)> callback) {
        // create new event
        uptr<TimeEvent> time_event = create_uptr<TimeEvent>();
        time_event->duration = seconds;
        time_event->callback = callback;
        // add the new timer
        timers.push_back(std::move(time_event));
    }

    /**
     * Step the timers, call the callback if the timer is complete, and delete the timer event
     * @param dt delta time
     */
    static void tick(float dt) {
        // iterate in reverse all the events
        for (int i = timers.size() - 1; i >= 0; --i) {
            TimeEvent &event = *timers[(size_t)i];
            event.timer += dt;
            // if the timer is completed, call the callback function
            if (event.timer >= event.duration) {
                if (event.callback != nullptr) {
                    event.callback(event.timer - event.duration);
                }
                // delete the event now that it's complete
                // std::move(timers[(size_t)i]);
                timers.erase(timers.begin() + i);
            }
        }
    }

  private:
    struct TimeEvent {
        float timer = 0.0f;
        float duration;
        std::function<void(float)> callback = nullptr;
    };
    static std::vector<uptr<TimeEvent>> timers;
};

} // namespace omega::util

#endif // OMEGA_UTIL_TIME_H