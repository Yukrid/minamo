#ifndef MINAMO_DRAWER_STANDARD_HPP
#define MINAMO_DRAWER_STANDARD_HPP

#include "../forward.hpp"
#include "../kernel.hpp"

#include <iostream>
#include <tuple>

//=================================//
//    Namespace: minamo::drawer    //
//=================================//
namespace minamo::drawer{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    minamo::drawer::Indicator<N> Structure Template    )//
    template <size_t N>
    struct Indicator{

    };



    //(    minamo::drawer::Methods<As...> Structure Template     )//
    template <class... As>
    struct Methods{
 
        //+    Member Functon    +//
        //_ Constructor
        Methods (void)    noexcept =default;
        Methods (Kernel&) noexcept;
        
        //_ Destructive Function
        void locate (void) noexcept;
        void prefix (void) noexcept;
        void suffix (void) noexcept;

        //_ Constant Function
        template <size_t N> void _get (Indicator<N>) const noexcept;
    };



    //(    minamo::drawer::Methods<A, As...> Structure Template     )//
    template <class A, class... As>
    struct Methods<A, As...>{
        
        //+    Member Variable    +//
        A              val;
        Methods<As...> sitp;
        

        //+    Member Functon    +//
        //_ Constructor
        Methods (void)    noexcept =default;
        Methods (Kernel&) noexcept;


        //_ Destructive Function
                            auto _get (Indicator<0>) noexcept -> A&;
        template <size_t N> auto _get (Indicator<N>) noexcept -> decltype(std::declval<Methods<As...>>()._get(std::declval<Indicator<N-1>>()));
        template <size_t N> auto  get (void)         noexcept -> decltype(_get(std::declval<Indicator<N>>()));

        void locate (void) noexcept;
        void prefix (void) noexcept;
        void suffix (void) noexcept;
    };



    //(    minamo::drawer::Standard<Methods...> Structure Template    )//
    template <class... Ms>
    struct Standard{
        
        //+    Member Variable    +//
        public :
        Kernel         kernel;
        Methods<Ms...> methods;

        
        //+    Member Function    +//
        public :
        //_ Constructor
        Standard (void) noexcept;

        //_ Destructor
        ~Standard (void) noexcept;
        
        //_ Destructive Function
        template <class... As> void draw (void (*)(As...), As...)  noexcept;
        template <class... As> void draw (void (*)(const As&...), As...) noexcept;
    };




}

#include "standard.inl"

#endif
