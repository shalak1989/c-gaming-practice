<!-- 
remember pointers are variables that point to other blocks of data

1. assignable
2. deferencerable (can access data)
3. incrementable, can use pointers arithmetic to move

32 bit example recap:

Man man = {0, 0, 10, NULL};
man.x = 50;

Man *ptr

*ptr = &man

int array[1024] = {0};
int *ptr = array;

array == &array[0] always true

dynamic allocation:

//int array[1024] = {0};
int *array = malloc(sizeof(int)*1024);

you can use it as long as you want, its on the heap not the stack and doesn't disappear with function scope

free(array);
array = NULL;

Man *ptr;
ptr = malloc(sizeof(Man));
ptr->x = 50;
free(ptr);

Tools of dynamic allocation

void *malloc(size_t num_bytes);
uses void pointer, these exist for temporarily having a pointer that can point to any type which later gets assigned to a concrete type

free(void *ptr) - must free everything eventually

in SDL, surfaces, textures, etc... all under the hood use malloc and free. This is why we have to free them later.

Watch out for pitfalls of freeing bad pointers:

1. NULL pointers or freeing an already freed pointer will crash, must check pointer validity first
2. Not catching things you need to be freed causes memory leaks which don't go away until your program quits.... sometimes this can persist to the OS level and wont free until
computer restart

If a function returns a pointer, check documentation to see what its "destroy" function is. usually destroy, release, close, or shutdown

Don't just call the default free function because there is probably something you will miss.

***Just be careful whenever using any library/built in function that returns pointers and make sure its freed appropriately later with the right function.

 -->