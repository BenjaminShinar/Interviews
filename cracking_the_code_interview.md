# Cracking the code interview
notes from reading the book (6th edition, 2015)


## sample questions in the book
* all o find all positive integer solutions under 1,000 to a^3 + b^3 = c^3 + d^3.

### Chapter 1: Arrays and Strings
1. Is Unique
    - with set: insert until there is already a match
    - without DS - for each char, search if it exists in the rest
    - sort and then check - **not Implemented**
2. Check permutations
    -  with map - count appearences of each char and compare maps
    -  sort and then check - **not Implemented**
3. Urlify
    - simple form (many copies) works
    - advanced form still is buggy - **can't get it to works**
4. Is permutation of palindrome?
    - with map: count appearnces and then ensure that at most one entry is odd.
    - with hash - if not exist, add, if exists, remove. ensure that there is at most one enrty
        - can be improved if we keep count of the size and exit if we decide there is no longer a chance to find a match 
5. Is One Change away?
    - early exit if lengths are two far appart
6. stringCompression and decompression
    - early exit if we determine our built string to be too long
7. rotate matrix in place
    - *not sure, need example*
8. zero matrix row and columns
    - 2x2 and 3x3 are pretty trivial. larger matrixes require another loop.
9. is String a rotation of another string using One call to isSubstring
    - concatenate one string to itself and then call isSubstring
    - either do this twice and boolean **&&** the results or check the lengths beforehand to avoid getting false positives from isSubstring


### Chapter 2: Linked Lists
1. Remove Duplicates from unsorted linkedList
    - with set: similiar to string is unique, create set, and each time try to insert the next node, if it already exists, remove it.
    - without extra buffer **not implemented**
2. return Kth to Last
    k Should be non zero positive (1 for last element)
    - use recursiveFunction
    - use iterative style, circular buffer or whatnot
3. delete middleNode
    - this is just swap and delete next
4. partition
    - using two lists... *I don't have actual nodes in CPP, so i'm not really moving nodes*
    - in C i could probably keep a running pointer and move nodes around easily.
5. sum lists of digits
    - get sum of each list, combine and then create new list
6. is linkedList a palindrome
    - the hints are to reverse the list, use a stack,try recursion
    - stack works - jump to the mid point (need length) and start inserting to stack, then iterate with from the head and compare to stack. this is basically reversing half the list on somewhere else.
7. determine intersection **not implemented**
    - use lengths to make sure nodes are the distance from the end, and then advance them and compare. *I don't have actual nodes in CPP, so i'm not going to do this*
    - might be weird in cpp becuase nodes aren't necesarly pointing to null, and have a unique end position?
    - maybe its possible to early exis when calculatin lengths.
8. find loop start **not implemented**
    - -make slow and fast runners, their meeting point is the intersection. *I don't have actual nodes in CPP, so i'm not going to do this*

### Chapter 3: Stacks and Queues
1. three stacks in one array? **not implemented**
    - maybe like linked list? each element holds the previous element location, and we store the top and update it at push(),pop()?
2. stack that provides O(1) min() operation
    - use two stacks, one for values, other for min values
3. stack of plates: self regulating stacks
    - have a stack of stacks that adds new stack at push (if needed) and removes at pop(if needed). just be careful not to to top() an empty stack.
    - add 'pop at index' : use vector or lineked list of stacks instead of stack of stacks.
4. queue via two stack **not implemented**
    - *hints: 15,32,43 - new sorted order? imagine other stack is sorted? use main and secondary stack?*
    - keep one stack with One element, and the other with all the rest elements
    - at deque, use the shortstack, and then put all the other elements in it except for on.
    - at enqueu - add to the long list (unless one is empty, then add to it and remember which is the recent one)?
5. sort stack (with other stack) **not implemented**
    - feels like hannoi towers.
   
6. FIFO animal strucutre cats and dogs
    - need to have a linked list for enques or keep end iterator... not very fun

### Chapter 4: Trees and Grpahs
trees, binary trees, binary search tree, balanced and unbalanced trees, complete,full and perfect trees.  
Traversal: inOrder (left, parent, right), preOrder(parent,left,right), postOrder(left, right parent).  
Binary Heaps. Tries.
DFS - depth first Search - use stack
BFS - breadth first search - use queue
1. Route between nodes - *I don't know graphs*
2. minimal tree from sorted array
3. list of nodes in each depth
4. check is tree Balanced
5. validate tree is binary search tree
6. successor - find next node in tree, assume bidirectional tree/
7. build order
8. common ancestor
9. bst sequqance- print possible arrays?
10. check if tree is subtree of other tree
11. tree that gives Random Node.
12. count paths to sum

### Chapter 5: Bit Manipulation
1. insertion
2. binary to string 
transform from double to binary? how?
3. flip bit and get largest sequance
4. next numbers with same number of ON Bits
5. explain **((n & (n-1))==0)**
This will tell us if n is a power of 2 or not.
a number that is a power of 2 has just 1 ON bit, so decremeting it by 1 will make all the bits after it 1, so the logical **and** will result in zero.
6. how many bits to flip to convert?
    - feels like all I need to to do is to xor the numbers and count the on bits.
7. pairwise swap?
8. draw line?

