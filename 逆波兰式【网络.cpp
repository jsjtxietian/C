
//�沨�����ʽ����׺���ʽ��reverse polish notation
//����ʵ�ֵĹ����ǽ���׺���ʽת��Ϊ��׺���ʽ���������ֵ
//��Ҫ���õ�֪ʶ���У�isdigit������pow������system("cls")��������ջ����ʽ��ǿ��ת��

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

void shift( char notation[]);				//��׺���ʽת��Ϊ��׺���ʽ��ת������
float calculate(float a[][2],int k);		//�����׺���ʽ
int judge(char notation[]);					//�ж��������׺���ʽ�Ƿ����Ҫ��
int grade(char a);							//����������ĵȼ�
void display(float a[][2],int k);			//����Ļ����ʾ��׺���ʽ
//������
int main()									
{
	char notation [100];
	char choice;
	do
	{
		printf("��������ȷ����׺���ʽ:\n");
		printf("���磺2*3+4/3-(2+1)\n");
		scanf("%s",&notation);
		if(judge(notation))
		{			
			shift(notation);
		}
		else
			printf("��ı��ʽ�д�������ϸ��飡\n");
			
	fflush(stdin);
		printf("\n���Ƿ���Ҫ�������㣨������Y/y�������������������\n");
		scanf("%c",&choice);
		getchar();
		system("cls");
	}while(choice=='Y'||choice=='y');
	printf("\n���������ллʹ�ã�\n");
}
//�ж�����
int judge(char notation[])
{
	int i,m,num=1,p1=0,p2=0;
	for(i=0;notation[i]!='\0';i++)								//�ų����ʽ����ַ�
	{
		if(notation[i]!='('&&notation[i]!=')'&&notation[i]!='+'&&notation[i]!='-'
			&&notation[i]!='*'&&notation[i]!='/'&&!isdigit(notation[i])&&notation[i]!='.')
		{
			num=0;
			return num;
		}
	}
	if(notation[0]=='*'||notation[0]=='/'||notation[0]==')'||notation[0]=='.')	//�ų���һ���ַ�Ϊ*��/��)��.
	{
		num=0;
		return num;
	}
	for(i=0;notation[i]!='\0';i++)	  //�ų�'+'��'-'��'*'��'/','.'֮������������Լ�'+'��'-','*'��'/','.'����ֱ�Ӽ�')'
	{
		if(notation[i]!='('&&notation[i]!=')'&&!isdigit(notation[i]))
		{
			if(notation[i+1]!='('&&!isdigit(notation[i+1]))
			{
				num=0;
				return num;
			}
		}
		if(notation[i]=='('&&(notation[i+1]==')'||notation[i+1]=='.'||notation[i+1]=='*'||notation[i+1]=='/'))	
		{										//�ų�'('��')','.','*','/'һ������
			num=0;
			return num;
		}
		if(notation[i]==')'&&(notation[i+1]=='('||notation[i+1]=='.'))//�ų�')'��'('��'.'һ������
		{
			num=0;
			return num;
		}		
	}
	for(i=0;notation[i]!='\0';i++)								//С��λ���ó���4λ
	{
		if(notation[i]=='.'&&notation[i+1]!='\0'&&notation[i+2]!='\0'&&notation[i+3]!='\0'&&notation[i+4]!='\0'&&notation[i+5]!='\0')
		{
			if(isdigit(notation[i+1])&&isdigit(notation[i+2])&&isdigit(notation[i+3])&&isdigit(notation[i+4])&&isdigit(notation[i+5]))
			{
				num=0;
				return num;
			}
		}
	}
	for(i=0;notation[i]!='\0';i++)					//�ų�һ��С����������С��������
	{
		if(notation[i]=='.')
		{
			i++;
			while(isdigit(notation[i]))
			{
				i++;
			}
			if(notation[i]=='.')
			{
				num=0;
				return 0;
			}
		}
	}
	for(i=0;notation[i]!='\0';i++)					//�ų�')'���治����ֱ�Ӹ������Լ�'('ǰ�治���Լ�����
	{
		if(notation[i]==')'&&isdigit(notation[i+1]))
		{
			num=0;
			return num;
		}
		if(isdigit(notation[i])&&notation[i+1]=='('	)
		{
			num=0;
			return num;
		}
	}
	for(i=0;notation[i]!='\0';i++)			//Լ�����ֵ�λ��һ�����Ϊ��λ
	{
		if(isdigit(notation[i]))
		{
			m=0;							//�������������ֵ�λ��Ϊ7
			while(isdigit(notation[i])||notation[i]=='.')
			{
				i++;
				m++;
				if(notation[i]=='.')
				{
					m--;
				}
			}
			if(m>7)
			{
				num=0;
				return num;
			}
		}
	}
	for(i=0;notation[i]!='\0';i++)		//'('��')'��Ҫ��Դ���
	{
		if(notation[i]=='(')
			p1++;
		if(notation[i]==')')
			p2++;
		if(p1!=p2)
		{
			num=0;
			return num;
		}
	}
	return num;

}
//ת������
void shift( char notation[])
{
	char s1[100];
	s1[0]='#';
	float s2[100][2];				//��һά�ź�׺���ʽ��Ԫ�أ��ڶ�ά��ʾС�����λ���Լ��Ƿ��������
	int i=0,j=1,k=0,t=0;
	float sum,num1=0,num2=0;		//num1Ϊ�洢����λnum2Ϊ�洢С��λ
	while(notation[i]!='\0')
	{
		if(i==0&&notation[i]=='+')	//��һλΪ���ŵ����
		{
			if(isdigit(notation[++i]))
			{
				num1=0;						//��������
				while(isdigit(notation[i]))
				{
					num1=num1*10+(notation[i]-'0');		//notation[i]-'0'���Խ��ַ�ת��Ϊ����0~9
					i++;
				}
				num2=0;						//С������
				t=0;
				if(notation[i]=='.')
				{				
					i++;				
					while(isdigit(notation[i]))
					{
						num2=float (num2+pow(0.1,++t)*(notation[i]-'0'));
						i++;
					}
				}
				s2[k++][0]=float(num1+num2);
				s2[k-1][1]=float(t);
			}
		}
		if(i==0&&notation[i]=='-')	//��һλΪ���ŵ��������������������
		{
			if(isdigit(notation[++i]))
			{
				num1=0;
				while(isdigit(notation[i]))
				{
					num1=(-1)*num1*10+(-1)*(notation[i]-'0');
					i++;
				}
				num2=0;
				t=0;
				if(notation[i]=='.')
				{				
					i++;				
					while(isdigit(notation[i]))
					{
						num2=float(num2+(-1)*pow(0.1,++t)*(notation[i]-'0'));
						i++;
					}
				}
				s2[k++][0]=float(num1+num2);
				s2[k-1][1]=float(t);
			}
		}
		if(isdigit(notation[i]))	//��ǰ�ַ�Ϊ���ֵ������Ϊ���ŵ����һ��
		{
			num1=0;
			while(isdigit(notation[i]))
			{
				num1=num1*10+(notation[i]-'0');
				i++;
			}
			num2=0;
			t=0;
			if(notation[i]=='.')
			{				
				i++;				
				while(isdigit(notation[i]))
				{
					num2=float(num2+pow(0.1,++t)*(notation[i]-'0'));
					i++;
				}
			}
			s2[k++][0]=float(num1+num2);
			s2[k-1][1]=float(t);
		}
		if(notation[i]=='+'||notation[i]=='-'||notation[i]=='*'||notation[i]=='/')
		{								//��ǰ���ַ�Ϊ������ʱ�����s1��վ��Ϊ'('���ַ�ֱ������s1
			if(s1[j-1]=='(')
			{		
				s1[j++]=notation[i++];
			}
		}
		if(notation[i]=='+'||notation[i]=='-'||notation[i]=='*'||notation[i]=='/')
		{								//��ǰ�ַ�Ϊ������ʱ����ͨ�����
			if(grade(notation[i])>grade(s1[j-1]))
			{
				s1[j++]=notation[i++];	
			}
			else
			{			
				s2[k++][0]=s1[--j];
				s2[k-1][1]=-1;
				s1[j++]=notation[i++];
			}
		}
		if(notation[i]=='(')			//��ǰ�ַ�Ϊ'('�����
		{	
			s1[j++]=notation[i++];
			if(notation[i]=='+')		//'('������ŵ����
			{
				if(isdigit(notation[++i]))
				{
					num1=0;
					while(isdigit(notation[i]))
					{
						num1=num1*10+(notation[i]-'0');
						i++;
					}
					num2=0;
					t=0;
					if(notation[i]=='.')
					{				
						i++;				
						while(isdigit(notation[i]))
						{
							num2=float(num2+pow(0.1,++t)*(notation[i]-'0'));
							i++;
						}
					}
					s2[k++][0]=float(num1+num2);
					s2[k-1][1]=float(t);
				}
			}
			if(notation[i]=='-')	//'('������ŵ����
			{
				
				if(isdigit(notation[++i]))
				{
					num1=0;
					while(isdigit(notation[i]))
					{
						num1=float((-1)*num1*10+(-1)*(notation[i]-'0'));
						i++;
					}
					num2=0;
					t=0;
					if(notation[i]=='.')
					{				
						i++;				
						while(isdigit(notation[i]))
						{
							num2=float(num2+(-1)*pow(0.1,++t)*(notation[i]-'0'));
							i++;
						}
					}
					s2[k++][0]=float(num1+num2);
					s2[k-1][1]=float(t);
				}	
			}			
		}
		if(notation[i]==')')		//��ǰ�ַ�Ϊ')'�����
		{
			while(s1[--j]!='(')
			{
				s2[k++][0]=s1[j];
				s2[k-1][1]=-1;
			}
			i++;
		}
	}
	while(j>0&&s1[--j]!='#')	//���ν�s1�еĳ���'#'������в�������ջ���൱������ɨβ����
	{
		s2[k++][0]=s1[j];
		s2[k-1][1]=-1;
	}
	printf("\n��׺���ʽ���沨�����ʽ����\n");
	display(s2,k-1);
	printf("\n���ʽ��ֵΪ��\n");
	sum=calculate(s2,k-1);
	printf("%7.4f",sum);
}
//���㺯��
float calculate(float a[][2],int k)
{
	int i,t=0,j=k;
	float b[100][2],c[100];
	for(i=k;i>=0;i--)
	{
		b[i][0]=a[k-i][0];
		b[i][1]=a[k-i][1];
	}
	i=k;
	while(j>=0)
	{
		if(b[i][1]!=-1)
		{
			c[t]=float (b[i][0]);			
			j--;
			i--;
			t++;
		}
		if(b[i][1]==-1)	//ÿ������һ���������ջ���������������ջ�������㣬Ȼ������ջ	
		{
			if(int(b[i][0])=='+')
			{
				c[t-2]=float (c[t-2]+c[t-1]);
			}
			if(int(b[i][0])=='-')
			{	
				c[t-2]=float (c[t-2]-c[t-1]);
			}
			if(int(b[i][0])=='*')
			{
				c[t-2]=float (c[t-2]*c[t-1]);
			}
			if(int(b[i][0])=='/')
			{
				c[t-2]= float (c[t-2]/c[t-1]);
			}
			j--;
			i--;
			t--;
		}
	}
	return c[0];	//���㵽���ջ�е�Ԫ�ؼ�Ϊ���
}
//�ȼ�����
int grade(char a)	//��������������ȼ�
{
	if(a=='#')
		return 0;
	if(a=='(')
		return 1;
	if(a=='-'||a=='+')
		return 2;
	if(a=='*'||a=='/')
		return 3;
	if(a==')')
		return 4;
	else 
		return 5;
}
//��ʾ����	
void display(float a[][2],int k)
{
	int i;
	for(i=0;i<=k;i++)
	{
		if(a[i][1]==0)
			printf(" %d",int(a[i][0]));
		if(a[i][1]==1)
			printf(" %7.1f",a[i][0]);
		if(a[i][1]==2)
			printf(" %7.2f",a[i][0]);
		if(a[i][1]==3)
			printf(" %7.3f",a[i][0]);
		if(a[i][1]==4)
			printf(" %7.4f",a[i][0]);
		if(a[i][1]==-1)
			printf(" %c",int (a[i][0]));
	}
}


