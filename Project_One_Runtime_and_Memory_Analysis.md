# Project One Runtime and Memory Analysis

**Developer:** Yosif Al-khazaali  
**Course:** CS-300-19616-M01 DSA: Analysis and Design

## Purpose

Project One focused on choosing the best data structure for ABCU's advising program. The program needed to load course data, store each course as an object, print all courses in alphanumeric order, and search for one course to display its title and prerequisites. I compared three data structures: vector, hash table, and binary search tree.

## Assumptions Used in the Analysis

- `n` is the number of courses loaded from the file.
- `p` is the average number of prerequisites per course.
- Each course object stores a course number, title, and a list of prerequisite course numbers.
- File validation checks that every line has at least a course number and title.
- File validation also checks that every prerequisite listed exists as a course in the file.

## Loading Runtime and Memory

| Data Structure | Loading Steps | Average Runtime | Worst-Case Runtime | Memory Use | Explanation |
|---|---|---:|---:|---:|---|
| Vector | Read each line, parse tokens, create course object, push course into vector, validate prerequisites | O(n + n*p) | O(n + n*p) | O(n) | A vector loads data simply because each course can be appended to the end. The validation step depends on how many prerequisites are checked. Since the course file is small and each course only has a few prerequisites, this is efficient in practice. |
| Hash Table | Read each line, parse tokens, create course object, hash the course number, insert into bucket, validate prerequisites | O(n + n*p) average | O(n^2) if many collisions happen | O(n + b) | A hash table is fast when the hash function spreads keys across buckets. The extra bucket array adds some memory, but the main memory cost is still the course objects. The worst case happens if many courses collide into the same bucket chain. |
| Binary Search Tree | Read each line, parse tokens, create course object, compare course numbers, insert into tree, validate prerequisites | O(n log n + n*p) average | O(n^2 + n*p) if unbalanced | O(n) | A binary search tree stores courses as nodes with left and right pointers. If the tree is reasonably balanced, inserts are efficient. If the file is already in sorted order and the tree is not self-balancing, the tree can become a long chain, causing slower worst-case behavior. |

## Advisor Requirement Runtime Comparison

| Requirement | Vector | Hash Table | Binary Search Tree |
|---|---:|---:|---:|
| Print all courses in alphanumeric order | O(n log n) if sorting is needed | O(n log n) because courses must be collected and sorted | O(n) using in-order traversal |
| Search for one course | O(n) | O(1) average, O(n) worst case | O(log n) average, O(n) worst case |
| Print prerequisites for a course | O(p) after course is found | O(p) after course is found | O(p) after course is found |
| Memory use | O(n) | O(n + b) | O(n) |

## Vector Evaluation

A vector is the easiest structure to understand and implement. It stores courses in a simple list, and adding a new course to the end is efficient. It also has good memory behavior because the data is stored in one resizable array. The disadvantage is that a vector does not automatically keep the courses sorted unless sorting is performed. Searching for a single course can also take O(n) time because the program may need to check every course until it finds the right one. This makes the vector simple, but not the strongest choice for the advisor requirements.

## Hash Table Evaluation

A hash table is very strong for finding a single course quickly. With a good hash function, looking up a course by course number is close to O(1) on average. This is useful when an advisor wants to quickly find one course. The disadvantage is that a hash table does not naturally store courses in sorted order. To print the full course list alphabetically or alphanumerically, the program has to collect all courses from the buckets and sort them first. This adds extra logic and O(n log n) sorting time. Hash tables also have possible collision issues, which means worst-case search can become O(n) if many items land in the same bucket.

## Binary Search Tree Evaluation

A binary search tree is a strong fit for this project because the course number can be used as the key. Courses smaller than the current node go to the left, and courses larger than the current node go to the right. This makes it possible to print all courses in sorted order using an in-order traversal, which runs in O(n) time. Searching for one course is also efficient on average at O(log n), as long as the tree is not badly unbalanced. The main disadvantage is that a normal binary search tree can become unbalanced if the data is inserted in sorted order. Even with that risk, it still matches the advising program well because sorted output is one of the main requirements.

## Recommendation

My recommendation was to use the binary search tree for Project Two. The main reason is that the advisors need a sorted course list, and the tree handles that naturally through in-order traversal without needing a separate sorting step. A hash table is faster for direct lookup on average, but it creates extra work when printing the full course list in order. A vector is simple, but it is not as efficient for search and also needs sorting. The binary search tree gives the best balance for this project because it supports both sorted output and efficient course lookup in a clean structure.
