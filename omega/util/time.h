#ifndef OMEGA_UTIL_TIME_H
#define OMEGA_UTIL_TIME_H

#include "omega/util/std.h"
#include "omega/util/types.h"

namespace omega::util {

class Time {
  public:
    /**
     * Add a time event to be tracked
     * @param seconds
     * @param callback is called when the timer completes, passes the elapsed time since the timer ended as arg
     */
    static void add_timer(f32 seconds, std::function<void(f32)> callback) {
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
    static void tick(f32 dt) {
        // iterate in reverse all the events
        for (i32 i = timers.size() - 1; i >= 0; --i) {
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
        f32 timer = 0.0f;
        f32 duration;
        std::function<void(f32)> callback = nullptr;
    };
    static std::vector<uptr<TimeEvent>> timers;
};

} // namespace omega::util

#endif // OMEGA_UTIL_TIME_H