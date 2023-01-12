#ifndef MINAMO_PRESET_TEXT_STORE_HPP
#define MINAMO_PRESET_TEXT_STORE_HPP

#include "../forward.hpp"
#include "../method/basic_p1.hpp"
#include "../method/mold_c1u1.hpp"
#include "../drawer/standard.hpp"
#include "../extension/vert_buffer_2d_array.hpp"
#include "../extension/typewriter.hpp"
#include "../extension/position.hpp"

#include <unordered_map>

//=================================//
//    Namespace: minamo::preset    //
//=================================//
namespace minamo::preset{

    //(    minamo::preset::TextStore<dim_t D> Structure Template    )//
    template <dim_t D>
    struct TextStore{
        
        //+    Type Definiton    +//
        struct Text{
            extension::Position position;
            glm::vec3           base_coord;
            glm::vec3           rect_coord[4];
            vecn<D>             color;
            size_t              buf_width;
            size_t              buf_height;
            size_t              buf_pos;
            size_t              buf_layer;
            std::string         string;
           
            //+    Member Function    +//
            //_ Destructive Function
            void calc_rect_coord (void) noexcept;
        };

        
        //+    Member Variable    +//
                drawer::Standard<
                    method::BasicP1<3>,
                    method::MoldC1U1<D, 3, s2DArray>
                >                                     drawer;
                extension::VertBuffer2DArray<uint8_t> buffer_objs;
                std::unordered_map<index_t, Text>     storage;
                extension::Typewriter                 typewriter;
                GLint                                 unit_id;
        mutable index_t                               face_id;
        mutable index_t                               last_used_id;

        //+    Member Function    +//
        //_ Constructor
        TextStore (void) noexcept;

        //_ Destructor
        ~TextStore (void) noexcept =default;

        //_ Destructive Function
        void bind_font        (index_t)                      noexcept;
        auto get_new_index    (void)                         noexcept -> index_t;
        auto get_unicode      (const char*)                  noexcept -> std::array<uint32_t, 2>;
        auto get_unicodes     (const std::string&)           noexcept -> std::vector<uint32_t>;
        void calc_rect_coord  (Text&)                        noexcept;
        auto render           (const std::vector<uint32_t>&) noexcept -> std::array<int32_t, 5>;
        auto alloc_buffer     (size_t, size_t)               noexcept -> std::array<int32_t, 2>;

        auto set_window_size  (size_t, size_t)   noexcept -> void;
        void set_texture_unit (GLint)            noexcept;
        void set_coord_matrix (const glm::mat4&) noexcept;
        void set_uv_matrix    (const glm::mat3&) noexcept;
        
        auto add_font  (const char*, uint32_t, uint32_t =96, bool =true) noexcept -> index_t;
        
        auto append     (const std::string&,
                         const glm::vec3&,
                         extension::Position,
                         const vecn<D>&)                                 noexcept -> index_t;
        auto replace    (index_t, const std::string&)                    noexcept -> index_t;
        auto duplicate  (index_t,
                         const glm::vec3&,
                         extension::Position,
                         const vecn<D>&)                                 noexcept -> index_t;
        auto move       (index_t, const glm::vec3&, extension::Position) noexcept -> index_t;
        auto recolorize (index_t, const vecn<D>&)                        noexcept -> index_t;
        void erase      (index_t)                                        noexcept;
        void clear      (void)                                           noexcept;

        //_ Destructive Function
        void draw (void) noexcept;
    };
}

#include "text_store.inl"

#endif
