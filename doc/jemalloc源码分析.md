# je_malloc内存分析
## 对齐
为了减少存储器访问延迟，CPU中会有本地Cache，Cache被划分为cache line，大小一般为64B。 
CPU访问内存时，会首先将内存缓存在cache line中。在多处理器系统中，每个CPU都有自己的本地Cache，会导致数据多副本，也就带来了一致性问题：多个CPU的cache line中有相同地址的内存。
需要实现Cache Coherence Protocol来解决这个问题。
现代处理器一般使用MESI协议实现Cache Coherence，这会带来通讯耗时、总线压力、导致cache line的抖动，影响性能。
避免这个问题主要有下面几个方法：
1. __declspec (align(64)):变量起始地址按cache line对⻬
2. 当使用数组或结构体时，不仅需要起始地址对⻬，还需要padding，使得数组元素或结构体大小为cache line倍数
3. 避免多线程使用相近地址的内存，多使用局部变量。

