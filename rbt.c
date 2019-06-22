#include <stdio.h>
#include <stdlib.h>


struct RBTree
 {
        int key;
        char color;
        struct RBTree *left;
        struct RBTree *right;
        struct RBTree *parent;
 };


 typedef struct RBTree *pRBTree;


 pRBTree TreePtr;

 int RBTPrint();
 int RBTInsert(int *pInsKey);
 int LeftRotate(pRBTree x);
 int RightRotate(pRBTree x);
 pRBTree TreeMinimum(pRBTree x);
 pRBTree TreeMaximum(pRBTree x);
 pRBTree RBTSearch(pRBTree x, int *pTarKey);
main()
{

 int TarKey = 0, InsKey = 0;
 int choice = 1;
 int Status = 0;
 pRBTree z = NULL;
 TreePtr = NULL;

 while(choice!=0)
 {
        printf("\nQuit\t\t\t: 0\n");
        printf("Insert \t\t\t: 1\n");
        printf("Delete\t\t\t: 2\n");
        printf("Search\t\t\t: 3\n");
        printf("Print the RedBlack Tree\t: 4\n");
        printf("Enter Choice:");
        scanf("%d", &choice);
        fflush(stdin);
        switch(choice)
        {
                case 0: {
                        return;
                        break;
                        }

                case 1: {
                        printf("\nInsert key:");
                        scanf("%d", &InsKey);
                        fflush(stdin);
                        Status = RBTInsert(&InsKey);
                        if(Status == 0)
                                printf("\nDuplicate keys found. Insert Failure\n");
                        break;

                        }
                case 2: {

                 //       Status = RBTDelete(&TarKey);
                        if(Status == 0)
                                printf("\nTarget not found. Delete Failure\n");
                        }
                case 3: {
                        printf("\nTarget key:");
                        scanf("%d", &TarKey);
                        fflush(stdin);
                        z = (pRBTree)RBTSearch(TreePtr, &TarKey);
                        if(z)
                        {
                                printf("Target Node:\nKey: %d\tColor: %c\t", z->key, z->color);
                                printf("Left: %d\tRight: %d\n", z->left->key, z->right->key);
                        }
                        else
                                printf("\nTarget key not found.\n");

                        break;
                        }

                case 4: {
                        //Prints the tree  - takes root as the argument.
                        RBTPrint(TreePtr);
                        break;
                        }

        }
 }


 free(TreePtr);
 return;
}

pRBTree RBTSearch(pRBTree x, int *pTarKey)
{
        if ((x == NULL) || (x->key == *pTarKey))
        {
                return x;
        }
        if(*pTarKey < x->key)
        {
                return RBTSearch(x->left, pTarKey);
        }
        else
        {
                return RBTSearch(x->right, pTarKey);
        }
        return NULL;

}

int RBTDelete( int *pTarkey)
{
        pRBTree y = NULL;
        pRBTree x = NULL;
        pRBTree z = (pRBTree)malloc(sizeof(struct RBTree));

return 0;
}

/*
int RBTPrint()
{
        pRBTree x = NULL;
        pRBTree Maximum = NULL;

        x = (pRBTree)malloc(sizeof(struct RBTree));
        x = TreePtr;
        if( x != NULL)
        {
                x = TreeMinimum(x);
                printf("\nMin = %d\n", x->key);
        }
        while(x!=TreePtr)
        {
                if(x == x->parent->left)
                {
  //                      x = TreeMinimum(x);
                        printf("\n%d %c ",x->key, x->color);
                        if ((x->parent != NULL)&&(x->right == NULL))
                           x = x->parent;
                        else if (x->right != NULL)
                             x = x->right;
                }
                else if(x == x->parent->right)
                {
                        x = TreeMinimum(x);
                        printf("\nright%d %c ",x->key, x->color);
                        if ((x->parent != NULL)&&(x->right == NULL))
                           x = x->parent;
                        else if (x->right != NULL)
                             x = x->right;
             //           return 0;
                }
        }
        printf("\n%d %c\n", x->key, x->color);

        Maximum = TreeMaximum(x);
    //    printf("Max: %d %c", Maximum->key, Maximum->color);

        while(x != Maximum)
        {
         //       printf("\nMax While loop");
              if(x == TreePtr)
              {
                 x = x->right;
              }
              if(x == x->parent->left)
                {
//                        x = TreeMinimum(x);
                        printf("\n%d %c ",x->key, x->color);
                        if ((x->parent != NULL)&&(x->right == NULL))
                           x = x->parent;
                        else if (x->right != NULL)
                             x = x->right;
                }
                else if(x == x->parent->right)
                {
                        x = TreeMinimum(x);
                        printf("\n%d %c ",x->key, x->color);
                        if ((x->parent != NULL)&&(x->right == NULL))
                           x = x->parent;
                        else if (x->right != NULL)
                             x = x->right;
             //           return 0;
                }
        }

        return 0;
}
*/

int RBTPrint(pRBTree x)
{

if (x != NULL)
{
        RBTPrint(x->left);
        printf("\n%d %c\tParent: %d %c", x->key, x->color, x->parent->key, x->parent->color);
        RBTPrint(x->right);
}
return 0;
}







pRBTree TreeMinimum(pRBTree x)
{
while(x->left != NULL)
{
        x = x->left;
}
return x;
}

pRBTree TreeMaximum(pRBTree x)
{
while(x->right != NULL)
{
        x = x->right;
}
return x;
}



int RBTInsert(int *pInsKey)
{
        int InsertDone = 0;
        pRBTree y = NULL;
        pRBTree x = TreePtr;
        pRBTree z = (pRBTree)malloc(sizeof(struct RBTree));
        z->key = *pInsKey;
        z->color = 'r';
        z->left = NULL;
        z->right = NULL;
        z->parent = NULL;

        while(x != NULL)
        {
                y = (pRBTree)malloc(sizeof(struct RBTree));
                y = x;
                if( z->key < x->key)
                {
                        x = x->left;
                }
                else
                {
                        x = x->right;
                }
        }
        z->parent = y;
        if (y == NULL)
        {
                TreePtr = (pRBTree)malloc(sizeof(struct RBTree));
                TreePtr = z;
        }
        else
        {
                if (z->key < y->key)
                {
                        y->left = z;
                }
                else
                {
                        y->right = z;
                        printf("\nTreePtr->right %d %c\n", y->right->key, y->right->color);
                }
        }
        z->color = 'r';
        while( (z != TreePtr ) && (z->parent->color == 'r'))
        {
                if( z->parent == z->parent->parent->left)
                {
                        y = z->parent->parent->right;
                        if(( y->color == 'r')&&(y!=NULL))
                        {
                                z->parent->color = 'b';
                                y->color = 'b';
                                z->parent->parent->color = 'r';
                                z = z->parent->parent;
                        }
                        else
                        {
                                if ( z == z->parent->right)
                                {
                                        z = z->parent;
                                        printf("\nRotate left");
                                        LeftRotate(z);
                                }
                                z->parent->color = 'b';
                                z->parent->parent->color = 'r';
                                RightRotate(z->parent->parent);
                        }
                }
                else
                {
                        y = z->parent->parent->left;
                        printf("\nY key:%d color:%c", y->key, y->color);
                        if(( y->color == 'r') && (y!=NULL))
                        {
                                z->parent->color = 'b';
                                y->color = 'b';
                                z->parent->parent->color = 'r';
                                z = z->parent->parent;
                        }
                        else
                        {
                                if ( z == z->parent->left)
                                {
                                        z = z->parent;
                                        RightRotate(z);
                                }
                                z->parent->color = 'b';
                                z->parent->parent->color = 'r';
                                LeftRotate(z->parent->parent);
                                printf("TreePtr Key = %d ", TreePtr->key);
                        }
                }
        }
        TreePtr -> color = 'b';
        InsertDone = 1;

return(InsertDone);
}

int LeftRotate(pRBTree x)
{
pRBTree y;
y = x->right;
x->right = y->left;
if (y->left != NULL)
   y->left->parent = x;
y->parent = x->parent;
if (x->parent == NULL)
{
        TreePtr = y;
}
else
{
        if (x == x->parent->left)
        {
                x->parent->left = y;
        }
        else
        {
                x->parent->right = y;
        }
}
y->left = x;
x->parent = y;
return 0;
}

int RightRotate(pRBTree x)
{
pRBTree y;
y = x->left;
x->left = y->right;
if (y->right != NULL)
   y->right->parent = x;
y->parent = x->parent;
if (x->parent == NULL)
{
        TreePtr = y;
}
else
{
        if (x == x->parent->right)
        {
                x->parent->right = y;
        }
        else
        {
                x->parent->left = y;
        }
}
y->right = x;
x->parent = y;
return 0;
}
