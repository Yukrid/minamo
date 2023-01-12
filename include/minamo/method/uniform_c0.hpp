#ifndef MINAMO_METHOD_UNIFORM_C0_HPP
#define MINAMO_METHOD_UNIFORM_C0_HPP

#include "../forward.hpp"
#include "../glm_type.hpp"
#include "../kernel.hpp"
#include "../uniform.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //(    minamo::method::UniformC0<D> Structure Template    )//
    template <dim_t D>
    struct UniformC0{
        
        //+    Member Variable    +//
        Kernel& kernel;
        Uf<D>   ucolor;

        //+    Member Function    +//
        //_ Constructor
        UniformC0 (Kernel&) noexcept;

        //_ Destructor
        ~UniformC0 (void) noexcept =default;
        

        //_ Destructive Function
        void locate (void) noexcept;
    };
}

#include "uniform_c0.inl"

#endif
