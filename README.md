# septheap
Organization of my own heap and general functions for working with it.  
Functions defined:  
• my_malloc()  
• my_realloc()  
• my_free()  
• my_memcpy()  
• my_memmove()  
• my_memset()  

## Usage  
Include `myheap.h` file.  
`namespace septmem` - namespace to work with its own heap-memory  
First of all, 50 MB of memory is reserved for use as its own heap.  
The bytes variable is responsible for the indexing step, that is, the number of offsets from the beginning of memory - heapmem [bytes].   Required for malloc () function.  
You can keep track of memory using `heapmap` structure. The `heapmap` structure contains fields:  
     - `used` / `free` - quantity of used and free  
       memory in bytes.  
     - `byteadd` - the unordered_map object, stores  
       the address of the first byte and the number of bytes of  
       allocated memory.  
`int* c = (int*)my_malloc(sizeof(int) * 8); // using my_malloc, allocate 32 bytes
c = (int*)my_realloc(c, sizeof(int)*2); // reallocate to 8 bytes
my_free(c); // free memory
my_memcpy(b, a, sizeof(a)); // copy sizeof(a) size data from a to b
my_memmove(e, f, sizeof(int)*5);  // copy 20 bytes from f to e
my_memset(f, 2, 5); // set 5 bytes of f in value 2`
