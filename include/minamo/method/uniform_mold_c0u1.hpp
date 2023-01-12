#ifndef MINAMO_METHOD_UNIFORM_MOLD_C0U1_HPP
#define MINAMO_METHOD_UNIFORM_MOLD_C0U1_HPP

#include "../forward.hpp"
#include "../float.hpp"
#include "../glm_type.hpp"
#include "../uniform.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //(    minamo::method::UniformMoldC0U1<D1, D2> Structure Template    )//
    template <dim_t D1, dim_t D2, TexEnum T>
    struct UniformMoldC0U1{
    
        //+    Constant Expression Value    +//
        static constexpr dim_t mat_dim=(D2+1>4 ? D2 : D2+1);


        //+    Alias    +//
        using mat =matnxm<mat_dim, mat_dim>;


        //+    Member Variable    +//
        Kernel&        kernel;
        FloatData<D2>  uv;
        Usmat<mat_dim> usmat;
        Uf<D1>         ucolor;
        Utex<T>        utex;

        //+    Member Function    +//
        //_ Constructor
        UniformMoldC0U1 (Kernel&) noexcept;

        //_ Destructor
        ~UniformMoldC0U1 (void) noexcept =default;

        //_ Destructive Function
        void locate (void) noexcept;
        void prefix (void) noexcept;
        void suffix (void) noexcept;
    };
    

/*
    //(    minamo::method::UniformMoldC0U1r<N> Structure Template    )//
    template <dim_t D>
    struct UniformMoldC0U1r{

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
        UniformMoldC0U1r (Kernel&, const Variable&) noexcept;

        //_ Destructor
        ~UniformMoldC0U1r (void) noexcept =default;

        //_ Destructive Function
        void locate (void) noexcept;
    };
*/
}

#include "uniform_mold_c0u1.inl"

#endif
