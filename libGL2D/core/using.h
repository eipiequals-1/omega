#ifndef _LIBGL2D_CORE_USING_H_
#define _LIBGL2D_CORE_USING_H_

#include <memory>

namespace libGL2D {

template <typename T>
using Uptr = std::unique_ptr<T>;

template <typename T>
using Sptr = std::shared_ptr<T>;

}  // namespace libGL2D

#endif  // _LIBGL2D_CORE_USING_H_