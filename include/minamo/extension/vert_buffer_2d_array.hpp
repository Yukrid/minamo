#ifndef MINAMO_EXTENSION_VERT_BUFFER_2D_ARRAY_HPP
#define MINAMO_EXTENSION_VERT_BUFFER_2D_ARRAY_HPP

#include "../forward.hpp"

#include <cstring>

//====================================//
//    Namespace: minamo::extension    //
//====================================//
namespace minamo::extension{
    
    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::VertBuffer2DArray<A> Structure Template    )//
    template <typename A>
    struct VertBuffer2DArray{
        
        //+    Type Definition    +//
        enum ErrorCode{
            SUCCESS, OVER_MAX_TEXTURE_WIDTH, OVER_MAX_TEXTURE_HEIGHT, FAILED_ALLOC, INVALID_ACCESS, INVALID_LOCK_OPERATION, LOCK_OVERFLOW
        };

        //+    Member Variable    +//
        size_t    width;
        size_t    height;
        size_t    nof_pages;
        A*        buffer;
        uint32_t* locks;


        //+    Member Function    +//
        //_ Constructor
        VertBuffer2DArray (void)                     noexcept;
        VertBuffer2DArray (size_t, size_t)           noexcept;
        VertBuffer2DArray (const VertBuffer2DArray&) noexcept;
        VertBuffer2DArray (VertBuffer2DArray&&)      noexcept;

        //_ Destructor
        ~VertBuffer2DArray (void) noexcept;

        //_ Destructive Function
        auto resize         (size_t, size_t)         noexcept -> ErrorCode;
        auto add_page       (void)                   noexcept -> ErrorCode;
        auto add_lock       (size_t, size_t)         noexcept -> ErrorCode;
        auto add_locks      (size_t, size_t, size_t) noexcept -> ErrorCode;
        auto subtract_lock  (size_t, size_t)         noexcept -> ErrorCode;
        auto subtract_locks (size_t, size_t, size_t) noexcept -> ErrorCode;
        auto get_lock       (size_t, size_t)         noexcept -> uint32_t&;
        auto get_locks      (size_t)                 noexcept -> uint32_t*;

        //_ Constant Function
        auto get_lock  (size_t, size_t) const noexcept -> const uint32_t&;
        auto get_locks (size_t)         const noexcept -> const uint32_t*;
        
        //_ Constant Binary Operator
        auto operator() (size_t, size_t)         const noexcept -> const A*;
        auto operator() (size_t, size_t, size_t) const noexcept -> const A&;

        //_ Destructive Binary Operator
        auto operator() (size_t, size_t)         noexcept -> A*;
        auto operator() (size_t, size_t, size_t) noexcept -> A&;
    };
}

#include "vert_buffer_2d_array.inl"

#endif
