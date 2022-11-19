#ifndef MINAMO_INHERITANCE_HPP
#define MINAMO_INHERITANCE_HPP

#include <stdexcept>

#include "forward.hpp"

namespace minamo{
    
    //------------------------------------------------//
    //    Constant Expression Function Declaration    //
    //------------------------------------------------//
    //(    minamo    )//
    template <class A> inline constexpr auto get_threshold_count (int)   -> decltype(A::_threshold_count());
    template <class A> inline constexpr auto get_threshold_count (short) -> size_t ;
    template <class A> inline constexpr auto get_threshold_count (void)  -> decltype(get_threshold_count<A>(0));
 



    //------------------------//
    //    Class Definition    //
    //------------------------//
    //(    minamo::Number<N>    )//
    template <size_t N> struct Number{

    };
    

    //(    minamo::Pack<As...>    )//
    template <class... As> struct Pack{

    };



    //(    minamo::Threshold<A,N> Template Structure    )//
    template <class A, size_t N> struct Threshold : A{
        
        //+   Member Constant Expression Function    +//
        inline static constexpr auto _threshold_count (void) -> size_t;
    
        //+    Member Function    +//
        //_ Constructor
        template <class... As> Threshold (As... as_) noexcept
            : A {as_...}
        {
            return;
        }
    
        //_ Destructor
        virtual ~Threshold (void) noexcept =default;
    };


    
    //(    minamo::InheritanceArray<A,N> Template Structure    )//
    template <class A, size_t N> struct InheritanceArray : Threshold<A, get_threshold_count<A>()+N>, InheritanceArray<A, N-1>{

        //+    Alias    +//
        using This =Threshold<A, get_threshold_count<A>()+N>;
        using Prev =InheritanceArray<A, N-1>;
        

        //+    Function Definition    +//
        //_ constuctor
        template <class... As> InheritanceArray (As...) noexcept;

        //_ Destructor
        virtual inline ~InheritanceArray (void) noexcept =default;

        //_ Destructive Function
        template <size_t M> inline auto _at (Number<M>)   noexcept -> A&;
                            inline auto _at (Number<N-1>) noexcept -> A&;
        template <size_t M> inline auto  at (void)        noexcept -> A&;

        //_ Constant Function
        template <size_t M> inline auto _at (Number<M>)   const noexcept -> const A&;
                            inline auto _at (Number<N-1>) const noexcept -> const A&;
        template <size_t M> inline auto  at (void)        const noexcept -> const A&;
    };


    template <class A> struct InheritanceArray<A, 1> : Threshold<A, get_threshold_count<A>()+1>{

        //+    Alias    +//
        using This =Threshold<A, get_threshold_count<A>()+1>;
    

        //+    Function Definition    +//
        //_ Constructor
        template <class... As> inline InheritanceArray (As...) noexcept;

        //_ Destructor
        virtual ~InheritanceArray (void) noexcept =default;

        //_ Destructive Function
        template <size_t M> [[noreturn]] inline auto _at (Number<M>)          -> A&;
                                         inline auto _at (Number<0>) noexcept -> A&;
        template <size_t M>              inline auto  at (void)      noexcept -> A&;
        
        //_ Constant Function
        template <size_t M> [[noreturn]] inline auto _at (Number<M>) const          -> const A&;
                                         inline auto _at (Number<0>) const noexcept -> const A&;
        template <size_t M>              inline auto  at (void)      const noexcept -> const A&;
    };
 


    //-------------//
    //    Alias    //
    //-------------//
    template <class A, class B> using CoverAFromB=Threshold<A, (get_threshold_count<A>()>get_threshold_count<B>() ? get_threshold_count<A>()+1 : get_threshold_count<B>())+1>;



    //------------------------//
    //    Class Definition    //
    //------------------------//
    //(    minamo::SolveAmbiguity<class A, class B>    )//
    template <class A, class B> struct SolveAmbiguity : CoverAFromB<A, B>, B{
        
        //+    Alias    +//
        using First  =typename CoverAFromB<A, B>::A;
        using Second =B;
    

        //+    Function Definition    +//
        //_ Constructor
        SolveAmbiguity (void) : CoverAFromB<A, B>{ }, B{ } { return; }

        //_ Destructor
        virtual ~SolveAmbiguity (void) noexcept =default;
    };



    //-----------------------------------------------//
    //    Constant Expression Function Definition    //
    //-----------------------------------------------//
    //(    minamo    )//
    template <class A> inline constexpr auto get_threshold_count (int) -> decltype(A::_threshold_count())
    {
        return A::_threshold_count();
    }
 

    template <class A> inline constexpr auto get_threshold_count (short) -> size_t
    {
        return 0;
    }
   

    template <class A> inline constexpr auto get_threshold_count (void) -> decltype(get_threshold_count<A>(0))
    {
        return get_threshold_count<A>(0);
    }



    //(    minamo::Threshold<A,N> Template Structure    )//
    //+   Member Constant Expression Function    +//
    template <class A, size_t N> inline static constexpr auto _threshold_count (void) -> size_t
    {
        return N;
    }

    



    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    minamo::InheritanceArray<A,N> Template Structure    )//
    //_ Constructor
    template <class A, size_t N> template <class... As> inline InheritanceArray<A, N>::InheritanceArray (As... as) noexcept
        : This {as...}
        , Prev {as...}
    {
        return;
    }


    template <class A> template <class... As> inline InheritanceArray<A, 1>::InheritanceArray (As... as) noexcept
        : This {as...}
    {
        return;
    }


    
    //_ Destructive Function
    template <class A, size_t N> template <size_t M> inline auto InheritanceArray<A, N>::_at (Number<M>) noexcept -> A&
    {
        return Prev::_at(Number<M>{ });
    }
    

    template <class A> template <size_t M> [[noreturn]] inline auto InheritanceArray<A, 1>::_at (Number<M>) -> A&
    {
        throw std::out_of_range{"out of range in at function"};
    }


    template <class A, size_t N> inline auto InheritanceArray<A, N>::_at (Number<N-1>) noexcept -> A&
    {
        return *dynamic_cast<This*>(this);
    }
 

    template <class A> inline auto InheritanceArray<A, 1>::_at (Number<0>) noexcept -> A&
    {
        return *this;
    }


    template <class A, size_t N> template <size_t M> inline auto InheritanceArray<A, N>::at (void) noexcept -> A&
    {
        return _at(Number<M>{ });
    }
 

    template <class A> template <size_t M> inline auto InheritanceArray<A, 1>::at (void) noexcept -> A&
    {
        return _at(Number<M>{ });
    }
    


    //_ Constructor Function
    template <class A, size_t N> template <size_t M> inline auto InheritanceArray<A, N>::_at (Number<M>) const noexcept -> const A&
    {
        return Prev::_at(Number<M>{ });
    }
 

    template <class A> template <size_t M> [[noreturn]] inline auto InheritanceArray<A, 1>::_at (Number<M>) const -> const A&
    {
        throw std::out_of_range{"out of range in at function"};
    }
    


    template <class A, size_t N> inline auto InheritanceArray<A, N>::_at (Number<N-1>) const noexcept -> const A&
    {
        return *dynamic_cast<This*>(this);
    }
    

    template <class A> inline auto InheritanceArray<A, 1>::_at (Number<0>) const noexcept -> const A&
    {
        return *this;
    }


    template <class A, size_t N> template <size_t M> inline auto InheritanceArray<A, N>::at (void) const noexcept -> const A&
    {
        return _at(Number<M>{ });
    }


    template <class A> template <size_t M> inline auto InheritanceArray<A, 1>::at (void) const noexcept -> const A&
    {
        return _at(Number<M>{ });
    }
}
#endif
