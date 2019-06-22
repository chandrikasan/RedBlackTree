/////////////////////////////////////////////////////////////
// rbnode.h: Red-black tree node class definition.
// Copyright(c) 1993 Azarona Software. All rights reserved.
/////////////////////////////////////////////////////////////
#ifndef H_RBNODE
#define H_RBNODE
#include "bnodeb.h"

#define INLINE

#define RED 0
#define BLACK 1

struct RBnodeb : Bnodeb {
  char color;
  RBnodeb *&Left();
  RBnodeb *&Right();
};

inline RBnodeb *&RBnodeb::Left()
{
  return (RBnodeb *)left;
}

inline RBnodeb *&RBnodeb::Right()
{
  return (RBnodeb *)right;
}

template<class TYPE>
struct RBnode : RBnodeb {
  TYPE info;
  RBnode();
  RBnode(const TYPE &x, char c=1, RBnode<TYPE> *l=0, RBnode<TYPE> *r=0);
  RBnode<TYPE> *&Left();
  RBnode<TYPE> *&Right();
};

template<class TYPE>
INLINE RBnode<TYPE>::RBnode()
{
  left = 0; right = 0; color = BLACK;
}

template<class TYPE>
INLINE RBnode<TYPE>::
RBnode(const TYPE &x, char c, RBnode<TYPE> *l, RBnode<TYPE> *r)
: info(x)
{
  left = l; right = r; color = c;
}

template<class TYPE>
INLINE RBnode<TYPE> *&RBnode<TYPE>::Left()
{
  return (RBnode<TYPE> *)left;
}

template<class TYPE>
INLINE RBnode<TYPE> *&RBnode<TYPE>::Right()
{
  return (RBnode<TYPE> *)right;
}

#undef INLINE

#endif

