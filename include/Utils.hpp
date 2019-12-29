#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>

namespace SpaceThing::Utils {
    template<typename T>
    struct IrrDeleter {
        void operator()(T* ptr) {
            ptr->drop();
        }
    };

    template<typename T>
    using IrrPtr = std::unique_ptr<T, IrrDeleter<T>>;
}

#endif
