#ifndef MINAMO_METHOD_BASIC_C1_HPP
#define MINAMO_METHOD_BASIC_C1_HPP

#include "../forward.hpp"
#include "../float.hpp"
#include "../glm_type.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //(    minamo::method::BasicC1<N> Structure Template    )//
    template <dim_t D>
    struct BasicC1{

        //+    Member Variable    +//
        Kernel&        kernel;
        FloatData<D>   color;
        

        //+    Member Function    +//
        //_ Constructor
        BasicC1 (Kernel&) noexcept;

        //_ Destructor
        ~BasicC1 (void) noexcept =default;

        //_ Destructive Function
        void prefix (void) noexcept;
        void suffix (void) noexcept;
    };
    

/*
    //(    minamo::method::BasicC1r<N> Structure Template    )//
    template <dim_t D>
    struct BasicC1r{

        //+    Member Variable    +//
        FloatAttrib<D> attrib;


        //+    Member Function    +//
        //_ Constructor
        BasicC1r (Kernel&, const Variable&) noexcept;

        //_ Destructor
        ~BasicC1r (void) noexcept =default;

        //_ Destructive Function
        void locate (void) noexcept;
        void prefix (void) noexcept;
        void suffix (void) noexcept;
    };
    */
}

#include "basic_c1.inl"

#endif
