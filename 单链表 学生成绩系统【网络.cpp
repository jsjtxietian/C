
#include <stdlib.h>  
#include <stdio.h>  
  

#define LEN sizeof(struct student)  
  
struct student  
{  
    int num;              //ѧ��   
    float score;          //������������Ϣ���Լ��������������ֶ�  
    struct student *next;       //ָ����һ�ڵ��ָ��  
};  
  
int n;  //�ڵ�����   
/* 
========================== 
���ܣ�����n���ڵ������ 
���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
struct student *Create()  
{  
    struct student *head;       //ͷ�ڵ�  
    struct student *p1 = NULL;  //p1���洴�����½ڵ�ĵ�ַ  
    struct student *p2 = NULL;  //p2����ԭ�������һ���ڵ�ĵ�ַ  
  
    n = 0;          //����ǰ����Ľڵ�����Ϊ0��������  
    p1 = (struct student *) malloc (LEN);   //����һ���½ڵ�  
    p2 = p1;            //����ڵ㿪�ٳɹ�����p2�Ȱ�����ָ�뱣�������Ա�����  
  
    if(p1==NULL)        //�ڵ㿪�ٲ��ɹ�  
    {  
        printf ("\nCann't create it, try it again in a moment!\n");  
        return NULL;  
    }  
    else                //�ڵ㿪�ٳɹ�  
    {  
        head = NULL;        //��ʼheadָ��NULL  
        printf ("Please input %d node -- num,score: ", n + 1);  
        scanf ("%d %f", &(p1->num), &(p1->score));    //¼������  
    }  
    while(p1->num != 0)      //ֻҪѧ�Ų�Ϊ0���ͼ���¼����һ���ڵ�  
    {  
        n += 1;         //�ڵ���������1��  
        if(n == 1)      //����ڵ�������1����headָ��մ����Ľڵ�p1  
        {  
            head = p1;  
            p2->next = NULL;  //��ʱ��p2����p1,Ҳ����p1->nextָ��NULL��  
        }  
        else  
        {  
            p2->next = p1;   //ָ���ϴ�����ոտ��ٵ��½ڵ�  
        }  
  
        p2 = p1;            //��p1�ĵ�ַ��p2������Ȼ��p1�����µĽڵ�  
  
        p1 = (struct student *) malloc (LEN);  
        printf ("Please input %d node -- num,score: ", n + 1);  
        scanf ("%d %f", &(p1->num), &(p1->score));  
    }  
    p2->next = NULL;     //�˾���Ǹ��ݵ�����������һ���ڵ�Ҫָ��NULL  
  
    free(p1);           //p1->numΪ0��ʱ��������whileѭ���������ͷ�p1  
    p1 = NULL;          //�ر�Ҫ���ǰ��ͷŵı��������ΪNULL,����ͱ��"Ұָ��"������ַ��ȷ����ָ��  
    return head;        //���ش��������ͷָ��   
}  
  
  
/* 
=========================== 
 ���ܣ�����ڵ� 
 ���أ� void 
=========================== 
*/  
void Print(struct student *head)  
{  
    struct student *p;  
    printf ("\nNow , These %d records are:\n", n);  
    p = head;  
    if(head != NULL)        //ֻҪ���ǿ�������������������нڵ�  
    {  
        printf("head is %o\n", head);    //���ͷָ��ָ��ĵ�ַ  
        do  
        {  
            /* 
            �����Ӧ��ֵ����ǰ�ڵ��ַ�����ֶ�ֵ����ǰ�ڵ����һ�ڵ��ַ�� 
            ����������ڶ������󿴵�һ�����������ڼ�����еĴ洢�ṹ�������� 
            ��Ƶ�ͼʾ��һģһ���ġ� 
            */  
            printf ("%o   %d   %5.1f   %o\n", p, p->num, p->score, p->next);  
            p = p->next;     //�Ƶ���һ���ڵ�  
        }  
        while (p != NULL);  
    }  
}  
  
/* 
========================== 
 ���ܣ�ɾ��ָ���ڵ� 
  (��������ɾ��ָ��ѧ�ŵĽڵ�) 
 ���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
struct student *Del (struct student *head, int num)  
{  
    struct student *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ  
    struct student *p2;     //p2���浱ǰ�����Ľڵ�ĵ�ַ  
    if (head == NULL)       //�ǿ��������ͼ3��⣩  
    {  
        printf ("\nList is null!\n");  
        return head;  
    }  
  
    //��λҪɾ���Ľڵ�  
    p1 = head;  
    while (p1->num != num && p1->next != NULL)    //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬�ͼ���������  
    {  
        p2 = p1;            //���浱ǰ�ڵ�ĵ�ַ  
        p1 = p1->next;       //����һ���ڵ�  
    }  
  
    if(p1->num==num)     //�ҵ��ˡ������ͼ4��5��⣩  
    {  
        if (p1 == head)     //���Ҫɾ���Ľڵ��ǵ�һ���ڵ�  
        {  
            head = p1->next; //ͷָ��ָ���һ���ڵ�ĺ�һ���ڵ㣬Ҳ���ǵڶ����ڵ㡣������һ���ڵ�Ͳ��������У���ɾ��  
        }  
        else            //����������ڵ㣬����ԭ��ָ��ǰ�ڵ��ָ�룬ָ��������һ���ڵ㣬���ɾ��  
        {  
            p2->next = p1->next;  
        }  
  
        free (p1);      //�ͷŵ�ǰ�ڵ�  
        p1 = NULL;  
        printf ("\ndelete %ld success!\n", num);  
        n -= 1;         //�ڵ�������1��  
    }  
    else                //û���ҵ�  
    {  
        printf ("\n%ld not been found!\n", num);  
    }  
  
    return head;  
}  
  
//��������  
int DestroyList(struct student *head)  
{  
    struct student *p;  
    if(head==NULL)  
        return 0; 
    while(head)  
    {  
        p=head->next;  
        free(head);  
        head=p;  
    }   
    return 1;
}  
  
/* 
========================== 
 ���ܣ�����ָ���ڵ�ĺ��� 
  (��������ָ��ѧ�ŵĽڵ�) 
 ���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
struct student *Insert (struct student *head, int num, struct student *node)  
{  
    struct student *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ  
    if (head == NULL)       //�����ͼʾ7��⣩  
    {  
        head = node;  
        node->next = NULL;  
        n += 1;  
        return head;  
    }  
  
    p1 = head;  
    while(p1->num != num && p1->next != NULL)  //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬����������  
    {  
        p1 = p1->next;       //����һ���ڵ�  
    }  
  
    if (p1->num==num)        //�ҵ��ˣ����ͼʾ8��⣩  
    {  
        node->next = p1->next;    //��Ȼnode����һ�ڵ���ԭp1��next  
        p1->next = node;     //�����ԭp1����һ�ڵ����Ҫ�����node  
        n += 1;         //�ڵ���������1��  
    }  
    else  
    {  
        printf ("\n%ld not been found!\n", num);  
    }  
    return head;  
}  
  
/* 
========================== 
 ���ܣ�����ڵ� 
  (�����ͷ��������β�������β���ͷ) 
 ���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
  
struct student *Reverse (struct student *head)  
{  
    struct student *p;      //��ʱ�洢  
    struct student *p1;     //�洢���ؽ��  
    struct student *p2;     //Դ����ڵ�һ��һ��ȡ  
  
    p1 = NULL;          //��ʼ�ߵ�ʱ���ѵߵ��Ĳ���Ϊ��  
    p2 = head;          //p2ָ�������ͷ�ڵ�  
    while(p2 != NULL)  
    {  
        p = p2->next;  
        p2->next = p1;  
        p1 = p2;  
        p2 = p;  
    }  
    head = p1;  
    return head;  
}  
/* 
========================== 
 ���ܣ�ѡ������(��С����) 
 ���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
struct student *SelectSort (struct student *head)  
{  
    struct student *first;     //���к��������ı�ͷָ��  
    struct student *tail;      //���к��������ı�βָ��  
    struct student *p_min;     //������ֵ��С�Ľڵ��ǰ���ڵ��ָ��  
    struct student *min;       //�洢��С�ڵ�  
    struct student *p;         //��ǰ�ȽϵĽڵ�  
  
    first = NULL;  
    while(head != NULL)       //���������Ҽ�ֵ��С�Ľڵ�  
    {  
        //ע�⣺����for����������ѡ������˼��ĵط�  
        for (p = head, min = head; p->next != NULL; p = p->next)  //ѭ�����������еĽڵ㣬�ҳ���ʱ��С�Ľڵ�  
        {  
            if (p->next->num < min->num)     //�ҵ�һ���ȵ�ǰminС�Ľڵ�  
            {  
                p_min = p;        //�����ҵ��ڵ��ǰ���ڵ㣺��Ȼp->next��ǰ���ڵ���p  
                min = p->next;     //�����ֵ��С�Ľڵ�  
            }  
        }  
  
        //����for�������󣬾�Ҫ�������£�һ�ǰ����������������У����Ǹ�����Ӧ�������жϣ��������뿪ԭ��������  
  
        //��һ����  
        if (first == NULL)     //�����������Ŀǰ����һ��������  
        {  
            first = min;        //��һ���ҵ���ֵ��С�Ľڵ�  
            tail = min;        //ע�⣺βָ������ָ������һ���ڵ�  
        }  
        else              //�����������Ѿ��нڵ�  
        {  
            tail->next = min;    //�Ѹ��ҵ�����С�ڵ�ŵ���󣬼���βָ���nextָ����  
            tail = min;           //βָ��ҲҪָ����  
        }  
  
        //�ڶ�����  
        if (min == head)            //����ҵ�����С�ڵ���ǵ�һ���ڵ�  
        {  
            head = head->next;      //��Ȼ��headָ��ԭhead->next,���ڶ����ڵ㣬��OK  
        }  
        else            //������ǵ�һ���ڵ�  
        {  
            p_min->next = min->next;  //ǰ����С�ڵ��nextָ��ǰmin��next,��������min�뿪��ԭ����  
        }  
    }  
  
    if (first != NULL)      //ѭ�������õ���������first  
    {  
        tail->next = NULL;   //������������һ���ڵ��nextӦ��ָ��NULL  
    }  
    head = first;  
    return head;  
}  
  
  
/* 
========================== 
 ���ܣ�ֱ�Ӳ�������(��С����) 
 ���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
struct student *InsertSort (struct student *head)  
{  
    struct student *first;    //Ϊԭ����ʣ������ֱ�Ӳ�������Ľڵ�ͷָ��  
    struct student *t;        //��ʱָ�����������ڵ�  
    struct student *p,*q;     //��ʱָ�����  
  
    first = head->next;      //ԭ����ʣ������ֱ�Ӳ�������Ľڵ������ɸ���ͼ12�����  
    head->next = NULL;       //ֻ����һ���ڵ����������������ɸ���ͼ11�����  
  
    while(first != NULL)        //����ʣ�����������  
    {  
        //ע�⣺����for����������ֱ�Ӳ�������˼��ĵط�  
        for (t = first, q = head; ((q != NULL) && (q->num < t->num)); p = q, q = q->next);  //����ڵ��������������Ҳ����λ��  
  
        //�˳�forѭ���������ҵ��˲����λ�ã�Ӧ�ý�t�ڵ���뵽p�ڵ�֮��q�ڵ�֮ǰ  
        //ע�⣺��������˵����仰���Էŵ�����ע���˵��Ǹ�λ��ҲӦ�öԵģ����Ǿ��ǲ��ܡ�ԭ���������������ĵ�3������֪����  
        //����Ĳ�����ǽ�t�ڵ㼴��first�ڵ���뵽p�ڵ�֮���Ѿ��ı���first�ڵ㣬����first�ڵ�Ӧ���ڱ��޸�֮ǰ�����ƶ������ܷŵ�����ע�͵�λ����ȥ  
        first = first->next; //���������еĽڵ��뿪���Ա������뵽����������  
  
        if (q == head)      //���ڵ�һ���ڵ�֮ǰ  
        {  
            head = t;  
        }  
        else            //p��q��ǰ��  
        {  
            p->next = t;  
        }  
        t->next = q;     //��ɲ��붯��  
        //first = first->next;   
    }  
    return head;  
}  
  
/* 
========================== 
 ���ܣ�ð������(��С����) 
 ���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
struct student *BubbleSort (struct student *head)  
{  
    struct student *endpt;    //����ѭ���Ƚ�  
    struct student *p;        //��ʱָ�����  
    struct student *p1,*p2;  
  
    p1 = (struct student *) malloc (LEN);  
    p1->next = head;        //ע����⣺��������һ���ڵ㣬���ڵ�һ���ڵ��ǰ�棬��Ҫ��Ϊ�˱��ڱȽϡ���Ϊ��һ���ڵ�û��ǰ�������ǲ��ܽ�����ַ  
    head = p1;                 //��headָ��p1�ڵ㣬������ɺ������ٰ�p1�ڵ��ͷŵ�  
  
    for (endpt = NULL; endpt != head; endpt = p)    //��ϵ�6�����  
    {  
        for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)  
        {  
            if (p1->next->num > p1->next->next->num)  //���ǰ��Ľڵ��ֵ�Ⱥ���ڵ�ļ�ֵ���򽻻�  
            {  
                p2 = p1->next->next;    //��ϵ�1�����  
                p1->next->next = p2->next;   //��ϵ�2�����  
                p2->next = p1->next;   //��ϵ�3�����  
                p1->next = p2;     //��ϵ�4�����  
                p = p1->next->next;   //��ϵ�6�����  
            }  
        }  
    }  
  
    p1 = head;              //��p1����Ϣȥ��  
    head = head->next;       //��headָ�������ĵ�һ���ڵ�  
    free (p1);          //�ͷ�p1  
    p1 = NULL;          //p1��ΪNULL����֤��������Ұָ�롱������ַ��ȷ����ָ�����  
  
    return head;  
}  
  
/* 
========================== 
 ���ܣ��������������ĳ���ڵ�ĺ���(��С����) 
 ���أ�ָ�������ͷ��ָ�� 
========================== 
*/  
  
struct student *SortInsert (struct student *head, struct student *node)  
{  
    struct student *p;      //p���浱ǰ��Ҫ���Ľڵ�ĵ�ַ  
    struct student *t;      //��ʱָ�����  
  
    if (head == NULL)       //����յ���������  
    {  
        head = node;  
        node->next = NULL;  
        n += 1;         //������ϣ��ڵ�������  
        return head;  
    }  
  
    p = head;             //��������Ϊ��  
    while(p->num < node->num && p != NULL)    //pָ��Ľڵ��ѧ�űȲ���ڵ��ѧ��С��������������NULL  
    {  
        t = p;            //���浱ǰ�ڵ��ǰ�����Ա�����жϺ���  
        p = p->next;     //����һ���ڵ�  
    }  
  
    if (p == head)      //�պò����һ���ڵ�֮ǰ  
    {  
        node->next = p;  
        head = node;  
    }  
    else                 //���������ڵ�֮��  
    {  
        t->next = node;      //��node�ڵ�ӽ�ȥ  
        node->next = p;  
    }  
    n += 1;         //������ϣ��ڵ�������1  
  
    return head;  
}  
  
/* 
���Ϻ����Ĳ��Գ��� 
��ʾ�����ݲ��Ժ����Ĳ�ͬע����Ӧ�ĳ���Σ���Ҳ��һ�ֲ��Է����� 
*/  
int main()  
{  
    struct student *head;  
    struct student *stu;  
    int thenumber;  
  
    // ����Create()��Print()   
    head = Create();  
    Print(head);  
  
    //����Del()  
    printf("\nWhich one delete: ");  
    scanf("%d",&thenumber);  
    head = Del(head,thenumber);  
    Print(head);  
  
    //����Insert()  
    stu = (struct student *)malloc(LEN);  
    printf("\nPlease input insert node -- num,score: ");  
    scanf("%d %f",&stu->num,&stu->score);  
    printf("\nInsert behind num: ");  
    scanf("%d",&thenumber);  
    head = Insert(head,thenumber,stu);  
    Print(head);  
  
    //����Reverse()  
    printf("\nReverse the LinkList: \n");  
    head = Reverse(head);  
    Print(head);  
  
    //����SelectSort()  
    printf("\nSelectSort the LinkList: \n");  
    head = SelectSort(head);  
    Print(head);  
  
    //����InsertSort()  
    printf("\nInsertSort the LinkList: \n");  
    head = InsertSort(head);  
    Print(head);  
  
    //����BubbleSort()  
    printf("\nBubbleSort the LinkList: \n");  
    head = BubbleSort(head);  
    Print(head);  
  
    printf("\nSortInsert the LinkList: \n");  
    //����SortInsert():���洴����������ڵ�ʱ��ע��ѧ��num��С�����˳��  
    stu = (struct student *)malloc(LEN);  
    printf("\nPlease input insert node -- num,score: ");  
    scanf("%d %f",&stu->num,&stu->score);  
    head = SortInsert(head,stu);  
    Print(head);  
  
    //��������  
    DestroyList(head);  
  
    printf ("\n");  
    system ("pause");
	return 0;  
}  

