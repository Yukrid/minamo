#ifndef MINAMO_UNIFORM_HPP
#define MINAMO_UNIFORM_HPP

#include "forward.hpp"
#include "inheritance.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::UniformVariable Structure    )//
    struct UniformVariable{
        
        //+    Member Variable    +//
        GLuint      id;
        std::string name;
        size_t      max_size;
    };



    //(    minamo::Uf<D_> Structure Template    )//
    template <uint16_t D_> struct Uf{

        static_assert(0<D_ and D_<5, "first template parameter of Uf should be 1, 2, 3, or 4");
        

        //+   Type Definition    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Uf (const std::string&, size_t =1) noexcept;
        
        //_ Destructive Function
        void set (std::initializer_list<GLfloat>) noexcept;
        void set (size_t, const GLfloat*)         noexcept;
    
        //_ Constant Function
        void locate   (GLuint) const noexcept;
        auto get_code (void)   const noexcept -> std::string;
        auto get_name (void)   const noexcept -> const std::string&;
    };



    //(    minamo::Uu<D_> Structure Template    )//
    template <uint16_t D_> struct Uu{

        static_assert(0<D_ and D_<5, "first template parameter of Uui should be 1, 2, 3, or 4");
        

        //+   Type Definition    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Uu (const std::string&, size_t =1) noexcept;
        
        //_ Destructive Function
        void set (std::initializer_list<GLuint>) noexcept;
        void set (size_t, const GLuint*)         noexcept;
    
        //_ Constant Function
        void locate   (GLuint) const noexcept;
        auto get_code (void)   const noexcept -> std::string;
        auto get_name (void)   const noexcept -> const std::string&;
    };
 



    //(    minamo::Ui<D_> Structure Template    )//
    template <uint16_t D_> struct Ui{

        static_assert(0<D_ and D_<5, "first template parameter of Ui should be 1, 2, 3, or 4");
        

        //+   Type Definition    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Ui (const std::string&, size_t =1) noexcept;
        
        //_ Destructive Function
        void set (std::initializer_list<GLint>) noexcept;
        void set (size_t, const GLint*)         noexcept;
    
        //_ Constant Function
        void locate   (GLuint) const noexcept;
        auto get_code (void)   const noexcept -> std::string;
        auto get_name (void)   const noexcept -> const std::string&;
    };



    //(    minamo::Umat<D1_, D2_> Structure Template    )//
    template <uint16_t D1_, uint16_t D2_> struct Umat{

        static_assert(1<D1_ and D1_<5 and 1<D2_ and D2_<5, "first and second template parameter of Umat should be 2, 3, or 4");

        //+   Member Variable    +//
        mutable UniformVariable uniform_var;


        //+   Member Function    +//
        //_ Constructor
        Umat (const std::string&, size_t =1) noexcept;
        
        //_ Destructive Function
        void set (size_t, GLboolean, const GLfloat*) noexcept;
    
        //_ Constant Function
        void locate   (GLuint) const noexcept;
        auto get_code (void)   const noexcept -> std::string;
        auto get_name (void)   const noexcept -> const std::string&;
    };
    


    //(    minamo::Utex<T> Structure Template    )//
    template <TexEnum T> struct Utex{
 
        //+   Type Definition    +//
        mutable UniformVariable uniform_var;
                

        //+   Member Function    +//
        //_ Constructor
        Utex(const std::string&, size_t =1) noexcept;
        
        //_ Destrucvtive Function
        auto bind   (void) noexcept -> GLuint;
        auto unbind (void) noexcept -> GLuint;

        //_ Constant Function
        void locate   (GLuint) const noexcept;
        auto get_code (void)   const noexcept -> std::string;
        auto get_name (void)   const noexcept -> const std::string&;
    };


    
    //-------------//
    //    Alias    //
    //-------------//
    using Uf1  =Uf<1>;
    using Uf2  =Uf<2>;
    using Uf3  =Uf<3>;
    using Uf4  =Uf<4>;

    template <uint16_t N> using Uf1s =InheritanceArray<Uf1, N>;
    template <uint16_t N> using Uf2s =InheritanceArray<Uf2, N>;
    template <uint16_t N> using Uf3s =InheritanceArray<Uf3, N>;
    template <uint16_t N> using Uf4s =InheritanceArray<Uf4, N>;
    
    template <uint16_t D_, uint16_t N> using Ufs =InheritanceArray<Uf<D_>, N>;
    
    using Uu1 =Uu<1>;
    using Uu2 =Uu<2>;
    using Uu3 =Uu<3>;
    using Uu4 =Uu<4>;

    template <uint16_t N> using Uu1s =InheritanceArray<Uu1, N>;
    template <uint16_t N> using Uu2s =InheritanceArray<Uu2, N>;
    template <uint16_t N> using Uu3s =InheritanceArray<Uu3, N>;
    template <uint16_t N> using Uu4s =InheritanceArray<Uu4, N>;

    template <uint16_t D_, uint16_t N> using Uus =InheritanceArray<Uu<D_>, N>;
 
    using Ui1 =Ui<1>;
    using Ui2 =Ui<2>;
    using Ui3 =Ui<3>;
    using Ui4 =Ui<4>;

    template <uint16_t N> using Ui1s =InheritanceArray<Ui1, N>;
    template <uint16_t N> using Ui2s =InheritanceArray<Ui2, N>;
    template <uint16_t N> using Ui3s =InheritanceArray<Ui3, N>;
    template <uint16_t N> using Ui4s =InheritanceArray<Ui4, N>;

    template <uint16_t D_, uint16_t N> using Uis =InheritanceArray<Ui<D_>, N>;
                                              
    using Umat2    =Umat<2, 2>;
    using Umat2x3  =Umat<2, 3>;
    using Umat2x4  =Umat<2, 4>;
    using Umat3x2  =Umat<3, 2>;
    using Umat3    =Umat<3, 3>;
    using Umat3x4  =Umat<3, 4>;
    using Umat4x2  =Umat<4, 2>;
    using Umat4x3  =Umat<4, 3>;
    using Umat4    =Umat<4, 4>;
    
    template <uint16_t D> using Usmat    =Umat<D, D>;
    
    template <uint16_t N> using Umat2s   =InheritanceArray<Umat2,   N>;
    template <uint16_t N> using Umat2x3s =InheritanceArray<Umat2x3, N>;
    template <uint16_t N> using Umat2x4s =InheritanceArray<Umat2x4, N>;
    template <uint16_t N> using Umat3x2s =InheritanceArray<Umat3x2, N>;
    template <uint16_t N> using Umat3s   =InheritanceArray<Umat3,   N>;
    template <uint16_t N> using Umat3x4s =InheritanceArray<Umat3x4, N>;
    template <uint16_t N> using Umat4x2s =InheritanceArray<Umat4x2, N>;
    template <uint16_t N> using Umat4x3s =InheritanceArray<Umat4x3, N>;
    template <uint16_t N> using Umat4s   =InheritanceArray<Umat4,   N>;
    
    template <uint16_t D, uint16_t N> using Usmats =InheritanceArray<Usmat<D>, N>;
    
    template <uint16_t D1_, uint16_t D2_, uint16_t N> using Umats =InheritanceArray<Umat<D1_, D2_>, N>;
}
#include "uniform.inl"

#endif
