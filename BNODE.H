/////////////////////////////////////////////////////////////
// bnode.h: Binary tree node class definitions.
// Copyright(c) 1993 Azarona Software. All rights reserved.
/////////////////////////////////////////////////////////////
#ifndef H_BNODE
#define H_BNODE
#include "bnodeb.h"

#define INLINE

template<class TYPE>
struct Bnode : public Bnodeb { // Binary tree node with data
  TYPE info;
  Bnode();
  Bnode(const TYPE &x, Bnode<TYPE> *l=0, Bnode<TYPE> *r=0);
  Bnode<TYPE> *&Left();
  Bnode<TYPE> *&Right();
};

template<class TYPE>
INLINE Bnode<TYPE>::Bnode()
{
  left = 0; right = 0;
}

template<class TYPE>
INLINE Bnode<TYPE>::Bnode(const TYPE &x, Bnode<TYPE> *l, Bnode<TYPE> *r)
: info(x)
{
  left = l; right = r;
}

template<class TYPE>
INLINE Bnode<TYPE> *&Bnode<TYPE>::Left()
// It's assumed left really IS a Bnode<TYPE>.
{
  return (Bnode<TYPE> *)left;
}

template<class TYPE>
INLINE Bnode<TYPE> *&Bnode<TYPE>::Right()
// It's assumed right really IS a Bnode<TYPE>.
{
  return (Bnode<TYPE> *)right;
}


#undef INLINE

#endif
