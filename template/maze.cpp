/*
 * =====================================================================================
 *
 *       Filename:  maze.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/26/2010 07:20:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include<stdio.h> 
#include<stdlib.h> 
#define M 16 
#define N 16 
typedef struct mark//�����Թ��ڵ���������� 
{ 
    int x; 
    int y; 
}mark; 

typedef struct Element//"��"ջԪ�أ��ٺ١��� 
{ 
    int x,y; //x��,y�� 
    int d; //d��һ���ķ��� 
}Element; 

typedef struct LStack //��ջ 
{ 
    Element elem; 
    struct LStack *next; 
}LStack, *PLStack;

/*************ջ����****************/ 
int InitStack(PLStack &S)//�����ջ 
{ 
    S=NULL; 
    return 1; 
} 

int StackEmpty(PLStack S)//�ж�ջ�Ƿ�Ϊ�� 
{ 
    if(S==NULL) 
        return 1; 
    else 
        return 0; 
} 

int Push(PLStack &S, Element e)//ѹ��������Ԫ�� 
{ 
    PLStack p; 
    p=(PLStack)malloc(sizeof(LStack)); 
    p->elem=e; 
    p->next=S; 
    S=p; 
    return 1; 
} 

int Pop(PLStack &S,Element &e) //ջ��Ԫ�س�ջ 
{ 
    PLStack p; 
    if(!StackEmpty(S)) 
    { 
        e=S->elem; 
        p=S; 
        S=S->next; 
        free(p); 
        return 1; 
    } 
    else 
        return 0; 
} 

/***************���Թ�·������***********************/ 
void MazePath(struct mark start,struct mark end,int maze[M][N],int diradd[4][2]) 
{ 
    int i,j,d;int a,b; 
    Element elem,e; 
    PLStack S1, S2; 
    InitStack(S1); 
    InitStack(S2); 
    maze[start.x][start.y]=2; //��ڵ����ϱ�� 
    elem.x=start.x; 
    elem.y=start.y; 
    elem.d=-1; //��ʼΪ-1 
    Push(S1,elem); 
    while(!StackEmpty(S1)) //ջ��Ϊ�� ��·������ 
    { 
        Pop(S1,elem); 
        i=elem.x; 
        j=elem.y; 
        d=elem.d+1; //��һ������ 
        while(d<4) //��̽���������������� 
        { 
            a=i+diradd[d][0]; 
            b=j+diradd[d][1]; 
            if(a==end.x && b==end.y && maze[a][b]==0) //������˳��� 
            { 
                elem.x=i; 
                elem.y=j; 
                elem.d=d; 
                Push(S1,elem); 
                elem.x=a; 
                elem.y=b; 
                elem.d=886; //�������Ϊ-1 �ж��Ƿ��˳��� 
                Push(S1,elem); 
                printf("\n0=E 1=S 2=W 3=N 886 means out of maze\n\npath is:(x,y,d)\n"); 
                while(S1) //�������� ������Թ�·������ 
                { 
                    Pop(S1,e); 
                    Push(S2,e); 
                } 
                while(S2) 
                { 
                    Pop(S2,e); 
                    printf("-->(%d,%d,%d)",e.x,e.y,e.d); 
                } 
                return; //��������ѭ����������break,�����ֳ���exit�ֻ��������ѡ��return���ǲ����o(��_��)o... 
            } 
            if(maze[a][b]==0) //�ҵ�����ǰ���ķǳ��ڵĵ� 
            { 
                maze[a][b]=2; //����߹��˵� 
                elem.x=i; 
                elem.y=j; 
                elem.d=d; 
                Push(S1,elem); //��ǰλ����ջ 
                i=a; //��һ��ת��Ϊ��ǰ�� 
                j=b; 
                d=-1; 
            } 
            d++; 
        } 
    } 
    printf("no path for this maze\n"); 
} 


/*************�����Թ�*******************/ 
void initmaze(int maze[M][N]) 
{ 
    int i,j; 
    int m,n; //�Թ���,�� 

    printf("column m="); 
    scanf("%d",&m); 
    printf("cow n="); 
    scanf("%d",&n); 
    printf("\ninput your maze:\nseperate by space,0 path,1 wall\n",m,n); 
    for(i=1;i<=m;i++) 
        for(j=1;j<=n;j++) 
            scanf("%d",&maze[i][j]); 
    printf("creating your maze...o(��_��)o...\n"); 
    for(i=0;i<=m+1;i++) //��һȦΧǽ 
    { 
        maze[i][0]=1; 
        maze[i][n+1]=1; 
    } 
    for(j=0;j<=n+1;j++) 
    { 
        maze[0][j]=1; 
        maze[m+1][j]=1; 
    } 
    for(i=0;i<=m+1;i++) //����Թ� 
    { 
        for(j=0;j<=n+1;j++) 
            printf("%d ",maze[i][j]); 
        printf("\n"); 
    } 
} 

int maze[][16] =
{
            /*0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15  */
    /*  0 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  1 */{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  2 */{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  3 */{1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    /*  4 */{1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    /*  5 */{1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    /*  6 */{1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1},
    /*  7 */{1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    /*  8 */{1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    /*  9 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
    /* 10 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 11 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 12 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 13 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 14 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    /* 15 */{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} 
};

int main() 
{ 
    int sto[M][N]; 
    int i,j;
    struct mark start,end; //start,end��ںͳ��ڵ����� 
    int add[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//�������������� ��������Ϊ�����ϱ� 

//    initmaze(sto);//�����Թ� 

    for(i=0;i<16;i++) //����Թ� 
    { 
        for(j=0;j<16;j++) 
            printf("%d ",maze[i][j]); 
        printf("\n"); 
    } 
    printf("start point, sperate by comma\n"); 
    scanf("%d,%d",&start.x,&start.y); 
    printf("ent point, sperate by comma\n"); 
    scanf("%d,%d",&end.x,&end.y); 

//    MazePath(start,end,sto,add); //find path 
    MazePath(start,end,maze,add); //find path 
    printf("\n");
} 
