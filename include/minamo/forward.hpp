#ifndef MINAMO_FORWARD_HPP
#define MINAMO_FORWARD_HPP

#include <GL/glew.h>

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-------------//
    //    Alias    //
    //-------------//
    using index_t       =size_t;
    using dim_t         =uint_fast8_t;
    using ProgramID     =GLuint;
    using LocationID    =GLuint;
    using VertexArrayID =GLuint;
    using BufferID      =GLuint;
    using UniformID     =GLint;
    
    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(   minamo::TexEnum    )//
    enum TexEnum{
        
        // float
        s1D, s2D, s3D, sCube, s2DRect, s1DShadow, s2DShadow, sCubeShadow, s2DRectShadow,
        s1DArray, s2DArray, sCubeArray, s1DArrayShadow, s2DArrayShadow, sCubeArrayShadow, sBuffer, s2DMS, s2DMSArray,

        // int
        is1D, is2D, is3D, isCube, is2DRect, is1DArray, is2DArray, isCubeArray, isBuffer, is2DMS, is2DMSArray,

        // uint
        us1D, us2D, us3D, usCube, us2DRect, us1DArray, us2DArray, usCubeArray, usBuffer, us2DMS, us2DMSArray
    };

    

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    template <dim_t D> constexpr auto glsl_float    (void) -> const char* { return ""; }
    template <>        constexpr auto glsl_float<1> (void) -> const char* { return "float"; }
    template <>        constexpr auto glsl_float<2> (void) -> const char* { return "vec2"; }
    template <>        constexpr auto glsl_float<3> (void) -> const char* { return "vec3"; }
    template <>        constexpr auto glsl_float<4> (void) -> const char* { return "vec4"; }
    
    template <dim_t D> constexpr auto glsl_uint     (void) -> const char* { return ""; }
    template <>        constexpr auto glsl_uint<1>  (void) -> const char* { return "uint"; }
    template <>        constexpr auto glsl_uint<2>  (void) -> const char* { return "uvec2"; }
    template <>        constexpr auto glsl_uint<3>  (void) -> const char* { return "uvec3"; }
    template <>        constexpr auto glsl_uint<4>  (void) -> const char* { return "uvec4"; }
    
    template <dim_t D> constexpr auto glsl_int      (void) -> const char* { return ""; }
    template <>        constexpr auto glsl_int<1>   (void) -> const char* { return "int"; }
    template <>        constexpr auto glsl_int<2>   (void) -> const char* { return "ivec2"; }
    template <>        constexpr auto glsl_int<3>   (void) -> const char* { return "ivec3"; }
    template <>        constexpr auto glsl_int<4>   (void) -> const char* { return "ivec4"; }
    
    template <dim_t D1, dim_t D2> constexpr auto glsl_mat       (void) -> const char* { return ""; }
    template <>                   constexpr auto glsl_mat<2, 2> (void) -> const char* { return "mat2"; }
    template <>                   constexpr auto glsl_mat<2, 3> (void) -> const char* { return "mat2x3"; }
    template <>                   constexpr auto glsl_mat<2, 4> (void) -> const char* { return "mat2x4"; }
    template <>                   constexpr auto glsl_mat<3, 2> (void) -> const char* { return "mat3x2"; }
    template <>                   constexpr auto glsl_mat<3, 3> (void) -> const char* { return "mat3"; }
    template <>                   constexpr auto glsl_mat<3, 4> (void) -> const char* { return "mat3x4"; }
    template <>                   constexpr auto glsl_mat<4, 2> (void) -> const char* { return "mat4x2"; }
    template <>                   constexpr auto glsl_mat<4, 3> (void) -> const char* { return "mat4x3"; }
    template <>                   constexpr auto glsl_mat<4, 4> (void) -> const char* { return "mat4"; }
    
    template <TexEnum T> constexpr auto glsl_tex                   (void) -> const char* { return ""; }
    template <>          constexpr auto glsl_tex<s1D>              (void) -> const char* { return "sampler1D"; }
    template <>          constexpr auto glsl_tex<s2D>              (void) -> const char* { return "sampler2D"; }
    template <>          constexpr auto glsl_tex<s3D>              (void) -> const char* { return "sampler3D"; }
    template <>          constexpr auto glsl_tex<sCube>            (void) -> const char* { return "samplerCube"; }
    template <>          constexpr auto glsl_tex<s2DRect>          (void) -> const char* { return "sampler2DRect"; }
    template <>          constexpr auto glsl_tex<s1DShadow>        (void) -> const char* { return "sampler1DShadow"; }
    template <>          constexpr auto glsl_tex<s2DShadow>        (void) -> const char* { return "sampler2DShadow"; }
    template <>          constexpr auto glsl_tex<sCubeShadow>      (void) -> const char* { return "samplerCubeShadow"; }
    template <>          constexpr auto glsl_tex<s2DRectShadow>    (void) -> const char* { return "sampler2DRectShadow"; }
    template <>          constexpr auto glsl_tex<s1DArray>         (void) -> const char* { return "sampler1DArray"; }
    template <>          constexpr auto glsl_tex<s2DArray>         (void) -> const char* { return "sampler2DArray"; }
    template <>          constexpr auto glsl_tex<sCubeArray>       (void) -> const char* { return "samplerCubeArray"; }
    template <>          constexpr auto glsl_tex<s1DArrayShadow>   (void) -> const char* { return "sampler1DArrayShadow"; }
    template <>          constexpr auto glsl_tex<s2DArrayShadow>   (void) -> const char* { return "sampler2DArrayShadow"; }
    template <>          constexpr auto glsl_tex<sCubeArrayShadow> (void) -> const char* { return "samplerCubeArrayShadow"; }
    template <>          constexpr auto glsl_tex<sBuffer>          (void) -> const char* { return "samplerBuffer"; }
    template <>          constexpr auto glsl_tex<s2DMS>            (void) -> const char* { return "sampler2DMS"; }
    template <>          constexpr auto glsl_tex<s2DMSArray>       (void) -> const char* { return "sampler2DMSArray"; }
    template <>          constexpr auto glsl_tex<is1D>             (void) -> const char* { return "isampler1D"; }
    template <>          constexpr auto glsl_tex<is2D>             (void) -> const char* { return "isampler2D"; }
    template <>          constexpr auto glsl_tex<is3D>             (void) -> const char* { return "isampler3D"; }
    template <>          constexpr auto glsl_tex<isCube>           (void) -> const char* { return "isamplerCube"; }
    template <>          constexpr auto glsl_tex<is2DRect>         (void) -> const char* { return "isampler2DRect"; }
    template <>          constexpr auto glsl_tex<is1DArray>        (void) -> const char* { return "isampler1DArray"; }
    template <>          constexpr auto glsl_tex<is2DArray>        (void) -> const char* { return "isampler2DArray"; }
    template <>          constexpr auto glsl_tex<isCubeArray>      (void) -> const char* { return "isamplerCubeArray"; }
    template <>          constexpr auto glsl_tex<isBuffer>         (void) -> const char* { return "isamplerBuffer"; }
    template <>          constexpr auto glsl_tex<is2DMS>           (void) -> const char* { return "isampler2DMS"; }
    template <>          constexpr auto glsl_tex<is2DMSArray>      (void) -> const char* { return "isampler2DMSArray"; }
    template <>          constexpr auto glsl_tex<us1D>             (void) -> const char* { return "usampler1D"; }
    template <>          constexpr auto glsl_tex<us2D>             (void) -> const char* { return "usampler2D"; }
    template <>          constexpr auto glsl_tex<us3D>             (void) -> const char* { return "usampler3D"; }
    template <>          constexpr auto glsl_tex<usCube>           (void) -> const char* { return "usamplerCube"; }
    template <>          constexpr auto glsl_tex<us2DRect>         (void) -> const char* { return "usampler2DRect"; }
    template <>          constexpr auto glsl_tex<us1DArray>        (void) -> const char* { return "usampler1DArray"; }
    template <>          constexpr auto glsl_tex<us2DArray>        (void) -> const char* { return "usampler2DArray"; }
    template <>          constexpr auto glsl_tex<usCubeArray>      (void) -> const char* { return "usamplerCubeArray"; }
    template <>          constexpr auto glsl_tex<usBuffer>         (void) -> const char* { return "usamplerBuffer"; }
    template <>          constexpr auto glsl_tex<us2DMS>           (void) -> const char* { return "usampler2DMS"; }
    template <>          constexpr auto glsl_tex<us2DMSArray>      (void) -> const char* { return "usampler2DMSArray"; }
    
    template <TexEnum T> constexpr auto tex_gl_uint                   (void) -> GLuint { return 0; } 
    template <>          constexpr auto tex_gl_uint<s1D>              (void) -> GLuint { return GL_TEXTURE_1D; }
    template <>          constexpr auto tex_gl_uint<s2D>              (void) -> GLuint { return GL_TEXTURE_2D; }
    template <>          constexpr auto tex_gl_uint<s3D>              (void) -> GLuint { return GL_TEXTURE_3D; }
    template <>          constexpr auto tex_gl_uint<sCube>            (void) -> GLuint { return GL_TEXTURE_CUBE_MAP; }
    template <>          constexpr auto tex_gl_uint<s2DRect>          (void) -> GLuint { return GL_TEXTURE_RECTANGLE; }
    template <>          constexpr auto tex_gl_uint<s1DArray>         (void) -> GLuint { return GL_TEXTURE_1D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<s2DArray>         (void) -> GLuint { return GL_TEXTURE_2D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<sCubeArray>       (void) -> GLuint { return GL_TEXTURE_CUBE_MAP_ARRAY; }
    
    template <>          constexpr auto tex_gl_uint<s1DShadow>        (void) -> GLuint { return GL_TEXTURE_1D; }
    template <>          constexpr auto tex_gl_uint<s2DShadow>        (void) -> GLuint { return GL_TEXTURE_2D; }
    template <>          constexpr auto tex_gl_uint<sCubeShadow>      (void) -> GLuint { return GL_TEXTURE_CUBE_MAP; }
    template <>          constexpr auto tex_gl_uint<s2DRectShadow>    (void) -> GLuint { return GL_TEXTURE_RECTANGLE; }
    template <>          constexpr auto tex_gl_uint<s1DArrayShadow>   (void) -> GLuint { return GL_TEXTURE_1D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<s2DArrayShadow>   (void) -> GLuint { return GL_TEXTURE_2D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<sCubeArrayShadow> (void) -> GLuint { return GL_TEXTURE_CUBE_MAP_ARRAY; }
    
    template <>          constexpr auto tex_gl_uint<sBuffer>          (void) -> GLuint { return GL_TEXTURE_BUFFER; }
    template <>          constexpr auto tex_gl_uint<s2DMS>            (void) -> GLuint { return GL_TEXTURE_2D_MULTISAMPLE; }
    template <>          constexpr auto tex_gl_uint<s2DMSArray>       (void) -> GLuint { return GL_TEXTURE_2D_MULTISAMPLE_ARRAY; }
    
    template <>          constexpr auto tex_gl_uint<is1D>             (void) -> GLuint { return GL_TEXTURE_1D; }
    template <>          constexpr auto tex_gl_uint<is2D>             (void) -> GLuint { return GL_TEXTURE_2D; }
    template <>          constexpr auto tex_gl_uint<is3D>             (void) -> GLuint { return GL_TEXTURE_3D; }
    template <>          constexpr auto tex_gl_uint<isCube>           (void) -> GLuint { return GL_TEXTURE_CUBE_MAP; }
    template <>          constexpr auto tex_gl_uint<is2DRect>         (void) -> GLuint { return GL_TEXTURE_RECTANGLE; }
    template <>          constexpr auto tex_gl_uint<is1DArray>        (void) -> GLuint { return GL_TEXTURE_1D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<is2DArray>        (void) -> GLuint { return GL_TEXTURE_2D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<isCubeArray>      (void) -> GLuint { return GL_TEXTURE_CUBE_MAP_ARRAY; }
    
    template <>          constexpr auto tex_gl_uint<isBuffer>         (void) -> GLuint { return GL_TEXTURE_BUFFER; }
    template <>          constexpr auto tex_gl_uint<is2DMS>           (void) -> GLuint { return GL_TEXTURE_2D_MULTISAMPLE; }
    template <>          constexpr auto tex_gl_uint<is2DMSArray>      (void) -> GLuint { return GL_TEXTURE_2D_MULTISAMPLE_ARRAY; }
    
    template <>          constexpr auto tex_gl_uint<us1D>             (void) -> GLuint { return GL_TEXTURE_1D; }
    template <>          constexpr auto tex_gl_uint<us2D>             (void) -> GLuint { return GL_TEXTURE_2D; }
    template <>          constexpr auto tex_gl_uint<us3D>             (void) -> GLuint { return GL_TEXTURE_3D; }
    template <>          constexpr auto tex_gl_uint<usCube>           (void) -> GLuint { return GL_TEXTURE_CUBE_MAP; }
    template <>          constexpr auto tex_gl_uint<us2DRect>         (void) -> GLuint { return GL_TEXTURE_RECTANGLE; }
    template <>          constexpr auto tex_gl_uint<us1DArray>        (void) -> GLuint { return GL_TEXTURE_1D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<us2DArray>        (void) -> GLuint { return GL_TEXTURE_2D_ARRAY; }
    template <>          constexpr auto tex_gl_uint<usCubeArray>      (void) -> GLuint { return GL_TEXTURE_CUBE_MAP_ARRAY; }
    
    template <>          constexpr auto tex_gl_uint<usBuffer>         (void) -> GLuint { return GL_TEXTURE_BUFFER; }
    template <>          constexpr auto tex_gl_uint<us2DMS>           (void) -> GLuint { return GL_TEXTURE_2D_MULTISAMPLE; }
    template <>          constexpr auto tex_gl_uint<us2DMSArray>      (void) -> GLuint { return GL_TEXTURE_2D_MULTISAMPLE_ARRAY; }
}
#endif
