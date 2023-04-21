# include <malloc.h>
# include <stdio.h>

#define LH 1        //ƽ������1
#define EH 0        //ƽ������0
#define RH -1       //ƽ������-1
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
    (*T) -> rchild = Rchild -> lchild;      //����������������Ϊ*T��������
    Rchild -> lchild = *T;                  //��������lchildָ��*T
    *T = Rchild;                            //���T���ɵ�ǰ��������
}

void RightRotate(AVLTree* T){
    AVLTree Lchild = (*T) -> lchild;
    (*T) -> lchild = Lchild -> rchild;      //������������������Ϊ��ǰ�ڵ��������
    Lchild -> rchild = *T;                  //��������������ָ��ǰ�ڵ�
    *T = Lchild;                            //���T��Ϊ������
}

void LeftBalance(AVLTree* T){
    AVLTree L = (*T) -> lchild;     //������
    AVLTree Lr;                     //��������������
    switch(L -> bf){    //�����������
        //LL��ת
        case LH:        //�����������
            RightRotate(T);
            (*T) -> bf = L -> bf = EH;  //��ת��ϣ�����������ƽ��״̬
            break;
        case RH:
            //LR��ת
            Lr = L -> rchild;
            switch(Lr -> bf){
                case LH:            //�ܹ���4�����������Ĳ�����
                    (*T) -> bf = RH;
                    L -> bf = EH;
                    break;
                case EH:            //������������Ҳ����һ���ߵ����
                    (*T) -> bf = L -> bf = EH;
                    break;
                case RH:            //�ܹ���4�����������Ĳ�����
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
    if( !(*T) ){            //��AVLTreeΪ�����������һ������Ԫ��Ϊe���½ڵ���ΪBBST�ĸ��ڵ�
        *T = (AVLTree)malloc(sizeof(AVLNode));
        (*T) -> key = e;      //�½��ڵ�����
        (*T) -> lchild = T1 -> rchild = NULL;
        (*T) -> bf = EH;      //�½��ڵ��ƽ���һ��Ϊ0
        *taller = TRUE;     //������ȼ�һ
    }else{
        if(e == (*T) -> key){   //�������ڷ�����ͬ�ڵ�
            *taller = FALSE;    //��������Ȳ��䣬
            return FALSE;       //�������
        }else if(e > (*T) -> key){      //�����������ݴ��ڵ�ǰ�ڵ�����ݣ�������������ֱ���������
           if(!InsertAVL(&(*T) -> rchild,e,taller)){
               return FALSE;
           }
           if(*taller){         //��������ȼ�һ�����ȡ��Ӧ��ʩ
               switch((*T) -> bf){       //��������ƽ���(�ܵĸ��ڵ�)
                   case LH:             //�������
                       (*T) -> bf = EH;
                       *taller = FALSE;
                       break;
                   case EH:             //�������
                       (*T) -> bf = RH;
                       *taller = TRUE;
                       break;
                   case RH:             //�Ҵ�����
                       RightBalance(&(*T));
                       *taller = FALSE;
                       break;
               }
           }
        }else{
            if(!InsertAVL(&(*T) -> lchild,e,taller)){   //ͬ��
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