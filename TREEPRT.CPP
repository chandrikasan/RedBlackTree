/////////////////////////////////////////////////////////////
// treeprt.cpp: Tree printing functions
// Copyright(c) 1993 Azarona Software. All rights reserved.
/////////////////////////////////////////////////////////////
#include <iostream.h>
#include "treeprt.h"
#include "twalk.h"

struct BnodeXY : public Bnodeb {
  int x, y;
  BnodeXY *Left();
  BnodeXY *Right();
};

inline BnodeXY *BnodeXY::Left()
{
  return (BnodeXY *)left;
}


inline BnodeXY *BnodeXY::Right()
{
  return (BnodeXY *)right;
}


BnodeXY *GetNodePosn(Bnodeb *t, int &x, int y, NodeWidthFunc NodeWidth)
// Using an in-order traversal, figure out x and y of each node
// in the tree t, assuming that the top left hand corner of the
// box bounding t is at (x, y). Builds a parallel shadow tree
// of nodes having x & y in them.
{
  if (t == 0) return 0;
  BnodeXY *l = GetNodePosn(t->left, x, y+1, NodeWidth);
  BnodeXY *xyt = new BnodeXY;
  xyt->left = l;
  xyt->x = x;
  x += NodeWidth(t);
  xyt->y = y;
  y++;
  xyt->right = GetNodePosn(t->right, x, y, NodeWidth);
  return xyt;
}

void PrintUp(Bnodeb *t, PrtFunc PrtNode, NodeWidthFunc NodeWidth)
// Print tree t upright, using positions in xyt as a guide.
{
  int spacing, last_sp, x, oldy;
  Bnodeb *nxt;
  BnodeXY *xynxt;

  if (t == 0) { cout << "Empty tree\n"; return; }

  x = 1;
  BnodeXY *xyt = GetNodePosn(t, x, 0, NodeWidth);

  TreeWalkerb tw(t, lvl_order);
  TreeWalker<BnodeXY> xytw(xyt, lvl_order);

  oldy = 0;
  last_sp = 0;
  while(1) {
    xynxt = xytw.Next();
    if (xynxt == 0) break;
    if (xynxt->y != oldy) {
       oldy = xynxt->y;
       cout << '\n';
       last_sp = 0;
    }
    spacing = xynxt->x - last_sp - 1;
    if (spacing < 0) spacing = 0;
    while(spacing--) cout << ' ';
    nxt = tw.Next();
    PrtNode(nxt);
    last_sp = xynxt->x + NodeWidth(nxt) - 1;
  }
  cout << "\n\n";

  // Need to delete shadow tree. Easy to do with postorder traversal
  xytw.Reset(xyt, post_order);
  while(1) {
    xynxt = xytw.Next();
    if (xynxt == 0) break;
    delete xynxt;
  }
}


void PrintSideWays(Bnodeb *t, PrtFunc PrtNode, int inc, int space)
// Using a right-to-left in-order traversal.
{
  while(t) {
    PrintSideWays(t->right, PrtNode, inc, space+inc);
    for(int i = 0; i<space; i++) cout << ' ';
    PrtNode(t); cout << '\n';
    t = t->left;
    space += inc;
  }
}


void TestTraversals(Bnodeb *root, VisitFunc Visit)
// This one tests out every traversal method we have.
{
  Bnodeb *nxt;

  if (root == 0) { cout << "Tree is empty\n"; return; }

  cout << "RecPre:   "; PreOrder(root, Visit); cout << '\n';
  cout << "FlatPre:  "; PreOrderFlat(root, Visit); cout << '\n';
  cout << "IterPre:  ";
  TreeWalkerb tw(root, pre_order);
  while((nxt = tw.Next()) != 0) Visit(nxt);
  cout << '\n';

  cout << "RecIn:    "; InOrder(root, Visit); cout << '\n';
  cout << "FlatIn:   "; InOrderFlat(root, Visit); cout << '\n';
  cout << "IterIn:   ";
  tw.Reset(root, in_order);
  while((nxt = tw.Next()) != 0) Visit(nxt);
  cout << '\n';

  cout << "RecPost:  "; PostOrder(root, Visit); cout << '\n';
  cout << "FlatPost: "; PostOrderFlat(root, Visit); cout << '\n';
  cout << "IterPost: ";
  tw.Reset(root, post_order);
  while((nxt = tw.Next()) != 0) Visit(nxt);
  cout << '\n';

  cout << "FlatLvl:  "; LvlOrder(root, Visit);  cout << '\n';
  cout << "IterLvl:  ";
  tw.Reset(root, lvl_order);
  while((nxt = tw.Next()) != 0) Visit(nxt);
  cout << '\n';
}


void TestTraversalsII(Bnodeb *root, VisitFunc Visit)
// Shorthand version. Tests the trickiest ones.
{
  if (root == 0) { cout << "Tree is empty\n"; return; }

  cout << "FlatPre:  "; PreOrderFlat(root, Visit); cout << '\n';
  cout << "FlatIn:   "; InOrderFlat(root, Visit); cout << '\n';
  cout << "FlatPost: "; PostOrderFlat(root, Visit); cout << '\n';
  cout << "FlatLvl:  "; LvlOrder(root, Visit);  cout << '\n';
}
