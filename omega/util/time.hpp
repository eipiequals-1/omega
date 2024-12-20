#ifndef OMEGA_UTIL_TIME_HPP
#define OMEGA_UTIL_TIME_HPP

#include <chrono>
#include <thread>

#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::util::time {

std::chrono::time_point<std::chrono::high_resolution_clock> get_start();

void init();

/**
 * @return the time since the initialization of the engine in milliseconds
 */
template <typename T>
T get_time_millis() {
    return static_cast<T>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - get_start())
            .count() *
        0.001 * 0.001);
}

/**
 * @return the time since the initialization of the engine in seconds
 */
template <typename T>
T get_time() {
    return static_cast<T>(get_time_millis<f64>() * 0.001);
}

/**
 * Add a time event to be tracked
 * @param seconds
 * @param callback is called when the timer completes,
 * passes the elapsed time since the timer ended
 */
void add_timer(f32 seconds, std::function<void(f32)> callback);

/**
 * Step the timers, call the callback if the timer is complete,
 * and delete the timer event
 * @param dt delta time
 */
void tick(f32 dt);

/**
 * Sleep the current thread for specified time
 * @param time seconds
 */
template <typename T>
void sleep(T time) {
    std::this_thread::sleep_for(
        std::chrono::microseconds((i64)(time * 1000.0 * 1000.0)));
}

/**
 * @return the current time formatted as such: Day-of-week Month Day hr:min:sec
 * yr
 */
std::string get_current_time();

} // namespace omega::util::time

#endif // OMEGA_UTIL_TIME_HPP
