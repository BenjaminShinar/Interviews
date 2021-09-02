# Cracking the code interview

notes from reading the book (6th edition, 2015)

## sample questions in the book

- all o find all positive integer solutions under 1,000 to a^3 + b^3 = c^3 + d^3.

### Chapter 1: Arrays and Strings

1. Is Unique
   - with set: insert until there is already a match
   - without DS - for each char, search if it exists in the rest
   - sort and then check - **not Implemented**
2. Check permutations
   - with map - count appearances of each char and compare maps
   - sort and then check - **not Implemented**
3. Urlify
   - simple form (many copies) works
   - advanced form still is buggy - **can't get it to works**
4. Is permutation of palindrome?
   - with map: count appearances and then ensure that at most one entry is odd.
   - with hash - if not exist, add, if exists, remove. ensure that there is at most one entry
     - can be improved if we keep count of the size and exit if we decide there is no longer a chance to find a match
5. Is One Change away?
   - early exit if lengths are two far apart
6. stringCompression and decompression
   - early exit if we determine our built string to be too long
7. rotate matrix in place
   - _not sure, need example_
8. zero matrix row and columns
   - 2x2 and 3x3 are pretty trivial. larger matrixes require another loop.
9. is String a rotation of another string using One call to isSubstring
   - concatenate one string to itself and then call isSubstring
   - either do this twice and boolean **&&** the results or check the lengths beforehand to avoid getting false positives from isSubstring

### Chapter 2: Linked Lists

1. Remove Duplicates from unsorted linkedList
   - with set: similar to string is unique, create set, and each time try to insert the next node, if it already exists, remove it.
   - without extra buffer **not implemented**
2. return Kth to Last
   k Should be non zero positive (1 for last element)
   - use recursiveFunction
   - use iterative style, circular buffer or whatnot
3. delete middleNode
   - this is just swap and delete next
4. partition
   - using two lists... _I don't have actual nodes in CPP, so i'm not really moving nodes_
   - in C i could probably keep a running pointer and move nodes around easily.
5. sum lists of digits
   - get sum of each list, combine and then create new list
6. is linkedList a palindrome
   - the hints are to reverse the list, use a stack,try recursion
   - stack works - jump to the mid point (need length) and start inserting to stack, then iterate with from the head and compare to stack. this is basically reversing half the list on somewhere else.
7. determine intersection **not implemented**
   - use lengths to make sure nodes are the distance from the end, and then advance them and compare. _I don't have actual nodes in CPP, so i'm not going to do this_
   - might be weird in cpp because nodes aren't necessarily pointing to null, and have a unique end position?
   - maybe its possible to early exit when calculating lengths.
8. find loop start **not implemented**
   - -make slow and fast runners, their meeting point is the intersection. _I don't have actual nodes in CPP, so i'm not going to do this_

### Chapter 3: Stacks and Queues

1. three stacks in one array? **not implemented**
   - maybe like linked list? each element holds the previous element location, and we store the top and update it at push(),pop()?
2. stack that provides O(1) min() operation
   - use two stacks, one for values, other for min values
3. stack of plates: self regulating stacks
   - have a stack of stacks that adds new stack at push (if needed) and removes at pop(if needed). just be careful not to to top() an empty stack.
   - add 'pop at index' : use vector or linked list of stacks instead of stack of stacks.
4. queue via two stack **not implemented**
   - _hints: 15,32,43 - new sorted order? imagine other stack is sorted? use main and secondary stack?_
   - keep one stack with One element, and the other with all the rest elements
   - at dequeue, use the short stack, and then put all the other elements in it except for on.
   - at enqueue - add to the long list (unless one is empty, then add to it and remember which is the recent one)?
5. sort stack (with other stack) **not implemented**
   - feels like Hanoi towers.
6. FIFO animal structure cats and dogs
   - need to have a linked list for enqueues or keep end iterator... not very fun

### Chapter 4: Trees and Graphs

trees, binary trees, binary search tree, balanced and unbalanced trees, complete,full and perfect trees.  
Traversal: inOrder (left, parent, right), preOrder(parent,left,right), postOrder(left, right parent).  
Binary Heaps. Tries.
DFS - depth first Search - use stack
BFS - breadth first search - use queue

1. Route between nodes - _I don't know graphs_
2. minimal tree from sorted array
3. list of nodes in each depth
4. check is tree Balanced
5. validate tree is binary search tree
6. successor - find next node in tree, assume bidirectional tree/
7. build order
8. common ancestor
9. bst sequence- print possible arrays?
10. check if tree is subtree of other tree
11. tree that gives Random Node.
12. count paths to sum

### Chapter 5: Bit Manipulation

1. insertion
2. binary to string
   transform from double to binary? how?
3. flip bit and get largest sequence
4. next numbers with same number of ON Bits
5. explain **((n & (n-1))==0)**
   This will tell us if n is a power of 2 or not.
   a number that is a power of 2 has just 1 ON bit, so decrementing it by 1 will make all the bits after it 1, so the logical **and** will result in zero.
6. how many bits to flip to convert?
   - feels like all I need to to do is to xor the numbers and count the on bits.
7. pairwise swap?
8. draw line?

### Chapter 6: Math and Logic

some probability questions

1. Identify Heavy bottle of pills with exact scale
   - probably 1..N bottles from each bottle.

```
for K= 1 to N, take K pills for from each bottle K.
total pills = 20*(1+20)/2 = 210 pills. expected weight is 210 grams.
take the calculated weight, subtract 210 grams and divide by the difference between weights, this will result in the index of the heavy bottle.

```

2. Basketball which probability is better?  
   at which value of _probability p_ it's better to take one shot (all or nothing) or take three shots.
   _I know this is 0.5, but can't express mathematically why_

```
p > (p^3)+(3c2*(p^2)*(1-p))
```

3. cover board with dominos
   - there are now 62 squares on the board, with 31 blocks of 2 to cover them.
   - from before _I know this is imposable,_
   - number of squares should be divisible by 4? no, because 3 \* 4 square is fine.
   - also not (N-1)_(M-1) is even because 3 _ 15 is bad.
   - maybe (N+M - 3) % 2 == 0?
   - checked wikipedia- it's because we are covering the same color of squares, so it's impossible. a domino piece must cover black and white squares, so we'll always be missing squares.
4. ants on a triangle  
   the ants will collide if one of them chooses a different direction than the others. so they will not collide if all choose the same direction, which means the probability to choose a direction power the number of ants (times two, because there are two possible directions)

```
2* (0.5 ^ n)
```

- _not sure why the shape of the polygon matters_

5. jugs of water - count 4 units with containers of 3,5
   - fill 5, pour into 3. {3/3,2/5}
   - spill 3, pour 5 into 3 {2/3,0/5}
   - fill 5 {2/3,5/5}
   - pour 5 into 3 {3/3,4/3}.
     jug 5 has 4 units of water.
6. blue eyed island
   - probably N, where N is the number of blue eyes people
   - if there is one person with blue eyes, he won't see anyone with blue eyes, so he must be it, so he boards the plane at day 1.
   - if there are two people with blue eyes, they see 1 person, and they know that an island with one person clears up after one day, so if they see one more person, they'll go to the plane at day 2.
   - etc...
7. gender rate in the apocalypse
   - feels like geometric distribution, number of tries until result.
   - mean is 1/0.5 = 2 kids per family, so ratio is 1:1
8. egg drop algorithm
   - i know it's about 14, but not sure why...
9. 100 lockers - flip lockers that are multiples of 1..N
   - i think this ends with 1, and any squared value of a prime.
   - all primes are on (by 1) and then off (by themselves)
   - all numbers that can be represented as x\*y are on by x, off by y.
   - only numbers that are x\*x have odd number of divisors.
10. find poison bottle from 1000 bottles using 10 strips that detect poison after 7 days.
    - relevant! look up corona pooling
    - stupid way: check half, wait a week,
      - check half of the poison suit, wait another week
      - 1000,500,250,125,64,32,16,8,4,2,1 - binary search. wastes too much time.
    - if we had one strip, we had to wait 1000 + 7 days to be sure. with one strip, we need N+7 tries.
    - if we have two strips, we can put p1,p2 on s1, p2,p3 on s2. if s1 and !s2 = p1, if s1 and s2 = p2, if !s1 and s2= p3.
    - can we expand this? - for 3 strips: one unique poison for each (x1,x2,x3), three poisons for each combinations (x12,x23,x13) and one for all three(x123) = total of seven checks =
      3c3 + 3c2 + 3c1 = 7. - for 4 strips? expected:4c4 + 4c3 +4c2 +4c1 = 1 + 4 +6 +4 = 15. (x1,x2,x3,x4)(x12,x13,x14,x23,x24,x34)(x123,x124,x134,x234)(x1234) - for ten strips? sum (10c[1..10]), excel says 1023, formula says **2 ^n -1** so (2^10) -1 = 1024 -1 = 1023.
    - this means that we just need to divide the poisons properly and we will get the results in one week exactly!
    - youtube has a different method of using powers of 2. i'm guessing it's the same core idea. assign each prisoner with a binary location, and have him drink all the bottles with the bit on in their number. then i take all the dead prisoners on bit and get the bottle number.

### Chapter 7: Object Oriented Design

#### Approach

six W's: Who, What, Where, When, How, Why
core objects (entities) and relationships (one to one, one to many, many to many).
actions between the core objects.
design patterns:

- singleton
- factory

1. Deck of cards - black jack game - get 21.

- objects:game, cards (how many decks in play?), players, dealer, hand.
- relationships: one game, with one dealer, N players, Q cards. each player has One or more hands (splitting)
- actions dealing cards, standing the hand, splitting the hand, hitting, doubling, or busting.
- are dealers a type of players? do they have stuff in common?

2. Call Center -three levels,

- dispatchCall(call, escalationLevel) - a singletons class (CallCenterCommand) gets the call and dispatches it according to the level.
- all levels of employees can escalate a call, by returnning it to the CallCenterCommand with the increased escalation level.
- the CallCenterCommand matches calls by looking at the escalation level and starting it's search from that level. if no employees of this level ara available, it will search in the higher locations. if possible, allow for 'hold call' method that either waits for N seconds for a call to end or subscribes to some synchronization method to attach itself to the next available employee.

3. Jukebox

- machine
- payment
- selection
- record
- song

4. parking lot
5. online book reader
6. jigsaw puzzle - this is interesting

- puzzle piece has edges?
- puzzle edge.
- bool fitsWith(PuzzleEdge edge1,PuzzleEdge edge2)
- if we put together two pieces, are they a new class or are they still a puzzle piece with transformed edges?
- how do I define the space which has two connected pieces? the empty space that has some edges in place and some missing? this needs to be updated at each connection.
- this is some damascened Data structure, maybe a graph? maybe we graph the missing parts instead of the existing parts?
- when connected to edge, the old piece is parent, so go in Perpendicular then the connection side, if, check connection, if we can go again and back, also check that?
- maybe linkedList?

7. chat-server
8. othello
9. circular array
10. mineSweeper

- populate board
- expose - iterative/recursive.
- when cell is clicked, if bomb, lose. else, mark as exposed.if value = 0 take none exposed cells surrounding them, whichever, expose them. if they are 0, put it sack put in stack. take element from stack (must be 0 value) and expose all it's neighbors like before. if element is not zero, don't push it's neighbors to a stack.
- have a flag to denote 'not exposed' that disallows exposing?
- win conditions - number of unexposed is the same as mines.
- board object, has squares (cells)
- cell object - has either a bomb or a number,can be exposed or not exposed. maybe also flag?
- don't forget about boundaries!

11. file system
12. hash table with linked lists to handle collisions.

### Chapter 8: Recursion and Dynamic Programming

1. Triple steps

- first try simple recursion!
  - at N-1: 1 options - > take one step.
  - at N-2: 2 options - > take two steps, or take one + N-1;
  - at N-3: 4 options - >take three steps, take two steps and then (N-1) = 1, take one step and then N(-2) =2. 1 + 1 +2 = 4 options.
  - at N-4: N-3(one step) + N-2 (two steps) N-1 (three steps) = 4 +2 +1 = 7
  - at N-5: N-4(one step) + N-3 (two steps) N-2 (three steps)
    = 7 +4 +2 = 13
  - at N-6: N-5(one step) + N-4 (two steps) N-3 (three steps)
    = 13 + 7 +4 = 24.
  - 24 + 13 +7 = 44.
  - 44 + 24 + 13 =81
- this obviously is a bad idea. but what can we do instead?
- memoization like fibonacci question, i guess

2. robot on a grid
   memoization, iterative, whatever
3. find magic index in a sorted array

- why is this dynamic/recursion?
- just do binary search or something.choose number x between bottom, top, check a[x], if it's lower than x, get x in value [x,top], if higher, [bottom,x], continue until match or top and bottom are equal or something like that.

4. all subsets of a set

- yikes. if we simply remove an element,recurse on ourselves and return it in, we'll have duplications.
- make other set S2, iterate over set 1, add to element to s2 and print s2, after that, add an element from s1 to s2. start again.

5. recursive multiply of (N\*M) positive, natural numbers only.
   - add N to itself M times
   - better: if M is even (m % 2==0), shift left the product, and shift right M, then continue.
6. Hanoi towers
7. permutations of unique items
8. permutations with duplications removal
9. parenthesis validation

- use stack, add opening parentheses, if meeting closing parentheses, check it against the top of the stack, if matching remove,else error. if finished and the stack has something, error.

10. paint-fill
11. represents N with different coins

- feels like dynamic programming. we create maps (coin:amount) and take unique
- nickels:5 cents, dimes: 10 cents, quarter:25 cents

12. eight queens
13. stack of boxes
14. boolean evaluation count ways of parenthesis expression

### Chapter 9: System design and Scalability

1. stock data
2. social network
3. web Crawler
4. detect duplicate urls

- maybe trie tree?

5. cache
6. sales rank
7. personal financial manager
8. paste-bin

### Chapter 10: Sorting and Searching

1. sorted merge
2. group anagrams
3. search in rotated array
4. sorted search with no size
5. sparse search
6. sort big file
7. missing int
8. find duplicates of 1...N (max 32,000) with 4k of memory
9. sorted matrix search
10. rank from stream
11. peaks and valleys

### Chapter 11: Testing

1. find mistake in code

```cpp
unsigned int i;
for (i=100; i >=0;--i)
    printf("%d\n",i);
```

    - unsigned int can't be less than zero, it will underflow to max unsigned int

2. random crashes
3. chessTest - canMoveTo(int x, int y)
4. test webpage without test tools
5. test a pen
6. test an ATM in distributed banking system

### Chapter 12: C and C++

1. Last K Lines from file

- maybe keep a K sized circular vector of offsets/positions, and when we reach the EOF, we can fseek back and start reading

2. reverse null terminated string

- go to the end, place ptr in the end and in the start, start swapping until meeting/passing

3. hash table vs stl map
4. how do virtual functions work
5. shallow vs deep copy
6. volatile
7. why must we have a virtual destructor in the base class when deleting through a base-class pointer.
8. copy node
9. smart ptr with reference counting
10. malloc aligned to power of 2. free() without parameters

- request 1000+128 (maybe +1?) bytes, immediately before the data that we give to the user, write an offset to the real start of the data.
- when trying to free,look up before the data for the offset, and then free from that point.

11. 2d allocation of m,n that returns 2d array with [][] syntax

- calculate the amount needed and request it in one malloc, and then cast it as pointer of the correct type.

### Chapter 13: Java

1. using private ctor in inheritance
2. can we return from a 'finally' block?
3. final, finally, finalize
   - final: class can't be inherited, method can't be overridden.
   - finally: try-catch-finally block
   - finalize: a method the garbage collector uses.
4. c++ templates vs java generics
   - c++ is compile time, they appear in the compiled code differently for each type. generics are synthetic sugar that remove the need to remember the casting operations. the function uses the Object object.
5. TreeMap, HashMap,LinkedHashMap differences

- hashMap: quick retrieval,
- tree map
- linkedHashMap: probably fast insertion, slow retrieval

6. object reflection

- query the Class object and the object itself to identify it's behavior.
- good for runtime generics.

7. lambda expression
8. lambda random

### Chapter 14: Databases

1. tenants with more than one apartment
2. find all open requests
3. close all requests
4. joins
5. de-normalization
6. entity relationship diagram
7. design grade database

### Chapter 15: Threads and Locks

1. thread vs process
2. how to measure time in context switch
3. dinning philosophers problem
4. deadlock free class
5. call in order
6. synchronized methods
7. threaded fizzbuzz

### Chapter 16: Moderate Difficulty

1. number swapper in place
2. word frequencies in a book
3. intersection of straight lines
4. tic tac wn
5. factorial zeros
6. smallest differences of two arrays
7. number max without if-else
8. english int
9. multiply, subtract, and divide using addition operator for integers
10. living people count.
11. diving board
12. xml encoding
13. bisect square
14. best line
15. master mind
16. sub sort
17. contiguous sequence
18. pattern matching
19. pond sizes
20. T9 keypad
21. sumSwap
22. langton's ant
23. rand7 from rand5.
24. pairs with sum
25. Lru (least recently used) cache
26. Calculator from equation.

### Chapter 15: Hard Difficulty

1. add without plus
2. shuffle
3. random set
4. missing number when we can only access and a bit
5. find loges subareas of numbers and letters
6. count of 2's in numbers between 0 and N.
7. baby names
8. circus towers
9. k-th multiple
10. majority element of an array in O(N) time and O(1) space
11. word distance from large text
    - what if this was repeated?
12. BiNode - from treeNode to doublyLinkedList node
13. reSpace text - insert spaces to recover a text.
14. return smallest K numbers in an array
15. longest word that can be constructed by other words in the list
16. the Massuse schedule algorithm
17. multi search of string and array of smaller strings
18. shortest super sequence
19. missing number 1..N
    - what if two numbers are missing
20. continues median from random source
21. volume of histogram
22. word transformer by one letter and keep being valid
23. maximum black sub square
24. maximum sum value sum matrix
25. word rectangle
26. sparse similarity
