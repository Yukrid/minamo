#ifndef MINAMO_UINT_INL
#define MINAMO_UINT_INL

#include <iostream>//

///#include "uint.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    //(    minamo::UintData<D> Structure Template    )//
    template <dim_t D> const std::string UintData<D>::data_name =typeid(UintData<D>).name();
    template <dim_t D>       index_t     UintData<D>::data_count=0;



    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::UintAttrib<D> Structure Template    )//
    //_ Constructor
    template <dim_t D>
    UintAttrib<D>::UintAttrib (Kernel& ker_, const Variable& var_) noexcept
        : kernel        {ker_}
        , variable      {var_}
        , location_id   {kernel.nof_locations++}
        , vertex_option { }
    {
        kernel.vertex_shd.in +="layout(location="+std::to_string(location_id)+") in "+glsl_uint<D>()+" "+variable.name+";";
    
        return;
    }


    template <dim_t D>
    UintAttrib<D>::UintAttrib (Kernel& ker_, const std::string& name_) noexcept
        : kernel        {ker_}
        , variable      {name_}
        , location_id   {kernel.nof_locations++}
        , vertex_option { }
    {
        kernel.vertex_shd.in +="layout(location="+std::to_string(location_id)+") in "+glsl_uint<D>()+" "+variable.name+";";
    
        return;
    }



    //_ Destructive Function
    template <dim_t D>
    void UintAttrib<D>::set_vert_option (const VertexOption& vo_) noexcept
    {
        vertex_option=vo_;
        
        return;
    }



    //_ Constant Function
    template <dim_t D>
    void UintAttrib<D>::prefix (void) const noexcept
    {
        glUseProgram(kernel.program_id);
        glEnableVertexAttribArray(location_id);
        glBindBuffer(GL_ARRAY_BUFFER, variable.buffer_id);
        glVertexAttribIPointer(location_id, D, GL_UNSIGNED_INT, vertex_option.stride, vertex_option.pointer);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[UintAttrib::prefix]  glUseProgram : "<<kernel.program_id<<std::endl;
        std::cout<<"[UintAttrib::prefix]  glEnableVertexAttribArray : "<<location_id<<std::endl;
        std::cout<<"[UintAttrib::prefix]  glBindBuffer : "<<variable.buffer_id<<std::endl;
        std::cout<<"[UintAttrib::prefix]  glVertexAttribPouinter : "<<location_id<<std::endl;
#endif    
        return;
    }
    

    template <dim_t D>
    void UintAttrib<D>::suffix (void) const noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(location_id);
        
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[UintAttrib::suffix]  glBindBuffer : "<<0<<std::endl;
        std::cout<<"[UintAttrib::suffix]  glDisableVertexAttribArray : "<<location_id<<std::endl;
#endif

        return;
    }
    



    //(    minamo::UintData<D> Structure Template    )//
    template <dim_t D>
    UintData<D>::UintData (Kernel& ker_) noexcept
        : UintAttrib<D> {ker_, data_name+"_"+std::to_string(data_count++)}
        , count_log      { }
        , enable_send    {false}
        , data           { }
    {
        return;
    }

     

    //_ Destructive Function
    template <dim_t D>
    void UintData<D>::attach (void) noexcept
    {
        if(enable_send){
            glBindBuffer(GL_ARRAY_BUFFER, UintAttrib<D>::variable.buffer_id);
            glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(GLuint), data.data(), UintAttrib<D>::kernel.draw_count.calc_buf_type(count_log));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            enable_send=false;

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[UintAttrib::attach]  glBindBuffer : "<<UintAttrib<D>::variable.buffer_id<<std::endl;
            std::cout<<"[UintAttrib::attach]  glBufferData : "<<data.size()*sizeof(GLuint)<<std::endl;
            std::cout<<"[UintAttrib::attach]  glBindBuffer : "<<0<<std::endl;
#endif
        }

        return;
    }

}
#endif
