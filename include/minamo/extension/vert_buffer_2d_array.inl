#ifndef MINAMO_EXTENSION_VERT_BUFFER_2D_ARRAY
#define MINAMO_EXTENSION_VERT_BUFFER_2D_ARRAY

#include "vert_buffer_2d_array.hpp"
#include <iostream>

//====================================//
//    Namespace: minamo::extension    //
//====================================//
namespace minamo::extension{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::VertBuffer2DArray<A> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <typename A> VertBuffer2DArray<A>::VertBuffer2DArray (void) noexcept
        : width       {1}
        , height      {1}
        , nof_pages   {1}
        , buffer      {reinterpret_cast<A*>(std::malloc(sizeof(A)))}
        , locks       {reinterpret_cast<uint32_t*>(std::malloc(sizeof(uint32_t)))}
    {
        buffer[0]=0;
        locks[0] =0;
    
        return;
    }


    template <typename A> VertBuffer2DArray<A>::VertBuffer2DArray (size_t w_, size_t h_) noexcept
        : width       {w_}
        , height      {h_}
        , nof_pages   {1}
        , buffer      {reinterpret_cast<A*>(std::malloc(sizeof(A)*width*height))}
        , locks       {reinterpret_cast<uint32_t*>(std::malloc(sizeof(uint32_t)*height))}
    {
        std::memset(buffer, 0, sizeof(A)*w_*h_);
        std::memset(locks , 0, sizeof(uint32_t)*h_);
    
        return;
    }


    template <typename A> VertBuffer2DArray<A>::VertBuffer2DArray (const VertBuffer2DArray& vb_) noexcept
        : width       {vb_.width}
        , height      {vb_.height}
        , nof_pages   {vb_.nof_pages}
        , buffer      {reinterpret_cast<A*>(std::malloc(sizeof(A)*width*height*nof_pages))}
        , locks       {reinterpret_cast<uint32_t*>(std::malloc(sizeof(uint32_t)*height*nof_pages))}
    {
        std::memcpy(buffer, vb_.buffer, sizeof(A)*width*height*nof_pages);
        std::memcpy(locks , vb_.locks, sizeof(uint32_t)*height*nof_pages);
    
        return;
    }


    template <typename A> VertBuffer2DArray<A>::VertBuffer2DArray (VertBuffer2DArray&& vb_) noexcept
        : width       {vb_.width}
        , height      {vb_.height}
        , buffer      {vb_.buffer}
        , locks       {vb_.locks}
    {
        vb_.locks  =nullptr;
        vb_.buffer =nullptr;
        vb_.height =0;
        vb_.width  =0;

        return;
    }



    //_ Destructor
    template <typename A> VertBuffer2DArray<A>::~VertBuffer2DArray (void) noexcept
    {
        std::free(locks);
        std::free(buffer);
        height=0;
        width=0;

        return;
    }


    //_ Destructive Function
    template <typename A> auto VertBuffer2DArray<A>::resize (size_t w_, size_t h_) noexcept
        -> ErrorCode
    {
        if(w_<=width and h_<=height) return SUCCESS;

        size_t nw=width;
        while(nw<w_) nw*=2;
        if(nw>GL_MAX_TEXTURE_SIZE) return OVER_MAX_TEXTURE_WIDTH;
       
        size_t nh=height;
        while(nh<h_) nh*=2;
        if(nh>GL_MAX_TEXTURE_SIZE) return OVER_MAX_TEXTURE_HEIGHT;

        A* new_buffer=reinterpret_cast<A*>(std::malloc(sizeof(A)*nw*nh*nof_pages));
        if(!new_buffer) return FAILED_ALLOC;

        std::memset(new_buffer, 0, sizeof(A)*nw*nh*nof_pages);

        for(size_t c=0; c<nof_pages; ++c){
            A*        cur_head =buffer+width*height*c;
            uint32_t* lock_head=locks+height*c;
            A*        new_head =new_buffer+nw*nh*c;
            for(size_t a=0, b=0, new_b=0; a<height; ++a, b+=width, new_b+=nw){
                if(lock_head[a]) std::memcpy(new_head+new_b, cur_head+b, sizeof(A)*width);
            }
        }
   
        if(nh!=height){
    
            uint32_t* new_locks=reinterpret_cast<uint32_t*>(std::malloc(sizeof(uint32_t)*nh*nof_pages));
            
            if(!new_locks){
                std::free(new_buffer);
                return FAILED_ALLOC;
            }
    
            std::memset(new_locks, 0, sizeof(uint32_t)*nh*nof_pages);
           
            for(size_t c=0; c<nof_pages; ++c){
                uint32_t* cur_lock_head=locks+height*c;
                uint32_t* new_lock_head=new_locks+nh*c;
               
                std::memcpy(new_lock_head, cur_lock_head, sizeof(uint32_t)*height);
            }
            std::free(locks);
            locks=new_locks;
        }
    
        std::free(buffer); 
        width =nw;
        height=nh;
        buffer=new_buffer;
            
        return SUCCESS;
    }


    template <typename A> auto VertBuffer2DArray<A>::add_page (void) noexcept
        -> ErrorCode
    {
        if(void* vptr=std::realloc(buffer, sizeof(A)*width*height*(nof_pages+1))){
            
            buffer=reinterpret_cast<A*>(vptr);
            std::memset(buffer+width*height*nof_pages, 0, sizeof(A)*width*height);
            
        }else{
            
            return FAILED_ALLOC;
        }

        if(void* vptr=std::realloc(locks, sizeof(uint32_t)*height*(nof_pages+1))){
                
            locks=reinterpret_cast<uint32_t*>(vptr);
            std::memset(locks+height*nof_pages, 0, sizeof(uint32_t)*height);
            
        }else{
            
            return FAILED_ALLOC;
        }

        ++nof_pages;
        
        return SUCCESS;
    }
    

    template <typename A> auto VertBuffer2DArray<A>::add_lock (size_t p_, size_t h_) noexcept
        -> ErrorCode
    {
        size_t of=p_*height;
        if(locks[of+h_]!=~0U){ ++locks[of+h_]; return SUCCESS; }
        else                 { return LOCK_OVERFLOW; }
    }


    template <typename A> auto VertBuffer2DArray<A>::add_locks (size_t p_, size_t h1_, size_t h2_) noexcept
        -> ErrorCode
    {
        size_t of=p_*height;
        for(size_t a=h1_; a<h2_; ++a){
            if(locks[of+a]!=~0U){ ++locks[of+a]; }
            else                { return LOCK_OVERFLOW; }
        }

        return SUCCESS;
    }


    template <typename A> auto VertBuffer2DArray<A>::subtract_lock (size_t p_, size_t h_) noexcept
        -> ErrorCode
    {
        size_t of=p_*height;
        if(locks[of+h_]){
            if(!(--locks[of+h_])) std::memset(this->operator()(p_, h_), 0, sizeof(A)*width);
            return SUCCESS; 
        }else{
            return INVALID_LOCK_OPERATION;
        }
    }


    template <typename A> auto VertBuffer2DArray<A>::subtract_locks (size_t p_, size_t h1_, size_t h2_) noexcept
        -> ErrorCode
    {
        size_t of=p_*height;
        for(size_t a=h1_; a<h2_; ++a){
            if(locks[of+a]){
                if(!(--locks[of+a])) std::memset(this->operator()(p_, a), 0, sizeof(A)*width);
            }else{
                return INVALID_LOCK_OPERATION;
            }
        }
        
        return SUCCESS;
    }
 

    template <typename A> auto VertBuffer2DArray<A>::get_lock (size_t p_, size_t h_) noexcept
        -> uint32_t&
    {
        return locks[p_*height+h_];
    }


    template <typename A> auto VertBuffer2DArray<A>::get_locks (size_t p_) noexcept
        -> uint32_t*
    {
        return locks+(p_*height);
    }



    //_ Constant Function
    template <typename A> auto VertBuffer2DArray<A>::get_lock (size_t p_, size_t h_) const noexcept
        -> const uint32_t&
    {
        return locks[p_*height+h_];
    }


    template <typename A> auto VertBuffer2DArray<A>::get_locks (size_t p_) const noexcept
        -> const uint32_t*
    {
        return locks+(p_*height);
    }



    //_ Constant Binary Operator
    template <typename A> auto VertBuffer2DArray<A>::operator() (size_t p_, size_t h_) const noexcept
        -> const A*
    {
        return buffer+(p_*height+h_)*width;
    }

    
    template <typename A> auto VertBuffer2DArray<A>::operator() (size_t p_, size_t w_, size_t h_) const noexcept
        -> const A&
    {
        return buffer[(p_*height+h_)*width+w_];
    }



    //_ Destructive Binary Operator
    template <typename A> auto VertBuffer2DArray<A>::operator() (size_t p_, size_t h_) noexcept
        -> A*
    {
        return buffer+(p_*height+h_)*width;
    }

    
    template <typename A> auto VertBuffer2DArray<A>::operator() (size_t p_, size_t w_, size_t h_) noexcept
        -> A&
    {
        return buffer[(p_*height+h_)*width+w_];
    }
}

#endif
