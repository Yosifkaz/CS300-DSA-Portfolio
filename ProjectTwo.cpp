/*
    Developer: Yosif Al-khazaali
    Course: CS-300-19616-M01 DSA: Analysis and Design
    Project: Project Two - ABCU Advising Assistance Program

    Purpose:
    This program helps ABCU academic advisors load a course file, store the courses
    in a binary search tree, print the Computer Science course list in alphanumeric
    order, and search for a specific course to view its title and prerequisites.
*/

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Course stores one line of course data from the input file.
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Node stores one course inside the binary search tree.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(const Course& aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;
    int courseCount;

    // Recursively deletes all nodes so memory is released correctly.
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Helper function used by insert() to place a course by alphanumeric course number.
    void addNode(Node* node, const Course& course) {
        if (course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                addNode(node->left, course);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                addNode(node->right, course);
            }
        }
    }

    // In-order traversal prints the courses from lowest to highest course number.
    void inOrder(Node* node) const {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ", " << node->course.title << endl;
            inOrder(node->right);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
        courseCount = 0;
    }

    ~BinarySearchTree() {
        clear();
    }

    void clear() {
        destroyTree(root);
        root = nullptr;
        courseCount = 0;
    }

    void insert(const Course& course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }

        ++courseCount;
    }

    Course* search(const string& courseNumber) const {
        Node* current = root;

        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return &(current->course);
            }
            else if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return nullptr;
    }

    void printCourseList() const {
        if (root == nullptr) {
            cout << "No course data is loaded." << endl;
            return;
        }

        cout << "Here is a sample schedule:" << endl;
        inOrder(root);
    }

    int size() const {
        return courseCount;
    }

    bool empty() const {
        return root == nullptr;
    }
};

// Removes leading and trailing whitespace from a string.
string trim(const string& value) {
    size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }

    size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

// Converts course numbers to uppercase so searches like "csci400" still work.
string toUpperCase(string value) {
    for (char& character : value) {
        character = static_cast<char>(toupper(static_cast<unsigned char>(character)));
    }

    return value;
}

// Splits one CSV line into tokens. The course files are simple comma-separated lines.
vector<string> splitCsvLine(const string& line) {
    vector<string> tokens;
    string token;
    stringstream stream(line);

    while (getline(stream, token, ',')) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

// Tries the entered file name first, then a couple of common local names for easier testing.
bool openCourseFile(ifstream& inputFile, const string& fileName) {
    inputFile.open(fileName);
    if (inputFile.is_open()) {
        return true;
    }

    vector<string> fallbackNames = {
        "ABCU_Advising_Program_Input.csv",
        "CS 300 ABCU_Advising_Program_Input.csv"
    };

    for (const string& fallbackName : fallbackNames) {
        inputFile.clear();
        inputFile.open(fallbackName);

        if (inputFile.is_open()) {
            cout << "Using file: " << fallbackName << endl;
            return true;
        }
    }

    return false;
}

// Reads the file, validates formatting and prerequisites, and returns course objects.
bool loadCoursesFromFile(const string& fileName, vector<Course>& courses) {
    ifstream inputFile;

    if (!openCourseFile(inputFile, fileName)) {
        cout << "Error: Could not open file '" << fileName << "'." << endl;
        return false;
    }

    vector<Course> parsedCourses;
    set<string> courseNumbers;
    string line;
    int lineNumber = 0;

    while (getline(inputFile, line)) {
        ++lineNumber;
        line = trim(line);

        // Ignore blank lines so accidental empty lines do not break the program.
        if (line.empty()) {
            continue;
        }

        vector<string> tokens = splitCsvLine(line);

        // Every valid row needs at least the course number and course title.
        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            cout << "Error: Invalid file format on line " << lineNumber << "." << endl;
            return false;
        }

        Course course;
        course.courseNumber = toUpperCase(tokens[0]);
        course.title = tokens[1];

        if (courseNumbers.count(course.courseNumber) > 0) {
            cout << "Error: Duplicate course number found: " << course.courseNumber << "." << endl;
            return false;
        }

        courseNumbers.insert(course.courseNumber);

        // Any fields after the title are prerequisites. Empty fields from trailing commas are skipped.
        for (size_t i = 2; i < tokens.size(); ++i) {
            string prerequisite = toUpperCase(tokens[i]);
            if (!prerequisite.empty()) {
                course.prerequisites.push_back(prerequisite);
            }
        }

        parsedCourses.push_back(course);
    }

    inputFile.close();

    if (parsedCourses.empty()) {
        cout << "Error: The file did not contain any course data." << endl;
        return false;
    }

    // Validate that every prerequisite listed in the file also exists as its own course.
    for (const Course& course : parsedCourses) {
        for (const string& prerequisite : course.prerequisites) {
            if (courseNumbers.count(prerequisite) == 0) {
                cout << "Error: Prerequisite " << prerequisite << " listed for "
                     << course.courseNumber << " does not exist as a course in the file." << endl;
                return false;
            }
        }
    }

    courses = parsedCourses;
    return true;
}

// Loads validated course objects into the binary search tree.
bool loadDataStructure(BinarySearchTree& courseTree, const string& fileName) {
    vector<Course> courses;

    if (!loadCoursesFromFile(fileName, courses)) {
        return false;
    }

    courseTree.clear();

    for (const Course& course : courses) {
        courseTree.insert(course);
    }

    cout << courses.size() << " courses loaded successfully." << endl;
    return true;
}

void printPrerequisites(const BinarySearchTree& courseTree, const Course& course) {
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites: ";

    for (size_t i = 0; i < course.prerequisites.size(); ++i) {
        const string& prerequisiteNumber = course.prerequisites[i];
        Course* prerequisiteCourse = courseTree.search(prerequisiteNumber);

        cout << prerequisiteNumber;

        // The title is included because the project asks for prerequisite numbers and titles.
        if (prerequisiteCourse != nullptr) {
            cout << " - " << prerequisiteCourse->title;
        }

        if (i < course.prerequisites.size() - 1) {
            cout << "; ";
        }
    }

    cout << endl;
}

void printCourseInformation(const BinarySearchTree& courseTree) {
    if (courseTree.empty()) {
        cout << "No course data is loaded. Please load the file first." << endl;
        return;
    }

    string courseNumber;
    cout << "What course do you want to know about? ";
    getline(cin, courseNumber);
    courseNumber = toUpperCase(trim(courseNumber));

    Course* course = courseTree.search(courseNumber);

    if (course == nullptr) {
        cout << "Course " << courseNumber << " was not found." << endl;
        return;
    }

    cout << course->courseNumber << ", " << course->title << endl;
    printPrerequisites(courseTree, *course);
}

void printMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    BinarySearchTree courseTree;
    string choiceInput;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        printMenu();
        getline(cin, choiceInput);

        try {
            choice = stoi(choiceInput);
        }
        catch (...) {
            cout << choiceInput << " is not a valid option." << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Enter the file name: ";
            getline(cin, fileName);
            fileName = trim(fileName);

            if (fileName.empty()) {
                fileName = "ABCU_Advising_Program_Input.csv";
            }

            loadDataStructure(courseTree, fileName);
            break;
        }
        case 2:
            if (courseTree.empty()) {
                cout << "No course data is loaded. Please load the file first." << endl;
            }
            else {
                courseTree.printCourseList();
            }
            break;
        case 3:
            printCourseInformation(courseTree);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
