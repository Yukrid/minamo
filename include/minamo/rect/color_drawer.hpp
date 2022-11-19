#ifndef MINAMO_RECT_COLOR_DRAWER_HPP
#define MINAMO_RECT_COLOR_DRAWER_HPP

#include "../forward.hpp"
#include "../coord_method.hpp"
#include "../simple_color_method.hpp"
#include "../unordered_map_drawer.hpp"

#include "rect.hpp"

//===============================//
//    Namespace: minamo::rect    //
//===============================//
namespace minamo::rect{

    //(    minamo::rect::ColorDrawer    )//
    struct ColorDrawer final : public CoordMethod<4>, public SimpleColorMethod<4>, public UnorderedMapDrawer<ColorRect>{
    
        //+    Member Function    +//
        //_ Constructor
        ColorDrawer (void)               noexcept;
        ColorDrawer (const ColorDrawer&) noexcept =delete;
        ColorDrawer (ColorDrawer&&)      noexcept =delete;
 
        //_ Destructor
        ~ColorDrawer (void) noexcept override =default;
        
        //_ Destructive Function
        auto append   (const Region&, const glm::vec4&)                            noexcept -> index_t;
        void remove   (index_t)                                                    noexcept;
        auto resize   (index_t, GLfloat[2])                                        noexcept -> index_t;
        auto move     (index_t, const glm::vec3&, Region::Anchor =Region::DEFAULT) noexcept -> index_t;
        auto move     (index_t, Region::Anchor)                                    noexcept -> index_t;
        auto colorize (index_t, const glm::vec4&)                                  noexcept -> index_t;        

        void attach_cb (void* =nullptr) noexcept override;

        //_ Constant Function
        void draw_cb (void* =nullptr) const noexcept override;
        auto get     (index_t)        const noexcept          -> const ColorRect&;
    };
}
#endif
