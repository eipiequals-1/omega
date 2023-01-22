#include "time.hpp"

namespace omega::util {

std::vector<uptr<Time::TimeEvent>> Time::timers;
std::chrono::time_point<std::chrono::high_resolution_clock> Time::start;

} // namespace omega::util
