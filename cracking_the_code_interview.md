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
9. is String a rotation of another string using One call to isSubstring


### Chapter 2: Linked Lists