// ��ϣ��Ҳ��ɢ�б�ͨ��ɢ�к���������ֵ�����Ĵ洢λ����ϵ��������ͨ�����ĵ��������Ԫ��ʵ�֣�
// �Ӷ���߷����ٶȡ������в�ȡ�Ľ����ͻ�İ취�ǽ���һ�����������λ�õĺ��棬����ɢ�к���ֵΪ���λ�õ�Ԫ�ض���ӵ���������У�
//��ʵ���˽��ļ�������ĸa-z���࣬�����ִ�Сд���ҿ��Դ�ͷ������Ҳ���Դ�β��׷�ӣ��������������λ�ú����ٹ�һ��ɢ�б�
//����������洢���ڵ㣬��������ͻ�󼴽��ڵ���������С�Ȼ�������ʾ���е��ļ�����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 26
#define FILENAMELENGTH 20
#define TRUE 1
#define FALSE 0

struct file
{
    char name[FILENAMELENGTH];
    struct file *next;
};

struct file * files[HASHSIZE];

/**����д�ַ�תΪСд��ĸ���������й�ϣ�����ִ�Сд*/
char case_insensitive(char ch)
{
    if(ch<'a') 
        return ch - 'A' + 'a';
    return ch;
}

/**��ɳ�ʼ������*/
void init()
{
    int i;
    for(i = 0 ; i < HASHSIZE; i++)
        files[i] = NULL;
}

/**��ϣ�����������ڹ�ϣ���е�λ�ã���ϣ��������ļ�������ĸa-z����*/
int hash(char *s)
{
   return case_insensitive(s[0]) - 'a';
}

/**��ѯĳ���ļ����ڹ�ϣ�ṹ���Ƿ��Ѵ���*/
int search(char *s)
{
    int num = hash(s);
    if(files[num] != NULL) //�����ϣ���գ��ѳ����Ը��ļ�������ĸ��ͷ���ļ���
    {
        struct file *p = files[num]; //pָ�������е�һ���ڵ�
        while(p != NULL)
        {
            if(strcmp(p->name,s) == 0)
                return TRUE;
            p = p->next;
        }
    }
    return FALSE;
}

/**����ļ����ڹ�ϣ�ṹ�в����ڣ������*/
void insert(char *s)
{
    if(search(s) == FALSE)
    {
        int num = hash(s);
        struct file *new_node = (struct file*)malloc(sizeof(struct file));
        strcpy(new_node->name,s);
        if(files[num] == NULL) //�������Ϊ�գ�����Ϊ��һ���ڵ�
        {
            files[num] = new_node;
            files[num]->next = NULL;
        }
        else //��������գ�������ڵ�һ���ڵ�λ��
        {
            new_node->next = files[num];
            files[num] = new_node;
        }
    }
    // else do nothing;
}

/**��ʾ�ù�ϣ�ṹ�д洢�������ļ���*/
void show_all()
{
    int i;
    struct file *p = NULL;
    for(i = 0 ; i < HASHSIZE ; i++)
    {
        p = files[i];
        if(p != NULL)
        {
            printf("For file begins with %c:\n",i + 'a');
            while(p != NULL)
            {
                printf("%s\n",p->name);
                p = p->next;
            }
            printf("\n");
        }
    }
}

int main()
{
    char *file_names[] = {"apple","because","song","Dan","discuz","cartoon","nobody","android","information","love","like","No","nothing","like","alone","nothing"};
    int len = sizeof(file_names) / sizeof(char *); //����ַ�������ĳ���
    int i;
    for(i = 0; i < len; i++)
        insert(file_names[i]);
    show_all();
    return 0;
}

