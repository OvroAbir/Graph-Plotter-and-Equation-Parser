#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define input_size 200
#define PI 3.14159
char token_eqn[200][201];
int find_target(char str[],int start,int serial,int mode)
{
    // mode 1 finds the end of brackets.
    // mode 2 finds the starting of brackets.
    int pos=-1,i,len,serial_temp=serial;
    len=strlen(str);
    for(i=start;i<len && mode==1;i++)
    {
        if(str[i]==')' && serial_temp==serial)
        {
            pos=i-1;
            break;
        }
        else if(str[i]=='(')
            serial_temp++;
        else if(str[i]==')')
            serial_temp--;
    }
    for(i=start;i<len && mode==2;i++)
    {
        if(str[i]=='(')
        {
            pos=i-2;
            break;
        }
    }
    return pos;
}
void n_strcpy(char from_str[],char to_str[],int pos1,int pos2)
{
    int i,j;
    for(i=pos1,j=0;i<=pos2;i++,j++)
        to_str[j]=from_str[i];
    to_str[j]='\0';
}
void leftShift_num(double array[],int len,int start_pos)
{
    int i;
    for(i=start_pos;i<len-1;i++)//the element of the starting pos will be erased
        array[i]=array[i+1];
    array[len-1]=0;
    //return len-1;
}
int leftShift_str(char array[],int len,int start_pos)
{
    int i;
    for(i=start_pos;i<len-1;i++)//the element of the starting pos will be erased
        array[i]=array[i+1];
    array[len-1]='\0';
    return len-1;
}
double ultimate_value(char ch, double val1,double val2)
{
    if(ch=='+')
        return val1+val2;
    if(ch=='-')
        return val1-val2;
    if(ch=='*')
        return val1*val2;
    if(ch=='/')
        return val1/val2;
    if(ch=='^')
        return pow(val1,val2);
}
int count_sign(char str1[],char sign[])
{
    int i,count=0,len,depth=0;
    len=strlen(str1);
    for(i=0;i<len;i++)
    {
        if(str1[i]=='(')
            depth++;
        else if(str1[i]==')')
            depth--;
        else if((str1[i]=='+' || str1[i]=='-' || str1[i]=='*' || str1[i]=='/' || str1[i]=='^') && depth==0)
        {
            sign[count]=str1[i];
            count++;
        }
    }
    return count;
}

double ff(char str[],double x, double y)
{

    if(strcmp(str,"x")==0)
        return x;
    if(strcmp(str,"y")==0)
        return y;
    return atof(str);
}

int strTok(char str1[],char str2[])//returns how many substrings are there
{
    int i,j,len1,len2,len3=0,flag1=0,count=0;
    len1=strlen(str1);
    len2=strlen(str2);
    for(i=0;i<=len1;i++)
    {
        flag1=0;
        for(j=0;j<len2;j++)
        {
            if(str1[i]==str2[j])
                flag1=1;
		}
        if(flag1==0)
        {
            token_eqn[count][len3]=str1[i];
            len3++;
        }
        else
        {
            token_eqn[count][len3]='\0';
            count++;
            len3=0;
        }
    }
	return count+1;
}
double f2(double temp[],char sign[],int num_signs)
{
    int found_pow=1,found_mult=1,found_div=1,i=0;
    while(found_mult==1 || found_div==1 || found_pow==1)
    {
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='^')
            {
                found_pow=1;
                temp[i]=ultimate_value('^',temp[i],temp[i+1]);
                leftShift_num(temp,num_signs+1,i+1);
                leftShift_str(sign,num_signs,i);
                num_signs--;
            }
        }
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='*')
            {
                found_mult=1;
                temp[i]=ultimate_value('*',temp[i],temp[i+1]);
                leftShift_num(temp,num_signs+1,i+1);
                leftShift_str(sign,num_signs,i);
                num_signs--;
            }
        }
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='/')
            {
                found_div=1;
                temp[i]=ultimate_value('/',temp[i],temp[i+1]);
                leftShift_num(temp,num_signs+1,i+1);
                leftShift_str(sign,num_signs,i);
                num_signs--;
            }
        }
        found_mult=0;
        found_div=0;
        found_pow=0;
        for(i=0;i<num_signs;i++)
        {
            if(sign[i]=='^')
            {
                found_pow=1;
                break;
            }
            if(sign[i]=='*')
            {
                found_mult=1;
                break;
            }
            if(sign[i]=='/')
            {
                found_div=1;
                break;
            }
        }
    }
    while(num_signs>0)
    {
        temp[0]=ultimate_value(sign[0],temp[0],temp[1]);
        leftShift_num(temp,num_signs+1,1);
        leftShift_str(sign,num_signs,0);
        num_signs--;
    }
    return temp[0];
}

/*double f1(char str[],double x,double y)
{
    double temp[input_size];
    int num_signs,i;
    char sign_temp[input_size];
    num_signs=count_sign(str,sign_temp);
    strTok(str,"+-/*^");
    for(i=0;i<=num_signs;i++)
        temp[i]=ff(token_eqn[i],x,y);
    return f2(temp,sign_temp,num_signs);
}
*/
//#define PI 3.14159265
double f3(char str[],double x,double y)
{
    int len,i,start=-1,end=-2,count1=0,count2=0,sign_num,k;
    double temp[input_size],argument=0;
    char sign[input_size],str_temp[input_size];
    len=strlen(str);
   // sign_num=count_sign(str,)
    for(i=0;i<len;i++)
    {
        if(str[i]=='(')
        {
            start=i+1;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            temp[count1]=f3(str_temp,x,y);
            count1++;
            i=end+1;
        }
        else if(str[i]=='+' ||str[i]=='-' ||str[i]=='*' ||str[i]=='/' ||str[i]=='^')
        {
            sign[count2]=str[i];
            count2++;
        }
        else if(str[i]=='s' && str[i+1]=='i' && str[i+2]=='n')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=sin(argument*PI/180.0);
            count1++;
            i=end+1;
        }
        else if(str[i]=='c' && str[i+1]=='o' && str[i+2]=='s' && str[i+3]!='e')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=cos(argument*PI/180.0);
            count1++;
            i=end+1;
        }
        else if(str[i]=='t' && str[i+1]=='a' && str[i+2]=='n')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=tan(argument*PI/180.0);
            count1++;
            i=end+1;
        }
        else if(str[i]=='c' && str[i+1]=='o' && str[i+2]=='t')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=(cos(argument*PI/180.0)/sin(argument*PI/180.0));
            count1++;
            i=end+1;
        }
        else if(str[i]=='s' && str[i+1]=='e' && str[i+2]=='c')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=(1.0/cos(argument*PI/180.0));
            count1++;
            i=end+1;
        }
        else if(str[i]=='c' && str[i+1]=='o' && str[i+2]=='s' && str[i+3]=='e' && str[i+4]=='c')
        {
            start=i+6;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=(1.0/sin(argument*PI/180.0));
            count1++;
            i=end+1;
        }
        else if(str[i]=='l' && str[i+1]=='o' && str[i+2]=='g')
        {
            start=i+4;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=log10(argument);
            count1++;
            i=end+1;
        }
        else if(str[i]=='l' && str[i+1]=='n')
        {
            start=i+3;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=log(argument);
            count1++;
            i=end+1;
        }
        else if(str[i]=='e' && str[i+1]=='^')
        {
            start=i+3;
            end=find_target(str,start,0,1);
            n_strcpy(str,str_temp,start,end);
            argument=f3(str_temp,x,y);
            temp[count1]=exp(argument);
            count1++;
            i=end+1;
        }
        else
        {
            k=0;
            while(str[i]!='(' && str[i]!=')' && str[i]!='+' && str[i]!='-' && str[i]!='*' && str[i]!='/' && str[i]!='^' && i<len)
            {
                str_temp[k]=str[i];
                k++;
                i++;
            }
            str_temp[k]='\0';
            temp[count1]=ff(str_temp,x,y);
            count1++;
           i--;
        }
    }
    sign[count2]='\0';
    return f2(temp,sign,count2);
}


int main()
{
    char str1[input_size], str[input_size];
    printf("Enter the expression : ");
    scanf("%s",str1);
    int i;

    if(str1[0] == '-')
    {
    	str[0] = '0';
    	for(i=0;str1[i]!='\0';i++)
    		str[i+1] = str1[i];
    	str[i+1] = '\0';
    }
    else
    	strcpy(str, str1);

    double x, y;
    printf("Set the value of x and y in f(x, y). (0 if they are absent).\n");
    printf("Enter the value of x : ");
    scanf("%lf", &x);

    printf("Enter the value of y : ");
    scanf("%lf", &y);

	double ans;
	ans=f3(str,x,y); //set value of x, y in f(x, y).
	printf("Value : %lf\n",ans);

	return 0;
}
//(sin(x)-x^5)*x-tan(x/x^2);
//(x^2+(x^5*cos(3*x+x)^2))^.5)/(2*sin(x))
