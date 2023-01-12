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
    //(    minamo::TextureUniformVarialbe    )//
    //+    Member Function    +//
    //_ Constructor
    TextureUniformVariable::TextureUniformVariable (size_t sz_) noexcept
        : textures {new GLuint[sz_]}
        , ids      { }
    {
        glGenTextures(sz_, textures);
    
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[TextureUniformVariable::TextureUniformVariable]  glGenTextures   : ";
        for(size_t a=0; a<sz_; ++a) std::cout<<textures[a]<<" ";
        std::cout<<std::endl;
#endif
   
        return;
    }



    //_ Destructor
    TextureUniformVariable::~TextureUniformVariable (void) noexcept
    {
        glDeleteTextures(max_size, textures);
    
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[TextureUniformVariable::~TextureUniformVariable]  glDeleteTextures   : ";
        for(size_t a=0; a<max_size; ++a) std::cout<<textures[a]<<" ";
        std::cout<<std::endl;
#endif
        
        delete textures;

        return;
    }




    //(    minamo::Uf<D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> Uf<D>::Uf (size_t sz_) noexcept
    {
        uniform_var.name    =std::string(typeid(Uf<D>).name())+"_"+std::to_string(uniform_variable_count++);
        uniform_var.max_size=sz_;

        return;
    }

    

    //_ Destructive Function
    template <dim_t D> void Uf<D>::set (std::initializer_list<GLfloat> v_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
        
            glUseProgram(p.first);
            switch(D){
                case 1 : glUniform1f(p.second, v_.begin()[0]);                                              break;
                case 2 : glUniform2f(p.second, v_.begin()[0], v_.begin()[1]);                               break;
                case 3 : glUniform3f(p.second, v_.begin()[0], v_.begin()[1], v_.begin()[2]);                break;
                case 4 : glUniform4f(p.second, v_.begin()[0], v_.begin()[1], v_.begin()[2], v_.begin()[3]); break;
            }

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Uf::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Uf::set]  glUniform*f : "<<p.second<<std::endl;
#endif
        }

        return;
    }
     

    template <dim_t D> void Uf<D>::set (size_t sz_, const GLfloat* pv_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
        
            glUseProgram(p.first);
            switch(D){
                case 1 : glUniform1fv(p.second, sz_, pv_); break;
                case 2 : glUniform2fv(p.second, sz_, pv_); break;
                case 3 : glUniform3fv(p.second, sz_, pv_); break;
                case 4 : glUniform4fv(p.second, sz_, pv_); break;
            }
#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Uf::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Uf::set]  glUniform*fv : "<<p.second<<std::endl;
#endif
        }

        return;
    }
    


    //_ Constant Function
    template <dim_t D> void Uf<D>::locate (ProgramID pid_) const noexcept
    {
        glUseProgram(pid_);
        uniform_var.ids.push_back(UniformVariable::IDPair{pid_, glGetUniformLocation(pid_, uniform_var.name.c_str())});

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Uf::locate]  glUseProgram   : "<<pid_<<std::endl;
        std::cout<<"[Uf::locate]  glGetUniformLocation : "<<pid_<<" "<<((uniform_var.ids.end()-1)->second)<<std::endl;
#endif
            
        return;
    }

    
    template <dim_t D> auto Uf<D>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_float<D>()+" "+uniform_var.name+";";
        
        return str;
    }


    template <dim_t D> auto Uf<D>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }
    


    //(    minamo::Uu<D, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor

    template <dim_t D> Uu<D>::Uu (size_t sz_) noexcept
    {
        uniform_var.name    =std::string(typeid(Uu<D>).name())+"_"+std::to_string(uniform_variable_count++);
        uniform_var.max_size=sz_;

        return;
    }
    
    

    //_ Destructive Function
    template <dim_t D> void Uu<D>::set (std::initializer_list<GLuint> v_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
            
            glUseProgram(p.first);            
            switch(D){
                case 1 : glUniform1ui(p.second, v_.begin()[0]);                                              break;
                case 2 : glUniform2ui(p.second, v_.begin()[0], v_.begin()[1]);                               break;
                case 3 : glUniform3ui(p.second, v_.begin()[0], v_.begin()[1], v_.begin()[2]);                break;
                case 4 : glUniform4ui(p.second, v_.begin()[0], v_.begin()[1], v_.begin()[2], v_.begin()[3]); break;
            }
#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Uu::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Uu::set]  glUniform*ui : "<<p.second<<std::endl;
#endif
        }

        return;
    }
    

    template <dim_t D> void Uu<D>::set (size_t sz_, const GLuint* pv_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
        
            glUseProgram(p.first);
            switch(D){
                case 1 : glUniform1uiv(p.second, sz_, pv_); break;
                case 2 : glUniform2uiv(p.second, sz_, pv_); break;
                case 3 : glUniform3uiv(p.second, sz_, pv_); break;
                case 4 : glUniform4uiv(p.second, sz_, pv_); break;
            }
#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Uu::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Uu::set]  glUniform*uiv : "<<p.second<<std::endl;
#endif
        }

        return;
    }
    


    //_ Constant Function
    template <dim_t D> void Uu<D>::locate (ProgramID pid_) const noexcept
    {
        glUseProgram(pid_);
        uniform_var.ids.push_back(UniformVariable::IDPair{pid_, glGetUniformLocation(pid_, uniform_var.name.c_str())});

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Uf::locate]  glUseProgram   : "<<pid_<<std::endl;
        std::cout<<"[Uf::locate]  glGetUniformLocation : "<<pid_<<" "<<(uniform_var.ids.end()->second)<<std::endl;
#endif
        return;
    }


    template <dim_t D> auto Uu<D>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_uint<D>()+" "+uniform_var.name+";";
        
        return str;
    }


    template <dim_t D> auto Uu<D>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }



    //(    minamo::Ui<D, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> Ui<D>::Ui (size_t sz_) noexcept
    {
        uniform_var.name    =std::string(typeid(Ui<D>).name())+"_"+std::to_string(uniform_variable_count++);
        uniform_var.max_size=sz_;

        return;
    }
    
    

    //_ Destructive Function
    template <dim_t D> void Ui<D>::set (std::initializer_list<GLint> v_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
        
            glUseProgram(p.first);
            switch(D){
                case 1 : glUniform1i(p.second, v_.begin()[0]);                                              break;
                case 2 : glUniform2i(p.second, v_.begin()[0], v_.begin()[1]);                               break;
                case 3 : glUniform3i(p.second, v_.begin()[0], v_.begin()[1], v_.begin()[2]);                break;
                case 4 : glUniform4i(p.second, v_.begin()[0], v_.begin()[1], v_.begin()[2], v_.begin()[3]); break;
            }
#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Ui::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Ui::set]  glUniform*i : "<<p.second<<std::endl;
#endif
        }

        return;
    }
    

    template <dim_t D> void Ui<D>::set (size_t sz_, const GLint* pv_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
        
            glUseProgram(p.first);
            switch(D){
                case 1 : glUniform1iv(p.second, sz_, pv_); break;
                case 2 : glUniform2iv(p.second, sz_, pv_); break;
                case 3 : glUniform3iv(p.second, sz_, pv_); break;
                case 4 : glUniform4iv(p.second, sz_, pv_); break;
            }
#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Ui::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Ui::set]  glUniform*iv : "<<p.second<<std::endl;
#endif
        }

        return;
    }
    


    //_ Constant Function
    template <dim_t D> void Ui<D>::locate (ProgramID pid_) const noexcept
    {
        glUseProgram(pid_);
        uniform_var.ids.push_back(UniformVariable::IDPair{pid_, glGetUniformLocation(pid_, uniform_var.name.c_str())});
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Ui::locate]  glUseProgram   : "<<pid_<<std::endl;
        std::cout<<"[Ui::locate]  glGetUniformLocation : "<<pid_<<" "<<(uniform_var.ids.end()->second)<<std::endl;
#endif
       
        return;
    }


    template <dim_t D> auto Ui<D>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_int<D>()+" "+uniform_var.name+";";
        
        return str;
    }


    template <dim_t D> auto Ui<D>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }

 

    //(    minamo::Umat<D1, D2, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor

    template <dim_t D1, dim_t D2> Umat<D1, D2>::Umat (size_t sz_) noexcept
    {
        uniform_var.name    =std::string(typeid(Umat<D1, D2>).name())+"_"+std::to_string(uniform_variable_count++);
        uniform_var.max_size=sz_;

        return;
    }
    
    

    //_ Destructive Function
    template <dim_t D1, dim_t D2> void Umat<D1, D2>::set (size_t sz_, GLboolean bl_, const GLfloat* pv_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
            
            glUseProgram(p.first);
            switch(D1){
                case 2 :
                switch(D2){
                    case 2 : glUniformMatrix2fv(p.second, sz_, bl_, pv_);   break;
                    case 3 : glUniformMatrix2x3fv(p.second, sz_, bl_, pv_); break;
                    case 4 : glUniformMatrix2x4fv(p.second, sz_, bl_, pv_); break;
                }
                break;
    
                case 3 :
                switch(D2){
                    case 2 : glUniformMatrix3x2fv(p.second, sz_, bl_, pv_); break;
                    case 3 : glUniformMatrix3fv(p.second, sz_, bl_, pv_);   break;
                    case 4 : glUniformMatrix3x4fv(p.second, sz_, bl_, pv_); break;
                }
                break;
                
                case 4 :
                switch(D2){
                    case 2 : glUniformMatrix4x2fv(p.second, sz_, bl_, pv_); break;
                    case 3 : glUniformMatrix4x3fv(p.second, sz_, bl_, pv_); break;
                    case 4 : glUniformMatrix4fv(p.second, sz_, bl_, pv_);   break;
                }
                break;
            }

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Umat::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Umat::set]  glUniformMatrix*fv : "<<p.second<<std::endl;
#endif
        }

        return;
    }
   


    //_ Constant Function
    template <dim_t D1, dim_t D2> void Umat<D1, D2>::locate (ProgramID pid_) const noexcept
    {
        glUseProgram(pid_);
        uniform_var.ids.push_back(UniformVariable::IDPair{pid_, glGetUniformLocation(pid_, uniform_var.name.c_str())});

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Umat::locate]  glUseProgram   : "<<pid_<<std::endl;
        std::cout<<"[Umat::locate]  glGetUniformLocation : "<<pid_<<" "<<((uniform_var.ids.end()-1)->second)<<std::endl;
#endif

        return;
    }


    template <dim_t D1, dim_t D2> auto Umat<D1, D2>::get_code (void) const noexcept -> std::string
    {
        std::string str;
        str+=std::string("uniform ")+glsl_mat<D1, D2>()+" "+uniform_var.name+";";
        
        return str;
    }
    

    template <dim_t D1, dim_t D2> auto Umat<D1, D2>::get_name (void) const noexcept -> const std::string&
    {
        return uniform_var.name;
    }




    //(    minamo::Utex<T, N> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <TexEnum T> Utex<T>::Utex (size_t sz_) noexcept
        : uniform_var {sz_}
    {

        this->uniform_var.name    =std::string(typeid(Utex<T>).name())+"_"+std::to_string(uniform_variable_count++);
        this->uniform_var.max_size=sz_;
 
        return;
    }


    template <TexEnum T> void Utex<T>::set (GLint texture_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
            
            glUseProgram(p.first);
            glUniform1i(p.second, texture_);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Utex::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Utex::set]  glUniform1i : "<<p.second<<" "<<texture_<<" "<<GL_TEXTURE0<<std::endl;
#endif
        }
        return;
    }


    template <TexEnum T> void Utex<T>::set (size_t sz_, const GLint* pv_) noexcept
    {
        for(const UniformVariable::IDPair& p : uniform_var.ids){
        
            glUseProgram(p.first);
            glUniform1iv(p.second, sz_, pv_); break;

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Utex::set]  glUseProgram   : "<<p.first<<std::endl;
            std::cout<<"[Utex::set]  glUniform1iv : "<<p.second<<std::endl;
#endif
        }

        return;
    }
 

    template <TexEnum T> void Utex<T>::bind (size_t id_) noexcept
    {
        glBindTexture(tex_gl_uint<T>(), uniform_var.textures[id_]);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Utex::bind]  glBindTexture : "<<tex_gl_uint<T>()<<" "<<uniform_var.textures[id_]<<std::endl;
#endif
        return;
    }


    template <TexEnum T> void Utex<T>::unbind (void) noexcept
    {
        glBindTexture(tex_gl_uint<T>(), 0);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
            std::cout<<"[Utex::bind]  glBindTexture : "<<tex_gl_uint<T>()<<" "<<0<<std::endl;
#endif
        return;
    }

    
    template <TexEnum T> void Utex<T>::locate (ProgramID pid_) const noexcept
    {
        glUseProgram(pid_);
        uniform_var.ids.push_back(UniformVariable::IDPair{pid_, glGetUniformLocation(pid_, uniform_var.name.c_str())});
 
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Utex::locate]  glUseProgram   : "<<pid_<<std::endl;
        std::cout<<"[Utex::locate]  glGetUniformLocation : "<<pid_<<" "<<((uniform_var.ids.end()-1)->second)<<std::endl;
#endif

        return;
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
