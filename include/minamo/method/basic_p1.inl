#ifndef MINAMO_METHOD_BASIC_P1_INL
#define MINAMO_METHOD_BASIC_P1_INL

#include "basic_p1.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    //(    minamo::method::BasicP1<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> BasicP1<D>::BasicP1 (Kernel& ker_) noexcept
        : kernel {ker_}
        , coord  {ker_}
        , usmat  {1}
    {
        kernel.vertex_shd.uniform +=usmat.get_code();
        switch(D){
            case 1: kernel.vertex_shd.main +="gl_Position=vec4(("+usmat.get_name()+"*"+glsl_float<D+1>()+"("+coord.variable.name+", 1.f)).x, 0.f, 0.f, 1.f);"; break;
            case 2: kernel.vertex_shd.main +="gl_Position=vec4(("+usmat.get_name()+"*"+glsl_float<D+1>()+"("+coord.variable.name+", 1.f)).xy, 0.f, 1.f);"; break;
            case 3: kernel.vertex_shd.main +="gl_Position="+usmat.get_name()+"*"+glsl_float<D+1>()+"("+coord.variable.name+", 1.f);"; break;
            case 4: kernel.vertex_shd.main +="gl_Position="+usmat.get_name()+"*"+coord.variable.name+";"; break;
        }
    
        return;
    }



    //_ Destructive Function
    template <dim_t D> void BasicP1<D>::locate (void) noexcept
    {
        mat m{1.f};

        usmat.locate(kernel.program_id);
        usmat.set(1, GL_FALSE, &m[0][0]);

        return;
    }


    template <dim_t D> void BasicP1<D>::prefix (void) noexcept
    {
        coord.prefix();

        return;
    }


    template <dim_t D> void BasicP1<D>::suffix (void) noexcept
    {
        coord.suffix();

        return;
    }


/*
    //(    minamo::method::BasicP1k<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> BasicP1k<D>::BasicP1k (const BufferVariable& bv_) noexcept
        : FloatKernel<D> {bv_}
        , Usmat<mat_dim> {1}
    {
        Kernel::vertex_shd.uniform +=Usmat<mat_dim>::get_code();
        switch(D){
            case 1: Kernel::vertex_shd.main +="gl_Position=vec4(("+Usmat<mat_dim>::get_name()+"*"+glsl_float<D+1>()+"("+FloatAttrib<D>::var_name+", 1.f)).x, 0.f, 0.f, 1.f);"; break;
            case 2: Kernel::vertex_shd.main +="gl_Position=vec4(("+Usmat<mat_dim>::get_name()+"*"+glsl_float<D+1>()+"("+FloatAttrib<D>::var_name+", 1.f)).xy, 0.f, 1.f);"; break;
            case 3: Kernel::vertex_shd.main +="gl_Position="+Usmat<mat_dim>::get_name()+"*"+glsl_float<D+1>()+"("+FloatAttrib<D>::var_name+", 1.f);"; break;
            case 4: Kernel::vertex_shd.main +="gl_Position="+Usmat<mat_dim>::get_name()+"*"+FloatAttrib<D>::var_name+";"; break;
        }

        return;
    }



    //_ Destructive Function
    template <dim_t D> void BasicP1k<D>::locate (ProgramID pid_) noexcept
    {
        mat m{1.f};

        ProgramID pid =(pid_ ? pid_ : Kernel::program_id);

        Usmat<mat_dim>::locate(pid);
        Usmat<mat_dim>::set(1, GL_FALSE, &m[0][0]);

        return;
    }
    */
}
#endif
