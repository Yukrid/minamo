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
    struct Kernel : virtual public DrawCount{
       
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
        std::string name_code;
        GLuint      nof_locations;
        Shader      vertex_shd;
        Shader      fragment_shd;
        GLuint      program_id;
        GLuint      vertex_array_id;

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

        //_ Constant Function
        void print_vertex_shader   (std::ostream&) const noexcept;
        void print_fragment_shader (std::ostream&) const noexcept;

        //_ Constant Binary Operator
        auto operator= (const Kernel&) noexcept -> Kernel& =delete;
        auto operator= (Kernel&&)      noexcept -> Kernel& =delete;
    };
}
#endif
