#include "minamo/rect/color_drawer.hpp"

//===============================//
//    Namespace: minamo::rect    //
//===============================//
namespace minamo::rect{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::rect::ColorDrawer    )//
    //_ Constructor
    ColorDrawer::ColorDrawer (void) noexcept
        : CoordMethod        { }
        , SimpleColorMethod  { }
        , UnorderedMapDrawer { }
    {
        glUseProgram(this->program_id);
        CoordMethod::locate(REMAIN_PROGRAM);
        
        return;
    }


    auto ColorDrawer::append (const Region& reg_, const glm::vec4& col_) noexcept -> index_t
    {

        index_t id=this->get_new_index();
        
        ColorRect& crec=store[id];
        crec.region=reg_;
        crec.calc();
        crec.colorize(col_);
        
        CoordMethod::enable_send      =true;
        SimpleColorMethod::enable_send=true;

        return id;
    }



    void ColorDrawer::remove (index_t id_) noexcept 
    {
        store.erase(id_);
        CoordMethod::enable_send=true;
        
        return;
    }


    auto ColorDrawer::resize (index_t id_, GLfloat scale_[2]) noexcept -> index_t
    {
        store.at(id_).resize(scale_);
        CoordMethod::enable_send=true;
        
        return id_;
    }


    auto ColorDrawer::move (index_t id_, const glm::vec3& v3_, Region::Anchor anc_) noexcept -> index_t
    {
        store.at(id_).move(v3_, anc_);
        CoordMethod::enable_send=true;

        return id_;
    }


    auto ColorDrawer::move (index_t id_, Region::Anchor anc_) noexcept -> index_t
    {
        store.at(id_).move(anc_);
        CoordMethod::enable_send=true;
    
        return id_;
    }


    auto ColorDrawer::colorize (index_t id_, const glm::vec4& col_) noexcept -> index_t
    {
        store.at(id_).colorize(col_);
        SimpleColorMethod::enable_send =true;
        
        return id_;
    }
    

    void ColorDrawer::attach_cb (void*) noexcept
    {
        if(CoordMethod::enable_send){
            
            this->coords.resize(0);

            for(const std::pair<index_t, ColorRect>& p : store){

                this->coords.push_back(p.second.coords[0]);
                this->coords.push_back(p.second.coords[1]);
                this->coords.push_back(p.second.coords[2]);
                this->coords.push_back(p.second.coords[3]);
            }
        }
            

        if(SimpleColorMethod::enable_send){
            
            this->colors.resize(0);

            for(const std::pair<index_t, ColorRect>& p : store){

                this->colors.push_back(p.second.base_color);
                this->colors.push_back(p.second.base_color);
                this->colors.push_back(p.second.base_color);
                this->colors.push_back(p.second.base_color);
            }
        }
        
        CoordMethod::attach_cb();
        SimpleColorMethod::attach_cb();

        return;
    }


    
    //_ Constant Function
    void ColorDrawer::draw_cb (void*) const noexcept{
        
        glUseProgram(this->program_id);
        
        CoordMethod::prefix(REMAIN_PROGRAM);
        SimpleColorMethod::prefix(REMAIN_PROGRAM);

        for(size_t a=0, b=0; a<store.size(); ++a, b+=4){
            glDrawArrays(GL_TRIANGLE_STRIP, b, 4);
        }

        SimpleColorMethod::suffix();
        CoordMethod::suffix();

        return;
    }
    

    auto ColorDrawer::get (index_t id_) const noexcept -> const ColorRect&
    {
        return store.at(id_);
    }
}
