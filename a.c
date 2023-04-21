# include <malloc.h>
# include <stdio.h>

#define LH 1        //平衡因子1
#define EH 0        //平衡因子0
#define RH -1       //平衡因子-1
#define TRUE 1
#define FALSE 0
#define OK 1

typedef int AVLElemType;
typedef struct _AVLNode{
    AVLElemType key;
    int bf;
    struct _AVLNode *lchild,*rchild;
}AVLNode,*AVLTree;

void LeftRotate(AVLTree* T){
    AVLTree Rchild = (*T) -> rchild;
    (*T) -> rchild = Rchild -> lchild;      //右子树的左子树作为*T的右子树
    Rchild -> lchild = *T;                  //右子树的lchild指向*T
    *T = Rchild;                            //最后将T换成当前的右子树
}

void RightRotate(AVLTree* T){
    AVLTree Lchild = (*T) -> lchild;
    (*T) -> lchild = Lchild -> rchild;      //左子树的右子树将作为当前节点的左子树
    Lchild -> rchild = *T;                  //左子树的右子树指向当前节点
    *T = Lchild;                            //最后将T换为右子树
}

void LeftBalance(AVLTree* T){
    AVLTree L = (*T) -> lchild;     //左子树
    AVLTree Lr;                     //左子树的右子树
    switch(L -> bf){    //左子树情况：
        //LL旋转
        case LH:        //最左侧深度最大
            RightRotate(T);
            (*T) -> bf = L -> bf = EH;  //右转完毕，整个树处于平衡状态
            break;
        case RH:
            //LR旋转
            Lr = L -> rchild;
            switch(Lr -> bf){
                case LH:            //总共有4层的情况：第四层在左
                    (*T) -> bf = RH;
                    L -> bf = EH;
                    break;
                case EH:            //三个点的情况，也就是一条线的情况
                    (*T) -> bf = L -> bf = EH;
                    break;
                case RH:            //总共有4层的情况：第四层在右
                    (*T) -> bf = EH;
                    L -> bf = LH;
                    break;
            }
            Lr -> bf = EH;
            LeftRotate(&L);
            RightRotate(&T);
            break;
    }
}

void RightBalance(AVLTree* T){
    AVLTree R = (*T) -> rchild;
    AVLTree Rr = R -> lchild;
    switch(R -> bf){
        case RH:
            LeftRotate(&(*T));
            (*T) -> bf = R -> bf = EH;
            break;
        case LH:
            switch(Rr -> bf){
                case LH:
                    (*T) -> bf = EH;
                    R -> bf = RH;
                    break;
                case EH:
                    (*T) -> bf = R -> bf = EH;
                    break;
                case RH:
                    (*T) -> bf = LH;
                    R -> bf = EH;
                    break;
            }
            Rr -> bf = EH;
            RightRotate(&R);
            LeftRotate(&(*T));
    }
}

int InsertAVL(AVLTree* T,int e,int* taller){
    if( !(*T) ){            //若AVLTree为空树，则插入一个数据元素为e的新节点作为BBST的根节点
        *T = (AVLTree)malloc(sizeof(AVLNode));
        (*T) -> key = e;      //新建节点数据
        (*T) -> lchild = T1 -> rchild = NULL;
        (*T) -> bf = EH;      //新建节点的平衡度一定为0
        *taller = TRUE;     //树的深度加一
    }else{
        if(e == (*T) -> key){   //若在树内发现相同节点
            *taller = FALSE;    //则树的深度不变，
            return FALSE;       //程序结束
        }else if(e > (*T) -> key){      //若被插入数据大于当前节点的数据，则检测右子树，直到程序结束
           if(!InsertAVL(&(*T) -> rchild,e,taller)){
               return FALSE;
           }
           if(*taller){         //若树的深度加一，则采取相应措施
               switch((*T) -> bf){       //整个树的平衡度(总的根节点)
                   case LH:             //左大于右
                       (*T) -> bf = EH;
                       *taller = FALSE;
                       break;
                   case EH:             //左右相等
                       (*T) -> bf = RH;
                       *taller = TRUE;
                       break;
                   case RH:             //右大于左
                       RightBalance(&(*T));
                       *taller = FALSE;
                       break;
               }
           }
        }else{
            if(!InsertAVL(&(*T) -> lchild,e,taller)){   //同上
                return FALSE;
            }
            switch ((*T) -> bf) {
                case LH:
                    LeftBalance(&(*T));
                    *taller = FALSE;
                    break;
                case EH:
                    *taller = TRUE;
                    (*T) -> bf = LH;
                    break;
                case RH:
                    *taller = FALSE;
                    (*T) -> bf = EH;
                    break;
            }
        }
    }
    return OK;
}