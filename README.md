# HashTable-from-scratch

Implemented a templated HashTable class in C++ with open addressing from scratch which: 
- Consists of a templated base (parent) Prober class and has templated LinearProber and DoubleHashProber children classes inheriting from it.
- The key to be probed can be set to any type by the user.
- In order to minimize the probability of collisions, the HashTable resizes itself and rehashes all its element whenever the alpha (loading factor) reaches   the desired alpha passed in by the user (default is set to 0.4). Additionally, the HashTable uses prime table sizes only.
