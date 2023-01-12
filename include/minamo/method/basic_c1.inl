#ifndef MINAMO_METHOD_BASIC_C1_INL
#define MINAMO_METHOD_BASIC_C1_INL

#include "basic_c1.hpp"

//=================================//
//    Namespace: minamo::method    //
//=================================//
namespace minamo::method{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    //(    minamo::method::BasicC1<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> BasicC1<D>::BasicC1 (Kernel& ker_) noexcept
        : kernel {ker_}
        , color  {kernel}
    {
        if(D==4 or D==2){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[BasicC1::BasicC1]  glEnable : "<<GL_BLEND<<"(GL_BLEND)"<<std::endl;
        std::cout<<"[BasicC1::BasicC1]  glBlendFunc : "<<GL_SRC_ALPHA<<"(GL_SRC_ALPHA)"<<" "<<GL_ONE_MINUS_SRC_ALPHA<<"(GL_ONE_MINUS_SRC_ALPHA)"<<std::endl;
#endif    
        }
            
        kernel.vertex_shd.out  +=std::string("out ")+glsl_float<D>()+" "+color.variable.name+"_vf;";
        kernel.vertex_shd.main +=color.variable.name+"_vf="+color.variable.name+";";

        kernel.fragment_shd.in +=std::string("in ")+glsl_float<D>()+" "+color.variable.name+"_vf;";
        
        kernel.assign_color<D>(color.variable.name+"_vf");
    
        return;
    }



    //_ Destructive Function
    template <dim_t D> void BasicC1<D>::prefix (void) noexcept
    {
        color.prefix();

        return;
    }


    template <dim_t D> void BasicC1<D>::suffix (void) noexcept
    {
        color.suffix();

        return;
    }


/*
    //(    minamo::method::BasicC1k<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> BasicC1k<D>::BasicC1k (const BufferVariable& bv_) noexcept
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
    template <dim_t D> void BasicC1k<D>::locate (ProgramID pid_) noexcept
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
