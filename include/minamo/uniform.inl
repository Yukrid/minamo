#ifndef MINAMO_UNIFORM_INL
#define MINAMO_UNIFORM_INL

#include "uniform.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::Uf<D_> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <uint16_t D_> Uf<D_>::Uf (const std::string& sur_, size_t sz_) noexcept
    {
        uniform_var.name    =sur_+"_"+typeid(Uf<D_>).name();
        uniform_var.max_size=sz_;

        return;
    }
    
    

    //_ Destructive Function
    template <uint16_t D_> void Uf<D_>::set (std::initializer_list<GLfloat> v_) noexcept
    {
        switch(D_){
            case 1 : glUniform1f(uniform_var.id, v_.begin()[0]);                                              break;
            case 2 : glUniform2f(uniform_var.id, v_.begin()[0], v_.begin()[1]);                               break;
            case 3 : glUniform3f(uniform_var.id, v_.begin()[0], v_.begin()[1], v_.begin()[2]);                break;
            case 4 : glUniform4f(uniform_var.id, v_.begin()[0], v_.begin()[1], v_.begin()[2], v_.begin()[3]); break;
        }

        return;
    }
     

    template <uint16_t D_> void Uf<D_>::set (size_t sz_, const GLfloat* pv_) noexcept
    {
        switch(D_){
            case 1 : glUniform1fv(uniform_var.id, sz_, pv_); break;
            case 2 : glUniform2fv(uniform_var.id, sz_, pv_); break;
            case 3 : glUniform3fv(uniform_var.id, sz_, pv_); break;
            case 4 : glUniform4fv(uniform_var.id, sz_, pv_); break;
        }
    }
    


    //_ Constant Function
    template <uint16_t D_> void Uf<D_>::locate (GLuint pid_) const noexcept
    {
        uniform_var.id=glGetUniformLocation(pid_, uniform_var.name.c_str());
    }


    template <uint16_t D_> auto Uf<D_>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_float<D_>()+" "+uniform_var.name+";";
        
        return str;
    }


    template <uint16_t D_> auto Uf<D_>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }
    


    //(    minamo::Uu<D_, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor

    template <uint16_t D_> Uu<D_>::Uu (const std::string& sur_, size_t sz_) noexcept
    {
        uniform_var.name    =sur_+"_"+typeid(Uu<D_>).name();
        uniform_var.max_size=sz_;

        return;
    }
    
    

    //_ Destructive Function
    template <uint16_t D_> void Uu<D_>::set (std::initializer_list<GLuint> v_) noexcept
    {
        switch(D_){
            case 1 : glUniform1ui(uniform_var.id, v_.begin()[0]);                                              break;
            case 2 : glUniform2ui(uniform_var.id, v_.begin()[0], v_.begin()[1]);                               break;
            case 3 : glUniform3ui(uniform_var.id, v_.begin()[0], v_.begin()[1], v_.begin()[2]);                break;
            case 4 : glUniform4ui(uniform_var.id, v_.begin()[0], v_.begin()[1], v_.begin()[2], v_.begin()[3]); break;
        }

        return;
    }
    

    template <uint16_t D_> void Uu<D_>::set (size_t sz_, const GLuint* pv_) noexcept
    {
        switch(D_){
            case 1 : glUniform1uiv(uniform_var.id, sz_, pv_); break;
            case 2 : glUniform2uiv(uniform_var.id, sz_, pv_); break;
            case 3 : glUniform3uiv(uniform_var.id, sz_, pv_); break;
            case 4 : glUniform4uiv(uniform_var.id, sz_, pv_); break;
        }
    }
    


    //_ Constant Function
    template <uint16_t D_> void Uu<D_>::locate (GLuint pid_) const noexcept
    {
        uniform_var.id=glGetUniformLocation(pid_, uniform_var.name.c_str());
    }


    template <uint16_t D_> auto Uu<D_>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_uint<D_>()+" "+uniform_var.name+";";
        
        return str;
    }


    template <uint16_t D_> auto Uu<D_>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }



    //(    minamo::Ui<D_, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <uint16_t D_> Ui<D_>::Ui (const std::string& sur_, size_t sz_) noexcept
    {
        uniform_var.name    =sur_+"_"+typeid(Ui<D_>).name();
        uniform_var.max_size=sz_;

        return;
    }
    
    

    //_ Destructive Function
    template <uint16_t D_> void Ui<D_>::set (std::initializer_list<GLint> v_) noexcept
    {
        switch(D_){
            case 1 : glUniform1i(uniform_var.id, v_.begin()[0]);                                              break;
            case 2 : glUniform2i(uniform_var.id, v_.begin()[0], v_.begin()[1]);                               break;
            case 3 : glUniform3i(uniform_var.id, v_.begin()[0], v_.begin()[1], v_.begin()[2]);                break;
            case 4 : glUniform4i(uniform_var.id, v_.begin()[0], v_.begin()[1], v_.begin()[2], v_.begin()[3]); break;
        }

        return;
    }
    

    template <uint16_t D_> void Ui<D_>::set (size_t sz_, const GLint* pv_) noexcept
    {
        switch(D_){
            case 1 : glUniform1iv(uniform_var.id, sz_, pv_); break;
            case 2 : glUniform2iv(uniform_var.id, sz_, pv_); break;
            case 3 : glUniform3iv(uniform_var.id, sz_, pv_); break;
            case 4 : glUniform4iv(uniform_var.id, sz_, pv_); break;
        }
    }
    


    //_ Constant Function
    template <uint16_t D_> void Ui<D_>::locate (GLuint pid_) const noexcept
    {
        uniform_var.id=glGetUniformLocation(pid_, uniform_var.name.c_str());
    }


    template <uint16_t D_> auto Ui<D_>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_int<D_>()+" "+uniform_var.name+";";
        
        return str;
    }


    template <uint16_t D_> auto Ui<D_>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }



    //(    minamo::Umat<D1_, D2_, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor

    template <uint16_t D1_, uint16_t D2_> Umat<D1_, D2_>::Umat (const std::string& sur_, size_t sz_) noexcept
    {
        uniform_var.name    =sur_+"_"+typeid(Umat<D1_, D2_>).name();
        uniform_var.max_size=sz_;

        return;
    }
    
    

    //_ Destructive Function
    template <uint16_t D1_, uint16_t D2_> void Umat<D1_, D2_>::set (size_t sz_, GLboolean bl_, const GLfloat* pv_) noexcept
    {
        switch(D1_){
            case 2 :
            switch(D2_){
                case 2 : glUniformMatrix2fv(uniform_var.id, sz_, bl_, pv_);   break;
                case 3 : glUniformMatrix2x3fv(uniform_var.id, sz_, bl_, pv_); break;
                case 4 : glUniformMatrix2x4fv(uniform_var.id, sz_, bl_, pv_); break;
            }
            break;

            case 3 :
            switch(D2_){
                case 2 : glUniformMatrix3x2fv(uniform_var.id, sz_, bl_, pv_); break;
                case 3 : glUniformMatrix3fv(uniform_var.id, sz_, bl_, pv_);   break;
                case 4 : glUniformMatrix3x4fv(uniform_var.id, sz_, bl_, pv_); break;
            }
            break;
            
            case 4 :
            switch(D2_){
                case 2 : glUniformMatrix4x2fv(uniform_var.id, sz_, bl_, pv_); break;
                case 3 : glUniformMatrix4x3fv(uniform_var.id, sz_, bl_, pv_); break;
                case 4 : {
                    glUniformMatrix4fv(uniform_var.id, sz_, bl_, pv_);   break;
                }
            }
            break;
        }
        
        return;
    }
   


    //_ Constant Function
    template <uint16_t D1_, uint16_t D2_> void Umat<D1_, D2_>::locate (GLuint pid_) const noexcept
    {
        uniform_var.id=glGetUniformLocation(pid_, uniform_var.name.c_str());
    }


    template <uint16_t D1_, uint16_t D2_> auto Umat<D1_, D2_>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_mat<D1_, D2_>()+" "+uniform_var.name+";";
        
        return str;
    }
    

    template <uint16_t D1_, uint16_t D2_> auto Umat<D1_, D2_>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }




    //(    minamo::Utex<T, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <TexEnum T> Utex<T>::Utex (const std::string& sur_, size_t sz_) noexcept
    {
        this->uniform_var.name    =sur_+"_"+typeid(Utex<T>).name();
        this->uniform_var.max_size=sz_;
        
        return;
    }


    template <TexEnum T> auto Utex<T>::bind (void) noexcept -> GLuint
    {
        glBindTexture(tex_gl_uint<T>(), uniform_var.id);
        
        return tex_gl_uint<T>();
    }


    template <TexEnum T> auto Utex<T>::unbind (void) noexcept -> GLuint
    {
        glBindTexture(tex_gl_uint<T>(), 0);
        
        return tex_gl_uint<T>();
    }


    template <TexEnum T> void Utex<T>::locate (GLuint pid_) const noexcept
    {
        uniform_var.id=glGetUniformLocation(pid_, uniform_var.name.c_str());
    }


    template <TexEnum T> auto Utex<T>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_tex<T>()+" "+this->uniform_var.name+";";
        
        return str;
    }
 

    template <TexEnum T> auto Utex<T>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }      
}
#endif
