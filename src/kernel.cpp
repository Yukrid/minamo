#include <iostream>

#include "minamo/kernel.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
          std::string Kernel::kernel_version ="330";
    const std::string Kernel::kernel_name    =typeid(Kernel).name();
          index_t     Kernel::kernel_count   =0;


    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::Kernel    )//
    //+    Static Member Function    +//
    void Kernel::set_version (const std::string& ver_) noexcept
    {
        kernel_version=ver_;

        return;
    }
    


    //+    Member Function    +//
    //_ Constructor
    Kernel::Kernel (void) noexcept
        : DrawCount      { }
        , name_code      {kernel_name+"_"+std::to_string(kernel_count++)}
        , nof_locations  {0}
    {
        vertex_shd.version  ="#version "+kernel_version+" core\r\n";
        vertex_shd.in       ="";
        vertex_shd.out      ="";
        vertex_shd.uniform  ="";
        vertex_shd.main_head="void main(){";
        vertex_shd.main     ="";
        vertex_shd.main_foot="}";

        fragment_shd.version  ="#version "+kernel_version+" core\r\n";
        fragment_shd.in       ="";
        fragment_shd.out      ="";
        fragment_shd.uniform  ="";
        fragment_shd.main_head="void main(){";
        fragment_shd.main     ="";
        fragment_shd.main_foot="}";
   
        program_id=glCreateProgram();
        
        glGenVertexArrays(1,&vertex_array_id);
        
        return;
    }


    //_ Destructor
    Kernel::~Kernel (void) noexcept
    {
        glDeleteVertexArrays(1, &vertex_array_id);

        glDeleteProgram(program_id);

        return;
    }



    //_ Destructive Function
    auto Kernel::compile_vertex_shader (void) noexcept -> std::string
    {
        GLint       result=GL_FALSE;
        int         info_log_length;
        std::string error_message;

        vertex_shd.id=glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shd.id, 1, vertex_shd.get_head_ptr(), nullptr);
        glCompileShader(vertex_shd.id);
        glGetShaderiv(vertex_shd.id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertex_shd.id, GL_INFO_LOG_LENGTH, &info_log_length);
        if(info_log_length>0){
            error_message.resize(info_log_length+1);
            glGetShaderInfoLog(vertex_shd.id, info_log_length, nullptr, &error_message[0]);   
        }
        glAttachShader(program_id, vertex_shd.id);
    
        return error_message; 
    }


    auto Kernel::compile_fragment_shader (void) noexcept -> std::string
    {
        GLint       result=GL_FALSE;
        int         info_log_length;
        std::string error_message;

        fragment_shd.id=glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shd.id, 1, fragment_shd.get_head_ptr(), nullptr);
        glCompileShader(fragment_shd.id);
        glGetShaderiv(fragment_shd.id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragment_shd.id, GL_INFO_LOG_LENGTH, &info_log_length);
        if(info_log_length>0){
            error_message.resize(info_log_length+1);
            glGetShaderInfoLog(fragment_shd.id, info_log_length, nullptr, &error_message[0]);   
        }
        glAttachShader(program_id, fragment_shd.id);
        
        return error_message; 
    }

    

    //_ Constant Function
    void Kernel::print_vertex_shader (std::ostream& os_) const noexcept
    {
        auto print =[](std::ostream& os_, const std::string& str_){
    
            for(const char& c: str_){
            
                if(c==';') os_<<c<<std::endl;
                else       os_<<c;
            }
        };

        print(os_, this->vertex_shd.version);
        os_<<std::endl;
        print(os_, this->vertex_shd.in);
        os_<<std::endl;
        print(os_, this->vertex_shd.out);
        os_<<std::endl;
        print(os_, this->vertex_shd.uniform);
        os_<<std::endl;
        print(os_, this->vertex_shd.main_head);
        os_<<std::endl;
        print(os_, this->vertex_shd.main);
        os_<<std::endl;
        print(os_, this->vertex_shd.main_foot);
        os_<<std::endl;

        return;
    }
 

    void Kernel::print_fragment_shader (std::ostream& os_) const noexcept
    {
        auto print =[](std::ostream& os_, const std::string& str_){
    
            for(const char& c: str_){
            
                if(c==';') os_<<c<<std::endl;
                else       os_<<c;
            }
        };

        print(os_, this->fragment_shd.version);
        os_<<std::endl;
        print(os_, this->fragment_shd.in);
        os_<<std::endl;
        print(os_, this->fragment_shd.out);
        os_<<std::endl;
        print(os_, this->fragment_shd.uniform);
        os_<<std::endl;
        print(os_, this->fragment_shd.main_head);
        os_<<std::endl;
        print(os_, this->fragment_shd.main);
        os_<<std::endl;
        print(os_, this->fragment_shd.main_foot);
        os_<<std::endl;
    
        return;
    }
}
