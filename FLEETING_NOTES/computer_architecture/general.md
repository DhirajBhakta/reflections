Computer Architecture
- Introduction
- Floating Point Representation
- Basics of Computer System & Microoperations
- CPU Design
- Instructions & Addressing Modes
- Data format
- CPU, Data-path & Control Unit
Computer Organisation
- IO Organisation
- Memory & Cache
- Pipelining 


A given CPU = (Instruction Set + Addressing Modes + Data format)
#### Data Format
Binary representation of data values.
Data
- Numbers
	- Integers (Fixed Point)
		- Unsigned
		- Signed (arithmetic numbers)
			- Sign Magnitude
				- First bit is for Sign. Remaining bits is for magnitude. 0 -> +ve , 1 -> -ve
				- eg: +5 = 0101 , -5 = 1101
				- but 0 will have 2 representation in this format: +0=000 , -0=100
			- 1's Complement
				- +5 = 0101, -5 = 1010
				- So if you see any binary repr starting with 1, its a negative value..so take one's complement and get the value. 
			- 2's Complement
				- = 1's Complement + 1
				- +5 = 0101 -> 1010 +1 = 1011 is -5
				- 
	- Float (Floating Point)
		- provides larger range of numbers with limited number of bits.
		- {S .. E .. M}
		- Sign, Exponent, Mantissa
		- Exponent is stored in biased form (unsigned).
			- if 5 bits are assigned to store the exponent, then it can represent values from -16 to 15.
			- we add the bias of 16 to the value to make it signed.. so that its in the rangle of 0-31.. and then store it.
		- Mantissa is signed normalized fraction number (implicit/explicit)
			- Explicit Normalization
				- 101.11 -> 0.10111 x 2^3 
				- first bit after the decimal point should be 1.
				- Mantissa(M) = Number after the decimal Point = 10111
				- Exponent = Power of 2 = 3.. stored exponent = 3+bias
				- {S .. E .. M} = {S .. 3+bias...10111}
				- Value = (-1)^s x 0.M x 2^(E-bias)
			- Implicit Normalization
				- 101.11 -> 1.0111 x 2^2 
				- first bit before the decimal point should be 1.
				- Mantissa(M) = Number after the decimal point = 0111
				- Exponent = Power of 2 = 2 .. stored exponent = 2+bias
				- {S..E..M} = {S.. 2+bias .. 0111}
				- Value = (-1)^s x 1.M x 2^(E-bias)
			- cannot store 0
			- cannot store very very small values close to 0 (underflow)
			- If you have more bits on Mantissa, you get more precision
			- If you have more bits on Exponent, you get more range.
- Characters
	- ASCII
	- EBCDIC

#### Stored Program Architecture
The program which the CPU executes should be stored in memory
- Von Neumann Architecture
- Harvard Architecture
