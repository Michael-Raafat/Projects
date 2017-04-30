#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// different array sizes
#define size 10
#define size2 5
#define sizepieces 6
#define sizeboard 8
//constant arrays and variables at any time
char column[sizeboard]= {'A','B','C','D','E','F','G','H'};
char row[sizeboard]= {'1','2','3','4','5','6','7','8'};
char blackpieces[sizepieces]= {'P','R','Q','K','B','N'};
char whitepieces[sizepieces]= {'p','r','q','k','b','n'};
char promotionBlack[4]= {'R','Q','B','N'};
char promotionWhite[4]= {'r','q','b','n'};
char unallowedname[9]= {'"','*','\\',':','<','>','?','/','|'};
int kingplace[2][2]= {5,1,5,8};
char boardhistory[10000000][size][size]= {0};
int r=0,boardhistorycount=0,apw=0,apb=0;
int aw[300][2]= {0},ab[300][2]= {0};
char deadbpieces[16]= {0},deadwpieces[16]= {0};
int db=0,dw=0,ddw[10000000]= {0},ddb[10000000]= {0};
int undo=0,save=0,turn=0,gameover=0,decideturn=0,redo=0,exitvalue=0,gametype=0;
int BLR=0,BRR=0,WLR=0,WRR=0,KW=0,KB=0;
int BLRH[10000000]= {0},BRRH[10000000]= {0},WLRH[10000000]= {0},WRRH[10000000]= {0},KWH[10000000]= {0},KBH[10000000]= {0};
//main board controls
void initializeboard(char board[][size])
{
    int i,j,s=1,c=64,n=57;
    for(i=1; i<9; i++)
    {
        for(j=1; j<9; j++)
        {
            if((i+j)%2==0)
            {
                board[i][j]='-';
            }
            else
            {
                board[i][j]='.';
            }
        }
        if(s==0)
            s=1;
        else
            s=0;
    }
    for (i=1; i<9; i++)
    {
        board[i][0]=n-i;
        board[i][9]=n-i;
        board[0][i]=c+i;
        board[9][i]=c+i;
    }
}
void printboard(char board[][size])
{
    int i,j;
    for (i=0; i<size; i++)
    {
        for (j=0; j<size; j++)
        {
            printf("%c  ",board[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");
}
void printall(char board[][size])
{
    int i,j;
    if(db>0)
    {
        printf("Black dead pieces:\n");
        for (i=0; i<db; i++)
        {
            printf("%c ",deadbpieces[i]);
        }
        printf("\n");
    }
    for (i=0; i<size; i++)
    {
        for (j=0; j<size; j++)
        {
            printf("%c  ",board[i][j]);
        }
        printf("\n\n");
    }
    if(dw>0)
    {
        printf("White dead pieces:\n");
        for (i=0; i<dw; i++)
        {
            printf("%c ",deadwpieces[i]);
        }
        printf("\n");
    }
}
void boardstart(char board[][size])
{
    board[1][1]='R';
    board[1][8]='R';
    board[8][1]='r';
    board[8][8]='r';
    board[1][2]='N';
    board[1][7]='N';
    board[8][2]='n';
    board[8][7]='n';
    board[1][3]='B';
    board[1][6]='B';
    board[8][3]='b';
    board[8][6]='b';
    board[1][4]='Q';
    board[1][5]='K';
    board[8][4]='q';
    board[8][5]='k';
    int i;
    for (i=1; i<size-1; i++)
    {
        board[2][i]='P';
        board[7][i]='p';
    }
}
void boardequal(char b[][size],char copy[][size])
{
    int i,j;
    for (i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            copy[i][j]=b[i][j];
        }
    }
}
void boardhistorywrite(char board[][size])
{
    int i,j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            boardhistory[turn][i][j]=board[i][j];
        }
    }
}
void boardhistoryload(char board[][size])
{
    int i,j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            board[i][j]=boardhistory[turn][i][j];
        }
    }
}
void blockboardreset(int i[],char board[][size])
{
    if ((i[0]+i[1])%2==0)
    {
        board[i[1]][i[0]]='-';
    }
    else
        board[i[1]][i[0]]='.';
}
//check functions list
int checkcurrentblack(int cur[],char board[][size])
{
    int i,s=0;
    for(i=0; i<sizepieces; i++)
    {
        if(board[cur[1]][cur[0]]==blackpieces[i])
        {
            s=1;
        }
    }
    return s;
}
int checkcurrentwhite(int cur[],char board[][size])
{
    int i,s=0;
    for(i=0; i<sizepieces; i++)
    {
        if(board[cur[1]][cur[0]]==whitepieces[i])
        {
            s=1;
        }
    }
    return s;
}
int checkcurrentempty(int cur[],char board[][size])
{
    int s=0,i;
    if (board[cur[1]][cur[0]]=='-'||board[cur[1]][cur[0]]=='.')
    {
        s=1;
    }
    return s;
}
int checkblack2(int r,int c,char board[][size])
{
    int i,s=0;
    for(i=0; i<sizepieces; i++)
    {
        if(board[r][c]==blackpieces[i])
        {
            s=1;
        }
    }
    return s;
}
int checkwhite2(int r,int c,char board[][size])
{
    int i,s=0;
    for(i=0; i<sizepieces; i++)
    {
        if(board[r][c]==whitepieces[i])
        {
            s=1;
        }
    }
    return s;
}
int checkempty2(int r,int c,char board[][size])
{
    int s=0,i;
    if (board[r][c]=='-'||board[r][c]=='.')
    {
        s=1;
    }
    return s;
}
int promotewhite(int cur[],char board[][size])
{
    int s=0;
    if (board[cur[1]][cur[0]]=='p' && cur[1]==2)
    {
        s=1;
    }
    return s;
}
int promoteblack(int cur[],char board[][size])
{
    int s=0;
    if (board[cur[1]][cur[0]]=='P' && cur[1]==7)
    {
        s=1;
    }
    return s;
}
int checkcolumn(int c)
{
    int s=0,i;
    for (i=1; i<9; i++)
    {
        if(c==i)
        {
            s=1;
        }
    }
    return s;
}
int checkrow(int c)
{
    int s=0,i;
    for (i=1; i<9; i++)
    {
        if(c==i)
        {
            s=1;
        }
    }
    return s;
}
int whiteverify(char p)
{
    int i,s=0;
    for (i=0; i<4; i++)
    {
        if(p==promotionWhite[i])
            s=1;
    }
    return s;
}
int blackverify(char p)
{
    int i,s=0;
    for (i=0; i<4; i++)
    {
        if(p==promotionBlack[i])
            s=1;
    }
    return s;
}
void findkings(char board[][size])
{
    int i,j;
    for (i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            if(board[i][j]=='K')
            {
                kingplace[0][0]=j;
                kingplace[0][1]=i;
            }
            else if(board[i][j]=='k')
            {
                kingplace[1][0]=j;
                kingplace[1][1]=i;
            }
        }
    }
}
//Input transforming to a suitable type
void transformCoord(char in[],int inn[])
{
    switch (in[0])
    {
    case 'A':
    {
        inn[0]=1;
        break;
    }
    case 'B':
    {
        inn[0]=2;
        break;
    }
    case 'C':
    {
        inn[0]=3;
        break;
    }
    case 'D':
    {
        inn[0]=4;
        break;
    }
    case 'E':
    {
        inn[0]=5;
        break;
    }
    case 'F':
    {
        inn[0]=6;
        break;
    }
    case 'G':
    {
        inn[0]=7;
        break;
    }
    case 'H':
    {
        inn[0]=8;
        break;
    }
    default:
    {
        inn[0]=9;
        break;
    }
    }
    switch (in[1])
    {
    case '1':
    {
        inn[1]=8;
        break;
    }
    case '2':
    {
        inn[1]=7;
        break;
    }
    case '3':
    {
        inn[1]=6;
        break;
    }
    case '4':
    {
        inn[1]=5;
        break;
    }
    case '5':
    {
        inn[1]=4;
        break;
    }
    case '6':
    {
        inn[1]=3;
        break;
    }
    case '7':
    {
        inn[1]=2;
        break;
    }
    case '8':
    {
        inn[1]=1;
        break;
    }
    default:
    {
        inn[1]=9;
        break;
    }
    }
}
//Moves probabilities  and board place determining white/black
void whitequeen (int b [][2],int a[],char board[][size])
{
    int i,j,s,k=0,l=1,m=1,n=1,q=1,f=1,d=1,e=1,g=1,h=1,o=1,p=1,t=1,u=1,v=1,w=1,x=1,y=1,z=1,ab=1,ac=1,ad=1,ae=1;//variables from l to jump between if conditions
    i=a[1];
    j=a[0];
    for (s=0; s<28; s++)
    {
        if (checkempty2(i+l,j+f,board) && (i+l)<9 && (j+f)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            l++,f++,d++ ;
        }
        else if (checkblack2(i+l,j+f,board) && d==f && (j+f)<9 && (i+l)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            d++ ;
        }
        else if (checkempty2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            m++,n++,e++;
        }
        else if (checkblack2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 && e==m )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            e++ ;
        }
        else if (checkempty2(i+g,j,board) && (i+g)<9)
        {
            b[r][k]= j;
            b[r][k+1]= i+g ;
            r++,k=0 ;
            g++,h++ ;
        }
        else if (checkblack2(i+h,j,board) && h==g && (i+h)<9 )
        {
            b[r][k]= j;
            b[r][k+1]= i+h ;
            r++,k=0 ;
            h++ ;
        }
        else if (checkempty2(i-o,j,board) && (i-o)>0 )
        {
            b[r][k]= j;
            b[r][k+1]= i-o ;
            r++,k=0 ;
            o++,p++;
        }
        else if (checkblack2(i-p,j,board)&& p==o && (i-p)>0)
        {
            b[r][k]= j;
            b[r][k+1]= i-p ;
            r++,k=0 ;
            p++ ;
        }
        else if (checkempty2(i,j-t,board) && (j-t)>0 )
        {
            b[r][k]= j-t;
            b[r][k+1]= i;
            r++,k=0 ;
            t++,u++ ;
        }
        else if (checkblack2(i,j-u,board)&& u==t && (j-u)>0)
        {
            b[r][k]= j-u ;
            b[r][k+1]= i ;
            r++,k=0 ;
            u++ ;
        }
        else if (checkempty2(i,j+v,board) && (j+v)<9 )
        {
            b[r][k]= j+v;
            b[r][k+1]= i;
            r++,k=0 ;
            v++,w++;
        }
        else if (checkblack2(i,j+w,board)&& w==v && (j+w)<9 )
        {
            b[r][k]= j+w ;
            b[r][k+1]= i ;
            r++,k=0 ;
            w++ ;
        }
        else if (checkempty2(i-ab,j+x,board) && (i-ab)>0 && (j+x)<9 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            ab++,x++,y++ ;
        }
        else if (checkblack2(i-ab ,j+x,board) && y==ab && (j+x)<9 && (i-ab)>0 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            y++ ;
        }
        else if (checkempty2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ac++,ad++,ae++;
        }
        else if (checkblack2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 && ae==ad )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ae++ ;
        }
        else
            s=28;
    }
}
void blackqueen (int b [][2],int a[],char board[][size])
{
    int i,j,l=1,s,k=0,m=1,n=1,q=1,f=1,d=1,e=1,g=1,h=1,o=1,p=1,t=1,u=1,v=1,w=1,x=1,y=1,z=1,ab=1,ac=1,ad=1,ae=1;
    i=a[1];
    j=a[0];
    for (s=0; s<28; s++)
    {
        if (checkempty2(i+l,j+f,board) && (i+l)<9 && (j+f)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            l++,f++,d++ ;
        }
        else if (checkwhite2(i+l,j+f,board) && d==f && (j+f)<9 && (i+l)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            d++ ;
        }
        else if (checkempty2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            m++,n++,e++;
        }
        else if (checkwhite2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 && e==m )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            e++ ;
        }
        else if (checkempty2(i+g,j,board) && (i+g)<9)
        {
            b[r][k]= j;
            b[r][k+1]= i+g ;
            r++,k=0 ;
            g++,h++ ;
        }
        else if (checkwhite2(i+h,j,board) && h==g && (i+h)<9 )
        {
            b[r][k]= j;
            b[r][k+1]= i+h ;
            r++,k=0 ;
            h++ ;
        }
        else if (checkempty2(i-o,j,board) && (i-o)>0 )
        {
            b[r][k]= j;
            b[r][k+1]= i-o ;
            r++,k=0 ;
            o++,p++;
        }
        else if (checkwhite2(i-p,j,board)&& p==o && (i-p)>0)
        {
            b[r][k]= j;
            b[r][k+1]= i-p ;
            r++,k=0 ;
            p++ ;
        }
        else if (checkempty2(i,j-t,board) && (j-t)>0 )
        {
            b[r][k]= j-t;
            b[r][k+1]= i;
            r++,k=0 ;
            t++,u++ ;
        }
        else if (checkwhite2(i,j-u,board)&& u==t && (j-u)>0)
        {
            b[r][k]= j-u ;
            b[r][k+1]= i ;
            r++,k=0 ;
            u++ ;
        }
        else if (checkempty2(i,j+v,board) && (j+v)<9 )
        {
            b[r][k]= j+v;
            b[r][k+1]= i;
            r++,k=0 ;
            v++,w++;
        }
        else if (checkwhite2(i,j+w,board)&& w==v && (j+w)<9 )
        {
            b[r][k]= j+w ;
            b[r][k+1]= i ;
            r++,k=0 ;
            w++ ;
        }
        else if (checkempty2(i-ab,j+x,board) && (i-ab)>0 && (j+x)<9 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            ab++,x++,y++ ;
        }
        else if (checkwhite2(i-ab ,j+x,board) && y==ab && (j+x)<9 && (i-ab)>0 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            y++ ;
        }
        else if (checkempty2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ac++,ad++,ae++;
        }
        else if (checkwhite2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 && ae==ad )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ae++ ;
        }
        else
            s=28;
    }
}
void blackrook (int b [][2],int a[],char board[][size])
{
    int i,j,l=1,s,k=0,m=1,n=1,q=1,f=1,d=1,e=1,g=1;
    i=a[1];
    j=a[0];
    for (s=0; s<14; s++)
    {
        if (checkempty2(i+l,j,board) && (i+l)<9)
        {
            b[r][k]= j;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            l++,f++ ;
        }
        else if (checkwhite2(i+l,j,board) && f==l && (i+f)<9 )
        {
            b[r][k]= j;
            b[r][k+1]= i+f ;
            r++,k=0 ;
            f++ ;
        }
        else if (checkempty2(i-m,j,board) && (i-m)>0 )
        {
            b[r][k]= j;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            m++,e++;
        }
        else if (checkwhite2(i-e,j,board)&& e==m && (i-e)>0)
        {
            b[r][k]= j;
            b[r][k+1]= i-e ;
            r++,k=0 ;
            e++ ;
        }
        else if (checkempty2(i,j-n,board) && (j-n)>0 )
        {
            b[r][k]= j-n;
            b[r][k+1]= i;
            r++,k=0 ;
            n++,d++ ;
        }
        else if (checkwhite2(i,j-d,board)&& d==n && (j-d)>0)
        {
            b[r][k]= j-d ;
            b[r][k+1]= i ;
            r++,k=0 ;
            d++ ;
        }
        else if (checkempty2(i,j+q,board) && (j+q)<9 )
        {
            b[r][k]= j+q;
            b[r][k+1]= i;
            r++,k=0 ;
            q++,g++;
        }
        else if (checkwhite2(i,j+g,board)&& g==q && (j+g)<9 )
        {
            b[r][k]= j+g ;
            b[r][k+1]= i ;
            r++,k=0 ;
            g++ ;
        }
        else
            s=14;
    }
}
void whiterook (int b[][2] ,int a[],char board[][size])
{
    int i,j,l=1,s,k=0,m=1,n=1,q=1,f=1,d=1,e=1,g=1;
    i=a[1];
    j=a[0];
    for (s=0; s<14; s++)
    {
        if (checkempty2(i+l,j,board) && (i+l)<9)
        {
            b[r][k]= j;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            l++,f++ ;
        }
        else if (checkblack2(i+l,j,board) && f==l && (i+f)<9 )
        {
            b[r][k]= j;
            b[r][k+1]= i+f ;
            r++,k=0 ;
            f++ ;
        }
        else if (checkempty2(i-m,j,board) && (i-m)>0 )
        {
            b[r][k]= j;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            m++,e++;
        }
        else if (checkblack2(i-e,j,board)&& e==m && (i-e)>0)
        {
            b[r][k]= j;
            b[r][k+1]= i-e ;
            r++,k=0 ;
            e++ ;
        }
        else if (checkempty2(i,j-n,board) && (j-n)>0 )
        {
            b[r][k]= j-n;
            b[r][k+1]= i;
            r++,k=0 ;
            n++,d++ ;
        }
        else if (checkblack2(i,j-d,board)&& d==n && (j-d)>0)
        {
            b[r][k]= j-d ;
            b[r][k+1]= i ;
            r++,k=0 ;
            d++ ;
        }
        else if (checkempty2(i,j+q,board) && (j+q)<9 )
        {
            b[r][k]= j+q;
            b[r][k+1]= i;
            r++,k=0 ;
            q++,g++;
        }
        else if (checkblack2(i,j+g,board)&& g==q && (j+g)<9 )
        {
            b[r][k]= j+g ;
            b[r][k+1]= i ;
            r++,k=0 ;
            g++ ;
        }
        else
            s=14;
    }
}
void blackpawn(int b[][2],int a[] ,char board[][size])
{
    int i,j,k=0;
    i=a[1];
    j=a[0];
    if (checkempty2(i+1,j,board)&& (i+1)<9 )
        {
            b[r][k]= j;
            b[r][k+1]= i+1 ;
            r++,k=0 ;
            if ( i==2  && checkempty2(i+2,j,board))
            {
                b[r][k]= j;
                b[r][k+1]= i+2 ;
                r++,k=0 ;
            }
        }
    if (checkwhite2(i+1,j+1,board)&& (j+1)<9 && (i+1)<9)
        {
            b[r][k]= j+1;
            b[r][k+1]= i+1 ;
            r++,k=0 ;
        }
    if (checkwhite2(i+1,j-1,board) && (j-1)>0 && (i+1)<9 )
        {
            b[r][k]= j-1;
            b[r][k+1]= i+1 ;
            r++,k=0 ;
        }
}
void whitepawn(int b[][2],int a[] ,char board[][size])
{
    int i,q=0,j,k=0;
    i=a[1];
    j=a[0];
    if (checkempty2(i-1,j,board)&& (i-1)>0 )
        {
            b[r][k]= j;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
            if ( i==7  && checkempty2(i-2,j,board))
            {
                b[r][k]= j;
                b[r][k+1]= i-2 ;
                r++,k=0 ;
            }
        }
    if (checkblack2(i-1,j+1,board)&& (j+1)<9 && (i-1)>0)
        {
            b[r][k]= j+1;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
    if (checkblack2(i-1,j-1,board) && (j-1)>0 && (i-1)>0 )
        {
            b[r][k]= j-1;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
}
void blackking (int b[][2],int a[],char board[][size])
{
    int i,c=0,j,l=1,k=0;
    i=a[1];
    j=a[0];
    if ((checkempty2(i+1,j,board)|| checkwhite2(i+1,j,board))&& (i+1)<9)
        {
            b[r][k]= j;
            b[r][k+1]= i+l ;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j,board)|| checkwhite2(i-1,j,board))&& (i-1)>0)
        {
            b[r][k]= j;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i,j-1,board)|| checkwhite2(i,j-1,board))&& (j-1)>0)
        {
            b[r][k]= j-1;
            b[r][k+1]= i;
            r++,k=0 ;
        }
    if ((checkempty2(i,j+1,board)|| checkwhite2(i,j+1,board))&& (j+1)<9)
        {
            b[r][k]= j+1;
            b[r][k+1]= i;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j+1,board)|| checkwhite2(i+1,j+1,board))&& (i+1)<9 && (j+1)<9)
        {
            b[r][k]= j+1 ;
            b[r][k+1]= i+1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j-1,board)|| checkwhite2(i+1,j-1,board))&& (i+1)<9 && (j-1)>0)
        {
            b[r][k]= j-1 ;
            b[r][k+1]= i+1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j+1,board)|| checkwhite2(i-1,j+1,board))&& (i-1)>0 && (j+1)<9)
        {
            b[r][k]= j+1 ;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j-1,board)|| checkwhite2(i-1,j-1,board))&& (i-1)>0 && (j-1)>0)
        {
            b[r][k]= j-1 ;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
}
void whiteking (int b[][2],int a[],char board[][size])
{
    int i,c=0,j,l=1,s=1,k=0;
    i=a[1];
    j=a[0];
    if ((checkempty2(i+1,j,board)|| checkblack2(i+1,j,board))&& (i+1)<9)
        {
            b[r][k]= j;
            b[r][k+1]= i+l ;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j,board)|| checkblack2(i-1,j,board))&& (i-1)>0)
        {
            b[r][k]= j;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i,j-1,board)|| checkblack2(i,j-1,board))&& (i-1)>0)
        {
            b[r][k]= j-1;
            b[r][k+1]= i;
            r++,k=0 ;
        }
    if ((checkempty2(i,j+1,board)|| checkblack2(i,j+1,board))&& (j+1)<9 )
        {
            b[r][k]= j+1;
            b[r][k+1]= i;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j+1,board)|| checkblack2(i+1,j+1,board))&& (i+1)<9 && (j+1)<9)
        {
            b[r][k]= j+1 ;
            b[r][k+1]= i+1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j-1,board)|| checkblack2(i+1,j-1,board))&& (i+1)<9 && (j-1)>0)
        {
            b[r][k]= j-1 ;
            b[r][k+1]= i+1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j+1,board)|| checkblack2(i-1,j+1,board))&& (i-1)>0 && (j+1)<9)
        {
            b[r][k]= j+1 ;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j-1,board)|| checkblack2(i-1,j-1,board))&& (i-1)>0 && (j-1)>0)
        {
            b[r][k]= j-1 ;
            b[r][k+1]= i-1 ;
            r++,k=0 ;
        }
}
void blackknight(int b[][2],int a[],char board[][size])
{
    int i,j,k=0;
    i=a[1];
    j=a[0];
    if ((checkempty2(i+2,j+1,board)|| checkwhite2(i+2,j+1,board))&& (i+2)<9 && (j+1)<9)
        {
            b[r][k]= j+1;
            b[r][k+1]= i+2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i+2,j-1,board)|| checkwhite2(i+2,j-1,board))&& (i+2)<9 && (j-1)>0)
        {
            b[r][k]= j-1;
            b[r][k+1]= i+2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-2,j+1,board)|| checkwhite2(i-2,j+1,board))&& (i-2)>0 && (j+1)<9)
        {
            b[r][k]= j+1;
            b[r][k+1]= i-2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-2,j-1,board)|| checkwhite2(i-2,j-1,board))&& (i-2)>0 && (j-1)>0)
        {
            b[r][k]= j-1;
            b[r][k+1]= i-2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j+2,board)|| checkwhite2(i+1,j+2,board))&& (i+1)<9 && (j+2)<9)
        {
            b[r][k]= j+2;
            b[r][k+1]= i+1;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j-2,board)|| checkwhite2(i+1,j-2,board))&& (i+1)<9 && (j-2)>0)
        {
            b[r][k]= j-2;
            b[r][k+1]= i+1;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j+2,board)|| checkwhite2(i-1,j+2,board))&& (i-1)>0 && (j+2)<9)
        {
            b[r][k]= j+2;
            b[r][k+1]= i-1;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j-2,board)|| checkwhite2(i-1,j-2,board))&& (i-1)>0 && (j-2)>0)
        {
            b[r][k]= j-2;
            b[r][k+1]= i-1;
            r++,k=0 ;
        }
}
void whiteknight(int b[][2], int a[],char board[][size])
{
    int i,j,k=0;
    i=a[1];
    j=a[0];
    if ((checkempty2(i+2,j+1,board)|| checkblack2(i+2,j+1,board))&& (i+2)<9 && (j+1)<9)
        {
            b[r][k]= j+1;
            b[r][k+1]= i+2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i+2,j-1,board)|| checkblack2(i+2,j-1,board))&& (i+2)<9 && (j-1)>0)
        {
            b[r][k]= j-1;
            b[r][k+1]= i+2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-2,j+1,board)|| checkblack2(i-2,j+1,board))&& (i-2)>0 && (j+1)<9)
        {
            b[r][k]= j+1;
            b[r][k+1]= i-2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i-2,j-1,board)|| checkblack2(i-2,j-1,board))&& (i-2)>0 && (j-1)>0)
        {
            b[r][k]= j-1;
            b[r][k+1]= i-2 ;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j+2,board)|| checkblack2(i+1,j+2,board))&& (i+1)<9 && (j+2)<9)
        {
            b[r][k]= j+2;
            b[r][k+1]= i+1;
            r++,k=0 ;
        }
    if ((checkempty2(i+1,j-2,board)|| checkblack2(i+1,j-2,board))&& (i+1)<9 && (j-2)>0)
        {
            b[r][k]= j-2;
            b[r][k+1]= i+1;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j+2,board)|| checkblack2(i-1,j+2,board))&& (i-1)>0 && (j+2)<9)
        {
            b[r][k]= j+2;
            b[r][k+1]= i-1;
            r++,k=0 ;
        }
    if ((checkempty2(i-1,j-2,board)|| checkblack2(i-1,j-2,board))&& (i-1)>0 && (j-2)>0)
        {
            b[r][k]= j-2;
            b[r][k+1]= i-1;
            r++,k=0 ;
        }
}
void blackbishop(int b[][2],int a[],char board[][size])
{
    int i,j,l=1,s,k=0,m=1,n=1,q=1,f=1,d=1,e=1,ab=1,x=1,y=1,z=1,ac=1,ad=1,ae=1;
    i=a[1];
    j=a[0];
    for (s=0; s<13; s++)
    {
        if (checkempty2(i+l,j+f,board) && (i+l)<9 && (j+f)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            l++,f++,d++ ;
        }
        else if (checkempty2(i+l,j+f,board)!= 1 && checkwhite2(i+l,j+f,board) && d==f && (j+f)<9 && (i+l)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            d++ ;
        }
        else if (checkempty2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            m++,n++,e++;
        }
        else if (checkempty2(i-m,j-n,board)!=1 && checkwhite2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 && e==m )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            e++ ;
        }
        else if (checkempty2(i-ab,j+x,board) && (i-ab)>0 && (j+x)<9 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            ab++,x++,y++ ;
        }
        else if (checkwhite2(i-ab ,j+x,board) && y==ab && (j+x)<9 && (i-ab)>0 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            y++ ;
        }
        else if (checkempty2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ac++,ad++,ae++;
        }
        else if (checkwhite2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 && ae==ad )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ae++ ;
        }

        else
            s=13;
    }
}
void whitebishop(int b[][2],int a[],char board[][size])
{
    int i,j,l=1,s,k=0,m=1,n=1,q=1,f=1,d=1,e=1,ab=1,x=1,y=1,z=1,ac=1,ad=1,ae=1;
    i=a[1];
    j=a[0];
    for (s=0; s<14; s++)
    {
        if (checkempty2(i+l,j+f,board) && (i+l)<9 && (j+f)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            l++,f++,d++ ;
        }
        else if (checkempty2(i+l,j+f,board)!= 1 && checkblack2(i+l,j+f,board) && d==f && (j+f)<9 && (i+l)<9 )
        {
            b[r][k]= j+f;
            b[r][k+1]= i+l ;
            r++,k=0 ;
            d++ ;
        }
        else if (checkempty2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            m++,n++,e++;
        }
        else if (checkempty2(i-m,j-n,board)!=1 && checkblack2(i-m,j-n,board) && (i-m)>0 && (j-n)>0 && e==m )
        {
            b[r][k]= j-n;
            b[r][k+1]= i-m ;
            r++,k=0 ;
            e++ ;
        }
        else if (checkempty2(i-ab,j+x,board) && (i-ab)>0 && (j+x)<9 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            ab++,x++,y++ ;
        }
        else if (checkblack2(i-ab ,j+x,board) && y==ab && (j+x)<9 && (i-ab)>0 )
        {
            b[r][k]= j+x;
            b[r][k+1]= i-ab ;
            r++,k=0 ;
            y++ ;
        }
        else if (checkempty2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ac++,ad++,ae++;
        }
        else if (checkblack2(i+ac,j-ad,board) && (i+ac)<9 && (j-ad)>0 && ae==ad )
        {
            b[r][k]= j-ad;
            b[r][k+1]= i+ac ;
            r++,k=0 ;
            ae++ ;
        }
        else
            s=13;
    }
}
void allpossiblewm(char board[][size])
{
    apw=0;
    r=0;
    int i,j,cur[2]= {0};
    for (i=1; i<9; i++)
    {
        for(j=1; j<9; j++)
        {
            if(checkwhite2(i,j,board))
            {
                cur[0]=j;
                cur[1]=i;
                if (board[i][j]=='p')
                {
                    whitepawn(aw,cur,board);
                }
                else if(board[i][j]=='r')
                {
                    whiterook(aw,cur,board);
                }
                else if(board[i][j]=='n')
                {
                    whiteknight(aw,cur,board);
                }
                else if(board[i][j]=='b')
                {
                    whitebishop(aw,cur,board);
                }
                else if(board[i][j]=='q')
                {
                    whitequeen(aw,cur,board);
                }
                else if(board[i][j]=='k')
                {
                    whiteking(aw,cur,board);
                }
            }
        }
    }
    apw=r;
    r=0;
}
void allpossiblebm(char board[][size])
{
    apb=0;
    r=0;
    int i,j,cur[2]= {0};
    for (i=1; i<9; i++)
    {
        for(j=1; j<9; j++)
        {
            if(checkblack2(i,j,board))
            {
                cur[0]=j;
                cur[1]=i;
                if (board[i][j]=='P')
                {
                    blackpawn(ab,cur,board);
                }
                else if(board[i][j]=='R')
                {
                    blackrook(ab,cur,board);
                }
                else if(board[i][j]=='N')
                {
                    blackknight(ab,cur,board);
                }
                else if(board[i][j]=='B')
                {
                    blackbishop(ab,cur,board);
                }
                else if(board[i][j]=='Q')
                {
                    blackqueen(ab,cur,board);
                }
                else if(board[i][j]=='K')
                {
                    blackking(ab,cur,board);
                }
            }
        }
    }
    apb=r;
    r=0;
}
int castlingwhiteleftrook(char board[][size])
{
    int i,j,s=1;
    allpossiblebm(board);
    for(i=0; i<apb; i++)
    {
        if(1== ab[i][0] && 8==ab[i][1])
        {
            s=0;
        }
        for (j=3; j<6; j++)
        {
            if ((j== ab[i][0] && 8==ab[i][1]))
            {
                s=0;
            }
        }
    }
    for( i=2; i<5; i++)
    {
        if (!checkempty2(8,i,board))
        {
            s=0;
        }
    }
    if(WLR!=0 || KW!=0)
        s=0;
    return s;

}
int castlingwhiterightrook(char board[][size])
{
    int i,j,s=1;
    allpossiblebm(board);
    for(i=0; i<apb; i++)
    {
        if(8== ab[i][0] && 8==ab[i][1])
        {
        s=0;
        }
        for (j=5; j<8; j++)
        {
            if ((j== ab[i][0] && 8==ab[i][1]))
            {
                s=0;
            }
        }
    }
    for( i=6; i<8; i++)
    {
        if (!checkempty2(8,i,board))
        {
            s=0;
        }
    }
    if(WRR!=0 || KW!=0)
        s=0;
    return s;
}
int castlingblackleftrook(char board[][size])
{
    int i,j,s=1;
    allpossiblewm(board);
    for(i=0; i<apw; i++)
    {
        if(1== aw[i][0] && 1==aw[i][1])
        {
            s=0;
        }
        for (j=3; j<6; j++)
        {
            if ((j== aw[i][0] && 1==aw[i][1]))
            {
                s=0;
            }
        }
    }
    for( i=2; i<5; i++)
    {
        if (!checkempty2(1,i,board))
        {
            s=0;
        }
    }
    if(BLR!=0 || KB!=0)
        s=0;
    return s;

}
int castlingblackrightrook(char board[][size])
{
    int i,j,s=1;
    allpossiblewm(board);
    for(i=0; i<apw; i++)
    {
        if(8==aw[i][0] && 1==aw[i][1])
        {
        s=0;
        }
        for (j=5; j<8; j++)
        {
            if ((j== aw[i][0] && 1==aw[i][1]))
            {
                s=0;
            }
        }
    }
    for( i=6; i<8; i++)
    {
        if (!checkempty2(1,i,board))
        {
            s=0;
        }
    }
    if(BRR!=0 || KB!=0)
        s=0;
    return s;

}
//Win/Draw/check/checkmate conditions
int checkingBlackKing(char board[][size])
{
    int i,s=0;
    allpossiblewm(board);
    findkings(board);
    for(i=0; i<apw; i++)
    {
        if (kingplace[0][1]==aw[i][1] && kingplace[0][0]==aw[i][0] )
        {
            s=1;
        }
    }
    return s;
}
int checkingwhiteKing(char board[][size])
{
    int i,s=0;
    allpossiblebm(board);
    findkings(board);
    for(i=0; i<apb; i++)
    {
        if (kingplace[1][1]==ab[i][1] && kingplace[1][0]==ab[i][0] )
        {
            s=1;
        }
    }
    return s;
}
int threeFoldRepitition(char board[][size])
{
    int x,y,z=1,check,tmpt;
    for (tmpt=turn-1;tmpt>=0;tmpt--)
    {
        check=0;
        for(x=0;x<size;x++)
        {
            for(y=0;y<size;y++)
            {
                if(!(board[x][y]==boardhistory[tmpt][x][y]))
                    check=1;
            }
        }
        if(check==0)
        {
            if(BLRH[tmpt]==BLR &&BRRH[tmpt]==BRR &&WLRH[tmpt]==WLR &&WRRH[tmpt]==WRR &&KBH[tmpt]==KB && KWH[tmpt]==KW)
            {
                z+=1;
            }
        }
    }
    if(z>2)
    {
        return 1;
    }
    else
        return 0;
}
int matewhite(char board[][size])
{
    char copy[size][size]= {0};
    int i,j,k,a[2],b[30][2],d=1,cr;
    findkings(board);
    for (i=1; i<9; i++)
    {
        for(j=1; j<9; j++)
        {
            boardequal(board,copy);
            a[1]=i;
            a[0]=j;
            if(copy[i][j]=='p')
            {
                whitepawn(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmovewhite(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='r')
            {
                whiterook(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmovewhite(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='n')
            {
                whiteknight(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmovewhite(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='b')
            {
                whitebishop(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmovewhite(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='q')
            {
                whitequeen(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmovewhite(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='k')
            {
                whiteking(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmovewhite(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
        }
    }
    return d;
}
int mateblack(char board[][size])
{
    char copy[size][size]= {0};
    int i,j,k,a[2],b[30][2],d=1,cr;
    findkings(board);
    for (i=1; i<9; i++)
    {
        for(j=1; j<9; j++)
        {
            boardequal(board,copy);
            a[1]=i;
            a[0]=j;
            if(copy[i][j]=='P')
            {
                blackpawn(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmoveblack(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='R')
            {
                blackrook(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmoveblack(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='N')
            {
                blackknight(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmoveblack(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='B')
            {
                blackbishop(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmoveblack(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='Q')
            {
                blackqueen(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmoveblack(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
            if(copy[i][j]=='K')
            {
                blackking(b,a,copy);
                cr=r;
                for(k=0; k<cr; k++)
                {
                    if(!checkmoveblack(copy,b[k],a))
                    {
                        d=0;
                    }
                }
                r=0;
            }
        }
    }
    return d;
}
//checking real Input with predicted ones
int checkmovewhite(char board[][size],int b2[],int a1[])
{
    char Boardcopy[size][size];
    int s=0;
    boardequal(board,Boardcopy);
    blockboardreset(a1,Boardcopy);
    Boardcopy[b2[1]][b2[0]]=board[a1[1]][a1[0]];
    if(board[a1[1]][a1[0]]=='k')
    {
        kingplace[1][1]=b2[1];
        kingplace[1][0]=b2[0];
    }
    if(checkingwhiteKing(Boardcopy))
    {
        s=1;
    }
    if (board[a1[1]][a1[0]]=='k')
    {
        kingplace[1][1]=a1[1];
        kingplace[1][0]=a1[0];
    }
    return s;
}
int checkmoveblack(char board[][size],int b2[],int a1[])
{
    char Boardcopy[size][size]= {0};
    int s=0;
    boardequal(board,Boardcopy);
    blockboardreset(a1,Boardcopy);
    Boardcopy[b2[1]][b2[0]]=board[a1[1]][a1[0]];
    if(board[a1[1]][a1[0]]=='K')
    {
        kingplace[0][1]=b2[1];
        kingplace[0][0]=b2[0];
    }
    if(checkingBlackKing(Boardcopy))
    {
        s=1;
    }
    if (board[a1[1]][a1[0]]=='K')
    {
        kingplace[0][1]=a1[1];
        kingplace[0][0]=a1[0];
    }
    return s;
}
int validplace(int fur[],char board[][size],int possible[][2],int b)
{
    int s=0,i;
    for(i=0; i<b; i++)
    {
        if(fur[0]==possible[i][0]&& fur[1]==possible[i][1])
        {
            s=1;
        }
    }
    return s;
}
//Collective turn functions
void turnwhite(char a[],char board[][size],char b[],char p,int a1[],int b2[])
{
    int i,j,s=0,pb[64][2],tempr;
    while (s==0)
    {
        scanf("%1c%1c",&a[0],&a[1]);
        if(a[0]=='u'&&a[1]=='n')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else if(turn<1)
            {
                printf("Can't undo!\n");
            }
            else
            {
                undo=1;
                s=1;
            }
        }
        else if(a[0]=='e'&&a[1]=='x')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else
            {
                exitvalue=1;
                s=1;
            }
        }
        else if(a[0]=='s'&&a[1]=='v')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else
            {
                save=1;
                s=1;
            }
        }
        else if(a[0]=='r'&&a[1]=='e')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else if(turn>=boardhistorycount)
            {
                printf("Can't redo!\n");
            }
            else
            {
                redo=1;
                s=1;
            }
        }
        else
        {
            transformCoord(a,a1);
            if (checkcolumn(a1[0])&& checkrow(a1[1]))
            {
                if (checkcurrentwhite(a1,board))
                {
                    scanf("%1c%1c",&b[0],&b[1]);
                    transformCoord(b,b2);
                    if (checkcolumn(b2[0])&& checkrow(b2[1]))
                    {
                        if(board[a1[1]][a1[0]]=='p')
                        {
                            whitepawn(pb,a1,board);
                            if(validplace(b2,board,pb,r))
                            {
                                if(promotewhite(a1,board))
                                {
                                    scanf("%c",&p);
                                    if(getchar()!='\n')
                                    {
                                        printf("Unknown command!\n");
                                        r=0;
                                        while(getchar()!='\n');
                                    }
                                    else if(!whiteverify(p))
                                    {
                                        printf("Unknown command!Choose the promotion type like (A7A8q)\n");
                                        r=0;
                                    }
                                    else
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will make your king in check!\n");
                                            r=0;
                                        }
                                        else if(checkcurrentblack(b2,board))
                                        {
                                            deadbpieces[db]=board[b2[1]][b2[0]];
                                            db+=1;
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]= p;
                                            r=0;
                                            s=1;
                                            printf("pawn has been promoted!\n");
                                        }
                                        else
                                        {
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]= p;
                                            r=0;
                                            s=1;
                                            printf("pawn has been promoted!\n");
                                        }
                                    }
                                }
                                else if(getchar()=='\n')
                                {
                                    if(checkcurrentblack(b2,board))
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will make your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            deadbpieces[db]=board[b2[1]][b2[0]];
                                            db+=1;
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]='p';
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                    }
                                    else
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will make your king in check\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]='p';
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                    }
                                }
                                else
                                {
                                    printf("Unknown Command!\n");
                                    r=0;
                                    if(getchar()!='\n')
                                    {
                                        while(getchar()!='\n');
                                    }
                                }
                            }
                            else
                            {
                                printf("Enter a valid move!\n");
                                r=0;
                                if(getchar()!='\n')
                                {
                                    while(getchar()!='\n');
                                }
                            }
                        }
                        else
                        {
                            if (getchar()== '\n')
                            {
                                if(board[a1[1]][a1[0]]=='r')
                                {
                                    whiterook(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentblack(b2,board))
                                            {
                                                deadbpieces[db]=board[b2[1]][b2[0]];
                                                db+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='r';
                                                s=1;
                                                r=0;
                                                if(a1[1]==8 && a1[0]==1)
                                                    WLR+=1;
                                                else
                                                    WRR+=1;

                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='r';
                                                s=1;
                                                r=0;
                                                if(a1[1]==8 && a1[0]==1)
                                                    WLR+=1;
                                                else
                                                    WRR+=1;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='n')
                                {
                                    whiteknight(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentblack(b2,board))
                                            {
                                                deadbpieces[db]=board[b2[1]][b2[0]];
                                                db+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='n';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='n';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='b')
                                {
                                    whitebishop(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentblack(b2,board))
                                            {
                                                deadbpieces[db]=board[b2[1]][b2[0]];
                                                db+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='b';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='b';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='q')
                                {
                                    whitequeen(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentblack(b2,board))
                                            {
                                                deadbpieces[db]=board[b2[1]][b2[0]];
                                                db+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='q';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='q';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='k')
                                {
                                    whiteking(pb,a1,board);
                                    tempr=r;
                                    if(a1[1]==8&&a1[0]==5 && b2[1]==8 &&b2[0]==1)
                                    {
                                        if(castlingwhiteleftrook(board))
                                        {
                                            blockboardreset(a1,board);
                                            blockboardreset(b2,board);
                                            board[8][3]='k';
                                            board[8][4]='r';
                                            kingplace[1][0]=b2[0];
                                            kingplace[1][1]=b2[1];
                                            KW+=1;
                                            WLR+=1;
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                        else
                                        {
                                            printf("Unable to castle!\n");
                                            r=0;
                                        }
                                    }
                                    else if(a1[1]==8&&a1[0]==5 && b2[1]==8 &&b2[0]==8)
                                    {
                                        if(castlingwhiterightrook(board))
                                        {
                                            blockboardreset(a1,board);
                                            blockboardreset(b2,board);
                                            board[8][7]='k';
                                            board[8][6]='r';
                                            kingplace[1][0]=b2[0];
                                            kingplace[1][1]=b2[1];
                                            KW+=1;
                                            WRR+=1;
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                        else
                                        {
                                            printf("Unable to castle!\n");
                                            r=0;
                                        }

                                    }
                                    else if(validplace(b2,board,pb,tempr))
                                    {
                                        if(checkmovewhite(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentblack(b2,board))
                                            {
                                                deadbpieces[db]=board[b2[1]][b2[0]];
                                                db+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='k';
                                                kingplace[1][0]=b2[0];
                                                kingplace[1][1]=b2[1];
                                                KW+=1;
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='k';
                                                kingplace[1][0]=b2[0];
                                                kingplace[1][1]=b2[1];
                                                s=1;
                                                r=0;
                                                KW+=1;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                            }
                            else
                            {
                                printf("Enter a valid command!\n");
                                if(getchar()!='\n')
                                {
                                    while(getchar()!='\n');
                                }
                            }
                        }
                    }
                    else
                    {
                        printf("Column\\row is wrong!Please enter a valid spot to move to!\n");
                        if(getchar()!='\n')
                        {
                            while(getchar()!='\n');
                        }
                    }
                }
                else
                {
                    printf("Enter a valid white piece place!\n");
                    if(getchar()!='\n')
                    {
                        while(getchar()!='\n');
                    }
                }
            }
            else
            {
                printf("Invalid column or row !Please enter a valid command!\n");
                if(getchar()!='\n')
                {
                    while(getchar()!='\n');
                }
            }
        }
    }
}
void turnblack(char a[],char board[][size],char b[],char p,int a1[],int b2[])
{
    int i,j,s=0,pb[64][2],tempr;
    while (s==0)
    {
        scanf("%1c%1c",&a[0],&a[1]);
        if(a[0]=='u'&&a[1]=='n')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else if(turn<1)
            {
                printf("Can't undo!\n");
            }
            else
            {
                undo=1;
                s=1;
            }
        }
        else if(a[0]=='e'&&a[1]=='x')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else
            {
                exitvalue=1;
                s=1;
            }
        }
        else if(a[0]=='r'&&a[1]=='e')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else if(turn>=boardhistorycount)
            {
                printf("Can't redo!\n");
            }
            else
            {
                redo=1;
                s=1;
            }
        }
        else if(a[0]=='s'&&a[1]=='v')
        {
            if(getchar()!='\n')
            {
                printf("unknown command!\n");
                while(getchar()!='\n');
            }
            else
            {
                save=1;
                s=1;
            }
        }
        else
        {
            transformCoord(a,a1);
            if (checkcolumn(a1[0])&& checkrow(a1[1]))
            {
                if (checkcurrentblack(a1,board))
                {
                    scanf("%1c%1c",&b[0],&b[1]);
                    transformCoord(b,b2);
                    if (checkcolumn(b2[0])&& checkrow(b2[1]))
                    {
                        if(board[a1[1]][a1[0]]=='P')
                        {
                            blackpawn(pb,a1,board);
                            if(validplace(b2,board,pb,r))
                            {
                                if(promoteblack(a1,board))
                                {
                                    scanf("%c",&p);
                                    if(getchar()!='\n')
                                    {
                                        printf("Unknown command!\n");
                                        r=0;
                                        while(getchar()!='\n');
                                    }
                                    else if(!blackverify(p))
                                    {
                                        printf("Unknown command!Choose the promotion type like (A2A1Q)\n");
                                        r=0;
                                    }
                                    else
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else if(checkcurrentwhite(b2,board))
                                        {
                                            deadwpieces[dw]=board[b2[1]][b2[0]];
                                            dw+=1;
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]= p;
                                            r=0;
                                            s=1;
                                            printf("pawn has been promoted!\n");
                                        }
                                        else
                                        {
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]= p;
                                            r=0;
                                            s=1;
                                            printf("pawn has been promoted!\n");
                                        }
                                    }
                                }
                                else if(getchar()=='\n')
                                {
                                    if(checkcurrentwhite(b2,board))
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            deadwpieces[dw]=board[b2[1]][b2[0]];
                                            dw+=1;
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]='P';
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                    }
                                    else
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            blockboardreset(a1,board);
                                            board[b2[1]][b2[0]]='P';
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                    }
                                }
                                else
                                {
                                    printf("Unknown Command!\n");
                                    r=0;
                                    if(getchar()!='\n')
                                    {
                                        while(getchar()!='\n');
                                    }
                                }
                            }
                            else
                            {
                                printf("Enter a valid move!\n");
                                r=0;
                                if(getchar()!='\n')
                                {
                                    while(getchar()!='\n');
                                }
                            }
                        }
                        else
                        {
                            if (getchar()== '\n')
                            {
                                if(board[a1[1]][a1[0]]=='R')
                                {
                                    blackrook(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentwhite(b2,board))
                                            {
                                                deadwpieces[dw]=board[b2[1]][b2[0]];
                                                dw+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='R';
                                                s=1;
                                                r=0;
                                                if(a1[1]==1 && a1[0]==1)
                                                    BLR+=1;
                                                else
                                                    BRR+=1;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='R';
                                                s=1;
                                                r=0;
                                                if(a1[1]==1 && a1[0]==1)
                                                    BLR+=1;
                                                else
                                                    BRR+=1;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='N')
                                {
                                    blackknight(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentwhite(b2,board))
                                            {
                                                deadwpieces[dw]=board[b2[1]][b2[0]];
                                                dw+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='N';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='N';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='B')
                                {
                                    blackbishop(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentwhite(b2,board))
                                            {
                                                deadwpieces[dw]=board[b2[1]][b2[0]];
                                                dw+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='B';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='B';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='Q')
                                {
                                    blackqueen(pb,a1,board);
                                    if(validplace(b2,board,pb,r))
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentwhite(b2,board))
                                            {
                                                deadwpieces[dw]=board[b2[1]][b2[0]];
                                                dw+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='Q';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='Q';
                                                s=1;
                                                r=0;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                                else if(board[a1[1]][a1[0]]=='K')
                                {
                                    blackking(pb,a1,board);
                                    tempr=r;
                                    if(a1[1]==1&&a1[0]==5 && b2[1]==1 &&b2[0]==1)
                                    {
                                        if(castlingblackleftrook(board))
                                        {
                                            blockboardreset(a1,board);
                                            blockboardreset(b2,board);
                                            board[1][3]='K';
                                            board[1][4]='R';
                                            kingplace[0][0]=b2[0];
                                            kingplace[0][1]=b2[1];
                                            KB+=1;
                                            BLR+=1;
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                        else
                                        {
                                            printf("Unable to castle!\n");
                                            r=0;
                                        }
                                    }
                                    else if(a1[1]==1 && a1[0]==5 && b2[1]==1 &&b2[0]==8)
                                    {
                                        if(castlingblackrightrook(board))
                                        {
                                            blockboardreset(a1,board);
                                            blockboardreset(b2,board);
                                            board[1][7]='K';
                                            board[1][6]='R';
                                            kingplace[0][0]=b2[0];
                                            kingplace[0][1]=b2[1];
                                            KB+=1;
                                            BRR+=1;
                                            s=1;
                                            r=0;
                                            printf("\n");
                                        }
                                        else
                                        {
                                            printf("Unable to castle!\n");
                                            r=0;
                                        }

                                    }
                                    else if(validplace(b2,board,pb,tempr))
                                    {
                                        if(checkmoveblack(board,b2,a1))
                                        {
                                            printf("Can't make that move!Will put your king in check!\n");
                                            r=0;
                                        }
                                        else
                                        {
                                            if(checkcurrentwhite(b2,board))
                                            {
                                                deadwpieces[dw]=board[b2[1]][b2[0]];
                                                dw+=1;
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='K';
                                                kingplace[0][0]=b2[0];
                                                kingplace[0][1]=b2[1];
                                                s=1;
                                                r=0;
                                                KB+=1;
                                                printf("\n");
                                            }
                                            else
                                            {
                                                blockboardreset(a1,board);
                                                board[b2[1]][b2[0]]='K';
                                                kingplace[0][0]=b2[0];
                                                kingplace[0][1]=b2[1];
                                                s=1;
                                                r=0;
                                                KB+=1;
                                                printf("\n");
                                            }
                                        }
                                    }
                                    else
                                    {
                                        printf("Enter a valid move!\n");
                                        r=0;
                                    }
                                }
                            }
                            else
                            {
                                printf("Enter a valid command!\n");
                                if(getchar()!='\n')
                                {
                                    while(getchar()!='\n');
                                }
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid column or row !Enter a valid spot to move to!\n");
                        if(getchar()!='\n')
                        {
                            while(getchar()!='\n');
                        }
                    }
                }
                else
                {
                    printf("Enter a valid black piece place!\n");
                    if(getchar()!='\n')
                    {
                        while(getchar()!='\n');
                    }
                }
            }
            else
            {
                printf("Invalid column or row !Please enter a valid command!\n");
                if(getchar()!='\n')
                {
                    while(getchar()!='\n');
                }
            }
        }
    }
}
//File handling!!
int checkemptyfile(FILE *text)
{
    fseek(text,0,SEEK_END);
    int s=ftell(text);
    if(s==0)
    {
        return 1;
    }
    else
        return 0;
}
int checksavename(char word[])
{
    int i,j,s=0;
    for (i=0; i<9; i++)
    {
        for(j=0; j<1036; j++)
        {
            if(word[j]==unallowedname[i])
                s=1;
        }
    }
    if(s==1)
    {
        printf("Can't save!Invalid char used in name!\n");
    }
    return s;
}
int duplicatesavename(char word[])
{
    FILE *list;
    char c[1036]= {0};
    int s=0,i;
    list =fopen("SaveList.txt", "r");
    if(list)
    {
        while(fread(c,1036,1,list))
        {
            if (strcmp(c,word)==0)
            {
                s=1;
            }
        }
    }
    fclose(list);
    return s;
}
void savegame(char board[size][size])
{
    FILE *save_file,*list,*list2;
    int i=1,j=0,k,yncheck;
    char rawname[1036]= {0},name[1036]= {0},yn,temp[1036]= {0};
    while(i||checksavename(rawname)|| (strcmp(name,"SaveList.txt")==0))
    {
        printf("Enter a name for the save file:\n");
        gets(rawname);
        strcpy(name,rawname);
        strcat(name,".txt");
        i=0;
        if(duplicatesavename(name))
        {
            do
            {
                printf("A saved file has this name. Want to overwrite y\\n ?\n");
                yncheck=scanf("%c",&yn);
                if (getchar()!='\n')
                {
                    yncheck=0;
                    while(getchar()!='\n');
                }
                else if(yn != 'y' && yn!= 'n')
                {
                    yncheck=0;
                    printf("Enter a valid answer!\n");
                }
            }while(!yncheck);
            if (yn=='y')
               {
                   list =fopen("SaveList.txt", "r");
                   list2=fopen("Temp.txt","w");
                   while(fread(temp,1036,1,list))
                    {
                        if (abs(strcmp(temp,name)))
                        {
                            fwrite(temp,1036,1,list2);
                        }
                    }
                    fclose(list);
                    fclose(list2);
                    remove("SaveList.txt");
                    rename("Temp.txt","SaveList.txt");
                   i=0;
               }
            else
                i=1;
        }
    }
    list =fopen("SaveList.txt", "a");
    fwrite(name,1036,1,list);
    fclose(list);
    save_file =fopen(name, "w");
    if (!save_file)
        printf("Error!Game hasn't saved\n");
    else
    {
        fwrite(board,100,1,save_file);
        fprintf(save_file,"%d,",decideturn);
        fprintf(save_file,"%d,",dw);
        fprintf(save_file,"%d,",db);
        fprintf(save_file,"%d,",turn);
        fprintf(save_file,"%d,",boardhistorycount);
        fprintf(save_file,"%d,",KB);
        fprintf(save_file,"%d,",KW);
        fprintf(save_file,"%d,",BLR);
        fprintf(save_file,"%d,",BRR);
        fprintf(save_file,"%d,",WLR);
        fprintf(save_file,"%d,",WRR);
        fprintf(save_file,"%d,",gametype);
        fwrite(deadwpieces,16,1,save_file);
        fwrite(deadbpieces,16,1,save_file);
        fwrite(boardhistory,boardhistorycount*100,1,save_file);
        fwrite(ddb,8*boardhistorycount,1,save_file);
        fwrite(ddw,8*boardhistorycount,1,save_file);
        fwrite(kingplace,16,1,save_file);
        fwrite(KBH,8*boardhistorycount,1,save_file);
        fwrite(KWH,8*boardhistorycount,1,save_file);
        fwrite(BLRH,8*boardhistorycount,1,save_file);
        fwrite(BRRH,8*boardhistorycount,1,save_file);
        fwrite(WLRH,8*boardhistorycount,1,save_file);
        fwrite(WRRH,8*boardhistorycount,1,save_file);
        fclose(save_file);
    }
}
int loadgame(char board[size][size])
{
    FILE *save_file,*list;
    int i=1,j=0,k;
    char name[1032]= {0},c[1036];

    list =fopen("SaveList.txt", "r");
    if(!list||checkemptyfile(list))
    {
        printf("No Saved games found!\n");
        fclose(list);
        return 0;
    }
    else
    {
        fseek(list,0,SEEK_SET);
        printf("Currently Saved games: \n");
        while(fread(c,1036,1,list))
        {
            printf("%5s\n",c);
        }
        fclose(list);
        while(i)
        {
            printf("Enter a name for the saved file(without .txt):\n");
            gets(name);
            i=0;
        }
        strcat(name,".txt");
        save_file =fopen(name,"r");
        if (!save_file || strcmp(name,"SaveList.txt")==0)
        {
            printf("No saved files by that name found!\n");
            return 0;
        }
        else
        {
            fread(board,100,1,save_file);
            fscanf(save_file,"%d,",&decideturn);
            fscanf(save_file,"%d,",&dw);
            fscanf(save_file,"%d,",&db);
            fscanf(save_file,"%d,",&turn);
            fscanf(save_file,"%d,",&boardhistorycount);
            fscanf(save_file,"%d,",&KB);
            fscanf(save_file,"%d,",&KW);
            fscanf(save_file,"%d,",&BLR);
            fscanf(save_file,"%d,",&BRR);
            fscanf(save_file,"%d,",&WLR);
            fscanf(save_file,"%d,",&WRR);
            fscanf(save_file,"%d,",&gametype);
            fread(deadwpieces,16,1,save_file);
            fread(deadbpieces,16,1,save_file);
            fread(boardhistory,boardhistorycount*100,1,save_file);
            fread(ddb,8*boardhistorycount,1,save_file);
            fread(ddw,8*boardhistorycount,1,save_file);
            fread(kingplace,16,1,save_file);
            fread(KBH,8*boardhistorycount,1,save_file);
            fread(KWH,8*boardhistorycount,1,save_file);
            fread(BLRH,8*boardhistorycount,1,save_file);
            fread(BRRH,8*boardhistorycount,1,save_file);
            fread(WLRH,8*boardhistorycount,1,save_file);
            fread(WRRH,8*boardhistorycount,1,save_file);
            fclose(save_file);
            return 1;
        }
    }
}
int deletegame()
{
    FILE *list,*list2;
    char c[1036]= {0},name[1036]= {0},temp[1036]= {0};
    int i=1,j=0,check,countingstars=0;
    list =fopen("SaveList.txt", "r");
    if(!list||checkemptyfile(list))
    {
        printf("No saved games to delete!\n");
        fclose(list);
        return 0;
    }
    else
    {
        fseek(list,0,SEEK_SET);
        printf("Currently Saved games: \n");
        while(fread(c,1036,1,list))
        {
            printf("%5s\n",c);
            countingstars+=1;
        }
        fclose(list);
        while(i||strcmp(name,"SaveList")==0)
        {
            printf("Enter a name for the saved file(without .txt):\n");
            gets(name);
            i=0;
        }
        strcat(name,".txt");
        check=remove(name);
        if(check==0)
        {
            list =fopen("SaveList.txt", "r");
            list2=fopen("Temp.txt","w");
            while(fread(temp,1036,1,list))
            {
                if (abs(strcmp(temp,name)))
                {
                    fwrite(temp,1036,1,list2);
                }
            }
            fclose(list);
            fclose(list2);
            remove("SaveList.txt");
            rename("Temp.txt","SaveList.txt");
            return 1;
        }
        else
        {
            printf("File not found to delete!\n");
            return 0;
        }
    }
}
//AI?!
int checkingAnyPlaceBlack(int a[],char board[][size])
{
   int i,j,s=0,k,f;
   i=a[1];
   j=a[0];
   allpossiblewm(board);
   f=apw;
   for(k=0;k<f;k++)
   {
        if (j== aw[k][0] && i==aw[k][1])
            {
                s=1;
            }
   }
   return s ;
}
int attackvalue (int a[],char board[][size])
{
    int s;
   if (checkempty2(a[1],a[0],board))
   {
     s=0;
   }
   else if (board[a[1]][a[0]]=='p')
   {
       s=200 ;
   }
   else if (board[a[1]][a[0]]=='n')
   {
       s=300 ;
   }
   else if (board[a[1]][a[0]]=='b')
   {
       s=700 ;
   }
   else if (board[a[1]][a[0]]=='r')
   {
       s=1300 ;
   }
   else if (board[a[1]][a[0]]=='q')
   {
       s=2100 ;
   }
   return s;
}
int losevalue (int a[],char board[][size])
{
   int s=0;
   if (checkempty2(a[1],a[0],board))
   {
     s= 0 ;
   }
   else if (board[a[1]][a[0]]=='P')
   {
     s=200 ;
   }
   else if (board[a[1]][a[0]]=='N')
   {
     s=300 ;
   }
   else if (board[a[0]][a[0]]=='B')
   {
     s=700 ;
   }
   else if (board[a[0]][a[0]]=='R')
   {
      s=1300 ;
   }
   else if (board[a[0]][a[0]]=='Q')
   {
      s=2100 ;
   }
   return s;
}
int smartcheck(int a[],char board[][size])
{
    int s=0;
    if(checkingwhiteKing(board)&&!checkingAnyPlaceBlack(a,board))
    {
        s=1;
    }
    return s;
}
void propermovelist(int a[][2],char board[][size],int properlist[][2],int *propercount,int cur[],int loopyloop)
{
    char Boardcopy[size][size]= {0};
    int s=0,k;
    for(k=0;k<loopyloop;k++)
    {
        boardequal(board,Boardcopy);
        blockboardreset(cur,Boardcopy);
        Boardcopy[a[k][1]][a[k][0]]=board[cur[1]][cur[0]];
        if(board[cur[1]][cur[0]]=='K')
        {
            kingplace[0][1]=a[k][1];
            kingplace[0][0]=a[k][0];
        }
        if(!checkingBlackKing(Boardcopy))
        {
            properlist[*propercount][0]=a[k][0];
            properlist[*propercount][1]=a[k][1];
            *propercount+=1;
        }
        if (board[cur[1]][cur[0]]=='K')
        {
            kingplace[0][1]=cur[1];
            kingplace[0][0]=cur[0];
        }
    }
}
int lostcurrentvalue(char board[][size],int a[])
{
    int s=0;
    if(checkingAnyPlaceBlack(a,board))
    {
        s=losevalue(a,board);
    }
    return s;
}
int biggestLossValue(char board[][size],int compare[])
{
    int i,j,k,cur[2],biggestlose=0,s;
    for(i=1;i<9;i++)
    {
        for(j=1;j<9;j++)
        {
            cur[0]=j;cur[1]=i;
            allpossiblewm(board);
            for(k=0;k<apw;k++)
            {
                if(checkcurrentblack(cur,board)&& aw[k][0] == cur[0] && aw[k][1] == cur[1])
                {
                        biggestlose+=losevalue(cur,board);
                }
            }
        }
    }
    return biggestlose;
}
void priorityAI(int *target,int properlist[][2],int propercount,int cur[],int finallist[][2],char board[][size])
{
    char boardcopy[size][size];
    int i,promoteconstant=0,l,w,tl;
    for(i=0;i<propercount;i++)
    {
        promoteconstant=0;
        boardequal(board,boardcopy);
        blockboardreset(cur,boardcopy);
        boardcopy[properlist[i][1]][properlist[i][0]]=board[cur[1]][cur[0]];
        if (board[cur[1]][cur[0]]=='P' && cur[1]==7)
        {
            boardcopy[properlist[i][1]][properlist[i][0]]='Q';
            promoteconstant=2100;
        }
        w=attackvalue(properlist[i],board);
        l=biggestLossValue(boardcopy,properlist[i]);
        if(board[cur[1]][cur[0]]=='K')
        {
            kingplace[0][1]=properlist[i][1];
            kingplace[0][0]=properlist[i][0];
        }
        if(matewhite(boardcopy)&& *target<10000)
        {
            *target=10000;
            finallist[0][0]=cur[0];
            finallist[0][1]=cur[1];
            finallist[1][0]=properlist[i][0];
            finallist[1][1]=properlist[i][1];
        }
        else if(smartcheck(properlist[i],boardcopy)&& *target<9500)
        {
            *target=9500;
            finallist[0][0]=cur[0];
            finallist[0][1]=cur[1];
            finallist[1][0]=properlist[i][0];
            finallist[1][1]=properlist[i][1];
        }
        else if((w-l+promoteconstant)>= *target)
        {
            *target=w-l;
            if (board[cur[1]][cur[0]]=='P' && cur[1]==7)
            {
                *target+=2100;
            }
            if(w==0 && lostcurrentvalue(boardcopy,properlist[i])==0)
            {
                if(board[properlist[i][1]][properlist[i][0]]=='P')
                {
                    *target+=5;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='N')
                {
                    *target+=4;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='B')
                {
                    *target+=3;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='R')
                {
                    *target+=2;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='Q')
                {
                    *target+=1;
                }
            }
            else if(*target==0)
            {
                if(board[properlist[i][1]][properlist[i][0]]=='P')
                {
                    *target+=10;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='N')
                {
                    *target+=20;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='B')
                {
                    *target+=30;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='R')
                {
                    *target+=40;
                }
                else if(board[properlist[i][1]][properlist[i][0]]=='Q')
                {
                    *target+=50;
                }
            }
            finallist[0][0]=cur[0];
            finallist[0][1]=cur[1];
            finallist[1][0]=properlist[i][0];
            finallist[1][1]=properlist[i][1];
        }
        if (board[cur[1]][cur[0]]=='K')
        {
            kingplace[0][1]=cur[1];
            kingplace[0][0]=cur[0];
        }
    }
}
int AIbestmove(int a[2][2],char board[][size])
{
    int i,j,curmovelist[30][2],cur[2],loopmovenumber,target=-10000000,properlist[30][2],propercount=0;
    if(turn>4)
    {
        for(i=1;i<9;i++)
        {
            for(j=1;j<9;j++)
            {
                cur[1]=i;
                cur[0]=j;
                if(board[i][j]=='P')
                {
                    blackpawn(curmovelist,cur,board);
                    loopmovenumber=r;
                    propermovelist(curmovelist,board,properlist,&propercount,cur,loopmovenumber);
                    r=0;
                    priorityAI(&target,properlist,propercount,cur,a,board);
                    r=0;
                    propercount=0;
                }
                else if(board[i][j]=='N')
                {
                    blackknight(curmovelist,cur,board);
                    loopmovenumber=r;
                    propermovelist(curmovelist,board,properlist,&propercount,cur,loopmovenumber);
                    priorityAI(&target,properlist,propercount,cur,a,board);
                    r=0;
                    propercount=0;
                }
                else if(board[i][j]=='B')
                {
                    blackbishop(curmovelist,cur,board);
                    loopmovenumber=r;
                    propermovelist(curmovelist,board,properlist,&propercount,cur,loopmovenumber);
                    r=0;
                    priorityAI(&target,properlist,propercount,cur,a,board);
                    r=0;
                    propercount=0;
                }
                else if(board[i][j]=='R')
                {
                    blackrook(curmovelist,cur,board);
                    loopmovenumber=r;
                    propermovelist(curmovelist,board,properlist,&propercount,cur,loopmovenumber);
                    r=0;
                    priorityAI(&target,properlist,propercount,cur,a,board);
                    r=0;
                    propercount=0;
                }
                else if(board[i][j]=='Q')
                {
                    blackqueen(curmovelist,cur,board);
                    loopmovenumber=r;
                    propermovelist(curmovelist,board,properlist,&propercount,cur,loopmovenumber);
                    r=0;
                    priorityAI(&target,properlist,propercount,cur,a,board);
                    r=0;
                    propercount=0;
                }
                else if(board[i][j]=='K')
                {
                    blackking(curmovelist,cur,board);
                    loopmovenumber=r;
                    propermovelist(curmovelist,board,properlist,&propercount,cur,loopmovenumber);
                    r=0;
                    priorityAI(&target,properlist,propercount,cur,a,board);
                    r=0;
                    propercount=0;
                }
            }
        }
    }
    else
    {
        if(turn==1)
        {
            a[0][0]=7;
            a[0][1]=1;
            a[1][0]=6;
            a[1][1]=3;
        }
        else
        {
            a[0][0]=4;
            a[0][1]=2;
            a[1][0]=4;
            a[1][1]=4;
        }
    }
}
void AIturn(char board[][size])
{
    int movemove[2][2];
    AIbestmove(movemove,board);
    if(board[movemove[0][1]][movemove[0][0]]=='K')
    {
            kingplace[0][0]=movemove[1][0];
            kingplace[0][1]=movemove[1][1];
    }
    if(checkcurrentwhite(movemove[1],board))
    {
        deadwpieces[dw]=board[movemove[1][1]][movemove[1][0]];
        dw+=1;
    }
    if (board[movemove[0][1]][movemove[0][0]]=='P' && movemove[0][1]==7)
    {
        board[movemove[1][1]][movemove[1][0]]='Q';
    }
    else
    {
        board[movemove[1][1]][movemove[1][0]]=board[movemove[0][1]][movemove[0][0]];
    }
    blockboardreset(movemove[0],board);
}
void alternategameengine(char gameboard[size][size],char curin[],char futin[],char p,int cuin[],int fuin[])
{
    while (!gameover)
    {
        if(threeFoldRepitition(gameboard))
        {
            gameover=1;
            printf("It's a draw by three fold repetition!\n");
        }
        if(decideturn%2==0)
        {
            printf("white player turn:\n");
            turnwhite(curin,gameboard,futin,p,cuin,fuin);
            if(undo!=1 && save !=1 && redo!=1 && exitvalue!=1)
            {
                printall(gameboard);
                if(mateblack(gameboard)&& checkingBlackKing(gameboard))
                {
                    printf("White Player WON!\n");
                    gameover=1;
                }
                else if(mateblack(gameboard))
                {
                    printf("It's a Draw!\n");
                    gameover=1;
                }
                turn+=1;
                ddb[turn]=db;
                ddw[turn]=dw;
                boardhistorywrite(gameboard);
                boardhistorycount=turn;
                BLRH[turn]=BLR;
                BRRH[turn]=BRR;
                KBH[turn]=KB;
                WLRH[turn]=WLR;
                WRRH[turn]=WRR;
                KWH[turn]=KW;
                decideturn=1;
            }
            else if(undo)
            {

                if(turn>1)
                {
                    turn-=2;
                    dw=ddw[turn];
                    db=ddb[turn];
                    boardhistoryload(gameboard);
                    BLR=BLRH[turn];
                    BRR=BRRH[turn];
                    KB=KBH[turn];
                    WLR=WLRH[turn];
                    WRR=WRRH[turn];
                    KW=KWH[turn];
                    printall(gameboard);
                    findkings(gameboard);
                    undo=0;
                }
                else
                {
                    printf("Unable to undo!\n");
                }
            }
            else if(redo)
            {
                if(turn<= boardhistorycount-2)
                {
                    turn+=2;
                    db=ddb[turn];
                    dw=ddw[turn];
                    boardhistoryload(gameboard);
                    printall(gameboard);
                    BLR=BLRH[turn];
                    BRR=BRRH[turn];
                    KB=KBH[turn];
                    WLR=WLRH[turn];
                    WRR=WRRH[turn];
                    KW=KWH[turn];
                    redo=0;
                }
                else
                {
                    printf("Unable to redo!\n");
                }
            }
            else if(save==1)
            {
                save=0;
                savegame(gameboard);
                printf("Game has been saved!\n");
            }
            else if (exitvalue==1)
            {
                exitvalue=0;
                gameover=1;
                printf("You exited the game!\n");
            }
        }
        else
        {
            printf("AI turn:\n");
            AIturn(gameboard);
            printall(gameboard);
            if(matewhite(gameboard)&& checkingwhiteKing(gameboard))
            {
                printf("AI WON!\n");
                gameover=1;
            }
            else if(matewhite(gameboard))
            {
                printf("It's a Draw!\n");
                gameover=1;
            }
            turn+=1;
            ddw[turn]=dw;
            ddb[turn]=db;
            boardhistorywrite(gameboard);
            boardhistorycount=turn;
            BLRH[turn]=BLR;
            BRRH[turn]=BRR;
            KBH[turn]=KB;
            WLRH[turn]=WLR;
            WRRH[turn]=WRR;
            KWH[turn]=KW;
            decideturn=0;
        }
    }
    gameover=0;
}
void newalternategame(char gameboard[size][size],char curin[],char futin[],char p,int cuin[],int fuin[])
{
    initializeboard(gameboard);
    boardstart(gameboard);
    boardhistorywrite(gameboard);
    BLRH[turn]=BLR;
    BRRH[turn]=BRR;
    WLRH[turn]=WLR;
    WRRH[turn]=WRR;
    KBH[turn]=KB;
    KWH[turn]=KW;
    printboard(gameboard);
    alternategameengine(gameboard,curin,futin,p,cuin,fuin);
}
void resumealternategame(char gameboard[size][size],char curin[],char futin[],char p,int cuin[],int fuin[])
{
    boardhistorywrite(gameboard);
    printall(gameboard);
    alternategameengine(gameboard,curin,futin,p,cuin,fuin);
}
//Finally the game engine :D
void gameengine(char gameboard[size][size],char curin[],char futin[],char p,int cuin[],int fuin[])
{
    while (!gameover)
    {
        if(threeFoldRepitition(gameboard))
        {
            gameover=1;
            printf("It's a draw by three fold repetition!\n");
        }
        if(decideturn%2==0)
        {
            printf("white player turn:\n");
            turnwhite(curin,gameboard,futin,p,cuin,fuin);
            if(undo!=1 && save !=1 && redo!=1 && exitvalue!=1)
            {
                printall(gameboard);
                if(mateblack(gameboard)&& checkingBlackKing(gameboard))
                {
                    printf("White Player WON!\n");
                    gameover=1;
                }
                else if(mateblack(gameboard))
                {
                    printf("It's a Draw!\n");
                    gameover=1;
                }
                turn+=1;
                ddb[turn]=db;
                ddw[turn]=dw;
                boardhistorywrite(gameboard);
                boardhistorycount=turn;
                BLRH[turn]=BLR;
                BRRH[turn]=BRR;
                KBH[turn]=KB;
                WLRH[turn]=WLR;
                WRRH[turn]=WRR;
                KWH[turn]=KW;
                decideturn=1;
            }
            else if(undo)
            {
                turn-=1;
                dw=ddw[turn];
                db=ddb[turn];
                boardhistoryload(gameboard);
                BLR=BLRH[turn];
                BRR=BRRH[turn];
                KB=KBH[turn];
                WLR=WLRH[turn];
                WRR=WRRH[turn];
                KW=KWH[turn];
                printall(gameboard);
                findkings(gameboard);
                undo=0;
                decideturn=1;
            }
            else if(redo)
            {
                turn+=1;
                db=ddb[turn];
                dw=ddw[turn];
                boardhistoryload(gameboard);
                printall(gameboard);
                BLR=BLRH[turn];
                BRR=BRRH[turn];
                KB=KBH[turn];
                WLR=WLRH[turn];
                WRR=WRRH[turn];
                KW=KWH[turn];
                redo=0;
                decideturn=1;
            }
            else if(save==1)
            {
                save=0;
                savegame(gameboard);
                printf("Game has been saved!\n");
            }
            else if (exitvalue==1)
            {
                exitvalue=0;
                gameover=1;
                printf("You exited the game!\n");
            }
        }
        else
        {
            printf("black player turn:\n");
            turnblack(curin,gameboard,futin,p,cuin,fuin);
            if(undo!=1 && save !=1 && redo!=1 && exitvalue!=1)
            {
                printall(gameboard);
                if(matewhite(gameboard)&& checkingwhiteKing(gameboard))
                {
                    printf("Black Player WON!\n");
                    gameover=1;
                }
                else if(matewhite(gameboard))
                {
                    printf("It's a Draw!\n");
                    gameover=1;
                }
                turn+=1;
                ddw[turn]=dw;
                ddb[turn]=db;
                boardhistorywrite(gameboard);
                boardhistorycount=turn;
                BLRH[turn]=BLR;
                BRRH[turn]=BRR;
                KBH[turn]=KB;
                WLRH[turn]=WLR;
                WRRH[turn]=WRR;
                KWH[turn]=KW;
                decideturn=0;
            }
            else if(undo)
            {
                turn-=1;
                db=ddb[turn];
                dw=ddw[turn];
                boardhistoryload(gameboard);
                printall(gameboard);
                WLR=WLRH[turn];
                WRR=WRRH[turn];
                KW=KWH[turn];
                BLR=BLRH[turn];
                BRR=BRRH[turn];
                KB=KBH[turn];
                findkings(gameboard);
                undo=0;
                decideturn=0;
            }
            else if (redo)
            {
                turn+=1;
                dw=ddw[turn];
                db=ddb[turn];
                boardhistoryload(gameboard);
                printall(gameboard);
                BLR=BLRH[turn];
                BRR=BRRH[turn];
                KB=KBH[turn];
                WLR=WLRH[turn];
                WRR=WRRH[turn];
                KW=KWH[turn];
                redo=0;
                decideturn=0;
            }
            else if (save==1)
            {
                save=0;
                savegame(gameboard);
                printf("Game has been saved!\n");
            }
            else if (exitvalue==1)
            {
                exitvalue=0;
                gameover=1;
                printf("You exited the game!\n");
            }
        }
    }
    gameover=0;
}
void newgame(char gameboard[size][size],char curin[],char futin[],char p,int cuin[],int fuin[])
{
    initializeboard(gameboard);
    boardstart(gameboard);
    boardhistorywrite(gameboard);
    BLRH[turn]=BLR;
    BRRH[turn]=BRR;
    WLRH[turn]=WLR;
    WRRH[turn]=WRR;
    KBH[turn]=KB;
    KWH[turn]=KW;
    printboard(gameboard);
    gameengine(gameboard,curin,futin,p,cuin,fuin);
}
void resumegame(char gameboard[size][size],char curin[],char futin[],char p,int cuin[],int fuin[])
{
    boardhistorywrite(gameboard);
    printall(gameboard);
    gameengine(gameboard,curin,futin,p,cuin,fuin);
}
//The game interface
int main()
{
    char gamemode;
    char gameboard[size][size]= {0};
    char curin[2]= {0},futin[2]= {0},p;
    int cuin[2]= {0},fuin[2]= {0},interface=1;
    printf("Welcome to our chess game!\n");
    while(interface)
    {
        printf("Enter H for options and commands\nL to load your latest saved game\nN to start a new game\nD to delete a saved game!\nB to try our new mode(human vs Machine)!YES,it's possible\nE to close the game\n");
        scanf("%c",&gamemode);
        if(getchar()!='\n')
        {
            printf("Unknown command\n");
            while(getchar()!='\n');
        }
        else if(gamemode=='N')
        {
            gametype=0;
            dw=0;
            db=0;
            turn=0;
            BLR=0;
            BRR=0;
            WLR=0;
            WRR=0;
            KW=0;
            KB=0;
            boardhistorycount=0;
            decideturn=0;
            kingplace[0][0]=5;
            kingplace[0][1]=1;
            kingplace[1][0]=5;
            kingplace[1][1]=8;
            newgame(gameboard,curin,futin,p,cuin,fuin);
        }
        else if(gamemode=='L')
        {
            if(loadgame(gameboard))
            {
                if(gametype==0)
                    resumegame(gameboard,curin,futin,p,cuin,fuin);
                else
                    resumealternategame(gameboard,curin,futin,p,cuin,fuin);
            }
        }
        else if(gamemode=='H')
        {
            printf("The game commands are simple to move a piece you enter it's current place with \nit's future one like (A2A4)\nIn case of promotion , you add a letter at the end to define the promotion and \nit's based on the player!\nBlack player with capital and white player with small letters like (A7A8q)\nTo undo , simply write un\nTo redo, simply write re\nTo save at any time ,simply write sv\nTo exit the game , write ex\n");
        }
        else if(gamemode=='D')
        {
            if(deletegame())
            {
                printf("Saved game has been deleted!\n");
            }
        }
        else if(gamemode=='E')
        {
            interface=0;
        }
        else if(gamemode=='B')
        {
            gametype=1;
            dw=0;
            db=0;
            turn=0;
            BLR=0;
            BRR=0;
            WLR=0;
            WRR=0;
            KW=0;
            KB=0;
            boardhistorycount=0;
            decideturn=0;
            kingplace[0][0]=5;
            kingplace[0][1]=1;
            kingplace[1][0]=5;
            kingplace[1][1]=8;
            newalternategame(gameboard,curin,futin,p,cuin,fuin);
        }
        else
            printf("Invalid Command\n");
    }
    printf("press enter to end!");
    getchar();
    return 0;
}
