/*******************************************************
FILENAME   : Node.hpp
AUTHOR     : Brian Denton
DATE       : 10/07/2011
DESCRIPTION: Define templated Node class.
*******************************************************/

#ifndef NODE_H
#define NODE_H

template< class T1, class T2 >
struct Node {
  T1 index;
  T2 value;
};

#endif

//END OF FILE
