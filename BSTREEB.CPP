//////////////////////////////////////////////////////////////
// bstreeb.cpp: Abstract binary search tree node functions.
// These functions assume the nodes are part of binary
// search trees. However, the functions don't depend on 
// the data stored in the nodes.
// Copyright(c) 1993 Azarona Software. All rights reserved.
//////////////////////////////////////////////////////////////
#include "bstreeb.h"

Bnodeb *Minimum(Bnodeb *t)
// Assuming that t is a binary search tree, this function
// returns the minimum node in the tree, which can be
// found by going as far left as possible. If t is null,
// a null is returned, else a pointer to the minimun
// node is returned.
{
  if (t) {
    while(t->left) t = t->left;
  }
  return t;
}

Bnodeb *Maximum(Bnodeb *t)
// Assuming that t is a binary search tree, this function
// returns the maximum node in the tree, which can be
// found by going as far right as possible. If t is null,
// a null is returned, else a pointer to the minimun
// node is returned.
{
  if (t) {
    while(t->right) t = t->right;
  }
  return t;
}


Bnodeb *ParentOfMinimum(Bnodeb *t)
// Assuming that t is a binary search tree, this function
// returns a pointer to the parent of the minimum node
// in the tree, which can be found by going as far left
// as possible. If t is null, or is itself the minimum,
// a null is returned.
{
  Bnodeb *p = 0;
  if (t) {
    while(t->left) {
       p = t;
       t = t->left;
    }
  }
  return p;
}

Bnodeb *ParentOfMaximum(Bnodeb *t)
// Assuming that t is a binary search tree, this function
// returns a pointer to the parent of the maximum node
// in the tree, which can be found by going as far right
// as possible. If t is null, or is itself the maximum,
// a null is returned.
{
  Bnodeb *p = 0;
  if (t) {
    while(t->right) {
       p = t;
       t = t->right;
    }
  }
  return p;
}

Bnodeb *ParentOfPredecessor(Bnodeb *t)
// Returns parent of predecessor of t, assumed to be 
// a binary search tree. Predecessor is the right child
// of node returned, unless t itself is the parent. Then 
// the left child is the predecessor. If t is a leaf, a 
// 0 is returned. ASSUMES t isn't null.
{
  Bnodeb *p = 0;
  // Go left, then all the way right
  Bnodeb *q = t->left;
  if (q) {
     p = t;
     while(q->right) {
       p = q;
       q = q->right;
     }
  }
  return p;
}

Bnodeb *ParentOfSuccessor(Bnodeb *t)
// Returns parent of successor of t, assumed to be 
// a binary search tree. Successor is the left child
// of node returned, unless t itself is the parent.
// Then the right child is the successor. If t is a 
// leaf, a 0 is returned. ASSUMES t isn't null.
{
  Bnodeb *p = 0;
  // Go right, then all the way left
  Bnodeb *q = t->right;
  if (q) {
     p = t;
     while(q->left) {
       p = q;
       q = q->left;
     }
  }
  return p;
}

Bnodeb *DetachNode(Bnodeb *&root, Bnodeb *t, Bnodeb *p, int side)
// Detaches node t with parent p from the tree. Node t is
// the left child if side = 0, else it's the right child.
// If p is 0, it means t is the root, and that is handled
// accordingly. Redundantly returns the pointer t. May
// have to update root pointer.
{
  Bnodeb *psucc, *replacement;

  if (t) {
     if (t->left == 0 || t->right == 0) {
        // At least one child is null, so use the other 
        // as the replacement. (It may be null too.)
        replacement = (t->left) ? t->left : t->right;
     }
     else { // Neither child is null
        psucc = ParentOfSuccessor(t); // guaranteed not null
        if (psucc == t) { // Immediate successor
           replacement = psucc->right;
        }
        else { 
           // Detach replacement from where it is and relocate
           // it to where t used to be.
           replacement = psucc->left;
           psucc->left = psucc->left->right;
           replacement->right = t->right;
        }
        // Finish relocating replacement to go where t used to.
        replacement->left = t->left;
     }
     if (p) { // Fixup parent of t to point to replacement
        if (side) p->right = replacement; else p->left = replacement;
     }
     else root = replacement; // No parent, so t was the root
  }
  return t;
}
