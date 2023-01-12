#ifndef MINAMO_METHOD_MOLD_C1U1_HPP
#define MINAMO_METHOD_MOLD_C1U1_HPP

#include "../forward.hpp"
#include "../float.hpp"
#include "../glm_type.hpp"
#include "../uniform.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //(    minamo::method::MoldC1U1<D1, D2> Structure Template    )//
    template <dim_t D1, dim_t D2, TexEnum T>
    struct MoldC1U1{
    
        //+    Constant Expression Value    +//
        static constexpr dim_t mat_dim=(D2+1>4 ? D2 : D2+1);


        //+    Alias    +//
        using mat =matnxm<mat_dim, mat_dim>;


        //+    Member Variable    +//
        Kernel&        kernel;
        FloatData<D1>  color;
        FloatData<D2>  uv;
        Usmat<mat_dim> usmat;
        Utex<T>        utex;

        //+    Member Function    +//
        //_ Constructor
        MoldC1U1 (Kernel&) noexcept;

        //_ Destructor
        ~MoldC1U1 (void) noexcept =default;

        //_ Destructive Function
        void locate (void) noexcept;
        void prefix (void) noexcept;
        void suffix (void) noexcept;
    };
}

#include "mold_c1u1.inl"

#endif
