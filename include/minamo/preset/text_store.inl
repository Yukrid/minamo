#ifndef MINAMO_PRESET_TEXT_STORE_INL
#define MINAMO_PRESET_TEXT_STORE_INL

#include "text_store.hpp"

//=================================//
//    Namespace: minamo::preset    //
//=================================//
namespace minamo::preset{

    //(    minamo::preset::TextStore<dim_t D> Structure Template    )//
    //+    Member Function    +//
    //_ Destructive Function
    template <dim_t D> void TextStore<D>::Text::calc_rect_coord (void) noexcept
    {
        float f_width =static_cast<float>(buf_width);
        float f_height=static_cast<float>(buf_height);

        switch(position){

            case extension::CENTER:
            {
                rect_coord[0]=glm::vec3(-f_width*0.5f, -f_height*0.5f, 0.f)+base_coord;
                rect_coord[1]=glm::vec3( f_width*0.5f, -f_height*0.5f, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(-f_width*0.5f,  f_height*0.5f, 0.f)+base_coord;
                rect_coord[3]=glm::vec3( f_width*0.5f,  f_height*0.5f, 0.f)+base_coord;
                break;
            }
            case extension::LEFT_TOP:
            {
                rect_coord[0]=glm::vec3(    0.f, -f_height, 0.f)+base_coord;
                rect_coord[1]=glm::vec3( f_width, -f_height, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(    0.f,     0.f, 0.f)+base_coord;
                rect_coord[3]=glm::vec3( f_width,     0.f, 0.f)+base_coord;
                break;
            }
            case extension::LEFT_CENTER:
            {
                rect_coord[0]=glm::vec3(    0.f, -f_height*0.5f, 0.f)+base_coord;
                rect_coord[1]=glm::vec3( f_width, -f_height*0.5f, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(    0.f,  f_height*0.5f, 0.f)+base_coord;
                rect_coord[3]=glm::vec3( f_width,  f_height*0.5f, 0.f)+base_coord;
                break;
            }
            case extension::LEFT_BOTTOM:
            {
                rect_coord[0]=glm::vec3(    0.f,     0.f, 0.f)+base_coord;
                rect_coord[1]=glm::vec3( f_width,     0.f, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(    0.f,  f_height, 0.f)+base_coord;
                rect_coord[3]=glm::vec3( f_width,  f_height, 0.f)+base_coord;
                break;
            }
            case extension::CENTER_BOTTOM:
            {
                rect_coord[0]=glm::vec3(-f_width*0.5f,    0.f, 0.f)+base_coord;
                rect_coord[1]=glm::vec3( f_width*0.5f,    0.f, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(-f_width*0.5f, f_height, 0.f)+base_coord;
                rect_coord[3]=glm::vec3( f_width*0.5f, f_height, 0.f)+base_coord;
                break;
            }
            case extension::RIGHT_BOTTOM:
            {
                rect_coord[0]=glm::vec3(-f_width,     0.f, 0.f)+base_coord;
                rect_coord[1]=glm::vec3(    0.f,     0.f, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(-f_width,  f_height, 0.f)+base_coord;
                rect_coord[3]=glm::vec3(    0.f,  f_height, 0.f)+base_coord;
                break;
            }
            case extension::RIGHT_CENTER:
            {
                rect_coord[0]=glm::vec3(-f_width, -f_height*0.5f, 0.f)+base_coord;
                rect_coord[1]=glm::vec3(    0.f, -f_height*0.5f, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(-f_width,  f_height*0.5f, 0.f)+base_coord;
                rect_coord[3]=glm::vec3(    0.f,  f_height*0.5f, 0.f)+base_coord;
                break;
            }
            case extension::RIGHT_TOP:
            {
                rect_coord[0]=glm::vec3(-f_width, -f_height, 0.f)+base_coord;
                rect_coord[1]=glm::vec3(    0.f, -f_height, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(-f_width,     0.f, 0.f)+base_coord;
                rect_coord[3]=glm::vec3(    0.f,     0.f, 0.f)+base_coord;
                break;
            }
            case extension::CENTER_TOP:
            {
                rect_coord[0]=glm::vec3(-f_width*0.5f, -f_height, 0.f)+base_coord;
                rect_coord[1]=glm::vec3( f_width*0.5f, -f_height, 0.f)+base_coord;
                rect_coord[2]=glm::vec3(-f_width*0.5f,     0.f, 0.f)+base_coord;
                rect_coord[3]=glm::vec3( f_width*0.5f,     0.f, 0.f)+base_coord;
                break;
            }
        }
        
        return;
    }




    //(    minamo::preset::TextStore<dim_t D> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <dim_t D> TextStore<D>::TextStore (void) noexcept
        : drawer       { }
        , buffer_objs  { }
        , storage      { }
        , typewriter   { }
        , unit_id      {0}
        , face_id      {0}
        , last_used_id {0}
    {
        glm::mat4 m{1.f};
        drawer.methods.template get<0>().usmat.set(1, GL_FALSE, &m[0][0]);
        
        return;
    }

    

    //_ Constant Function
    template <dim_t D> void TextStore<D>::bind_font (index_t id_) noexcept
    {
        face_id=id_;

        return;
    }
  

    template <dim_t D> auto TextStore<D>::get_new_index (void) noexcept
        -> index_t
    {
        index_t id=last_used_id;
        for(size_t a=last_used_id+1; a!=last_used_id; ++a){
            if(storage.find(a)==storage.end() and a!=0){
                id=a;
                break;
            }
        }
        if(id==last_used_id){
            return 0;
        }
        last_used_id=id;

        return id;
    }


    template <dim_t D> auto TextStore<D>::get_unicode (const char* str_) noexcept
        -> std::array<uint32_t, 2>
    {
        std::array<uint32_t, 2> ret;
        uint32_t& unicode=ret[0];
        uint32_t& stride =ret[1];
        
        unicode=0;
        if((str_[0] & 0b11100000)==0b11000000){
                        
            unicode+= ((str_[0] & 0b00111100)>>2)*0x000100;
            unicode+=(((str_[0] & 0b00000011)<<2)+((str_[1] & 0b00110000)>>4))*0x000010;
            unicode+=  (str_[1] & 0b00001111);
            stride=2;
                        
        }else if((str_[0] & 0b11110000)==0b11100000){
                        
            unicode+=  (str_[0] & 0b00001111)*0x001000;
            unicode+= ((str_[1] & 0b00111100)>>2)*0x000100;
            unicode+=(((str_[1] & 0b00000011)<<2)+((str_[2] & 0b00110000)>>4))*0x000010;
            unicode+=  (str_[2] & 0b00001111);
            stride=3;
                        
        }else if((str_[0] & 0b11111000)==0b11110000){
                        
            unicode+= ((str_[0] & 0b00000100)>>2)*0x100000;
            unicode+=(((str_[0] & 0b00000011)<<2)+((str_[1] & 0b00110000)>>4))*0x010000;
            unicode+=  (str_[1] & 0b00001111)*0x001000;
            unicode+= ((str_[2] & 0b00111100)>>2)*0x000100;
            unicode+=(((str_[2] & 0b00000011)<<2)+((str_[3] & 0b00110000)>>4))*0x000010;
            unicode+=  (str_[3] & 0b00001111)<<2;
            stride=4;

        }else{
                        
            unicode+=str_[0];
            stride=1;
        }

        return ret;
    }
    

    template <dim_t D> auto TextStore<D>::get_unicodes (const std::string& str_) noexcept
        -> std::vector<uint32_t>
    {
        std::vector<uint32_t> unicodes;
 
        std::array<uint32_t, 2> ret=std::move(get_unicode(str_.c_str()));
        uint32_t load_stride=ret[1];
       
        unicodes.push_back(ret[0]);
        while(ret[0]){
            ret=get_unicode(str_.c_str()+load_stride);
            unicodes.push_back(ret[0]);
            load_stride+=ret[1];
        }
       
        return unicodes;
    }


    template <dim_t D> void TextStore<D>::set_window_size (size_t w_, size_t h_) noexcept
    {
        glm::mat4 m{1.f};
        m[0][0]=2./w_;
        m[1][1]=2./h_;
       
        drawer.methods.template get<0>().usmat.set(1, GL_FALSE, &m[0][0]);

        return;
    }


    template <dim_t D> void TextStore<D>::set_texture_unit (GLint tu_) noexcept
    {
        unit_id=tu_;
        drawer.methods.template get<1>().utex.set(tu_);

        return;
    }


    template <dim_t D> void TextStore<D>::set_coord_matrix (const glm::mat4& m_) noexcept
    {
        drawer.methods.template get<0>().usmat.set(1, GL_FALSE, &m_[0][0]);

        return;
    }


    template <dim_t D> void TextStore<D>::set_uv_matrix (const glm::mat3& m_) noexcept
    {
        drawer.methods.template get<1>().usmat.set(1, GL_FALSE, &m_[0][0]);

        return;
    }



    //_ Destructive Function
    template <dim_t D> auto TextStore<D>::add_font (const char* path_, uint32_t sz_, uint32_t dpi_, bool shave_) noexcept
        -> index_t  
    {
        index_t fid=typewriter.add_font(path_, (sz_*dpi_)/72, shave_);

        bind_font(fid);

        return fid;
    }
 

    template <dim_t D> auto TextStore<D>::render (const std::vector<uint32_t>& unicodes_) noexcept
        -> std::array<int32_t, 5>
    {
        const FT_Face&      face        = typewriter.face(face_id);
        const FT_GlyphSlot& glyphs      = face->glyph;
        const FT_Bitmap&    bitmap      = glyphs->bitmap;
        const uint32_t      rh          = typewriter.req_height(face_id);
        const bool          shav_e      = typewriter.shaving_enable(face_id);
       
        unsigned int bl=(rh*face->bbox.yMax)/(face->bbox.yMax-face->bbox.yMin);
        
        int32_t  max_height=std::numeric_limits<int32_t>().min();
        int32_t  min_height=std::numeric_limits<int32_t>().max();
        
        size_t   max_width  = 0;
        size_t   cur_width  = 0;
        size_t   here       = bl;
        uint32_t nl_count   = 1;

        for(const uint32_t& unicode: unicodes_){

            switch(unicode){
                case +'\0':
                {
                    break;
                }
                case +'\r':
                {
                    break;
                }
                case +'\n':
                {
                    if(max_width<cur_width) max_width=cur_width;
                    cur_width=0;
                    ++nl_count;
                    break;
                }
                default :
                {
                    FT_Load_Glyph(face, FT_Get_Char_Index(face, unicode), FT_LOAD_RENDER);
                    int_fast16_t h=here-glyphs->bitmap_top;
                    if(h<min_height) min_height=h;
                    h+=glyphs->bitmap.rows;
                    if(h>max_height) max_height=h;
                    cur_width+=glyphs->advance.x>>6;
                    
                    break;
                }
            }
        }

        if(max_width<cur_width) max_width=cur_width;
        

        int32_t line_h;
        int32_t cor_rh;
        int32_t h_offset;
        if(shav_e){
            h_offset=(max_height>rh ? rh-max_height : 0)-min_height;
            line_h=max_height-min_height;
        }else{
            h_offset=(max_height>rh ? rh-max_height : 0)-min_height;
            line_h=(max_height-min_height>rh ? max_height+h_offset-min_height : rh);
        }
        cor_rh=(line_h+1)*nl_count;
        
        std::array<int32_t, 2> laybh=std::move(alloc_buffer(max_width, cor_rh));
        
        if(laybh[0]<0) return std::array<int32_t, 5>{-1};
    
        uint8_t* base =buffer_objs(laybh[0], 0);

        unsigned int cur_w=0;
        unsigned int cur_h=bl+h_offset;
        
        for(const uint32_t& unicode: unicodes_){

            switch(unicode){
                case +'\0':
                {
                    break;
                }
                case +'\r':
                {
                    break;
                }
                case +'\n':
                {
                    cur_w=0;
                    cur_h+=line_h+1;
                    break;
                }
                default:
                {
                    FT_Load_Glyph(face, FT_Get_Char_Index(face, unicode), FT_LOAD_RENDER);
                    unsigned int w=bitmap.width;
                    unsigned int h=bitmap.rows;

                    for(size_t b1=laybh[1]+cur_h-glyphs->bitmap_top , b2=(laybh[1]+cur_h-glyphs->bitmap_top)*buffer_objs.width, c1=0, c2=0; c1<h; ++b1, b2+=buffer_objs.width, ++c1, c2+=w){
                        if(b1>=0 and b1){
                            for(size_t d=cur_w+glyphs->bitmap_left, e=0; e<w; ++d, ++e){
                                base[b2+d]=bitmap.buffer[c2+e];
                            }
                        }
                    }
                    cur_w+=glyphs->advance.x>>6;
                    cur_h+=glyphs->advance.y>>6;
                    break;
                }
            }
        }
           
        return std::array<int32_t, 5>{0, (int32_t)laybh[1], (int32_t)max_width, (int32_t)cor_rh, laybh[0]};
    }


    template <dim_t D> auto TextStore<D>::append (const std::string& str_, const glm::vec3& coord_, extension::Position pos_, const vecn<D>& color_) noexcept
        -> index_t
    {
        method::BasicP1<3>&               m_coord=drawer.methods.template get<0>();
        method::MoldC1U1<D, 3, s2DArray>& m_mold =drawer.methods.template get<1>();
        
        m_coord.coord.enable_send=true;
        m_mold.color.enable_send =true;
        m_mold.uv.enable_send    =true;
       
        index_t id=get_new_index();
        
        std::vector<uint32_t> unicodes=std::move(get_unicodes(str_));
        
        std::array<int32_t, 5> result=std::move(render(unicodes));

        if(result[0]) return 0;
 
        Text& text=storage[id];
        text.position   =pos_;
        text.base_coord =coord_;
        text.color      =color_;
        text.buf_pos    =result[1];
        text.buf_width  =result[2];
        text.buf_height =result[3];
        text.buf_layer  =result[4];
        text.calc_rect_coord();

        return id;
    }


    template <dim_t D> auto TextStore<D>::replace (index_t id_, const std::string& str_) noexcept
        -> index_t
    {
        method::BasicP1<3>&               m_coord=drawer.methods.template get<0>();
        method::MoldC1U1<D, 3, s2DArray>& m_mold =drawer.methods.template get<1>();
        
        m_coord.coord.enable_send=true;
        m_mold.uv.enable_send    =true;
       
        Text& text=storage[id_];
        buffer_objs.subtract_locks(text.buf_layer, text.buf_pos, text.buf_pos+text.buf_height);

        std::vector<uint32_t> unicodes=std::move(get_unicodes(str_));

        std::array<int32_t, 5> result=std::move(render(unicodes));

        if(result[0]) return 0;
 
        text.buf_pos    =result[1];
        text.buf_width  =result[2];
        text.buf_height =result[3];
        text.buf_layer  =result[4];
        text.calc_rect_coord();

        return id_;
    }


    template <dim_t D> auto TextStore<D>::duplicate (index_t id_, const glm::vec3& coord_, extension::Position pos_, const vecn<D>& color_) noexcept
        -> index_t
    {
        method::BasicP1<3>&               m_coord=drawer.methods.template get<0>();
        method::MoldC1U1<D, 3, s2DArray>& m_mold =drawer.methods.template get<1>();
        
        m_coord.coord.enable_send=true;
        m_mold.color.enable_send =true;
        m_mold.uv.enable_send    =true;
         
        Text& cur_text=storage[id_];
        buffer_objs.add_locks(cur_text.buf_layer, cur_text.buf_pos, cur_text.buf_pos+cur_text.buf_height);

        index_t id=get_new_index();
        Text& text=storage[id];
        text.position   =pos_;
        text.base_coord =coord_;
        text.color      =color_;
        text.buf_pos    =cur_text.buf_pos;
        text.buf_width  =cur_text.buf_width;
        text.buf_height =cur_text.buf_height;
        text.buf_layer  =cur_text.buf_layer;
        text.calc_rect_coord();

        return id;
    }


    template <dim_t D> auto TextStore<D>::move (index_t id_, const glm::vec3& coord_, extension::Position pos_) noexcept
        -> index_t
    {
        method::BasicP1<3>& m_coord=drawer.methods.template get<0>();
        
        m_coord.coord.enable_send=true;
         
        Text& text=storage[id_];
        text.position   =pos_;
        text.base_coord =coord_;
        text.calc_rect_coord();

        return id_;
    }


    template <dim_t D> auto TextStore<D>::recolorize (index_t id_, const vecn<D>& color_) noexcept
        -> index_t
    {
        method::MoldC1U1<D, 3, s2DArray>& m_mold =drawer.methods.template get<1>();
       
        m_mold.color.enable_send=true;

        Text& text=storage[id_];
        text.color=color_;

        return id_;
    }


    template <dim_t D> void TextStore<D>::erase (index_t id_) noexcept
    {
        method::BasicP1<3>&               m_coord=drawer.methods.template get<0>();
        method::MoldC1U1<D, 3, s2DArray>& m_mold =drawer.methods.template get<1>();
       
        m_coord.coord.enable_send=true;
        m_mold.color.enable_send =true;
        m_mold.uv.enable_send    =true;

        if(storage.find(id_)!=storage.end()){
            Text& text=storage[id_];
            buffer_objs.subtract_locks(text.buf_layer, text.buf_pos, text.buf_pos+text.buf_height);
            storage.erase(id_);
        }
        
        return;
    }


    template <dim_t D> void TextStore<D>::clear (void) noexcept
    {
        storage.clear();
        std::memset(buffer_objs.locks, 0, sizeof(uint32_t)*buffer_objs.height*buffer_objs.nof_pages);
        std::memset(buffer_objs.buffer, 0, buffer_objs.width*buffer_objs.height*buffer_objs.nof_pages);

        return;
    }


    template <dim_t D> auto TextStore<D>::alloc_buffer (size_t w_, size_t h_) noexcept
        -> std::array<int32_t, 2>
    {

        int32_t error=buffer_objs.resize(w_, h_);
        if(error) return std::array<int32_t, 2>{-1, error};
        
        int32_t layer=-1;
        size_t base_height = 0;
        size_t load_height = 0;
        for(size_t b=0; b<buffer_objs.nof_pages; ++b){

            base_height=0;
            load_height=0;
       
            uint32_t* locks=buffer_objs.get_locks(b);
            for(size_t a=0; a<buffer_objs.height; ++a){
            
                if(!locks[a]){
               
                    if(load_height==0) base_height=a;
                    ++load_height;

                }else{
                    load_height=0;
                    base_height=a;
                }
                
                if(load_height>=h_) break;
            }

            if(load_height>=h_){
                layer=b;
                buffer_objs.add_locks(layer, base_height, base_height+h_);
                return std::array<int32_t, 2>{layer, (int32_t)base_height};
            
            }else{

                if(int32_t val=buffer_objs.resize(w_, buffer_objs.height+h_-load_height)){
                    if(val==extension::VertBuffer2DArray<uint8_t>::OVER_MAX_TEXTURE_HEIGHT){
                        continue;
                    }else{
                        return std::array<int32_t, 2>{-3, val};
                    }
                }
                ++base_height;
                layer=b;
                buffer_objs.add_locks(layer, base_height, base_height+h_);
                return std::array<int32_t, 2>{layer, (int32_t)base_height};
            }
        }

        if(int32_t error=buffer_objs.add_page()) return std::array<int32_t, 2>{-2, error};
        
        return alloc_buffer(w_, h_);
    }


    template <dim_t D> void TextStore<D>::draw (void) noexcept
    {
        method::BasicP1<3>&               m_coord=drawer.methods.template get<0>();
        method::MoldC1U1<D, 3, s2DArray>& m_mold =drawer.methods.template get<1>();

        if(m_coord.coord.enable_send){
            
            m_coord.coord.data.resize(0);

            for(const std::pair<index_t, Text>& it : storage){
                
                m_coord.coord.data.push_back(it.second.rect_coord[0].x);
                m_coord.coord.data.push_back(it.second.rect_coord[0].y);
                m_coord.coord.data.push_back(it.second.rect_coord[0].z);
 
                m_coord.coord.data.push_back(it.second.rect_coord[1].x);
                m_coord.coord.data.push_back(it.second.rect_coord[1].y);
                m_coord.coord.data.push_back(it.second.rect_coord[1].z);
 
                m_coord.coord.data.push_back(it.second.rect_coord[2].x);
                m_coord.coord.data.push_back(it.second.rect_coord[2].y);
                m_coord.coord.data.push_back(it.second.rect_coord[2].z);
          
                m_coord.coord.data.push_back(it.second.rect_coord[3].x);
                m_coord.coord.data.push_back(it.second.rect_coord[3].y);
                m_coord.coord.data.push_back(it.second.rect_coord[3].z);
            }
        }


        if(m_mold.color.enable_send){
            
            m_mold.color.data.resize(0);

            for(const std::pair<index_t, Text>& it : storage){    
                for(uint_fast16_t b=0; b<4; ++b){
                    for(dim_t a=0; a<D; ++a){
                        m_mold.color.data.push_back(it.second.color[a]);
                    }
                }
            }
        }


        if(m_mold.uv.enable_send){
            
            m_mold.uv.data.resize(0);

            for(const std::pair<index_t, Text>& it : storage){    
                
                float bob_w=buffer_objs.width;
                float bob_h=buffer_objs.height;
                float tex_maxx=it.second.buf_width;
                float tex_miny=it.second.buf_pos;
                float tex_maxy=it.second.buf_pos+it.second.buf_height; 

                m_mold.uv.data.push_back(0.f);
                m_mold.uv.data.push_back(tex_maxy/bob_h);
                m_mold.uv.data.push_back(it.second.buf_layer);
                
                m_mold.uv.data.push_back(tex_maxx/bob_w);
                m_mold.uv.data.push_back(tex_maxy/bob_h);
                m_mold.uv.data.push_back(it.second.buf_layer);
                
                m_mold.uv.data.push_back(0.f);
                m_mold.uv.data.push_back(tex_miny/bob_h);
                m_mold.uv.data.push_back(it.second.buf_layer);
                
                m_mold.uv.data.push_back(tex_maxx/bob_w);
                m_mold.uv.data.push_back(tex_miny/bob_h);
                m_mold.uv.data.push_back(it.second.buf_layer);
            }


            GLuint tex_target=minamo::tex_gl_uint<minamo::s2DArray>();
            glActiveTexture(GL_TEXTURE0+unit_id);
            m_mold.utex.bind(0);
            glTexImage3D(tex_target, 0, GL_RED, buffer_objs.width, buffer_objs.height, buffer_objs.nof_pages, 0, GL_RED, GL_UNSIGNED_BYTE, buffer_objs.buffer);
            glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glGenerateMipmap(tex_target);
        }
        
        m_coord.coord.attach();
        m_mold.color.attach();
        m_mold.uv.attach();
        
        drawer.draw(+[](const size_t& sz_){
            
            for(size_t a=0; a<sz_; a+=4) glDrawArrays(GL_TRIANGLE_STRIP, a, 4);
        
            return;
        }, 4*storage.size());
        
        m_coord.coord.enable_send=false;
        m_mold.color.enable_send=false;
        m_mold.uv.enable_send=false; 
        
        return;
    }
}

#endif
