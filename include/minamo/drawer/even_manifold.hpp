#ifndef MINAMO_DRAWER_UNIFORM_COLOR_MOLD_HPP
#define MINAMO_DRAWER_UNIFORM_COLOR_MOLD_HPP

#include "../forward.hpp"
#include "../method/basic_p1.hpp"
#include "../method/fixed_color.hpp"

#include <iostream>

//=================================//
//    Namespace: minamo::drawer    //
//=================================//
namespace minamo::drawer{

    //(    minamo::drawer::EvenManifold Structure Template    )//
    template <dim_t D1, dim_t D2>
    struct EvenManifold{

        //+    Member Variable    +//
        Kernel                 kernel;
        method::BasicP1<D1>    basic_p1;
        method::FixedColor<D2> fixed_color;

        
        //+    Member Function    +//
        //_ Constructor
        EvenManifold (void) noexcept;

        //_ Destructor
        ~EvenManifold (void) noexcept;

        //_ Destructive Function
        void draw (GLenum, GLsizei) noexcept;
    };
}

#include "even_manifold.inl"

#endif
