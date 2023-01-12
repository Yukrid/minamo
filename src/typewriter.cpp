#include "minamo/extension/typewriter.hpp"

//=====================================//
//    Namespace : minamo::extension    //
//=====================================//
namespace minamo::extension{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::extension::Typewriter::Font Class    )//
    //+    Member Function    +//
    //_ Constructor
    Typewriter::Font::Font (void) noexcept
        : _face           { }
        , _req_height     {0}
        , _shaving_enable {true}
    {
        return;
    }

    
    Typewriter::Font::Font (const FT_Library& library_, const char* str_, uint32_t height_, bool se_)
        : _face           { }
        , _req_height     { height_ }
        , _shaving_enable { se_ }
    {
        std::ifstream ifs{str_};
        if(!ifs){
            ifs.close();
            std::cerr<<"[Error] minamo::extension::Typewriter::Font::Font -> failed to open font file"<<std::endl;
        }
        ifs.close();

        FT_New_Face(library_, str_, 0, &_face);
        FT_Size_RequestRec req;
        req.type           =FT_SIZE_REQUEST_TYPE_NOMINAL;
        req.width          =0;
        req.height         =(height_<<6);
        req.horiResolution =0;
        req.vertResolution =0;
        
        FT_Request_Size(_face, &req);
        _req_height=height_;
        _shaving_enable=se_;

        return;
    }


    auto Typewriter::Font::construct (void) noexcept
        -> Typewriter::Font&
    {
        new(this) Typewriter::Font();

        return *this;
    }


    auto Typewriter::Font::construct (const FT_Library& library_, const char* str_, uint32_t height_, bool se_)
        -> Typewriter::Font&
    {
        new(this) Typewriter::Font(library_, str_, height_, se_);

        return *this;
    }
 


    //_ Destructor   
    Typewriter::Font::~Font (void) noexcept
    {
        _req_height =0;
        FT_Done_Face(_face);
        
        return;
    }


    auto Typewriter::Font::destruct (void) noexcept
        -> Typewriter::Font&
    {
        this->~Font();
        
        return *this;
    }



    //_ Constant Accessor
    auto Typewriter::Font::face (void) noexcept
        -> const FT_Face&
    {
        return _face;
    }

    
    auto Typewriter::Font::req_height (void) noexcept
        -> const uint32_t&
    {
        return _req_height;
    }
 

    auto Typewriter::Font::shaving_enable (void) noexcept
        -> const bool&
    {
        return _shaving_enable;
    }



    //_ Destructive Function
    auto Typewriter::Font::set (const FT_Library& library_, const char* str_, uint32_t height_, bool se_) noexcept
        -> bool
    { 
        std::ifstream ifs{str_};
        if(!ifs){
            ifs.close();
            return false;
        }
        ifs.close();

        FT_New_Face(library_, str_, 0, &_face);
        FT_Size_RequestRec req;
        req.type           =FT_SIZE_REQUEST_TYPE_NOMINAL;
        req.width          =0;
        req.height         =(height_<<6);
        req.horiResolution =0;
        req.vertResolution =0;
        
        FT_Request_Size(_face, &req);
        _req_height=height_;
        _shaving_enable=se_;

        return true;
    }




    //(    minamo::extension::Typewriter Class    )//
    //+    Member Function    +//
    //_ Constructor
    Typewriter::Typewriter (void) noexcept
        : _library     { }
        , _num_of_font {0}
        , _cap_of_font {0}
        , _fonts       {reinterpret_cast<Font*>(std::malloc(0))}
    {
        FT_Init_FreeType(&_library);

        return;
    }


    auto Typewriter::construct (void) noexcept
        -> Typewriter& 
    {
        new(this) Typewriter();
        
        return *this;
    }
 

    
    //_ Destructor
    Typewriter::~Typewriter (void) noexcept
    {    
        for(size_t a=0; a<_num_of_font; ++a) _fonts[a].~Font();
        std::free(_fonts);  _fonts=nullptr;
        _cap_of_font=0;
        _num_of_font=0;
        FT_Done_FreeType(_library);
        
        return;
    }


    auto Typewriter::destruct (void) noexcept
        -> Typewriter&
    {    
        this->~Typewriter();

        return *this;
    }
   


    //_ Constant Accessor
    auto Typewriter::library (void) const noexcept
        -> const FT_Library&
    {
        return _library;
    }


    auto Typewriter::num_of_font(void) const noexcept
        -> const size_t&
    {
        return _num_of_font;
    }


    auto Typewriter::face (index_t fi_) const noexcept
        -> const FT_Face&
    {
        return this->_fonts[fi_].face();
    }


    auto Typewriter::req_height(index_t fi_) const noexcept
        -> const uint32_t&
    {
        return this->_fonts[fi_].req_height();
    }


    auto Typewriter::shaving_enable(index_t fi_) const noexcept
        -> const bool&
    {
        return this->_fonts[fi_].shaving_enable();
    }
    


    //_ Constnat Accessor
    auto Typewriter::add_font (const char* str_, uint32_t height_, bool se_) noexcept
        -> index_t
    {
        if(_cap_of_font<_num_of_font+1){
            
            if(void* vptr_=std::realloc(_fonts, sizeof(Font)*((_num_of_font+1)*2))){
                _fonts=reinterpret_cast<Font*>(vptr_);
                _cap_of_font=(_num_of_font+1)*2;
                ++_num_of_font;
            }else{
                return 0;
            }
        
        }else{
            
            ++_num_of_font;
        }

        if(!_fonts[_num_of_font-1].set(_library, str_, height_, se_)) return 0;

        return _num_of_font-1;
    }
}
