#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

typedef struct resident//����ṹ�壺�����û���Ϣ
{
    char number[10];//�����
    char name[10];//��������
    char sex[10];//�����Ա�
    char num[25];//�������֤��
    int time1;//��ס����
    struct resident *next;//����ָ����һ�ڵ�
} RDT;

RDT *Input(RDT *head);//�������û�
RDT *Del(RDT *head,char number[]);//ɾ���û���Ϣ
void Prt(RDT *p);//��ӡ��������
void Search1(RDT *head,char number[]);//�����������
void Search2(RDT *head,char name[]);//����������
void Search3(RDT *head,char name[]);//ģ������
int Comfirm(RDT *head,char number[]);//����Ƿ�÷����Ƿ�����ס��
void STA(RDT *head);//ͳ������¥���ס�����
void STO(RDT *head);//����������ݴ�����data.txt�ļ���

int main()
{
    PlaySoundA("hmbb.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
    printf(" ������������������������������������������������������������������������������������-----------------------------------");
    printf("|                                               ��ӭ����XXX�Ƶ����ϵͳ                                                |");
    printf(" ������������������������������������������������������������������������������������-----------------------------------");
    int n;
    RDT *head = NULL;
    char put[10];
    do
    {
        printf("��ѡ����Ҫ���еĲ���\n");
        printf("1��������Ϣ¼��\n");
        printf("2����Ϣ����\n");
        printf("3�������˷�\n");
        printf("4���������ס����Ϣ\n");
        printf("5����ǰס�����\n");
        printf("6�����浱ǰ��������\n");
        printf("0���˳�ϵͳ\n");
        scanf("%d",&n);
        while(getchar()!='\n');
        while(n<0||n>6)
        {
            printf("����������������������\n");
            scanf("%d",&n);
            while(getchar()!='\n');
        }
        switch (n)
        {
        case 1:
            head = Input(head);
            break;
        case 2:
            printf("��������Ҫ�Ĳ��ҷ�ʽ��\n");
            printf("1������Ų���\n");
            printf("2����������\n");
            printf("3��ģ������\n");
            scanf("%d",&n);
            while(getchar()!='\n');
            while(n<0||n>3)
            {
                printf("����������������������\n");
                scanf("%d",&n);
                while(getchar()!='\n');
            }
            switch(n)
            {
            case 1:
                printf("�����뷿��ţ�");
                gets(put);
                Search1(head,put);
                break;
            case 2:
                printf("������������");
                gets(put);
                Search2(head,put);
                break;
            case 3:
                printf("��������Ϣ��");
                gets(put);
                Search3(head,put);
                break;
            }
            break;
        case 3:
            printf("�������˷��ķ���ţ�");
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
    printf("��лʹ�ñ�ϵͳ��");
    return 0;
}

RDT *Input(RDT *head)//�������û�
{
    RDT *p = NULL, *pr = head;
    int i,flag,k=0,t=0;
    char number[10];
    p = (RDT *)malloc(sizeof(RDT));
    if(p==NULL)
    {
        printf("�ڴ治������\n");
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
            p->number[q] = '\0' ;                            //forѭ���������
        printf("�����뷿���(5�������ֿ�ͷ����λ��):");
        scanf("%s",number);
        t=strlen(number);
        if(t!=3)
        {
            printf("��������ȷ�ķ���ţ�!!!!!!!!!!!!!!!!!!!!!!!\n");
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
                printf("��������ȷ�ķ���ţ�!!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
            }
        }
        k = Comfirm(head,number);
        if(k==1)
        {
            printf("�÷�������ס\n");
            continue;
        }
        strcpy(p->number,number);
    }
    while(k==1||t!=3);
    while(getchar()!='\n');
    printf("�����뷿��������");
    scanf("%s",p->name);
    while(getchar()!='\n');
    printf("�����뷿���Ա�");
    scanf("%s",p->sex);
    while(getchar()!='\n');
    do
    {
        flag = 0;
        printf("�����뷿�����֤��(18λ����)��");
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
            printf("������������������");
        }
    }
    while (flag!=0);
    do
    {
        printf("�����붩��������");
        scanf("%d",&p->time1);
        while(getchar()!='\n');
        if(p->time1==0)     printf("������������\n");
    }
    while(p->time1==0);
    p->next = NULL;
    printf("�����ɹ���(*��3��)�q\n");
    return head;
}

RDT *Del(RDT *head,char number[])//ɾ���û���Ϣ
{
    RDT *pr = head,*p = head;
    int k=0;
    if(head == NULL)
    {
        printf("ʲôҲû���ţ�\n\n\n");
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
    printf("�˷��ɹ�\n\n");
    if (k==0)   printf("�˷�Ϊ�գ��޷�����\n\n\n");
    return head;
}

void Prt(RDT *head)//��ӡ����
{
    RDT *pr = head;
    printf("�����    ������        �Ա�                 ���֤��         ��ס����       \n");
    do
    {

        printf("%5s%11s%11s%30s%10d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
        pr = pr->next;
    }
    while (pr!=NULL);
}

void Search1(RDT *head,char number[])//�����������
{
    RDT *pr = head;
    int k=0;
    printf("�����    ������        �Ա�                 ���֤��         ��ס����       \n");
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
    if (k==0)   printf("Not Found��\n");
}

void Search2(RDT *head,char name[])//����������
{
    RDT *pr = head;
    int k=0;
    printf("�����    ������        �Ա�                 ���֤��         ��ס����       \n");
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
    if (k==0)   printf("Not Found��\n");
}

int Comfirm(RDT *head,char number[])//����Ƿ�÷����Ƿ�����ס��
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

void Search3(RDT *head,char name[])//ģ������
{
    char str[10];
    RDT *pr = head;
    int k = strlen(name),i,j,sum=0;
    printf("%d",k);
    do
    {
        for(i=0; pr->name[i+k-1]!='\0'; i++) //�������������
        {
            for(j=0; j<k; j++) //����ͬ���ȵ��ַ�����pr->name��ȡ��������str[]��
            {
                str[j] = pr->name[i+j];
            }
            str[j] = '\0';
            if(strcmp(str,name)==0)//����ַ������ƥ�䣬����������ݣ���������һѭ��
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

void STA(RDT *head)//ͳ������¥���ס�����
{
    int i,sum=0;
    RDT *pr = NULL;
    printf("�����    ������        �Ա�                 ���֤��         ��ס����       \n");
    for(i=0,pr = head; i<5; i++)
    {
        printf("��%d���ס����\n",i+1);
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
        if(sum==0)      printf("��\n");
        pr = head;
        sum = 0;
    }
    return;
}

void STO(RDT *head)//�����ļ����
{
    FILE *fp;
    RDT *pr=head;
    fp = fopen("data.txt","a+");
    if(fp==NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(0);
    }
    do
    {
        printf("%5s%11s%11s%30s%10d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
        fprintf(fp,"%5s%11s%11s%30s%10d\n",pr->number,pr->name,pr->sex,pr->num,pr->time1);
        pr = pr->next;
    }
    while(pr!=NULL);
    printf("����ɹ���\n");
    fclose(fp);
    return;
}

