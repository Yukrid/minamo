#ifndef MINAMO_PUBLIC_GLM_TYPE_HPP 
#define MINAMO_PUBLIC_GLM_TYPE_HPP 

#include <glm/glm.hpp>

#include "forward.hpp"

//=========================//
//    Namespace: minamo    //
//=========================//
namespace minamo{

    //-------------//
    //    Alias    //
    //-------------//
    template <uint16_t N> using  vecn = glm::vec<N, float, glm::defaultp>; 
    template <uint16_t N> using ivecn = glm::vec<N, int, glm::defaultp>; 
    template <uint16_t N> using uvecn = glm::vec<N, unsigned int, glm::defaultp>; 

    template <uint16_t N, uint16_t M> using matnxm = glm::mat<N, M, float, glm::defaultp>; 

}
#endif
