#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include "printv.h"


//
// DYNAMIC PROGRAMMING
//

// example of o(n) time and O(n) space

int foo(int n)
{
    // O(n) time
    // O(n) space
    if (n <= 1) return 1;
    foo(n - 1);
}

int bar(int n)
{
    // O(n/2) time
    // O(n/2) space
    if (n <= 1) return 1;
    bar(n - 2);
}

// foo and bar have the same space and time complexity

int dib(int n)
{
    // O(2 ^ n) time
    // O(n) space
    if (n <= 1) return 1;
    dib(n - 1);
    dib(n - 1);
}

int lib(int n)
{
    // O(2 ^ n/2) time
    // O(n/2) space
    if (n <= 1) return 1;
    lib(n - 2);
    lib(n - 2);
}
//
// FIBONACCI RECURSION
//
unsigned long long int fib_recu(const int &n)
{
    // O(2^n) time
    // O(n) space
    if(n <= 2) return 1;
    return fib_recu(n - 1) + fib_recu(n - 2);
}
//
// FIBONACCI MEMOIZATION
//
unsigned long long int fib_memo(const int &n, std::map<int, long long int>& memo)
{
    // O(n) time
    // O(n) space
    if(memo.count(n)) return memo[n];
    if(n <= 2) return 1;
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    return memo[n];
}

unsigned long long int fib_memo(const int &n)
{
    std::map<int, long long int> memo;
    return fib_memo(n, memo);
}
//
// FIBONACCI TABULATION
//
unsigned long long int fib_tab(const int &n)
{
    // time O(n)
    // space O(n)
    std::vector<long long int> table(n + 1, 0);
    table[1] = 1;
    for(int i = 0; i < table.size() - 2; ++i){
        table[i + 1] += table[i];
        table[i + 2] += table[i];
    }
    table[table.size() - 1] += table[table.size() - 2];
    return table[n];
}
//
// FIBONACCI CALLER
//
unsigned long long int fib(const int &n, unsigned long long int(*fib_fun)(const int&) = fib_tab)
{
    // max number 12,200,160,415,121,876,738
    if(n > 93) std::clog << "Number > 93, FIB OVERFLOW!" << std::endl;
    else if(n < 0){
        std::clog << "Negative number! Invalid." << std::endl;
        return 0;
    }
    else if(n == 0) return 0;
    else if(n == 1 || n == 2) return 1;
    return fib_fun(n);  // callback fib algorithm
}

void test_fib(unsigned long long int(*fib_fun)(const int&) = fib_tab)
{
    std::map<int, long long int> memo;
    std::cout << fib(6, fib_fun) << '\n';    // 8
    std::cout << fib(7, fib_fun) << '\n';    // 13
    std::cout << fib(8, fib_fun) << '\n';    // 21
    std::cout << fib(50, fib_fun) << '\n';   // 12'586'269'025
}
//
// GRID TRAVELER RECURSION
//
unsigned int grid_traveler_recu(const int &x, const int &y)
{
    // O(2 ^ y+x) time
    // O(y+x) space
    if (x == 1 && y == 1) return 1;
    if (x == 0 || y == 0) return 0;
    return grid_traveler_recu(x - 1, y) + grid_traveler_recu(x, y - 1);
}
//
// GRID TRAVELER MEMOIZATION
//
unsigned int grid_traveler_memo(const int &x, const int &y, std::map<std::vector<int>, long long int>& memo)
{
    // O(x * y) time
    // O(y + x) space
    const std::vector<int> key = { x, y };
    if (memo.count(key)) return memo[key];
    if (x == 1 && y == 1) return 1;
    if (x == 0 || y == 0) return 0;
    memo[key] = grid_traveler_memo(x - 1, y, memo) + grid_traveler_memo(x, y - 1, memo);
    return memo[key];
}

// overload
unsigned int grid_traveler_memo(const int &x, const int &y)
{
    std::map<std::vector<int>, long long int> memo;
    return grid_traveler_memo(x, y, memo);
}
//
// GRID TRAVELER TABULATION
//
unsigned int grid_traveler_tab(const int &x, const int &y)
{
    // O(n*m) time
    // O(n*m) space
    std::vector<std::vector<int>> table(x+1, std::vector<int>(y+1, 0));
    table[1][1] = 1;
    for(int i = 0; i <= x; ++i){
        for(int j = 0; j <= y; ++j){
            const int current = table[i][j];
            if(j+1 <= y) table[i][j + 1] += current;
            if(i+1 <= x) table[i + 1][j] += current;
        }
    }
    return table[x][y];
}
//
// GRID TRAVELER CALLER
//
unsigned int grid_traveler(const int &x, const int &y, unsigned int(*grid_traveler_func)(const int&, const int&) = grid_traveler_tab)
{
    if(x < 0 || y < 0) std::clog << "Negative numbers are not alowed." << std::endl;
    if (x == 1 && y == 1) return 1;
    if (x == 0 || y == 0) return 0;
    return grid_traveler_func(x, y);
}

void test_grid_traveler(unsigned int(*grid_traveler_func)(const int&, const int&))
{
    std::cout << grid_traveler(1, 1, grid_traveler_func) << '\n';   // 1
    std::cout << grid_traveler(2, 3, grid_traveler_func) << '\n';   // 3
    std::cout << grid_traveler(3, 2, grid_traveler_func) << '\n';   // 3
    std::cout << grid_traveler(3, 3, grid_traveler_func) << '\n';   // 6
    std::cout << grid_traveler(18, 18, grid_traveler_func) << '\n'; // 2'333'806'220
}
//
// CAN SUM RECURSION
//
bool can_sum_recu(const int &target, const std::vector<int> &numbers)
{
    // O(n ^ m) time
    // O(m) space
    if (target == 0) return true;
    if (target < 0) return false;
    
    for (int number : numbers){
        const int remainder = target - number;
        if (can_sum_recu(remainder, numbers))
            return true;
    }
    return false;
}
//
// CAN SUM? MEMOIZATION
//
bool can_sum_memo(const int &target, const std::vector<int> &numbers, std::map<int, bool> &memo)
{
    if (memo.count(target)) return memo[target];
    if (target == 0) return true;
    if (target < 0) return false;
    
    for (int number : numbers){
        const int remainder = target - number;
        if (can_sum_memo(remainder, numbers, memo)){
            memo[target] = true;
            return true;
        }
    }
    memo[target] = false;
    return false;
}

// can_sum_memo overload
bool can_sum_memo(const int &target, const std::vector<int> &numbers)
{
    std::map<int, bool> memo;
    return can_sum_memo(target, numbers, memo);
}
//
// CAN SUM TABULATION
//
bool can_sum_tab(const int &target, const std::vector<int> &numbers)
{
    // O(m*n) time
    // O(m) space
    std::vector<bool> table(target+1, false);
    table[0] = true;
    for(int i = 0; i < table.size(); ++i)
        if(table[i])
            for(int num : numbers)
                if(i + num <= table.size())table[i + num] = true;
    return table[target];
}
//
// CAN SUN CALLER
//
bool can_sum(const int &target, const std::vector<int> &numbers, bool(*can_sum_func)(const int&, const std::vector<int>&) = can_sum_tab)
{
    if(target < 0){
        std::clog << "Negative number! Invalid." << std::endl;
        return false;
    }
    else if(target == 0) return true;
    return can_sum_func(target, numbers);
}
void test_can_sum(bool(*can_sum_func)(const int&, const std::vector<int>&))
{
    std::cout << std::boolalpha;
    std::vector<int> numbers1 = { 2, 3 };
    std::cout << can_sum(7, numbers1, can_sum_func) << std::endl;     // true
    std::vector<int> numbers2 = { 5, 3, 4, 7 };
    std::cout << can_sum(7, numbers2, can_sum_func) << std::endl;     // true
    std::vector<int> numbers3 = { 2, 4 };
    std::cout << can_sum(7, numbers3, can_sum_func) << std::endl;     // false
    std::vector<int> numbers4 = { 2, 3, 5 };
    std::cout << can_sum(8, numbers4, can_sum_func) << std::endl;     // true
    std::vector<int> numbers5 = { 7, 14 };
    std::cout << can_sum(300, numbers5, can_sum_func) << std::endl;   // false
}
//
// HOW SUM RECURSION
//
std::vector<int> how_sum_recu(const int &target, const std::vector<int> &numbers)
{
    // O(n ^ m * m) time
    // O(m) space
    if (target == 0) return {};
    std::vector<int> null_vector = {0};
    if (target < 0) return null_vector;
    
    for (int number : numbers){
        const int remainder = target - number;
        std::vector<int> remainder_result = how_sum_recu(remainder, numbers);
        if (remainder_result != null_vector){
            remainder_result.push_back(number);
            return remainder_result;
        }
    }
    return null_vector;
}
//
// HOW SUM MEMOIZATION
//
std::vector<int> how_sum_memo(const int &target, const std::vector<int> &numbers, std::map<int, std::vector<int>>& memo){
    if (memo.count(target)) return memo[target];
    if (target == 0) return {};
    const std::vector<int> null_vector = {0};
    if (target < 0) return null_vector;
    
    for (int number : numbers){
        const int remainder = target - number;
        std::vector<int> remainder_result = how_sum_memo(remainder, numbers, memo);
        if (remainder_result != null_vector){
            remainder_result.push_back(number);
            memo[target] = remainder_result;
            return memo[target];
        }
    }
    memo[target] = null_vector;
    return null_vector;
}

// how_sum overload
std::vector<int> how_sum_memo(const int &target, const std::vector<int> &numbers)
{
    std::map<int, std::vector<int>> memo;
    return how_sum_memo(target, numbers, memo);
}
//
// HOW SUM TABULATION
//
std::vector<int> how_sum_tab(const int &target, const std::vector<int> &numbers)
{
    // O(m^2*n) time
    // O(m^2) space
    std::vector<int> null_vector(1, 0);
    std::vector<std::vector<int>> table(target+1, null_vector);
    table[0] = {};
    
    for(int i = 0; i < table.size(); ++i){
        // printv(table);
        if(table[i] != null_vector){
            for(int num : numbers){
                if(i + num < table.size()){
                    // std::cout << i + num << '\n';
                    table[i + num] = table[i];
                    table[i + num].push_back(num);
                }
            }
        }
    }
    return table[target];
}
//
// HOW SUM CALLER
//
std::vector<int> how_sum(const int &target, const std::vector<int> &numbers, std::vector<int>(*how_sum_func)(const int&, const std::vector<int>&))
{
    if(target < 0){
        std::clog << "Negative number! Invalid." << std::endl;
        return std::vector<int>(0, 0);
    }
    return how_sum_func(target, numbers);
}

void test_how_sum(std::vector<int>(*how_sum_func)(const int&, const std::vector<int>&))
{
    std::vector<int> numbers1 = { 2, 3 };
    printv(how_sum(7, numbers1, how_sum_func));     // {3, 2, 2}
    std::vector<int> numbers2 = { 5, 3, 4, 7 };
    printv(how_sum(7, numbers2, how_sum_func));     // {4, 3}
    std::vector<int> numbers3 = { 2, 4 };
    printv(how_sum(7, numbers3, how_sum_func));     // {}
    std::vector<int> numbers4 = { 2, 3, 5 };
    printv(how_sum(8, numbers4, how_sum_func));     // {2, 2, 2, 2}
    std::vector<int> numbers5 = { 7, 14 };
    printv(how_sum(300, numbers5, how_sum_func));   // {}
}
//
// BEST SUM RECURSION
//
std::vector<int> best_sum_recu(const int &target, const std::vector<int> &numbers)
{
    // time O(n^m * m)
    // space O(m^2)
    if(target == 0) return {};
    std::vector<int> null_vector = { '\0' };
    if(target < 0) return null_vector;
    
    std::vector<int> shortest_combination = null_vector;
    
    for(int number : numbers){
        const int remainder = target - number;
        std::vector<int> remainder_combination = best_sum_recu(remainder, numbers);
        if(remainder_combination != null_vector){
            std::vector<int> combination = remainder_combination;
            combination.push_back(number);
            // if the combination is shorter than the current "shortest", update it
            if(shortest_combination == null_vector || combination.size() < shortest_combination.size()){
                shortest_combination = combination;
            }
        }
    }
    return shortest_combination;
}
//
// BEST SUM MEMOIZATION
//
std::vector<int> best_sum_memo(const int &target, const std::vector<int> &numbers, std::map<int, std::vector<int>>& memo)
{
    // time O(m^2 * n)
    // space O(m^2)
    if(memo.count(target)) return memo[target];
    if(target == 0) return {};
    std::vector<int> null_vector = { '\0' };
    if(target < 0) return null_vector;
    
    std::vector<int> shortest_combination = null_vector;
    
    for(int number : numbers){
        const int remainder = target - number;
        std::vector<int> remainder_combination = best_sum_memo(remainder, numbers, memo);
        if(remainder_combination != null_vector){
            std::vector<int> combination = remainder_combination;
            combination.push_back(number);
            // if the combination is shorter than the current "shortest", update it
            if(shortest_combination == null_vector || combination.size() < shortest_combination.size()){
                shortest_combination = combination;
            }
        }
    }
    memo[target] = shortest_combination;
    return shortest_combination;
}

std::vector<int> best_sum_memo(const int &target, const std::vector<int> &numbers)
{
    std::map<int, std::vector<int>> memo;
    return best_sum_memo(target, numbers, memo);
}
//
// BEST SUM TABULATION
//
std::vector<int> best_sum_tab(const int &target, const std::vector<int> &numbers)
{
    // time O(m^2 * n)
    // space O(m^2)
    const std::vector<int> null_vector(1, 0);
    std::vector<std::vector<int>> table(target + 1, null_vector);
    table[0] = {};
    
    for(int i = 0; i < table.size(); ++i){
        if(table[i] != null_vector){
            for(int num : numbers){
                if(i + num < table.size()){
                    std::vector<int> combination = table[i];
                    combination.push_back(num);
                    // printv(combination);
                    if(table[i + num] == null_vector || combination.size() < table[i + num].size())
                        table[i + num] = combination;
                }
            }
        }
    }
    return table[target];
}
//
// BEST SUM CALLER
//
std::vector<int> best_sum(const int &target, const std::vector<int> &numbers, std::vector<int>(*best_sum_func)(const int&, const std::vector<int>&))
{
    if(target < 0){
        std::clog << "Negative number! Invalid." << std::endl;
        return std::vector<int>(0, 0);
    }
    return best_sum_func(target, numbers);
}

void test_best_sum(std::vector<int>(*best_sum_func)(const int&, const std::vector<int>&))
{
    std::vector<int> numbers1 = { 5, 3, 4, 7 };
    printv(best_sum(7, numbers1, best_sum_func));   // {7}
    std::vector<int> numbers2 = { 2, 3, 5 };
    printv(best_sum(8, numbers2, best_sum_func));   // {3, 5}
    std::vector<int> numbers3 = { 1, 4, 5 };
    printv(best_sum(8, numbers3, best_sum_func));   // {4, 4}
    std::vector<int> numbers4 = { 1, 2, 5, 25 };
    printv(best_sum(100, numbers4, best_sum_func)); // {25, 25, 25, 25}
}
//
// CAN CONSTRUCT RECURSION
//
bool can_construct_recu(const std::string &target, const std::vector<std::string> &word_bank)
{
    // time O(n^m*m)
    // space O(m^2)
    if(target == "") return true;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            if(can_construct_recu(suffix, word_bank))
                return true;
        }
    }
    return false;
}
//
// CAN CONSTRUCT MEMOIZATION
//
bool can_construct_memo(const std::string &target, const std::vector<std::string> &word_bank, std::map<std::string, bool> &memo)
{
    // time O(n*m^2)
    // space O(m^2)
    if(memo.count(target)) return memo[target];
    if(target == "") return true;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            if(can_construct_memo(suffix, word_bank, memo)){
                memo[target] = true;
                return true;
            } 
        }
    }
    memo[target] = false;
    return false;
}

bool can_construct_memo(const std::string &target, const std::vector<std::string> &word_bank)
{
    std::map<std::string, bool> memo;
    return can_construct_memo(target, word_bank, memo);
}
//
// CAN CONSTRUCT TABULATION
//
bool can_construct_tab(const std::string &target, const std::vector<std::string> &word_bank)
{
    // time O(m*n*m)
    // space O(m)
    std::vector<bool> table(target.size()+1, false);
    table[0] = true;
    
    for(int i = 0; i < table.size(); ++i){
        if(table[i]){
            for(std::string word : word_bank){
                if(target.substr(i, word.size()) == word){
                    table[i + word.size()] = true;
                }
            }
        }
    }
    return table[target.size()];
}
//
// CAN CONSTRUCT CALLER
//
bool can_construct(const std::string &target, const std::vector<std::string> &word_bank, bool(*can_construct_func)(const std::string&, const std::vector<std::string>&))
{
    if(!target.size()) return true;
    return can_construct_func(target, word_bank);
}

void test_can_construct(bool(*can_construct_func)(const std::string&, const std::vector<std::string>&))
{
    std::cout << std::boolalpha;
    std::vector<std::string> strs1 = { "ab", "abc", "cd", "def", "abcd" };
    std::cout << can_construct("abcdef", strs1, can_construct_func) << '\n';     // true
    
    std::vector<std::string> strs2 = { "bo", "rd", "ate", "t", "ska", "sk", "boar" }; 
    std::cout << can_construct("skateboard", strs2, can_construct_func) << '\n';     // false
    
    std::vector<std::string> strs3 = { "a", "p", "ent", "enter", "ot", "o", "t" };
    std::cout << can_construct("enterapotentpot", strs3, can_construct_func) << '\n';     // true
    
    std::vector<std::string> strs4 = { "e", "ee", "eee", "eeee", "eeeee", "eeeeee" };
    std::cout << can_construct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", strs4, can_construct_func) << '\n';     // false
}
//
// COUNT CONSTRUCT RECURSION
//
int count_construct_recu(const std::string &target, const std::vector<std::string> &word_bank)
{
    if(target == "") return 1;
    int total_count = 0;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            int num_ways_for_rest = count_construct_recu(suffix, word_bank);
            total_count += num_ways_for_rest;
        }
    }
    return total_count;
}
//
// COUNT CONSTRUCT MEMOIZATION
//
int count_construct_memo(const std::string &target, const std::vector<std::string> &word_bank, std::map<std::string, int> &memo)
{
    // time(n*m^2)
    // space(m^2)
    if(memo.count(target)) return memo[target];
    if(target == "") return 1;
    int total_count = 0;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            int num_ways_for_rest = count_construct_memo(suffix, word_bank, memo);
            total_count += num_ways_for_rest;
        }
    }
    memo[target] = total_count;
    return total_count;
}

int count_construct_memo(const std::string &target, const std::vector<std::string> &word_bank)
{
    std::map<std::string, int> memo;
    return count_construct_memo(target, word_bank, memo);
}
//
// COUNT CONSTRUCT TABULATION
//
int count_construct_tab(const std::string &target, const std::vector<std::string> &word_bank)
{
    // time O(m^2*n)
    // space O(m)
    std::vector<int> table(target.size() + 1, 0);
    table[0] = 1;
    
    for(int i = 0; i < table.size(); ++i){
        for(std::string word : word_bank){
            if(target.substr(i, word.size()) == word){
                // std::cout << target.substr(i, i + word.size()) << " = " << word << '\n';
                table[i + word.size()] += table[i];
            }
        }
    }
    return table[target.size()];
}
//
// COUNT CONSTRUCT CALLER
//
int count_construct(const std::string &target, const std::vector<std::string> &word_bank, int(*count_construct_func)(const std::string&, const std::vector<std::string>&))
{
    if(!target.size()) return 1;
    return count_construct_func(target, word_bank);
}

void test_count_construct(int(*count_construct_func)(const std::string&, const std::vector<std::string>&))
{
    std::vector<std::string> strs1 = { "purp", "p", "ur", "le", "purpl" };
    std::cout << count_construct_func("purple", strs1) << '\n';     // 2
    
    std::vector<std::string> strs2 = { "ab", "abc", "cd", "def", "abcd" };
    std::cout << count_construct_func("abcdef", strs2) << '\n';     // 1
    
    std::vector<std::string> strs3 = { "bo", "rd", "ate", "t", "ska", "sk", "boar" }; 
    std::cout << count_construct_func("skateboard", strs3) << '\n';     // 0
    
    std::vector<std::string> strs4 = { "a", "p", "ent", "enter", "ot", "o", "t" };
    std::cout << count_construct_func("enterapotentpot", strs4) << '\n';     // 4
    
    std::vector<std::string> strs5 = { "e", "ee", "eee", "eeee", "eeeee", "eeeeee" };
    std::cout << count_construct_func("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", strs5) << '\n';     // 0
}
//
// ALL CONSTRUCT RECURSION
//
std::vector<std::vector<std::string>> all_construct_recu(const std::string &target, const std::vector<std::string> &word_bank)
{
    // time O(n^m)
    // space O(m)
    if(target == "") return {{}};
    std::vector<std::vector<std::string>> result;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            // std::cout << suffix << '\n';
            std::vector<std::vector<std::string>> suffix_ways = all_construct_recu(suffix, word_bank);
            // printv(suffix_ways);
            std::vector<std::vector<std::string>> target_ways = suffix_ways;
            for(int i = 0; i < target_ways.size(); ++i){
                target_ways[i].insert(target_ways[i].begin(), word);
            }
            result.insert(std::end(result), std::begin(target_ways), std::end(target_ways));
        }
    }
    return result;
}
//
// ALL CONSTRUCT MEMOIZATION
//
std::vector<std::vector<std::string>> all_construct_memo(const std::string &target, const std::vector<std::string> &word_bank, std::map<std::string, std::vector<std::vector<std::string>>> &memo)
{
    // time O(n^m)
    // space O(m)
    // this memoization doesn't really help in the worst case scenario
    // but can optimize some results
    if(memo.count(target)) return memo[target];
    if(target == "") return {{}};
    
    std::vector<std::vector<std::string>> result;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            std::vector<std::vector<std::string>> suffix_ways = all_construct_memo(suffix, word_bank, memo);
            std::vector<std::vector<std::string>> target_ways = suffix_ways;
            for(int i = 0; i < target_ways.size(); ++i){
                target_ways[i].insert(target_ways[i].begin(), word);
            }
            result.insert(std::end(result), std::begin(target_ways), std::end(target_ways));
        }
    }
    memo[target] = result;
    return result;
}

// all construct overload
std::vector<std::vector<std::string>> all_construct_memo(const std::string &target, const std::vector<std::string> &word_bank)
{
    std::map<std::string, std::vector<std::vector<std::string>>> memo;
    return all_construct_memo(target, word_bank, memo);
}
//
// ALL CONSTRUCT TABULATION
//
std::vector<std::vector<std::string>> all_construct_tab(const std::string &target, const std::vector<std::string> &word_bank)
{
    // time ~O(n^m)
    // space ~O(n^m)
    std::vector<std::vector<std::vector<std::string>>> table(target.size() + 1);
    table[0] = {{}};
    std::cout << table.size();
    
    for(int i = 0; i < table.size(); ++i){
        for(std::string word : word_bank){
            if(target.substr(i, word.size()) == word){
                std::vector<std::vector<std::string>> new_combination = table[i];
                for(int j = 0; j < new_combination.size(); ++j)
                    new_combination[j].push_back(word);
                table[i + word.size()].insert(table[i + word.size()].end(), new_combination.begin(), new_combination.end());
            }
        }
    }
    return table[target.size()];
}
//
// ALL CONSTRUCT CALLER
//
std::vector<std::vector<std::string>> all_construct(
    const std::string &target,
    const std::vector<std::string> &word_bank,
    std::vector<std::vector<std::string>>(*all_construct_func)(const std::string&, const std::vector<std::string>&))
{
    if(!target.size()) return {{}};
    return all_construct_func(target, word_bank);
}

void test_all_construct(std::vector<std::vector<std::string>>(*all_construct_func)(const std::string&, const std::vector<std::string>&))
{
    std::vector<std::string> strs1 = { "purp", "p", "ur", "le", "purpl" };
    printv(all_construct("purple", strs1, all_construct_func));
    // {
    //     {"purp", "le"},
    //     {"p", "ur", "p", "le"}
    // }
    
    std::vector<std::string> strs2 = { "ab", "abc", "cd", "def", "abcd" , "ef", "c"};
    printv(all_construct("abcdef", strs2, all_construct_func));
    // {
    //     {"ab", "cd", "ef"},
    //     {"ab", "c", "def"},
    //     {"abc", "def"},
    //     {"abcd", "ef"}
    // }
    
    std::vector<std::string> strs3 = { "bo", "rd", "ate", "t", "ska", "sk", "boar" }; 
    printv(all_construct("skateboard", strs3, all_construct_func));
    // { }
    
    std::vector<std::string> strs4 = { "a", "aa", "aaa", "aaaa", "aaaaa" };
    printv(all_construct("aaaaaaaaaaaaaaaaaaaaaaaaaaaz", strs4, all_construct_func));
    // { }
}

int main()
{
    test_all_construct(&all_construct_memo);
}