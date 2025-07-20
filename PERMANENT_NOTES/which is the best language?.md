
languages like Rust and c++ aren't the silver bullet for extreme performance. It depends on what "extreme performance" means to you. Rust c++ would probably not perform as good as Golang,Java on a webapp  backend as the latter are fiercely optimized for the web, to handle millions of concurrent requests. Rust doesnt even entertain green threads anymore, it has been removed to reduce overall binary size. (not so sure about c++, since you have libuv libev there).

On the other extreme, you have Erlang(epitome of green threads), which is supremely performant for I/O intensive loads and bad for CPU intensive loads. 
Whatsapp is written in Erlang. 

To support greenthreads, you need some sort of a "runtime". Look at nodejs, golang, python..all of them come with a "runtime". Whereas, systems programming languages like c++ and rust need to have extremely small binary size..and cannot afford to embed a runtime in that binary, nor  force the consumer to "hey you need to install nodejs in your system to run my code." it MUST be directly executable on the machine, as a binary.

