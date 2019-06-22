////////////////////////////////////////////////////////////
// treeprt.h: Header file for tree printing functions.
// Copyright(c) 1993 Azarona Software. All rights reserved.
////////////////////////////////////////////////////////////
#ifndef H_TREEPRT
#define H_TREEPRT
#include "bnodeb.h"

typedef void (*PrtFunc)(Bnodeb *n);
typedef int (*NodeWidthFunc)(Bnodeb *n);

template<class TYPE>
struct PrtClass {
  static void PrtNode(Bnodeb *n);
  static void PrtNodeWSpace(Bnodeb *n);
  static void PrtRBNode(Bnodeb *n);
  static void PrtRBNodeWSpace(Bnodeb *n);
  static int NodeWidth(Bnodeb *n);
  static int RBNodeWidth(Bnodeb *n);
};

void PrintUp(Bnodeb *root, PrtFunc PrtNode, NodeWidthFunc NodeWidth);
void PrintSideWays(Bnodeb *t, PrtFunc PrtNode, int inc, int space=0);

void TestTraversals(Bnodeb *root, VisitFunc Visit);
void TestTraversalsII(Bnodeb *root, VisitFunc Visit);

// Whether or not we should include the following template
// methods here is implementation dependent

#include "treeprt.mth"

#endif
