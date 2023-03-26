# Strategy
## Order
1. Udemy course DSA https://udemy.com/course/datastructurescncpp
2. Leetcode https://github.com/Chanda-Abdul/Grokking-the-Coding-Interview-Patterns 
3. Leetcode https://seanprashad.com/leetcode-patterns/
4. Leetcode BLIND https://leetcode.com/discuss/general-discussion/460599/blind-75-leetcode-questions OR https://docs.google.com/spreadsheets/d/1A2PaQKcdwO_lwxz9bAnxXnIQayCouZP6d-ENrBz_NXc/

- Arrays
- Matrices
- LinkedList
- Stack
- Queue
- Trees
- Graph
- Hashing
- Recursion
- Sorting

### Physical Data Structures
- Arrays, Matrices, LinkedList
- How data is arranged in main memory

### Logical Data Structures
- Stack, Queues, Trees, Graph, Hashing
- How data is utilized

## Further
1. Elements of Programming Interview book
2. Cracking the Coding Interview book

## C++ centric
1. Udemy course c++ https://www.udemy.com/course/cpp-deep-dive/
2. STL https://www.topcoder.com/thrive/articles/Power%20up%20C++%20with%20the%20Standard%20Template%20Library%20Part%20One
https://www.topcoder.com/thrive/articles/Power%20up%20C++%20with%20the%20Standard%20Template%20Library%20Part%20Two:%20Advanced%20Uses
https://gist.github.com/satwikkansal/c959e89161cc60db16b412233177feab

# DSA
- in main memory
- Program has to be brought into main memory
- Associated data has to be brought into main memory
- How you **organise/arrange the data for running the operations** is called data structure.
- OTOH, databases deal with organising/arranging data in the HDD.

### Main Memory
- every byte has address
- "0"-"65535" => total of 65536 bytes = 64 x 1024 = 64KB RAM
- stack, heap, codesection
- 
static memory allocation happens in stack. "static" as in, amount of memory to be reserved is decided at compile time.
Heap memory should be treated as a "resource". Accessible only via pointers. Dynamic memory allocation is done in Heap.

![](http://tinyurl.com/memory-layout)

```
	----
	heap
	----
	stack
		{
			stackframe for func
			(activation record)
		}
		{
			stackframe for main function
			(activation record)
		}
	----
	codesection
		int main() { int a,b; func()}
		...
		...
	----
```
### Intro to Data Structures
Logical DS are implemented using Physical DS

- Physical Data structures
	- Array (stack or heap)
	- LinkedList
- Login Data structures
	- Stack ...Linear
	- Queue ...Linear
	- Tree ...NonLinear
	- Graph ...NonLinear
	- HashTable ..Tabular

### ADT: Abstract Data Type
1. Representation of Data
2. Operation on Data

Basically hide internal details and expose clean API to manipulate the DS.
- add(), remove(), search(), sort(), get(), set(), replace()

### Time and Space Complexity








# C & C++ Concepts
- Arrays
- Structure
- Pointers
- Reference
- Parameter Passing
- Classes 
- Constructor
- Templates

## Memory Layout of Programs 
https://www.geeksforgeeks.org/memory-layout-of-c-program/


MainMemory

----------
HEAP

----------
STACK

----------
CODE SECTION

----------


Main Memory is divided into
- code section, stack & Heap
- //TODO: what goes into stack and what goes into heap?
	- All variables are created in STACK.
	- Pointers are also created in STACK.

## data types
- char (1 bytes)
- int (4bytes)
- 


## Arrays
- Collection of similar data elements (homogenous, contiguous)
```c
int main(){
	// just declaration
	int A[5];
	// declaration + initialization
	int B[5] = {1,2,3,4,5};
	// declaration + initialization without array size
	int C[] = {1,2,3,4,5,6,7,8,9};

	int D[10] = {1,2,3,4}; // rest of the elements will be 0
	int E[10] = {0} //same as above

	for(int i=0; i<5; i++){
		printf("%d",B[i]);
	}

	/**for each loop*/
	for(int x:A){
		cout<<x<<endl;
	}

	int n;
	cout<<"Enter size"; cin>>n;
	int A[n] = {1,2,3,4} // !NOT ALLOWED! variable sized object may not be initialized
	int B[n];
	B[0]=2;
}
```
- Above arrays are created in `stack` section of memory


## Structures

- defining structure
- size of structure (with padding)
- declaring a structure

```c
struct Rectangle{
	int length;     //2bytes
	int breadth;	//2bytes
} 

struct	Rectange r1, r2, r3; //global

struct RectangleOther{
	int length;     //2bytes
	int breadth;	//2bytes
	char x;			//1byte ?
} r0; // declare variable directly.

int main(){
	// just declaration
	struct	Rectange r;
	// declaration + initialization
	struct	Rectangle r = {10,5};

	//these structs will reside in **stack**

	printf("Area of Rectangle is %d", r.length * r.breadth);
	printf("size of struct  is %lu", sizeof(r)); //8
	printf("size of struct  is %lu", sizeof(r0)); //not 9, but 12 because of `padding`
}
```
- How padding works in structs ?

## Pointers

- Why Pointers?
	Pointers are address variables.
	Programs do not directly access heap memory. Heap memory is `external` to the program. This is why it needs pointers.
	Pointer is in Stack, but addresses a value in Heap.
	Accessing resources outside the program (files) ...keyboard, mouse, devices...


- Declaration, initialization, dereferencing
```c
	 int *p; // declaration
	 p = &a; // initialization
	 printf("%d %d %d", p, &a, *p); // dereferencing
```
- Dynamic Memory Allocation
```c
	p=(int*)malloc(5*sizeof(int)); //c
	p=new int[5]; //c++
```

### Pointer to an array
Name of the array itself is a pointer to the first element.

```c
	//Array created in STACK
	int A[5]={1,2,3,4};
	int *p;
	p = A; //correct
	p = &A[0] //correct
	p = &A //WRONG!

	for(int i=0;i<5;i++)
	count<<A[i]<<endl

	for(int i=0;i<5;i++)
	count<<p[i]<<endl

	//Array created in HEAP (c syntax)
	int *p;
	p=(int*)malloc(5*sizeof(int)); //c syntax
	p[0]=1;
	p[1]=2;
	p[2]=3;
	p[3]=4;

	for(int i=0;i<5;i++)
	count<<p[i]<<endl
	free(p);

	//Array created in HEAP (c++ syntax)
	int *p;
	p=new int[5]; //c++ syntax
	p[0]=1;
	p[1]=2;
	p[2]=3;
	p[3]=4;

	for(int i=0;i<5;i++)
	count<<p[i]<<endl
	
	delete [ ] p;
```

### Pointer to a structure
```c
	//static object..structure in stack
	struct Rectange r={10,5};
	r.length=15;
	struct Rectange *p=&r;
	(*p).length=20; //correct
	p->length=20; //correct

	//dynamic object..structure in heap
	struct Rectange *p;
	p=(struct Rectangle*)malloc(sizeof(struct Rectange));
	p->length = 10;
	p->breadth = 5;
```

```cpp
	//stack
	Rectange r={10,5};
	cout<<r.length<<endl;
	cout<<r.breadth<<endl;

	//stack
	Rectange *p=&r;
	cout<<r->length<<endl;
	cout<<r->breadth<<endl;

	//heap
	Rectange *p;
	p=(struct Rectange *)malloc(sizeof(struct Rectange)); //c
	p=new Rectangle; //c++
	p->length=15;
	p->breadth=7;


```

### Size of a pointer
Size of a pointer is independant of datatype.
ITS ALWAYS 8 bytes
```c
	int *p1;
	char *p2;
	float *p3;
	double *p4;
	struct Rectangle *p5;

	cout<<sizeof(p1)<<endl; //8 bytes 
	cout<<sizeof(p2)<<endl; //8 bytes
	cout<<sizeof(p3)<<endl; //8 bytes
	cout<<sizeof(p4)<<endl; //8 bytes
	cout<<sizeof(p5)<<endl; //8 bytes
```

### References (only c++)
Alias or Nickname to a variable.
Reference must be initialized during declaration.
	else its an error.
References are used in parameter passing & Functions.
Conceptually, references dont take memory.
```c
	int a=10;
	int &r=a;
	cout<<a; //10
	r++;
	cout<<a; //11
	cout<<r; //11
	int b=30;
	r=b;
	cout<<a; //30
	cout<<r; //30
	cout<<b; //30
```

## Functions
- Actual Parameters and Formal Parameters and activation record
	- Actual Parameters // at fn call time
	- Formal Parameters // variables of the function which gets COPY of actual parameters
	- Activation Record: // stack frame
```c
	int add(int a, int b){ //formal parameters
		return a+b;
	}

	int main(){
		int x,y,z;
		x=10;y=5; 
		z=add(x,y); //actual parameters
	}
```
### Parameter Passing
	- Pass by Value
		- formal parameters are __values__
	- Pass by Address
		- formal parameters are __pointers__
	- Pass by Reference (only c++)
		- formal parameters are __references__
		- there is only ONE activation record (inline function)
		- no separate activation record for the function.
		- body of the function is copy pasted into the main.

```c
	//call by value
	void swap(int x, int y){ //formal parameters
		int temp;
		temp=x;
		x=y;
		y=temp;
	}
	//call by address
	void swap(int* x, int* y){ //formal parameters
		int temp;
		temp=*x;
		*x=*y;
		*y=temp;
	}
	//call by reference (only c++)
	void swap(int& x, int& y){ //formal parameters
		int temp;
		temp=x;
		x=y;
		y=temp;
	}
	int main(){
		//pass by value
		int a,b;
		a=10;
		b=20;
		swap(a,b); //actual parameters
		printf("%d, %d", a,b); //10, 20
		// actual parameters are not modified even if formal parameters are modified

		//pass by address
		swap(&a,&b); 
		printf("%d, %d", a,b); //20, 10
		// actual parameters are modified!

		//pass by reference
		swap(a,b); 
		printf("%d, %d", a,b); //20, 10
		// actual parameters are modified!
	}

```

### Array as parameter
**Arrays can be passed ONLY by address**

```c
void func(int A[], int n){ //A is a pointer to array
	int i;
	for(i=o;i<n;i++)
		printf("%d", A[i]);
}
int main(){
	int A[5]={2,4,6,8,10};
	func(A, 5);
}
```

```c
int* fun(int n){
	int *p;
	p=(int*)malloc(n*sizeof(int));
	return p;
}

int main(){
	int *A;
	A=fun(5);
}
```


```c
void func(int A[]){
	count<<sizeof(A)/sizeof(int)<<endl; //prints 2 (sizeofPOINTER/sizeofINT)=(4/2)=2
	for(int x:A)   //wrong!you cannot use foreach loop on pointer. It works only on array
		cout<<x<<" ";
}
void func(int A[], int n){ //you NEED to pass the length of array too. Its not possible to infer it.
	for(int i=0;i<n;i++)
		cout<<A[i]<<endl;
}
int* func(int n){
	int *p;
	p=new int[n];
	for(int i=0;i<n;i++)
		p[i]=i+1;
	return p;
}
int main(){
	int A[]={2,4,6,8,10};
	int n=5;
	for(int x:A)
		cout<<x<<" ";
	count<<sizeof(A)/sizeof(int)<<endl; //prints 5
	func(A)

	int *ptr;
	ptr=func(5);
	for(int i=0;i<5;i++)
		cout<<ptr[i]<<endl;

}
```

### Structure as Parameter
**Structs can be passed by value OR by address OR by reference**

```c
//call by value
int area(struct Rectangle r){
	r.length++; //will not change actual parameters in main. main's struct length is not changed.
	return r.breadth*r.length;
}
//call by reference
int area(struct Rectangle &r){
	r.length++;
	return r.breadth*r.length;
}
//call by address
int changeLength(struct Rectangle *r, int l){
	r->length=l;
}
int main(){
	struct Rectangle r={10,5};
	printf("%d", area(r));
	changeLength(&r, 20);
}
```

**Arrays can only be passed by address**
<u>BUT, if a struct contains an array, the whole struct, incl array can be passed by value</u>
...everything copied..

```c
struct Test{
	int A[5];
	int n;
};

void func(struct Test t){
	t.A[0] = 10; //this change wont be reflected in actual parameter
	t.A[1] = 9; //this change wont be reflected in actual parameter
}

int main(){
	struct Test t={{2,4,6,8,10}, 5};
	func(t);
}
```

### Structures and Functions...

```c
struct Rectangle{
	int length;
	int breadth;
}

void initialize(struct Rectangle *r, int l, int b){
	r->length=l;
	r->breadth=b;
}
int area(struct Rectangle r){
	return r.length*r.breadth;
}
void changeLength(struct Rectangle *r, l){
	r->length= l;
}

int main(){
	struct Rectangle r;
	initialize(&r, 10,5);
	area(r);
	changeLength(&r, 20);
}
```

## Classes

```c++
class Rectangle{
private:
	int length;
	int breadth;

public:
	Rectangle(){length=breadth=1;}
	Rectangle(int l, int b){
		length=l;
		breadth=b;
	}
	int area(){
		return length*breadth;
	}
	void changeLength(int l){
		length= l;
	}
};

int main(){
	Rectangle r(10,5);
	r.area();
	r.changeLength(20);
}
```

## Templates

```c++
class Arithmetic{
	private:
		int a;
		int b;
	public:
		Arithmetic(int a, int b);
		int add();
		int sub();
};
Arithmetic::Arithmetic(int a, int b){
	//`this` is a pointer to current object, hence use arrows
	this->a = a;
	this->b = b;
}
int Arithmetic::add(){
	return a+b;
}
int Arithmetic::sub(){
	return a-b;
}
```

```c++
template<class T>
class Arithmetic{
	private:
		T a;
		T b;
	public:
		Arithmetic(T a, T b);
		T add();
		T sub();
};
template<class T>
Arithmetic<T>::Arithmetic(T a, T b){
	//`this` is a pointer to current object, hence use arrows
	this->a = a;
	this->b = b;
}
template<class T>
T Arithmetic<T>::add(){
	return a+b;
}
template<class T>
T Arithmetic<T>::sub(){
	return a-b;
}
```

```
int main(){
	Arithmetic<int> ar(10,5);
	cout<<ar.add();
	Arithmetic<float> ar(10.2,5.1);
	cout<<ar.add();
}
```



# Recursion
Function that calls itself with a **Base condition which will terminate the recursion**

"Tracing Tree" of a recursive function 
	- debugging and visualizing

Recursion has two phases
- Calling phase (ascending)
- Returning phase (descending)

## General form of recursion
```c
void func(int n){
	if(n>0){
		1. calling phase...
		func(n-1);
		2. returning phase...
	}
}

```
## Recursion uses Stack
multiple activation records for each function call.

## Time Complexity
```c
void func(int n){
	if(n>0){...............................1
		printf("%d",n);....................1
		func(n-1);.........................T(n-1)
	}
}

// O(n)

// T(n) = T(n-1)+1
        = T(n-2)+2
		= T(n-3)+3
		=...
		= T(n-k)+k
		Assume n-k=0 => n=k
		= T(n-n) +n
		= T(0) + n
		= n
```

## Types of Recursion
- tail recursion
- head recursion
- tree recursion
- indirect recursion
- nested recursion

### Tail recursion
- ![](https://tinyurl.com/tailrrecursion)
- perform all operations at calling phase
- no operations at returning phase
- ```c
	{
		...
		...
		...
		recurse(n-1);
	}
```
- **Loops are better than tail recursion** with O(1) space complexity, where recursion is O(N) space complexity due to activation records for each recursive call
- Converting tail recursion to loop is straight forward

### Head recursion
- ![](https://tinyurl.com/headrrecursion)
- first operation itself is a recursive call
- no operations at calling phase
- all operations at returning phase
- ```c
	{
		recurse(n-1);
		...
		...
		...
	}
```
- **Loops are better than tail recursion** with O(1) space complexity, where recursion is O(N) space complexity due to activation records for each recursive call
- Converting head recursion to loop is slightly difficult

### Tree recursion
- ![](https://tinyurl.com/treerrecursion)
- Head and Tail recursion are **Linear** recursion as they call itself just ONCE
- Tree recursion is where the recursive call is made more than once
```c
	{
		....
		...
		recurse(n-1);
		...
		...
		recurse(n-1);
	}
```
- O(2^n) for the above example
- How?: level1 =1call ; level2 =2calls ; level3 =4calls ; level4 =8calls ;...
- = 2^0 + 2^1 + 2^2 +...+2^N = 2^(N+1) - 1 (GP sum)
- = O(2^N)
- Space complexity = O(N) as N stackframes are required

### Indirect Recursion
- Cycle ..Circular calls
- A-->B-->C-->A OR A calls B, B calls A
- 
```c
void funcA(int n)
{
	...
	...
	funcB(n/2)
}
void funcB(int n)
{
	...
	...
	funcA(n/2)
}
```


### Nested Recursion
recurse(recurse(n-1))

```c
int func(int n){
	if(n>100)
		return n-10;
	else
		return func(func(n+11)); //nested
}
```


---


## New Concepts learnt
1. Taylor Series and Maclauren Series and Power Series...
	a. And how to approximate any functions
2. nPr nCr and pascals triangle 
3. bottom up = table driven memoization, top down = linear memoization
4. tower of hanoi.

## Questions and todos

1. Why do you need **Header files**? (xyz.h)
2. Scope resolution operators?
3. When running a c program, how much stack, how much heap is reserved?
4. https://cs.gmu.edu/~zduric/cs262/Slides/teoX.pdf and https://courses.engr.illinois.edu/cs225/sp2022/resources/stack-heap/
5. Good hang of Time complexity Space complexity. Understand "Log" Logarithm properly
6. Good hang of Math. 3Brown1Blue all courses.
7. Have a list of popular power series byheart.



