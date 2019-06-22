/////////////////////////////////////////////////////////////
// twalk.h: Tree walking object header file.
// Copyright(c) 1993 Azarona Software. All rights reserved.
/////////////////////////////////////////////////////////////
#ifndef H_TWALK
#define H_TWALK
#include "ListSQ.h"
#include "rbnode.h"
#include "bnode.h"

#define INLINE

enum WalkOrder { pre_order, post_order, in_order, lvl_order };

class TreeWalkerb { // Tree-walking base class
protected:
  ListSQ<Bnodeb *> path;
  Bnodeb *root, *curr;
  WalkOrder worder;
  int state;
  Bnodeb *NextPreOrder();
  Bnodeb *NextInOrder();
  Bnodeb *NextPostOrder();
  Bnodeb *NextLvlOrder();
  Bnodeb *(TreeWalkerb::* NextFptr)();
public:
  TreeWalkerb(Bnodeb *r, WalkOrder w);
  virtual ~TreeWalkerb();
  void Reset();
  void Reset(Bnodeb *r, WalkOrder w);
  Bnodeb *Next();
};

template<class NTYPE>
class TreeWalker : private TreeWalkerb {
public:
  TreeWalker(NTYPE *r, WalkOrder w);
  void Reset();
  void Reset(NTYPE *r, WalkOrder w);
  NTYPE *Next();
};

template<class NTYPE>
INLINE TreeWalker<NTYPE>::TreeWalker(NTYPE *r, WalkOrder w)
: TreeWalkerb(r, w)
{
}

template<class NTYPE>
INLINE void TreeWalker<NTYPE>::Reset()
{
  TreeWalkerb::Reset();
}

template<class NTYPE>
INLINE void TreeWalker<NTYPE>::Reset(NTYPE *r, WalkOrder w)
{
  TreeWalkerb::Reset(r, w);
}

template<class NTYPE>
INLINE NTYPE *TreeWalker<NTYPE>::Next()
{
  return (NTYPE *)((this->*NextFptr)());
}

#undef INLINE

#endif
