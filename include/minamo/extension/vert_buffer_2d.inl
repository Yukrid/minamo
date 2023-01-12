#ifndef MINAMO_EXTENSION_VERT_BUFFER_2D_INL
#define MINAMO_EXTENSION_VERT_BUFFER_2D_INL

#include "vert_buffer_2d.hpp"
#include <iostream>

//====================================//
//    Namespace: minamo::extension    //
//====================================//
namespace minamo::extension{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::VertBuffer2D<A> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <typename A> VertBuffer2D<A>::VertBuffer2D (void) noexcept
        : width  {1}
        , height {1}
        , buffer {reinterpret_cast<A*>(std::malloc(sizeof(A)))}
        , locks  {reinterpret_cast<uint32_t*>(std::malloc(sizeof(uint32_t)))}
    {
        buffer[0]=0;
        locks[0] =0;
    
        return;
    }


    template <typename A> VertBuffer2D<A>::VertBuffer2D (size_t w_, size_t h_) noexcept
        : width  {w_}
        , height {h_}
        , buffer {reinterpret_cast<A*>(std::malloc(sizeof(A)*width*height))}
        , locks  {reinterpret_cast<uint32_t*>(std::malloc(sizeof(uint32_t)*height))}
    {
        std::memset(buffer, 0, sizeof(A)*w_*h_);
        std::memset(locks , 0, sizeof(uint32_t)*h_);
    
        return;
    }


    template <typename A> VertBuffer2D<A>::VertBuffer2D (const VertBuffer2D& vb_) noexcept
        : width  {vb_.width}
        , height {vb_.height}
        , buffer {reinterpret_cast<A*>(std::malloc(sizeof(A)*width*height))}
        , locks  {reinterpret_cast<uint32_t*>(std::malloc(sizeof(uint32_t)*height))}
    {
        std::memcpy(buffer, vb_.buffer, sizeof(A)*width*height);
        std::memcpy(locks , vb_.locks, sizeof(uint32_t)*height);
    
        return;
    }


    template <typename A> VertBuffer2D<A>::VertBuffer2D (VertBuffer2D&& vb_) noexcept
        : width  {vb_.width}
        , height {vb_.height}
        , buffer {vb_.buffer}
        , locks  {vb_.locks}
    {
        vb_.locks  =nullptr;
        vb_.buffer =nullptr;
        vb_.height =0;
        vb_.width  =0;

        return;
    }



    //_ Destructor
    template <typename A> VertBuffer2D<A>::~VertBuffer2D (void) noexcept
    {
        std::free(locks);
        std::free(buffer);
        height=0;
        width=0;

        return;
    }


    //_ Destructive Function
    template <typename A> auto VertBuffer2D<A>::resize (size_t w_, size_t h_) noexcept
        -> ErrorCode
    {
        if(w_<=width){

            return reheight(h_);
        
        }else if(h_<=height){
            
            return rewidth(w_);
        
        }else{
    
            size_t nw=width;
            while(nw<w_) nw*=2;
            if(nw>GL_MAX_TEXTURE_SIZE) return OVER_MAX_TEXTURE_WIDTH;
            
            size_t nh=height;
            while(nh<h_) nh*=2;
            if(nh>GL_MAX_TEXTURE_SIZE) return OVER_MAX_TEXTURE_HEIGHT;

            A* new_buffer=reinterpret_cast<A*>(std::malloc(sizeof(A)*nw*nh));
            if(!new_buffer) return FAILED_ALLOC;

            std::memset(new_buffer, 0, sizeof(A)*nw*nh);

            if(void* vptr=std::realloc(locks, sizeof(uint32_t)*nh)){
                
                locks=reinterpret_cast<uint32_t*>(vptr);
                std::memset(locks+height, 0, sizeof(uint32_t)*(nh-height));
            
            }else{
                return FAILED_ALLOC;    
            }
                 
            size_t new_b=0;
            for(size_t a=0, b=0; a<height; ++a, b+=width, new_b+=nw){
                
                if(locks[a]) std::memcpy(new_buffer+new_b, buffer+b, sizeof(A)*width);
            }
            
            std::free(buffer); 
            width =nw;
            height=nh;
            buffer=new_buffer;

            return SUCCESS;
        }
    }


    template <typename A> auto VertBuffer2D<A>::rewidth (size_t w_) noexcept
        -> ErrorCode
    {
        if(w_<=width){

            return SUCCESS;
        
        }else{
        
            size_t nw=width;
            while(nw<w_) nw*=2;
            if(nw>GL_MAX_TEXTURE_SIZE) return OVER_MAX_TEXTURE_WIDTH;
                
            A* new_buffer=reinterpret_cast<A*>(std::malloc(sizeof(A)*nw*height));
            std::memset(new_buffer, 0, sizeof(A)*nw*height);

            if(!new_buffer) return FAILED_ALLOC; 

            size_t new_b=0;
            for(size_t a=0, b=0; a<height; ++a, b+=width, new_b+=nw){
                if(locks[a]){
                    std::memcpy(new_buffer+new_b, buffer+b, sizeof(A)*width);
                }
            }
            
            std::free(buffer);

            width =nw;
            buffer=new_buffer;

            return SUCCESS;
        }
    }


    template <typename A> auto VertBuffer2D<A>::reheight (size_t h_) noexcept
        -> ErrorCode
    {
        if(h_<=height){

            return SUCCESS;
        
        }else{
    
            size_t nh=height;
            while(nh<h_) nh*=2;
            if(nh>GL_MAX_TEXTURE_SIZE) return OVER_MAX_TEXTURE_HEIGHT;

            if(void* vptr=std::realloc(buffer, sizeof(A)*width*nh)){
                
                buffer=reinterpret_cast<A*>(vptr);
                std::memset(buffer+width*height, 0, sizeof(A)*width*(nh-height));
            
            }else{
            
                return FAILED_ALLOC;
            }
            

            if(void* vptr=std::realloc(locks, sizeof(uint32_t)*nh)){
                
                locks=reinterpret_cast<uint32_t*>(vptr);
                std::memset(locks+height, 0, sizeof(uint32_t)*(nh-height));
            
            }else{
            
                return FAILED_ALLOC;
            }
            
            height=nh;

            return SUCCESS;
        }
    }


    template <typename A> auto VertBuffer2D<A>::add_lock (size_t h_) noexcept
        -> ErrorCode
    {
        if(locks[h_]!=~0U){ ++locks[h_]; return SUCCESS; }
        else              { return LOCK_OVERFLOW; }
    }


    template <typename A> auto VertBuffer2D<A>::add_locks (size_t h1_, size_t h2_) noexcept
        -> ErrorCode
    {
        for(size_t a=h1_; a<h2_; ++a){
            if(locks[a]!=~0U){ ++locks[a]; }
            else             { return LOCK_OVERFLOW; }
        }

        return SUCCESS;
    }


    template <typename A> auto VertBuffer2D<A>::subtract_lock (size_t h_) noexcept
        -> ErrorCode
    {
        if(locks[h_]){ --locks[h_]; return SUCCESS; }
        else         { return INVALID_LOCK_OPERATION; }
    }


    template <typename A> auto VertBuffer2D<A>::subtract_locks (size_t h1_, size_t h2_) noexcept
        -> ErrorCode
    {
        for(size_t a=h1_; a<h2_; ++a){
            if(locks[a]){ --locks[a]; }
            else        { return INVALID_LOCK_OPERATION; }
        }
        
        return SUCCESS;
    }
 


    //_ Constant Binary Operator
    template <typename A> auto VertBuffer2D<A>::operator() (size_t h_) const noexcept
        -> const A*
    {
        return buffer+h_*width;
    }

    
    template <typename A> auto VertBuffer2D<A>::operator() (size_t w_, size_t h_) const noexcept
        -> const A&
    {
        return buffer[h_*width+w_];
    }



    //_ Destructive Binary Operator
    template <typename A> auto VertBuffer2D<A>::operator() (size_t h_) noexcept
        -> A*
    {
        return buffer+h_*width;
    }

    
    template <typename A> auto VertBuffer2D<A>::operator() (size_t w_, size_t h_) noexcept
        -> A&
    {
        return buffer[h_*width+w_];
    }

}

#endif
