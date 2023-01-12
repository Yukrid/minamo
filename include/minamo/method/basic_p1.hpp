#ifndef MINAMO_METHOD_BASIC_P1_HPP
#define MINAMO_METHOD_BASIC_P1_HPP

#include "../forward.hpp"
#include "../float.hpp"
#include "../glm_type.hpp"
#include "../uniform.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //(    minamo::method::BasicP1<N> Structure Template    )//
    template <dim_t D>
    struct BasicP1{

        //+    Constant Expression Value    +//
        static constexpr dim_t mat_dim=(D+1>4 ? D : D+1);


        //+    Alias    +//
        using mat =matnxm<mat_dim, mat_dim>;


        //+    Member Variable    +//
        Kernel&        kernel;
        FloatData<D>   coord;
        Usmat<mat_dim> usmat;

        
        //+    Member Function    +//
        //_ Constructor
        BasicP1 (Kernel&) noexcept;

        //_ Destructor
        ~BasicP1 (void) noexcept =default;

        //_ Destructive Function
        void locate (void) noexcept;
        void prefix (void) noexcept;
        void suffix (void) noexcept;
    };
    

/*
    //(    minamo::method::BasicP1r<N> Structure Template    )//
    template <dim_t D>
    struct BasicP1r{

        //+    Constant Expression Value    +//
        static constexpr dim_t mat_dim=(D+1>4 ? D : D+1);


        //+    Alias    +//
        using mat =matnxm<mat_dim, mat_dim>;


        //+    Member Variable    +//
        Kernel&        kernel;
        FloatAttrib<D> attrib;
        Usmat<mat_dim> usmat;


        //+    Member Function    +//
        //_ Constructor
        BasicP1r (Kernel&, const Variable&) noexcept;

        //_ Destructor
        ~BasicP1r (void) noexcept =default;

        //_ Destructive Function
        void locate (void) noexcept;
    };
*/
}

#include "basic_p1.inl"

#endif
