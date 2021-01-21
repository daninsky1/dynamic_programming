#pragma once
#include <iostream>
#include <vector>
//
// PRINT VECTOR
//
template<typename T>
void printv(const std::vector<T> &vector, const bool endline = true)
{
    // 1D vector
    const int v_size = vector.size();    // size of the vector
    
    std::cout << '{';
    for(int i = 0; i < v_size; ++i){
        std::cout << vector[i];
        if(i < v_size - 1)   // put comma until the last element
            std::cout << ", ";
    }
    std::cout << '}';
    if(endline) std::cout << std::endl;
}

template<typename T>
void printv(const std::vector<std::vector<T>> &vector, const bool endline = true, const bool extra_indent = false)
{
    // 2D vector
    const int v_size = vector.size();        // size of the vector
    
    if(extra_indent) std::cout << "    ";
    std::cout << "{\n";
    for(int i = 0; i < v_size; ++i){
        if(extra_indent) std::cout << "    ";
        std::cout << "    ";
        printv(vector[i], false);
        if(i < v_size - 1)   // put comma and \n until the last element
            std::cout << ", \n";
    }
    std::cout << '\n';
    if(extra_indent) std::cout << "    ";
    std::cout << '}';
    if(endline) std::cout << std::endl;
}

template<typename T>
void printv(const std::vector<std::vector<std::vector<T>>> &vector)
{
    // 3D vector
    const int v_size = vector.size();        // size of the vector
    
    std::cout << "{\n";
    for(int i = 0; i < v_size; ++i){
        printv(vector[i], false, true);
        if(i < v_size - 1)   // put comma until the last element
            std::cout << ", \n";
    }
    std::cout << "\n}" << std::endl;
}
//
// TESTS
//
void printv_test1()
{
    // 1d vectors
    std::vector<char> char_list1 = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    std::vector<char> char_list2 = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    std::vector<int> int_list1 = {1, 20, 300, 1'000, 10'000, 100'000, 1'000'000};
    std::vector<int> int_list2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<double> double_list1 = {1.1, 20.22, 300.333, 400.4444};
    std::vector<double> double_list2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::vector<std::string> str_list1 = {
        "purp", "le", "p", "ur", "p", "le"
    };
    std::vector<std::string> str_list2 = {
        "ab", "cd", "ef", "ab", "c", "def", "abc", "def", "abcd", "ef"
    };
    printv(char_list1);
    printv(char_list2);
    printv(int_list1);
    printv(int_list2);
    printv(double_list1);
    printv(double_list2);
    printv(str_list1);
    printv(str_list2);
}

void printv_test2()
{
    // 2d vectors
    std::vector<std::vector<char>> char_list1 = {
        {'a', 'b', 'c', 'd', 'e'},
        {'f', 'g', 'h', 'i', 'j'}
    };
    std::vector<std::vector<char>> char_list2 = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'J'}
    };
    std::vector<std::vector<int>> int_list1 = {
        {1, 20, 300, 1'000},
        {10'000, 100'000, 1'000'000}
    };
    std::vector<std::vector<int>> int_list2 = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10 }
    };
    std::vector<std::vector<double>> double_list1 = {
        {1.1, 20.22},
        {300.333, 400.4444}
    };
    std::vector<std::vector<double>> double_list2 = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };
    std::vector<std::vector<std::string>> str_list1 = {
        {"purp", "le"},
        {"p", "ur", "p", "le"}
    };
    std::vector<std::vector<std::string>> str_list2 = {
        {"ab", "cd", "ef"},
        {"ab", "c", "def"},
        {"abc", "def"},
        {"abcd", "ef"}
    };
    printv(char_list1);
    printv(char_list2);
    printv(int_list1);
    printv(int_list2);
    printv(double_list1);
    printv(double_list2);
    printv(str_list1);
    printv(str_list2);  
}

void printv_test3()
{
    // 2d vectors
    std::vector<std::vector<std::vector<char>>> char_list1 = {
        {
            {'a', 'b', 'c', 'd', 'e'},
            {'f', 'g', 'h', 'i', 'j'}            
        },
        {
            {'A', 'B', 'C', 'D', 'E'},
            {'F', 'G', 'H', 'I', 'J'}
        }
    };
    std::vector<std::vector<std::vector<char>>> char_list2 = {
        {
            {'A', 'B', 'C', 'D', 'E'},
            {'F', 'G', 'H', 'I', 'J'}
        },
        {
            {'a', 'b', 'c', 'd', 'e'},
            {'f', 'g', 'h', 'i', 'j'}            
        }
    };
    std::vector<std::vector<std::vector<int>>> int_list1 = {
        {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10 }
        },
        {
            {1, 20, 300, 1'000},
            {10'000, 100'000, 1'000'000}
        }        
    };
    std::vector<std::vector<std::vector<int>>> int_list2 = {
        {
            {1, 20, 300, 1'000},
            {10'000, 100'000, 1'000'000}
        },  
        {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10 }
        }
    };
    std::vector<std::vector<std::vector<double>>> double_list1 = {
        {
            {1.1, 20.22},
            {300.333, 400.4444}
        },
        {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
        }
    };
    std::vector<std::vector<std::vector<double>>> double_list2 = {
        {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
        },
        {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
        }
    };
    std::vector<std::vector<std::vector<std::string>>> str_list1 = {
        {
            {"purp", "le"},
            {"p", "ur", "p", "le"}
        },
        {
            {"ab", "cd", "ef"},
            {"ab", "c", "def"},
            {"abc", "def"},
            {"abcd", "ef"}
        }
    };
    std::vector<std::vector<std::vector<std::string>>> str_list2 = {
        {
            {"ab", "cd", "ef"},
            {"ab", "c", "def"},
            {"abc", "def"},
            {"abcd", "ef"}
        },
        {
            {"purp", "le"},
            {"p", "ur", "p", "le"}
        }
    };
    printv(char_list1);
    printv(char_list2);
    printv(int_list1);
    printv(int_list2);
    printv(double_list1);
    printv(double_list2);
    printv(str_list1);
    printv(str_list2);  
}