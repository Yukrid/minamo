#ifndef MINAMO_KERNEL_HPP
#define MINAMO_KERNEL_HPP

#include <string>

#include "forward.hpp"
#include "shader.hpp"
#include "draw_count.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::Kernel    )//
    struct Kernel{
       
        public:
        //+    Static Constant Expression Function   +//
        static constexpr int _kernel_authentification_key (void) {return 0;};

        private:
        //+    Static Member Variable    +//
        static       std::string kernel_version;
        static const std::string kernel_name;
        static       index_t     kernel_count;

        public:
        //+    Static Member Variable    +//
        static void set_version (const std::string&) noexcept;

        public:
        //+    Member Variable     +//
        std::string   frag_out_name;
        GLuint        nof_locations;
        Shader        vertex_shd;
        Shader        fragment_shd;
        ProgramID     program_id;
        VertexArrayID vertex_array_id;
        DrawCount     draw_count;
        GLint         texture_id;

        public:
        //+    Member Function    +//
        //_ Constructor
        Kernel (void)          noexcept;
        Kernel (const Kernel&) noexcept =delete;
        Kernel (Kernel&&)      noexcept =delete;

        //_ Destructor
        virtual ~Kernel (void) noexcept;

        //_ Destructive Function
        auto compile_vertex_shader   (void) noexcept -> std::string;
        auto compile_fragment_shader (void) noexcept -> std::string;
        auto use_texture             (void) noexcept -> GLint;

        //_ Constant Function
        void print_vertex_shader   (std::ostream&) const noexcept;
        void print_fragment_shader (std::ostream&) const noexcept;

        //_ Constant Binary Operator
                           auto operator=    (const Kernel&)      noexcept -> Kernel& =delete;
                           auto operator=    (Kernel&&)           noexcept -> Kernel& =delete;
        template <dim_t D> void assign_color (const std::string&) noexcept;
    };



    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::Kernel    )//
    template <dim_t D>
    void Kernel::assign_color (const std::string& str_) noexcept
    {
        switch(D){
            case 1: fragment_shd.main +=frag_out_name+"=vec4("+str_+","  +str_+","  +str_+","  +"1.f"    +");";  break;
            case 2: fragment_shd.main +=frag_out_name+"=vec4("+str_+".x,"+str_+".x,"+str_+".x,"+str_+".y"+");";  break;
            case 3: fragment_shd.main +=frag_out_name+"=vec4("+str_+".x,"+str_+".y,"+str_+".z,"+"1.f"    +");";  break;
            case 4: fragment_shd.main +=frag_out_name+"="+str_+";";  break;
        };

        return;
    }
}
#endif
