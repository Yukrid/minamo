#ifndef MINAMO_EXTENSION_TYPEWRITER_HPP
#define MINAMO_EXTENSION_TYPEWRITER_HPP

#include <iostream>
#include <vector>
#include <fstream>

#include <freetype2/ft2build.h>

#include "../forward.hpp"

#include FT_FREETYPE_H

//=====================================//
//    Namespace : minamo::extension    //
//=====================================//
namespace minamo::extension{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::extension::Typewriter Class    )//
    class Typewriter{
        
        public :
        //+    Type Definition    +//
        //(    minamo::extension::Typewriter::Font Class    )//
        class Font{
            
            private:
            //+    Member Variable    +//
            FT_Face  _face;       // Array of FreeType Faces
            uint32_t _req_height; // Array of User Requested Heights for Each Faces
            bool     _shaving_enable;


            public :
            //+    Memeber Function    +//
            //_ Constructor
                 Font      (void)                                                 noexcept;
                 Font      (const FT_Library&, const char*, uint32_t, bool =true);
            auto construct (void)                                                 noexcept -> Font&;
            auto construct (const FT_Library&, const char*, uint32_t, bool =true)          -> Font&;
 
            //_ Destructor
                 ~Font    (void) noexcept;
            auto destruct (void) noexcept -> Font&;
            
            //_ Constant Accessor
            auto face           (void) noexcept -> const FT_Face&;
            auto req_height     (void) noexcept -> const uint32_t&;
            auto shaving_enable (void) noexcept -> const bool&;

            //_ Destructive Function
            auto set (const FT_Library&, const char*, uint32_t, bool =true) noexcept -> bool;
        };

        
        private:
        //+    Member Variable    +//
        FT_Library _library;     // FreeType Library 
        size_t     _num_of_font; 
        size_t     _cap_of_font; 
        Font*      _fonts;


        public :
        //+    Memeber Function    +//
        //_ Constructor
             Typewriter (void) noexcept;
        auto construct  (void) noexcept -> Typewriter&;
 
        //_ Destructor
             ~Typewriter (void) noexcept;
        auto  destruct   (void) noexcept -> Typewriter&;

        //_ Constant Accessor
        auto library        (void)    const noexcept -> const FT_Library&;
        auto num_of_font    (void)    const noexcept -> const size_t&;
        auto face           (index_t) const noexcept -> const FT_Face&;
        auto req_height     (index_t) const noexcept -> const uint32_t&;
        auto shaving_enable (index_t) const noexcept -> const bool&;
        
        //_ Destructive Function
        auto add_font (const char*, uint32_t, bool =true) noexcept -> index_t;
    };
}
#endif

