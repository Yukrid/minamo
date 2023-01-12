#ifndef MINAMO_METHOD_UNIFORM_C0_INL
#define MINAMO_METHOD_UNIFORM_C0_INL

#include "uniform_c0.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    //(    minamo::method::UniformC0<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> UniformC0<D>::UniformC0 (Kernel& ker_) noexcept
        : kernel {ker_}
        , ucolor {1}
    {
        if(D==4 or D==2){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[BasicC1::BasicC1]  glEnable : "<<GL_BLEND<<"(GL_BLEND)"<<std::endl;
        std::cout<<"[BasicC1::BasicC1]  glBlendFunc : "<<GL_SRC_ALPHA<<"(GL_SRC_ALPHA)"<<" "<<GL_ONE_MINUS_SRC_ALPHA<<"(GL_ONE_MINUS_SRC_ALPHA)"<<std::endl;
#endif    
        }

        ker_.fragment_shd.uniform +=ucolor.get_code();
        switch(D){
            case 1: ker_.fragment_shd.main +=ker_.frag_out_name+"=vec4("+ucolor.get_name()+","  +ucolor.get_name()+","  +ucolor.get_name()       +", 1.f);";                break;
            case 2: ker_.fragment_shd.main +=ker_.frag_out_name+"=vec4("+ucolor.get_name()+".x,"+ucolor.get_name()+".x,"+ucolor.get_name()+".x, "+ucolor.get_name()+".y);"; break;
            case 3: ker_.fragment_shd.main +=ker_.frag_out_name+"=vec4("+ucolor.get_name()+".x,"+ucolor.get_name()+".y,"+ucolor.get_name()+".z, "+"1.f);";                break;
            case 4: ker_.fragment_shd.main +=ker_.frag_out_name+"=vec4("+ucolor.get_name()+".x,"+ucolor.get_name()+".y,"+ucolor.get_name()+".z, "+ucolor.get_name()+".w);"; break;
        }
    
        return;
    }



    //_ Destructive Function
    template <dim_t D> void UniformC0<D>::locate (void) noexcept
    {
        ucolor.locate(kernel.program_id);
        ucolor.set({0.5, 0.5, 0.5, 0.5});

        return;
    }
    

/*
    //(    minamo::method::UniformC0k<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> UniformC0k<D>::UniformC0k (const BufferVariable& bv_) noexcept
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
    template <dim_t D> void UniformC0k<D>::locate (ProgramID pid_) noexcept
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
