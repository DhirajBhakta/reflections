#include<iostream>
#include<cmath>
using namespace std;

//types of recursion---------------
void tail_recursion(int n)
{
	if(n>0)
	{
		cout<<n<<" ";
		tail_recursion(n-1);
	}
}

void head_recursion(int n)
{
	if(n>0)
	{
		head_recursion(n-1);
		cout<<n<<" ";
	}
}

void tree_recursion(int n)
{
	if(n>0)
	{
		cout<<n<<" ";
		tree_recursion(n-1);
		tree_recursion(n-1);
	}
}

void indirect_recursion_A(int n);
void indirect_recursion_B(int n);
void indirect_recursion_A(int n)
{
	if(n>0)
	{
		cout<<n<<" ";
		indirect_recursion_B(n/2);
	}
}
void indirect_recursion_B(int n)
{
	if(n>1)
	{
		cout<<n<<" ";
		indirect_recursion_A(n/2);
	}
}
int nested_recursion(int n)
{
	if(n>100)
		return n-10;
	else
		return nested_recursion(nested_recursion(n+11));
}

//recursion with static variables------
int rec(int n){
	if (n>0)
	{
		return rec(n-1) + n;
	}
	return 0;
}
int static_rec(int n){
	static int x=0;
	if (n>0)
	{
		x++;
		return static_rec(n-1) + x;
	}
	return 0;
}

//sum of first N natural numbers
int sum(int n){
	if(n==0)
		return 0;
	return sum(n-1)+n;
}

//factorial
long long factorial(int n){
	if(n<=1)
		return 1;
	return factorial(n-1)*n;
}

//power
template <typename T> 
T power(T n, int pow){
	if(pow==0)
		return 1;
	return n * power(n, pow-1);
}

int power_fast(int n, int pow){
	if(n==0)
		return 1;
	if(pow%2==0)
		return power_fast(n*n, pow/2);
	else
		return n * power_fast(n*n,(pow-1)/2);
}

//taylor series
//e^x = 1 +x/1 +x^2/2! + x^3/3! + x^4/4!....n times
double taylor(int x,int n)
{
	if(n==0)
		return 1;
	return taylor(x, n-1) + power(x,n)/(factorial(n) *1.0);
}

double taylor_static(int x, int n)
{
	static double p=1, f=1;
	double r;
	if(n==0)
		return 1;
	r = taylor_static(x, n-1);
	p = p*x;
	f = f*n;
	return r + p/f;
}

double taylor_horner(int x, int n)
{
	static double sum=0;
	if(n==0)
		return sum;
	sum=1+x*sum/n;
	return taylor_horner(x, n-1);
}
double taylor_iterative(int x, int n){
	double sum=1;
	double num=1;
	double den=1;
	for(int i=1;i<=n;i++){
		num*=x;
		den*=i;
		sum+=num/den;
	}
	return sum;
}

double fib(int n)
{
	if (n<=1)
		return n;
	return fib(n-2) + fib(n-1);
}


int M[100] = {0};
int fib_memoized(int n)
{
	static int initilized=0;;
	if(!initilized){
		initilized=1;
		for(int i=0;i<200;i++) M[i] = -1;
	}
	if(n<=1)
	{
		M[n] = n;
		return n;
	}
	if(M[n-1]==-1)
		M[n-1] = fib_memoized(n-1);
	if(M[n-2]==-1)
		M[n-2] = fib_memoized(n-2);
	return M[n-1]+M[n-2];
}

int fib_formula(int n)
{
	float Phi = (1+ sqrt(5))/2;
	float phi = (1- sqrt(5))/2;
	return (pow(Phi,n) - pow(phi,n))/sqrt(5);
}

double nCr(int n, int r)
{
	return 1.0*factorial(n)/(factorial(r)*factorial(n-r));
}

double nPr(int n, int r)
{
	return 1.0*factorial(n)/factorial(n-r);
}

double nCr_pascals_triangle(int n, int r)
{
	if(r==0 || n==r) return 1;
	return nCr_pascals_triangle(n-1, r-1) + nCr_pascals_triangle(n-1, r);
}

void tower_of_hanoi(int total, char source, char inter, char dest)
{	static int i=0;
	if(total>0)
	{
		i++;
		tower_of_hanoi(total-1, source, dest, inter);
		cout<<endl<<"Move a disk from:"<<source<<" to:"<<dest;
		tower_of_hanoi(total-1, inter, source, dest);
	}
}
int main(){
	cout<<endl<<"Output of tail recursion is:"; 
	tail_recursion(3);//3 2 1
	cout<<endl<<"Output of head recursion is:";
	head_recursion(3);//1 2 3
	cout<<endl<<"Output of tree recursion is:";
	tree_recursion(3);//3 2 1 1 2 1 1
	cout<<endl<<"Output of indirect recursion is:";
	indirect_recursion_A(20);//20 10 5 2 1
	cout<<endl<<"Output of nested recursion is:"<<nested_recursion(20);
	cout<<endl<<"Output of nested recursion is:"<<nested_recursion(30);
	cout<<endl<<"Output of nested recursion is:"<<nested_recursion(100);
	

	cout<<endl<<"Output of simple recursion is:"<<rec(5);
	cout<<endl<<"Output of static recursion is:"<<static_rec(5);
	cout<<endl<<"Sum of N=10 Natural numbers is:"<<sum(10);
	cout<<endl<<"Factorial of N=5 is:"<<factorial(5);
	cout<<endl<<"Factorial of N=0 is:"<<factorial(0);
	cout<<endl<<"Power of 2^5 is:"<<power(2,5);
	cout<<endl<<"Power of 2^5 is:"<<power_fast(2,5);
	cout<<endl<<"Power of e^5 is:"<<power(2.71828,5);
	cout<<endl<<"Taylor of e^5 upto 13 terms is:"<<taylor(5, 100);
	cout<<endl<<"Taylor of e^5 upto 10 terms is:"<<taylor_static(5, 100);
	cout<<endl<<"Taylor of e^5 upto 10 terms is:"<<taylor_horner(5, 100);
	cout<<endl<<"Taylor of e^5 upto 10 terms is:"<<taylor_iterative(5, 100);
	cout<<endl<<"Fibonacci of 7:"<<fib(20);
	cout<<endl<<"Fibonacci of 7:"<<fib_memoized(20);
	cout<<endl<<"Fibonacci of 7:"<<fib_formula(20);
	cout<<endl<<"nCr 10C2=:"<<nCr(10,2);
	cout<<endl<<"nCr 10C2=:"<<nCr_pascals_triangle(10,2);
	cout<<endl<<"Tower of hanoi:10";
	tower_of_hanoi(10, 'A', 'B', 'C');
	return 0;
}
