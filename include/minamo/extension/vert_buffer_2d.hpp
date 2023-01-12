#ifndef MINAMO_EXTENSION_VERT_BUFFER_2D_HPP
#define MINAMO_EXTENSION_VERT_BUFFER_2D_HPP

#include "../forward.hpp"

#include <cstring>

//====================================//
//    Namespace: minamo::extension    //
//====================================//
namespace minamo::extension{
    
    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::VertBuffer2D<A> Structure Template    )//
    template <typename A>
    struct VertBuffer2D{
        
        //+    Type Definition    +//
        enum ErrorCode{
            SUCCESS, OVER_MAX_TEXTURE_WIDTH, OVER_MAX_TEXTURE_HEIGHT, FAILED_ALLOC, INVALID_ACCESS, INVALID_LOCK_OPERATION, LOCK_OVERFLOW
        };

        //+    Member Variable    +//
        size_t    width;
        size_t    height;
        A*        buffer;
        uint32_t* locks;


        //+    Member Function    +//
        //_ Constructor
        VertBuffer2D (void)                noexcept;
        VertBuffer2D (size_t, size_t)      noexcept;
        VertBuffer2D (const VertBuffer2D&) noexcept;
        VertBuffer2D (VertBuffer2D&&)      noexcept;

        //_ Destructor
        ~VertBuffer2D (void) noexcept;

        //_ Destructive Function
        auto resize         (size_t, size_t) noexcept -> ErrorCode;
        auto rewidth        (size_t)         noexcept -> ErrorCode;
        auto reheight       (size_t)         noexcept -> ErrorCode;
        auto add_lock       (size_t)         noexcept -> ErrorCode;
        auto add_locks      (size_t, size_t) noexcept -> ErrorCode;
        auto subtract_lock  (size_t)         noexcept -> ErrorCode;
        auto subtract_locks (size_t, size_t) noexcept -> ErrorCode;

        //_ Constant Binary Operator
        auto operator() (size_t)         const noexcept -> const A*;
        auto operator() (size_t, size_t) const noexcept -> const A&;

        //_ Destructive Binary Operator
        auto operator() (size_t)         noexcept -> A*;
        auto operator() (size_t, size_t) noexcept -> A&;
    };
}

#include "vert_buffer_2d.inl"

#endif
