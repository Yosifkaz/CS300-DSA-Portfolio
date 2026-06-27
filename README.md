# CS 300 Data Structures and Algorithms Portfolio

**Developer:** Yosif Al-khazaali  
**Course:** CS-300-19616-M01 DSA: Analysis and Design  
**Portfolio Focus:** Data structures, algorithm design, runtime analysis, and advising software development

## Portfolio Artifacts

This repository includes the main portfolio work from CS 300:

1. **Project One Runtime and Memory Analysis**  
   This artifact explains the runtime and memory behavior of the vector, hash table, and binary search tree data structures. It also explains why the binary search tree was the best fit for the advising program requirement.

2. **Project Two Advising Assistance Program**  
   This artifact is the completed C++ program for ABCU advisors. It reads course data from a file, loads it into a binary search tree, prints all courses in alphanumeric order, and allows the user to search for a specific course and its prerequisites.

## Reflection

### What was the problem I was solving in the projects for this course?

The main problem I was solving was how to build an advising assistance program for ABCU’s Computer Science department. The advisors needed a program that could load course data from a file, print all courses in alphanumeric order, and let a user search for one course to see its title and prerequisites. This sounds simple at first, but the important part was choosing the right data structure so the program would not just work, but would also be efficient, organized, and easy to maintain.

### How did I approach the problem, and why are data structures important?

I approached the problem by first looking at what the program needed to do most often. It needed to store course objects, print the full list in order, and search for a single course. Because of that, I compared a vector, a hash table, and a binary search tree. A vector is simple and easy to load, but it needs to be sorted before printing and it can be slower when searching. A hash table is very fast for direct lookup, but it does not naturally keep the courses in order. A binary search tree made the most sense for this project because an in-order traversal prints the courses in sorted order, and searching is still efficient when the tree is reasonably balanced. This showed me why data structures matter so much. The structure I choose changes the speed, memory use, and overall design of the program.

### How did I overcome roadblocks while working through the activities and projects?

One roadblock was making sure the input file was handled correctly. The file had course numbers, titles, and optional prerequisites, so I had to make sure each line was parsed correctly and that empty or badly formatted lines did not break the program. I handled this by separating the file loading, trimming, parsing, and validation into their own functions. Another roadblock was making sure user input worked even if the user typed a course in lowercase, like `csci400`. I fixed that by converting course numbers to uppercase before searching. I also had to be careful with the binary search tree logic so courses were inserted correctly and printed in sorted order. Breaking the program into smaller parts made the issues easier to test and fix.

### How did this project expand my approach to designing software and developing programs?

This project helped me think more like a software designer instead of only trying to make the code run. Before coding, I had to think about the problem, compare different data structures, write pseudocode, and analyze runtime and memory. That made the coding part easier because I already had a plan. I also learned that a good solution is not always the shortest or easiest one. A good solution should match the requirements, handle bad input, and still be understandable later. This changed the way I look at programming because I now pay more attention to design decisions before jumping straight into code.

### How did this project evolve the way I write maintainable, readable, and adaptable programs?

My code became more maintainable because I kept each function focused on one job. For example, one function trims strings, another splits CSV lines, another loads the file, another inserts courses into the tree, and another prints course information. This makes the program easier to read and easier to change later. I also used clear names like `Course`, `BinarySearchTree`, `loadCoursesFromFile`, and `printCourseInformation` so the purpose of each part is obvious. I added comments where they help explain the logic without over-commenting every line. Overall, this project helped me write code that is cleaner, easier to test, and easier for another programmer to understand.

## Final Recommendation From Project One

For this advising program, I recommended using a binary search tree. The reason is that the advisors specifically need to print the course list in alphanumeric order, and a binary search tree can do that naturally using an in-order traversal. A hash table is faster for direct search on average, but it does not keep the data sorted. A vector is easy to use, but it needs extra sorting and has slower search time. The binary search tree gives the best overall balance for the project requirements because it supports ordered output and efficient course lookup in one structure.
