#ifndef MINAMO_DRAWER_STANDARD_INL
#define MINAMO_DRAWER_STANDARD_INL

#include "standard.hpp"

//=================================//
//    Namespace: minamo::drawer    //
//=================================//
namespace minamo::drawer{
    
    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::drawer Namespace    )//
    template <class A> inline auto _call_locate(A& a_, int32_t) noexcept
        -> decltype(void(std::declval<A>().locate()))
    {
        a_.locate();
    
        return;
    }


    template <class A> inline auto _call_locate(A& a_, int16_t) noexcept
        -> void
    {
        return;
    }
    

    template <class A> inline auto call_locate (A& a_) noexcept
        -> decltype(void(_call_locate(std::declval<A&>, 0)))
    {
        return _call_locate(a_, 0);
    }


    template <class A> inline auto _call_prefix(A& a_, int32_t) noexcept
        -> decltype(void(std::declval<A>().prefix()))
    {
        a_.prefix();
    
        return;
    }


    template <class A> inline auto _call_prefix(A& a_, int16_t) noexcept
        -> void
    {
        return;
    }
    

    template <class A> inline auto call_prefix (A& a_) noexcept
        -> decltype(void(_call_prefix(std::declval<A&>(), 0)))
    {
        return _call_prefix(a_, 0);
    }


    template <class A> inline auto _call_suffix(A& a_, int32_t) noexcept
        -> decltype(void(std::declval<A>().suffix()))
    {
        a_.suffix();
    
        return;
    }


    template <class A> inline auto _call_suffix(A& a_, int16_t) noexcept
        -> void
    {
        return;
    }
    

    template <class A> inline auto call_suffix (A& a_) noexcept
        -> decltype(void(_call_suffix(std::declval<A&>(), 0)))
    {
        return _call_suffix(a_, 0);
    }




    //(    minamo::drawer::Methods<As...> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <class... As> Methods<As...>::Methods (Kernel&) noexcept
    {
        return;
    }



    //_ Destructive Function
    template <class... As> void Methods<As...>::locate (void) noexcept
    {
        return;
    }


    template <class... As> void Methods<As...>::prefix (void) noexcept
    {
        return;
    }


    template <class... As> void Methods<As...>::suffix (void) noexcept
    {
        return;
    }



    //_ Constant Function
    template <class... As> template <size_t N> void Methods<As...>::_get (Indicator<N>) const noexcept
    {
        return;
    }




    //(    minamo::drawer::Methods<A, As...> Structure Template    )//
    //+    Member Function    +//
    //_ Constructor
    template <class A, class... As> Methods<A, As...>::Methods (Kernel& ker_) noexcept
        : val  {ker_}
        , sitp {ker_}
    {
        return;
    }


    //_ Destructive Function
    template <class A, class... As> auto Methods<A, As...>::_get (Indicator<0>) noexcept
        -> A&
    {
        return val;
    }
    

    template <class A, class... As> template <size_t N> auto Methods<A, As...>::_get (Indicator<N>) noexcept
        -> decltype(std::declval<Methods<As...>>()._get(std::declval<Indicator<N-1>>()))
    {
        return sitp._get(Indicator<N-1>{ });
    }


    template <class A, class... As> template <size_t N> auto Methods<A, As...>::get (void) noexcept
        -> decltype(_get(std::declval<Indicator<N>>()))
    {
        return _get(Indicator<N>{ });
    }


    template <class A, class... As> void Methods<A, As...>::locate (void) noexcept
    {
        call_locate(val);

        return sitp.locate();;
    }
 

    template <class A, class... As> void Methods<A, As...>::prefix (void) noexcept
    {
        call_prefix(val);

        return sitp.prefix();;
    }
   

    template <class A, class... As> void Methods<A, As...>::suffix (void) noexcept
    {
        call_suffix(val);

        return sitp.suffix();;
    }





    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::drawer::Standard<Ms...>    )//
    //+    Member Function    +//
    //_ Constructor
    template <class... Ms> Standard<Ms...>::Standard (void) noexcept
        : kernel  { }
        , methods {kernel}
    {
        std::cerr<<kernel.compile_vertex_shader()<<std::endl;
        std::cerr<<kernel.compile_fragment_shader()<<std::endl;
        glLinkProgram(kernel.program_id);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Standard::Standard]  glLinkProgram : "<<kernel.program_id<<std::endl;
#endif
    
        methods.locate();

        return;
    }
    

    template <class... Ms> Standard<Ms...>::~Standard (void) noexcept
    {
        glDetachShader(kernel.program_id, kernel.vertex_shd.id);
        glDetachShader(kernel.program_id, kernel.fragment_shd.id);
        glDeleteShader(kernel.vertex_shd.id);
        glDeleteShader(kernel.fragment_shd.id);

#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Standard::~Standard]  glDetachShader : "<<kernel.program_id<<' '<<kernel.vertex_shd.id<<std::endl;
        std::cout<<"[Standard::~Standard]  glDetachShader : "<<kernel.program_id<<' '<<kernel.fragment_shd.id<<std::endl;
        std::cout<<"[Standard::~Standard]  glDeleteShader : "<<kernel.vertex_shd.id<<std::endl;
        std::cout<<"[Standard::~Standard]  glDeleteShader : "<<kernel.fragment_shd.id<<std::endl;
#endif

        return;
    }
    

    //_ Destructive Function
    //void Drawer::attach (void* ptr_) noexcept
    //{
    //    attach_cb(ptr_);

    //    return;
    //}
   


    //_ Destructive Function
    template <class... Ms> template <class... As> void Standard<Ms...>::draw (void (*func_)(As...), As... as_) noexcept
    {
        glBindVertexArray(kernel.vertex_array_id);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Standard::draw]  glBindVertexArray : "<<kernel.vertex_array_id<<std::endl;
#endif
        methods.prefix();
        func_(as_...);
        methods.suffix();
        
        glBindVertexArray(0);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Standard::draw]  glBindVertexArray : "<<0<<std::endl;
#endif
       
        kernel.draw_count.increment();

        return;
    }



    template <class... Ms> template <class... As> void Standard<Ms...>::draw (void (*func_)(const As&...), As... as_) noexcept
    {
        glBindVertexArray(kernel.vertex_array_id);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Standard::draw]  glBindVertexArray : "<<kernel.vertex_array_id<<std::endl;
#endif
        methods.prefix();
        func_(as_...);
        methods.suffix();
        
        glBindVertexArray(0);
#ifdef MINAMO_CALLED_GL_FUNC_INFO
        std::cout<<"[Standard::draw]  glBindVertexArray : "<<0<<std::endl;
#endif
       
        kernel.draw_count.increment();

        return;
    }
}

#endif
