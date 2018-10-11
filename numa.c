#include <stdio.h>

float neg(float n)
{
	return (n >=0)?n:-n;
}
float f(float n)
{
		return ((3*n*n*n) - (9*n*n) +8);
}
float f1(float n)
{
		return ((9*n*n) - (18*n)); 
}
void newton(float x,float epsilon,float delta,int n)
{
		int i;
		float c,d,x1;
		int count;
		for (i =0; i < n; i++)
		{
				printf("iteration =%d\n", ++count);
				c=f(x);
				d=f1(x);
				if (neg(d) <= delta)
				{
				printf("not possible");
				}
				x1 = x -(c/d);
				if ( neg(((x1 - x)/x1)) <= epsilon)
				{
					printf("convergent solution at %7f = %7f\n",x1,f(x1));
					break;
				}
				x =x1; 
		}
}
void false_position(float start, float end, int n, float epsilon)
{
		float a,b,c,mid;
		int count =0;
		a = f(start);b = f(end);
		int i;
		printf ("No. of iterations\tstart\tend\troot\n");
		for( i=0; i < n;i++)
		{
							if (a*b <0)
							{
									
									mid= ((start*f(end)-end*f(start)))/(f(end)-f(start));
									c=f(mid);
								    
									printf ("%d\t%7f\t%7f\t%7f\n",++count,start, end, c);
									if ( neg(c) <= epsilon)
									{
										printf ("the root=%7f", mid);
										break;
									}
									if ( a*c > 0)
									{
										start = mid;
										a = c;
									}
								
									else
									{
										 end= mid;
										 b = c;
									}
							}
							else
							printf("not possible");
								
			
		}
}

void bisection(float start, float end ,int n, float epsilon)
{
		float a,b,c,mid;
		int count =0;
		a = f(start);b = f(end);
		int i;
		printf ("No. of iterations\tstart\tend\troot\n");
		for( i=0; i < n;i++)
		{
							if (a*b <0)
							{
									mid= (start+end)/2.0;
									c= f(mid);
								    
									printf ("%d\t%7f\t%7f\t%7f\n",++count,start, end, c);
									if ( neg(c) <= epsilon)
									{
										printf ("the root=%7f", mid);
										break;
									}
									if ( a*c > 0)
									{
										start = mid;
										a = c;
									}
								
									else
									{
										 end= mid;
										 b = c;
									}
							}
							else
							printf("not possible");
								
			
		}
		
	
}
int main()
{
		printf("ENTER 1:BISECTION METHOD");
		printf("ENTER 2: FALSE POSITION");
		printf("ENTER 3: NEWTON RAPHSON METHOD");
		printf("\n");
		int n;
		scanf("%d" , &n);
		switch(n)
		{
		case 1:
		bisection(0.0,2.0,1000, 0.000001);
		case 2:
		false_position(0.0,2.0,1000,0.000001);
		case 3:
		newton(3.0, 0.0000001,0.0000001,1000);
		}
		

}
