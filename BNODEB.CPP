/////////////////////////////////////////////////////////////
// bnodeb.cpp: Binary tree node base class functions.
// Copyright(c) 1993 Azarona Software. All rights reserved.
/////////////////////////////////////////////////////////////
#include "bnodeb.h"
#include "listsq.h"

int NumNodes(Bnodeb *t)
// Counts the number of nodes in t, using pre-order
{
  int n = 0;
  if (t != 0) {
     ++n;
     while(t) {
       if (t->left) n += NumNodes(t->left);
       if (t->right) {
          ++n; 
          t = t->right;
       }
     }
  }
  return n;
}


int Height(Bnodeb *t)
// Determines the height of tree t
{
  int h = 0;
  if (t != 0) {
     int lh = Height(t->left);
     int rh = Height(t->right);
     h = ((lh > rh) ? lh : rh) + 1;
  }
  return h;
}


void PreOrder(Bnodeb *t, VisitFunc Visit)
// Visit each node of tree t in pre-order (first the
// parent, then the left subtree, then the right subtree).
// Tail recursion removed.
{
  while(t) {
    Visit(t);
    PreOrder(t->left, Visit);
    t = t->right;
  }
}


void InOrder(Bnodeb *t, VisitFunc Visit)
// Visit each node of tree t in in-order, (first the left
// subtree, then the parent, then the right subtree).
// Tail recursion removed
{
  while(t) {
    InOrder(t->left, Visit);
    Visit(t);
    t = t->right;
  }
}

void PostOrder(Bnodeb *t, VisitFunc Visit)
// Visit each node of tree t in post order (first the
// left subtree, then the right subtree, then the parent.)
{
  if (t == 0) return;
  PostOrder(t->left, Visit);
  PostOrder(t->right, Visit);
  Visit(t);
}

void PreOrderFlat(Bnodeb *t, VisitFunc Visit)
// Visit each node of tree t in pre-order (first the
// parent, then the left subtree, then the right
// subtree), using an explicit stack.
{
  ListStk<Bnodeb *> path;

  while(1) {
    if (t) {
       Visit(t);
       path.Push(t);
       t = t->left;
    }
    else {
      if (path.Pop(t) == 0) break;
      t = t->right;
    }
  }
}


void InOrderFlat(Bnodeb *t, VisitFunc Visit)
// Visit each node of tree t in in-order, (first the left
// subtree, then the parent, then the right subtree), using
// an explicit stack.
{
  ListStk<Bnodeb *> path;

  while(1) {
    if (t) {
       path.Push(t);
       t = t->left;
    }
    else {
      if (path.Pop(t) == 0) break;
      Visit(t);
      t = t->right;
    }
  }
}

void PostOrderFlat(Bnodeb *t, VisitFunc Visit)
// Visit each node of tree t in post order (first the
// left subtree, then the right subtree, then the parent),
// using an explicit stack.
{
  ListStk<Bnodeb *> path;
  int state = 0;

  while(1) {
    if (state == 0) { // Ready to go down to the left
       if (t) {
          path.Push(t);
          t = t->left;
       }
       else state = 1;
    }
    else { // state == 1: Ready to come up from either direction
       Bnodeb *c = t;
       if (path.IsEmpty()) break;
       t = *path.Top();
        if (c == t->left && t->right) {
          // Coming back up the tree from the left, and
          // there is a right child, so go right.
          // Note that t is still on top of stack.
          t = t->right;
          state = 0;
       }
       else {
          // Coming back up the tree from the right,
          // or there was no right child, so visit
          // the node, and continue on up. (State
          // stays at 1.)
          Visit(t);
          path.Pop();
       }
    }
  }
}

void LvlOrder(Bnodeb *t, VisitFunc Visit)
// Visit each node of tree t left to right, level by level.
{
  ListSQ<Bnodeb *> path;

  path.Insert(t);

  while(1) {
    Bnodeb *p;
    if (path.Extract(p) == 0) break;
    Visit(p);
    if (p->left != 0) path.Insert(p->left);
    if (p->right != 0) path.Insert(p->right);
  }
}


#ifdef OLD

Bnodeb *RotateRight(Bnodeb *t)
// Rotates to the right about non-null t. Returns a
// pointer to the node that takes the place of t.
{
  if (t->left != 0) {
     Bnodeb *p = t;
     t = t->left;
     p->left = t->right;
     t->right = p;
  }
  return t;
}

Bnodeb *RotateLeft(Bnodeb *t)
// Rotates to the left about non-null t. Returns a
// pointer to the node that takes the place of t.
{
  if (t->right != 0) {
     Bnodeb *p = t;
     t = t->right;
     p->right = t->left;
     t->left = p;
  }
  return t;
}

#else

Bnodeb *RotateRight(Bnodeb *p)
// Rotates to the right about non-null p. Returns a
// pointer to the node that takes the place of p.
// ASSUMES left child of p exists.
{
  Bnodeb *t = p->left;
  p->left = t->right;
  t->right = p;
  return t;
}

Bnodeb *RotateLeft(Bnodeb *p)
// Rotates to the left about non-null p. Returns a
// pointer to the node that takes the place of p.
// ASSUMES right child of p exists.
{
  Bnodeb *t = p->right;
  p->right = t->left;
  t->left = p;
  return t;
}

#endif
