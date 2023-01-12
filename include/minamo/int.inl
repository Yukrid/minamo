#ifndef MINAMO_INT_INL
#define MINAMO_INT_INL

#include <iostream>//

#include "int.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    //(    minamo::IntData<D> Structure Template    )//
    template <dim_t D> const std::string IntData<D>::data_name =typeid(IntData<D>).name();
    template <dim_t D>       index_t     IntData<D>::data_count=0;



    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::IntAttrib<D> Structure Template    )//
    //_ Constructor
    template <dim_t D>
    IntAttrib<D>::IntAttrib (Kernel& ker_, const Variable& var_) noexcept
        : kernel        {ker_}
        , variable      {var_}
        , location_id   {kernel.nof_locations++}
        , vertex_option { }
    {
        kernel.vertex_shd.in +="layout(location="+std::to_string(location_id)+") in "+glsl_int<D>()+" "+variable.name+";";
    
        return;
    }


    template <dim_t D>
    IntAttrib<D>::IntAttrib (Kernel& ker_, const std::string& name_) noexcept
        : kernel        {ker_}
        , variable      {name_}
        , location_id   {kernel.nof_locations++}
        , vertex_option { }
    {
        kernel.vertex_shd.in +="layout(location="+std::to_string(location_id)+") in "+glsl_int<D>()+" "+variable.name+";";
    
        return;
    }



    //_ Destructive Function
    template <dim_t D>
    void IntAttrib<D>::set_vert_option (const VertexOption& vo_) noexcept
    {
        vertex_option=vo_;
        
        return;
    }



    //_ Constant Function
    template <dim_t D>
    void IntAttrib<D>::prefix (void) const noexcept
    {
        glUseProgram(kernel.program_id);
        glEnableVertexAttribArray(location_id);
        glBindBuffer(GL_ARRAY_BUFFER, variable.buffer_id);
        glVertexAttribIPointer(location_id, D, GL_INT, vertex_option.stride, vertex_option.pointer);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[IntAttrib::prefix]  glUseProgram : "<<kernel.program_id<<std::endl;
        std::cout<<"[IntAttrib::prefix]  glEnableVertexAttribArray : "<<location_id<<std::endl;
        std::cout<<"[IntAttrib::prefix]  glBindBuffer : "<<variable.buffer_id<<std::endl;
        std::cout<<"[IntAttrib::prefix]  glVertexAttribPointer : "<<location_id<<std::endl;
#endif    
        return;
    }
    

    template <dim_t D>
    void IntAttrib<D>::suffix (void) const noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(location_id);
        
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[IntAttrib::suffix]  glBindBuffer : "<<0<<std::endl;
        std::cout<<"[IntAttrib::suffix]  glDisableVertexAttribArray : "<<location_id<<std::endl;
#endif

        return;
    }
    



    //(    minamo::IntData<D> Structure Template    )//
    template <dim_t D>
    IntData<D>::IntData (Kernel& ker_) noexcept
        : IntAttrib<D> {ker_, data_name+"_"+std::to_string(data_count++)}
        , count_log      { }
        , enable_send    {false}
        , data           { }
    {
        return;
    }

     

    //_ Destructive Function
    template <dim_t D>
    void IntData<D>::attach (void) noexcept
    {
        if(enable_send){
            glBindBuffer(GL_ARRAY_BUFFER, IntAttrib<D>::variable.buffer_id);
            glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(GLint), data.data(), IntAttrib<D>::kernel.draw_count.calc_buf_type(count_log));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            enable_send=false;

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[IntAttrib::attach]  glBindBuffer : "<<IntAttrib<D>::variable.buffer_id<<std::endl;
            std::cout<<"[IntAttrib::attach]  glBufferData : "<<data.size()*sizeof(GLint)<<std::endl;
            std::cout<<"[IntAttrib::attach]  glBindBuffer : "<<0<<std::endl;
#endif
        }

        return;
    }

}
#endif
