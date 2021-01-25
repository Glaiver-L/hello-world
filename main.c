#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

typedef struct resident//定义结构体：储存用户信息
{
    char number[10];//房间号
    char name[10];//房客姓名
    char sex[10];//房客性别
    char num[25];//房客身份证号
    int time1;//居住天数
    struct resident *next;//链表指向下一节点
} RDT;

RDT *Input(RDT *head);//建立新用户
RDT *Del(RDT *head,char number[]);//删除用户信息
void Prt(RDT *p);//打印链表数据
void Search1(RDT *head,char number[]);//按房间号搜索
void Search2(RDT *head,char name[]);//按姓名搜索
void Search3(RDT *head,char name[]);//模糊搜索
int Comfirm(RDT *head,char number[]);//检测是否该房间是否已有住户
void STA(RDT *head);//统计所有楼层的住房情况
void STO(RDT *head);//将输入的数据储存在data.txt文件中

int main()
{
    PlaySoundA("hmbb.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
    printf(" ——————————————————————————————————————————-----------------------------------");
    printf("|                                               欢迎进入XXX酒店管理系统                                                |");
    printf(" ——————————————————————————————————————————-----------------------------------");
    int n;
    RDT *head = NULL;
    char put[10];
    do
    {
        printf("请选择您要进行的操作\n");
        printf("1、房客信息录入\n");
        printf("2、信息查找\n");
        printf("3、房客退房\n");
        printf("4、输出所有住户信息\n");
        printf("5、当前住房情况\n");
        printf("6、保存当前输入数据\n");
        printf("0、退出系统\n");
        scanf("%d",&n);
        while(getchar()!='\n');
        while(n<0||n>6)
        {
            printf("您的输入有误，请重新输入\n");
            scanf("%d",&n);
            while(getchar()!='\n');
        }
        switch (n)
        {
        case 1:
            head = Input(head);
            break;
        case 2:
            printf("请输入想要的查找方式：\n");
            printf("1、房间号查找\n");
            printf("2、姓名查找\n");
            printf("3、模糊查找\n");
            scanf("%d",&n);
            while(getchar()!='\n');
            while(n<0||n>3)
            {
                printf("您的输入有误，请重新输入\n");
                scanf("%d",&n);
                while(getchar()!='\n');
            }
            switch(n)
            {
            case 1:
                printf("请输入房间号：");
                gets(put);
                Search1(head,put);
                break;
            case 2:
                printf("请输入姓名：");
                gets(put);
                Search2(head,put);
                break;
            case 3:
                printf("请输入信息：");
                gets(put);
                Search3(head,put);
                break;
            }
            break;
        case 3:
            printf("请输入退房的房间号：");
            gets(put);
            head =Del(head,put);
            break;
        case 4:
            Prt(head);
            break;
        case 5:
            STA(head);
            break;
        case 6:
            STO(head);
            break;
        }
    }
    while(n!=0);
    printf("感谢使用本系统！");
    return 0;
}

RDT *Input(RDT *head)//建立新用户
{
    RDT *p = NULL, *pr = head;
    int i,flag,k=0,t=0;
    char number[10];
    p = (RDT *)malloc(sizeof(RDT));
    if(p==NULL)
    {
        printf("内存不够辣！\n");
        exit(0);

    }
    if(head==NULL)
    {
        head = p;
    }
    else
    {
        while(pr->next!=NULL)
        {
            pr = pr->next;
        }
        pr->next = p;
    }
    do
    {
        for (unsigned int q = 0; q < strlen(p->number); q++)
            p->number[q] = '\0' ;                            //for循环清空数组
        printf("请输入房间号(5以内数字开头，三位数):");
        scanf("%s",number);
        t=strlen(number);
        if(t!=3)
        {
            printf("请输入正确的房间号：!!!!!!!!!!!!!!!!!!!!!!!\n");
            continue;
        }
        if(number[0]-'0'<0||number[0]-'0'>5)
        {
            t = -1;
        }
        for(i=1; i<3; i++)
        {
            if(number[i]-'0'<0||number[i]-'0'>9)
            {
                t = -1;
            }
            if(t!=3)
            {
                printf("请输入正确的房间号：!!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
            }
        }
        k = Comfirm(head,number);
        if(k==1)
        {
            printf("该房间已入住\n");
            continue;
        }
        strcpy(p->number,number);
    }
    while(k==1||t!=3);
    while(getchar()!='\n');
    printf("请输入房客姓名：");
    scanf("%s",p->name);
    while(getchar()!='\n');
    printf("请输入房客性别：");
    scanf("%s",p->sex);
    while(getchar()!='\n');
    do
    {
        flag = 0;
        printf("请输入房客身份证号(18位数字)：");
        scanf("%s",p->num);
        while(getchar()!='\n');
        for(i=0; p->num[i]!='\0'; i++)
        {
            if (p->num[i]>'9'||p->num[i]<'0')
            {
                flag = 1;
                break;
            }
        }
        if (i!=18)
        {
            flag = 1;
            printf("输入有误，请重新输入");
        }
    }
    while (flag!=0);
    do
    {
        printf("请输入订房天数：");
        scanf("%d",&p->time1);
        while(getchar()!='\n');
        if(p->time1==0)     printf("您的输入有误！\n");
    }
    while(p->time1==0);
    p->next = NULL;
    printf("开房成功！(*￣3￣)╭\n");
    return head;
}

RDT *Del(RDT *head,char number[])//删除用户信息
{
    RDT *pr = head,*p = head;
    int k=0;
    if(head == NULL)
    {
        printf("什么也没有呐？\n\n\n");
        return head;
    }
    while(strcmp(number,pr->number)!=0&&pr->next==NULL)
    {
        p = pr;
        pr = pr->next;
    }
    if(pr==head)
    {
        head=pr->next;
        k++;
    }
    else
    {
        p->next = pr->next;
        k++;
    }
    free(pr);
    printf("退房成功\n\n");
    if (k==0)   printf("此房为空，无法操作\n\n\n");
    return head;
}

void Prt(RDT *head)//打印链表
{
    RDT *pr = head;
    printf("房间号    房客名        性别                 身份证号         居住天数       \n");
    do
    {

        printf("%5s%11s%11s%30s%10d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
        pr = pr->next;
    }
    while (pr!=NULL);
}

void Search1(RDT *head,char number[])//按房间号搜索
{
    RDT *pr = head;
    int k=0;
    printf("房间号    房客名        性别                 身份证号         居住天数       \n");
    do
    {
        if (strcmp(pr->number,number)==0)
        {
            printf("%5s%10s%3s%30s%3d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
            k++;
            break;
        }
        pr = pr->next;
    }
    while(pr!=NULL);
    if (k==0)   printf("Not Found！\n");
}

void Search2(RDT *head,char name[])//按姓名搜索
{
    RDT *pr = head;
    int k=0;
    printf("房间号    房客名        性别                 身份证号         居住天数       \n");
    do
    {
        if (strcmp(pr->name,name)==0)
        {
            printf("%5s%10s%3s%30s%3d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
            k++;
            break;
        }
        pr = pr->next;
    }
    while(pr!=NULL);
    if (k==0)   printf("Not Found！\n");
}

int Comfirm(RDT *head,char number[])//检测是否该房间是否已有住户
{
    RDT *pr = head;
    do
    {
        if (strcmp(pr->number,number)==0)
        {
            return 1;
        }
        pr = pr->next;
    }
    while(pr!=NULL);
    return 0;
}

void Search3(RDT *head,char name[])//模糊搜索
{
    char str[10];
    RDT *pr = head;
    int k = strlen(name),i,j,sum=0;
    printf("%d",k);
    do
    {
        for(i=0; pr->name[i+k-1]!='\0'; i++) //反复将检查点后移
        {
            for(j=0; j<k; j++) //将相同长度的字符串从pr->name中取出，放在str[]中
            {
                str[j] = pr->name[i+j];
            }
            str[j] = '\0';
            if(strcmp(str,name)==0)//如果字符串完成匹配，输出该行数据，并进行下一循环
            {
                sum++;
                printf("%5s%10s%3s%30s%3d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
                break;
            }
        }
        pr = pr->next;
    }
    while(pr!=NULL);
    if(sum==0)      printf("Not Found!");
}

void STA(RDT *head)//统计所有楼层的住房情况
{
    int i,sum=0;
    RDT *pr = NULL;
    printf("房间号    房客名        性别                 身份证号         居住天数       \n");
    for(i=0,pr = head; i<5; i++)
    {
        printf("第%d层的住户：\n",i+1);
        do
        {
            if((pr->number[0] - '0')==i+1)
            {
                printf("%5s%11s%11s%30s%10d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
                sum++;
            }
            pr = pr->next;
        }
        while(pr!=NULL);
        if(sum==0)      printf("无\n");
        pr = head;
        sum = 0;
    }
    return;
}

void STO(RDT *head)//进行文件输出
{
    FILE *fp;
    RDT *pr=head;
    fp = fopen("data.txt","a+");
    if(fp==NULL)
    {
        printf("文件打开失败！\n");
        exit(0);
    }
    do
    {
        printf("%5s%11s%11s%30s%10d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
        fprintf(fp,"%5s%11s%11s%30s%10d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
        pr = pr->next;
    }
    while(pr!=NULL);
    printf("保存成功！\n");
    fclose(fp);
    return;
}

