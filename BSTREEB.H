//////////////////////////////////////////////////////////////
// bstreeb.h: Abstract binary search tree node functions.
// These functions assume the nodes are part of binary
// search trees, but don't depend on the data stored in
// the nodes.
// Copyright(c) 1993 Azarona Software. All rights reserved.
//////////////////////////////////////////////////////////////
#ifndef H_BSTREEB
#define H_BSTREEB
#include "bnode.h"

Bnodeb *Minimum(Bnodeb *t);
Bnodeb *Maximum(Bnodeb *t);
Bnodeb *ParentOfMinimum(Bnodeb *t);
Bnodeb *ParentOfMaximum(Bnodeb *t);
Bnodeb *ParentOfPredecessor(Bnodeb *t);
Bnodeb *ParentOfSuccessor(Bnodeb *t);
Bnodeb *DetachNode(Bnodeb *&root, Bnodeb *t, Bnodeb *p, int side);

#endif
