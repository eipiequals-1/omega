#include "time.hpp"

namespace omega::util::time {

struct TimeEvent {
    f32 timer = 0.0f;
    f32 duration = 0.0f;
    std::function<void(f32)> callback = nullptr;
};

std::vector<uptr<TimeEvent>> timers;
std::chrono::time_point<std::chrono::high_resolution_clock> start;

void init() {
    start = std::chrono::high_resolution_clock::now();
}

std::chrono::time_point<std::chrono::high_resolution_clock> get_start() {
    return start;
}

void add_timer(f32 seconds, std::function<void(f32)> callback) {
    // create new event
    uptr<TimeEvent> time_event = create_uptr<TimeEvent>();
    time_event->duration = seconds;
    time_event->callback = callback;
    // add the new timer
    timers.push_back(std::move(time_event));
}

void tick(f32 dt) {
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

std::string get_current_time() {
    std::time_t current_time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return std::string(std::ctime(&current_time));
}

} // namespace omega::util::time
