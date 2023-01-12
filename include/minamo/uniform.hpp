#ifndef MINAMO_UNIFORM_HPP
#define MINAMO_UNIFORM_HPP

#include <array>
#include <vector>
#include <string>

#include "forward.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    inline size_t uniform_variable_count =0;



    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::UniformVariable Structure    )//
    struct UniformVariable{
        
        //+    Alias    +//
        using IDPair=std::pair<ProgramID, UniformID>; 

        //+    Member Variable    +//
        std::vector<IDPair> ids;
        std::string         name;
        size_t              max_size;
    };
    

    //(    minamo::UniformVariable Structure    )//
    struct TextureUniformVariable{
        
        //+    Alias    +//
        using IDPair=std::pair<ProgramID, UniformID>; 

        
        //+    Mebmer Function    +//
        //_ Constructor
        TextureUniformVariable (size_t) noexcept;

        //_ Destructor
        ~TextureUniformVariable (void) noexcept;


        //+    Member Variable    +//
        GLuint*             textures;
        std::vector<IDPair> ids;
        std::string         name;
        size_t              max_size;
    };
   


    //(    minamo::Uf<D> Structure Template    )//
    template <dim_t D> struct Uf{

        static_assert(0<D and D<5, "first template parameter of Uf should be 1, 2, 3, or 4");


        //+   Type Definition    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Uf (size_t =1) noexcept;
        
        //_ Destructive Function
        void set (std::initializer_list<GLfloat>) noexcept;
        void set (size_t, const GLfloat*)         noexcept;
    
        //_ Constant Function
        void locate   (ProgramID) const noexcept;
        auto get_code (void)      const noexcept -> std::string;
        auto get_name (void)      const noexcept -> const std::string&;
    };



    //(    minamo::Uu<D> Structure Template    )//
    template <dim_t D> struct Uu{

        static_assert(0<D and D<5, "first template parameter of Uui should be 1, 2, 3, or 4");
        

        //+   Type Definition    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Uu (size_t =1) noexcept;
        
        //_ Destructive Function
        void set (std::initializer_list<GLuint>) noexcept;
        void set (size_t, const GLuint*)         noexcept;
    
        //_ Constant Function
        void locate   (ProgramID) const noexcept;
        auto get_code (void)      const noexcept -> std::string;
        auto get_name (void)      const noexcept -> const std::string&;
    };
 



    //(    minamo::Ui<D> Structure Template    )//
    template <dim_t D> struct Ui{

        static_assert(0<D and D<5, "first template parameter of Ui should be 1, 2, 3, or 4");
        

        //+   Type Definition    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Ui (size_t =1) noexcept;
        
        //_ Destructive Function
        void set (std::initializer_list<GLint>) noexcept;
        void set (size_t, const GLint*)         noexcept;
    
        //_ Constant Function
        void locate   (ProgramID) const noexcept;
        auto get_code (void)      const noexcept -> std::string;
        auto get_name (void)      const noexcept -> const std::string&;
    };



    //(    minamo::Umat<D1, D2> Structure Template    )//
    template <dim_t D1, dim_t D2> struct Umat{

        static_assert(1<D1 and D1<5 and 1<D2 and D2<5, "first and second template parameter of Umat should be 2, 3, or 4");

        //+   Member Variable    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Umat (size_t =1) noexcept;
        
        //_ Destructive Function
        void set (size_t, GLboolean, const GLfloat*) noexcept;
    
        //_ Constant Function
        void locate   (ProgramID) const noexcept;
        auto get_code (void)      const noexcept -> std::string;
        auto get_name (void)      const noexcept -> const std::string&;
    };
    


    //(    minamo::Utex<T> Structure Template    )//
    template <TexEnum T> struct Utex{
 
        //+   Type Definition    +//
        mutable TextureUniformVariable uniform_var;
    

        //+   Member Function    +//
        //_ Constructor
        Utex(size_t =1) noexcept;
        
        //_ Destrucvtive Function
        void set    (GLint)                noexcept;
        void set    (size_t, const GLint*) noexcept;
        void bind   (size_t)               noexcept;
        void unbind (void)                 noexcept;

        //_ Constant Function
        void locate   (ProgramID) const noexcept;
        auto get_code (void)      const noexcept -> std::string;
        auto get_name (void)      const noexcept -> const std::string&;
    };


    
    //-------------//
    //    Alias    //
    //-------------//
    using Uf1  =Uf<1>;
    using Uf2  =Uf<2>;
    using Uf3  =Uf<3>;
    using Uf4  =Uf<4>;

    template <size_t N> using Uf1s =std::array<Uf1, N>;
    template <size_t N> using Uf2s =std::array<Uf2, N>;
    template <size_t N> using Uf3s =std::array<Uf3, N>;
    template <size_t N> using Uf4s =std::array<Uf4, N>;
    
    template <dim_t D, size_t N> using Ufs =std::array<Uf<D>, N>;
    
    using Uu1 =Uu<1>;
    using Uu2 =Uu<2>;
    using Uu3 =Uu<3>;
    using Uu4 =Uu<4>;

    template <size_t N> using Uu1s =std::array<Uu1, N>;
    template <size_t N> using Uu2s =std::array<Uu2, N>;
    template <size_t N> using Uu3s =std::array<Uu3, N>;
    template <size_t N> using Uu4s =std::array<Uu4, N>;

    template <dim_t D, size_t N> using Uus =std::array<Uu<D>, N>;
 
    using Ui1 =Ui<1>;
    using Ui2 =Ui<2>;
    using Ui3 =Ui<3>;
    using Ui4 =Ui<4>;

    template <size_t N> using Ui1s =std::array<Ui1, N>;
    template <size_t N> using Ui2s =std::array<Ui2, N>;
    template <size_t N> using Ui3s =std::array<Ui3, N>;
    template <size_t N> using Ui4s =std::array<Ui4, N>;

    template <dim_t D, size_t N> using Uis =std::array<Ui<D>, N>;
                                              
    using Umat2    =Umat<2, 2>;
    using Umat2x3  =Umat<2, 3>;
    using Umat2x4  =Umat<2, 4>;
    using Umat3x2  =Umat<3, 2>;
    using Umat3    =Umat<3, 3>;
    using Umat3x4  =Umat<3, 4>;
    using Umat4x2  =Umat<4, 2>;
    using Umat4x3  =Umat<4, 3>;
    using Umat4    =Umat<4, 4>;
    
    template <dim_t D> using Usmat    =Umat<D, D>;
    
    template <size_t N> using Umat2s   =std::array<Umat2,   N>;
    template <size_t N> using Umat2x3s =std::array<Umat2x3, N>;
    template <size_t N> using Umat2x4s =std::array<Umat2x4, N>;
    template <size_t N> using Umat3x2s =std::array<Umat3x2, N>;
    template <size_t N> using Umat3s   =std::array<Umat3,   N>;
    template <size_t N> using Umat3x4s =std::array<Umat3x4, N>;
    template <size_t N> using Umat4x2s =std::array<Umat4x2, N>;
    template <size_t N> using Umat4x3s =std::array<Umat4x3, N>;
    template <size_t N> using Umat4s   =std::array<Umat4,   N>;
    
    template <dim_t D, size_t N> using Usmats =std::array<Usmat<D>, N>;
    
    template <dim_t D1, dim_t D2, size_t N> using Umats =std::array<Umat<D1, D2>, N>;
}
#include "uniform.inl"

#endif
