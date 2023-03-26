![](https://miro.medium.com/max/700/1*3G7uz4l1GnFacxz6InrLLw.png)

a LOAD instruction loads the data from memory into a register.

a STORE instruction stores the date back into the memory from the register.

## Instruction Set Architecture (ISA) RISC vs CISC

There is a fixed number of instructions that the CPU understands.
You as a programmer cannot add to this set.

The combination of instructions a CPU understands and the registers it knows about is called ISA

- Intel and AMD chips both understand x86 ISA.
- chips used in iphone, ipad ..A12,A13,M1 etc understand the ARM ISA

Programs compiled for x86 ISA cannot be understood by a ARM CPU and vice versa. Apple's M1 has a complementary program called Rosetta2 which translates x86 programs to ARM instructions.

![](https://miro.medium.com/max/700/1*KY292On2Vg06zT_wgmq-Bw.png)

x86 is CISC (Complex Instruction Set Computing)<br>
ARM is RISC (Reduced Instruction Set Computing)

CISC came first in 1970s - By Intel. RISC came in 1980's , as a total redesign because CISC was becoming more complex.

The primary goal of CISC is to complete the task in as few lines of assembly code as possible. This is done by building a processor capable of understanding a large number of instructions (complex instructions). It can also operate directly on main memory without explicit instructions to LOAD STORE into registers. Advantage &mdash; the compiler has to do very little work to translate high lvl langs to assembly. Also since the length of the code is small, less RAM is needed to store instructions.
However, each "complex instruction" may take one or more cycles to complete.

RISC &mdash; simple instructions which can be executed in one clock cycle. => More RAM to store more instructions, compiler also takes the load of heavy translating to simple instruction set.

RISC is better for pipelining &mdash; as every instruction takes just one cycle - uniform amount of time.

In 1970s, memory was expensive, compilers were bad and people wrote programs in assembly by hand. The only way to conserve memory was to build a powerful CPU instruction set which could do a lot of stuff in one instruction -> Helped assembly programmers. But designing decoders for all these complex instructions became a hassle. They solved it using "Microcode" (for each complex instruction in ISA, you make a little program stored in special memory in the CPU made up of much simpler instructions). They went on adding more and more complex instructions..and more and more microcodes.(ROM was much cheaper than RAM..this was an economic tradeoff)

As microcodes became more and more complex (a bug there will turn out to be too costly lol). &mdash; the rise of RISC.

RAM started getting cheaper, people were not writing assembly code anymore. Compliler writers were also getting confused looking at wide variety of options in CISC and chose simpler instructions and combined them instead. 80% of the time was spent using 20% of the instruction set. so guys thought..why not ditch all these complex instructions and use "reduced" instruction set. Instead of debugging and fixing microcode, you leave it to the compiler writers to solve their own issues.

"Reduced" means reduction in instruction complexity. Reduction in number of instructions the CPU understands. This is simpler to implement in h/w, utilizing few CPU resources at the same time.

RISC is optimized for compilers and not humans. as a human, you will die writing Assembly for RISC CPU.

Performance equation<br>
time/program = time/cycle *cycles/instruction* instructions/program

CISC minimizes instructions per program..sacrificing the number of cycles per instruction.
RISC minimizes the number of cycles per instruction..at the cost of instructions per program

## Pipelining

![](https://upload.wikimedia.org/wikipedia/commons/thumb/c/cb/Pipeline%2C_4_stage.svg/375px-Pipeline%2C_4_stage.svg.png)

RISC gave birth to the concept of pipelining. In a single clock cycle, you could fetch instruction C, decode instruction B, execute instruction A ...all in one clock cycle!!

But it assumes that each stage is equally long (fetch decode execute). RISC designers understood this and they tried to standardize how long each instruction takes. That way each resource inside the CPU can remain utilized to the max constantly as instructions get processed.

- **Fetch**
- **Decode**
- **Execute**
- **load** (memory access)
- **store**(write-back)

In ARM, each stage takes 1 clock cycle. this makes it easy to push ARM instructions through a pipeline. With CISC this gets tricky as instructions are of variable length.
