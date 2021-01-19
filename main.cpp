#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>


//
// PRINT VECTOR
//
template<typename T>
void printv(const std::vector<T> &vector, bool endline = true)
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
void printv(const std::vector<std::vector<T>> &vector, bool endline = true, bool extra_indent = false)
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
void print(const std::vector<std::vector<std::vector<T>>> &vector)
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
unsigned long long int fib_recu(int n)
{
    if (n <= 2) return 1;
    return fib_recu(n - 1) + fib_recu(n - 2);
}
//
// FIBONACCI MEMOIZATION
//
unsigned long long int fib_memo(int n, std::map<int, long long int>& memo)
{
    if (memo.count(n)) return memo[n];
    if (n <= 2) return 1;
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    return memo[n];
    // O(2n) time
    // O(2n) space
}

unsigned long long int fib_memo(int n)
{
    std::map<int, long long int> default_map;
    return fib_memo(n, default_map);
}
//
// FIBONACCI TABULATION
//
unsigned long long int fib_tab(int n)
{
    // time O(n)
    // space O(n)
    std::vector<long long int> table(n+1, 0);
    table[1] = 1;
    for(int i = 0; i < table.size()-2; ++i){
        table[i + 1] += table[i];
        table[i + 2] += table[i];
    }
    table[table.size()-1] += table[table.size()-2];
    // table[-1] += table[-2];
    return table[n];
}

unsigned long long int fib(int n, unsigned long long int(*fib_fun)(int) = fib_tab)
{
    // max number 12,200,160,415,121,876,738
    if(n > 93) std::clog << "Number > 93, FIB OVERFLOW!" << std::endl;
    return fib_fun(n);
}

void run_fib(unsigned long long int(*fib_fun)(int) = fib_tab)
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
unsigned int grid_traveler(int m, int n)
{
    // O(2 ^ n+m) time
    // O(n+m) space
    if (m == 1 && n == 1) return 1;
    if (m == 0 || n == 0) return 0;
    return grid_traveler(m - 1, n) + grid_traveler(m, n - 1);
}

//
// GRID TRAVELER MEMOIZATION
//
unsigned int grid_traveler_memo(int m, int n, std::map<std::vector<int>, long long int>& memo)
{
    std::vector<int> key = { m, n };
    if (memo.count(key)) return memo[key];
    
    if (m == 1 && n == 1) return 1;
    if (m == 0 || n == 0) return 0;
    
    memo[key] = grid_traveler_memo(m - 1, n, memo) + grid_traveler_memo(m, n - 1, memo);
    return memo[key];
    // O(m * n) time
    // O(n + m) space
}

// grid_traveler_memo overload
unsigned int grid_traveler_memo(int m, int n)
{
    std::map<std::vector<int>, long long int> default_map;
    return grid_traveler_memo(m, n, default_map);
}
//
// GRID TRAVELER TABULATION
//
unsigned int grid_traveler_tab(int m, int n)
{
    // O(n*m) time
    // O(n*m) space
    // TODO bug: out of range crashe
    std::vector<std::vector<int>> table(n+1, std::vector<int>(n+1));
    table[1][1] = 1;
    for(int i = 0; i <= m; ++i){
        for(int j = 0; j <= n; ++j){
            int current = table[i][j];
            if(j+1 <= n) table[i][j + 1] += current;
            if(i+1 <= m) table[i + 1][j] += current;
        }
    }
    // printv(table);
    return table[m][n];
}

void run_grid_traveler(unsigned int(*grid_traveler_func)(int, int))
{
    std::cout << grid_traveler_func(1, 1) << '\n';
    std::cout << grid_traveler_func(2, 3) << '\n';
    std::cout << grid_traveler_func(3, 2) << '\n';
    std::cout << grid_traveler_func(3, 3) << '\n';
    std::cout << grid_traveler_func(18, 18) << '\n';
    std::cout << "I made it!" << std::endl;
}
//
// CAN SUM RECURSION
//
bool can_sum(int target_sum, std::vector<int> numbers)
{
    // O(n ^ m) time
    // O(m) space
    
    if (target_sum == 0) return true;
    if (target_sum < 0) return false;
    
    for (int number : numbers){
        const int remainder = target_sum - number;
        if (can_sum(remainder, numbers))
            return true;
    }
    return false;
}
//
// CAN SUM? MEMOIZATION
//
bool can_sum_memo(int target_sum, std::vector<int> numbers, std::map<int, bool>& memo)
{
    if (memo.count(target_sum)) return memo[target_sum];
    if (target_sum == 0) return true;
    if (target_sum < 0) return false;
    
    for (int number : numbers){
        const int remainder = target_sum - number;
        if (can_sum_memo(remainder, numbers, memo)){
            memo[target_sum] = true;
            return true;
        }
    }
    memo[target_sum] = false;
    return false;
}

// can_sum_memo overload
bool can_sum_memo(int target_sum, std::vector<int> numbers)
{
    std::map<int, bool> default_map;
    return can_sum_memo(target_sum, numbers, default_map);
}
//
// CAN SUM TABULATION
//
bool can_sum_tab(int target_sum, std::vector<int> numbers)
{
    // O(m*n) time
    // O(m) space
    std::vector<bool> table(target_sum+1, false);
    table[0] = true;
    for(int i = 0; i < table.size(); ++i)
        if(table[i])
            for(int num : numbers)
                if(i + num <= table.size())table[i + num] = true;
    return table[target_sum];
}

void run_can_sum(bool(*can_sum_func)(int, std::vector<int>))
{
    std::vector<int> numbers1 = { 2, 3 };
    std::cout << can_sum_func(7, numbers1) << std::endl;     // true
    std::vector<int> numbers2 = { 5, 3, 4, 7 };
    std::cout << can_sum_func(7, numbers2) << std::endl;     // true
    std::vector<int> numbers3 = { 2, 4 };
    std::cout << can_sum_func(7, numbers3) << std::endl;     // false
    std::vector<int> numbers4 = { 2, 3, 5 };
    std::cout << can_sum_func(8, numbers4) << std::endl;     // true
    std::vector<int> numbers5 = { 7, 14 };
    std::cout << can_sum_func(300, numbers5) << std::endl;   // false
}
//
// HOW SUM RECURSION
//
std::vector<int> how_sum(int target_sum, std::vector<int> numbers)
{
    // O(n ^ m * m) time
    // O(m) space
    if (target_sum == 0) return {};
    std::vector<int> null_vector = {0};
    if (target_sum < 0) return null_vector;
    
    for (int number : numbers){
        const int remainder = target_sum - number;
        std::vector<int> remainder_result = how_sum(remainder, numbers);
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
std::vector<int> how_sum_memo(int target_sum, std::vector<int> numbers, std::map<int, std::vector<int>>& memo){
    if (memo.count(target_sum)) return memo[target_sum];
    if (target_sum == 0) return {};
    std::vector<int> null_vector = {0};
    if (target_sum < 0) return null_vector;
    
    for (int number : numbers){
        const int remainder = target_sum - number;
        std::vector<int> remainder_result = how_sum(remainder, numbers);
        if (remainder_result != null_vector){
            remainder_result.push_back(number);
            memo[target_sum] = remainder_result;
            return memo[target_sum];
        }
    }
    memo[target_sum] = null_vector;
    return null_vector;
}

// how_sum overload
std::vector<int> how_sum_memo(int target_sum, std::vector<int> numbers)
{
    std::map<int, std::vector<int>> default_map;
    return how_sum_memo(target_sum, numbers, default_map);
}
//
// HOW SUM TABULATION
//
std::vector<int> how_sum_tab(int target_sum, std::vector<int> numbers)
{
    // O(m^2*n) time
    // O(m^2) space
    std::vector<int> null_vector(1, 0);
    std::vector<std::vector<int>> table(target_sum+1, null_vector);
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
    
    return table[target_sum];
}

void run_how_sum(std::vector<int>(*how_sum_func)(int, std::vector<int>))
{
    std::vector<int> numbers1 = { 2, 3 };
    for (int number : how_sum_func(7, numbers1)){
        std::cout << number << " ";     // {3, 2, 2}
    }
    std::cout << std::endl;
    std::vector<int> numbers2 = { 5, 3, 4, 7 };
    for (int number : how_sum_func(7, numbers2)){
        std::cout << number << " ";     // {4, 3}
    }
    std::cout << std::endl;
    std::vector<int> numbers3 = { 2, 4 };
    for (int number : how_sum_func(7, numbers3)){
        std::cout << number << " ";     // {}
    }
    std::cout << std::endl;
    std::vector<int> numbers4 = { 2, 3, 5 };
    for (int number : how_sum_func(8, numbers4)){
        std::cout << number << " ";     // {2, 2, 2, 2}
    }
    std::cout << std::endl;
    std::vector<int> numbers5 = { 7, 14 };
    for (int number : how_sum_func(300, numbers5)){
        std::cout << number << " ";     // {}
    }
}
//
// BEST SUM RECURSION
//
std::vector<int> best_sum(int target_sum, std::vector<int> numbers)
{
    // time O(n^m * m)
    // space O(m^2)
    if(target_sum == 0) return {};
    std::vector<int> null_vector = { '\0' };
    if(target_sum < 0) return null_vector;
    
    std::vector<int> shortest_combination = null_vector;
    
    for(int number : numbers){
        const int remainder = target_sum - number;
        std::vector<int> remainder_combination = best_sum(remainder, numbers);
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
std::vector<int> best_sum_memo(int target_sum, std::vector<int> numbers, std::map<int, std::vector<int>>& memo)
{
    // time O(m^2 * n)
    // space O(m^2)
    if(memo.count(target_sum)) return memo[target_sum];
    if(target_sum == 0) return {};
    std::vector<int> null_vector = { '\0' };
    if(target_sum < 0) return null_vector;
    
    std::vector<int> shortest_combination = null_vector;
    
    for(int number : numbers){
        const int remainder = target_sum - number;
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
    
    memo[target_sum] = shortest_combination;
    return shortest_combination;
}

std::vector<int> best_sum_memo(int target_sum, std::vector<int> numbers)
{
    std::map<int, std::vector<int>> memo;
    return best_sum_memo(target_sum, numbers, memo);
}
//
// BEST SUM TABULATION
//
std::vector<int> best_sum_tab(int target_sum, std::vector<int> numbers)
{
    // time O(m^2 * n)
    // space O(m^2)
    std::vector<int> null_vector(1, 0);
    std::vector<std::vector<int>> table(target_sum + 1, null_vector);
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
    
    return table[target_sum];
}

void run_best_sum(std::vector<int>(*best_sum_func)(int, std::vector<int>))
{
    std::vector<int> numbers1 = { 5, 3, 4, 7 };
    for (int number : best_sum_func(7, numbers1)){
        std::cout << number << " ";     // {7}
    }
    std::cout << std::endl;
    std::vector<int> numbers2 = { 2, 3, 5 };
    for (int number : best_sum_func(8, numbers2)){
        std::cout << number << " ";     // {3, 5}
    }
    std::cout << std::endl;
    std::vector<int> numbers3 = { 1, 4, 5 };
    for (int number : best_sum_func(8, numbers3)){
        std::cout << number << " ";     // {4, 4}
    }
    std::cout << std::endl;
    std::vector<int> numbers4 = { 1, 2, 5, 25 };
    for (int number : best_sum_func(100, numbers4)){
        std::cout << number << " ";     // {25, 25, 25, 25}
    }
    std::cout << std::endl;
}
//
// CAN CONSTRUCT RECURSION
//
bool can_construct(std::string target, std::vector<std::string> word_bank)
{
    // time O(n^m*m)
    // space O(m^2)
    if(target == "") return true;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            if(can_construct(suffix, word_bank))
                return true;
        }
    }
    return false;
}
//
// CAN CONSTRUCT MEMOIZATION
//
bool can_construct_memo(std::string target, std::vector<std::string> word_bank, std::map<std::string, bool> &memo)
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

bool can_construct_memo(std::string target, std::vector<std::string> word_bank)
{
    std::map<std::string, bool> memo;
    return can_construct_memo(target, word_bank, memo);
}
//
// CAN CONSTRUCT TABULATION
//
bool can_construct_tab(std::string target, std::vector<std::string> word_bank)
{
    // time O(m*n*m)
    // space O(m)
    std::vector<bool> table(target.size()+1, false);
    table[0] = true;
    // std::cout << table.size() << '\n';
    
    for(int i = 0; i < table.size(); ++i){
        if(table[i]){
            for(std::string word : word_bank){
                if(target.substr(i, word.size()) == word){
                    // std::cout << target.substr(i, i + word.size()) << " = " << word << '\n';
                    table[i + word.size()] = true;
                }
            }
        }
    }
    
    return table[target.size()];
}

void run_can_construct(bool(*can_construct_func)(std::string, std::vector<std::string>))
{
    std::vector<std::string> strs1 = { "ab", "abc", "cd", "def", "abcd" };
    std::cout << std::boolalpha << can_construct_func("abcdef", strs1) << '\n';     // true
    
    std::vector<std::string> strs2 = { "bo", "rd", "ate", "t", "ska", "sk", "boar" }; 
    std::cout << can_construct_func("skateboard", strs2) << '\n';     // false
    
    std::vector<std::string> strs3 = { "a", "p", "ent", "enter", "ot", "o", "t" };
    std::cout << can_construct_func("enterapotentpot", strs3) << '\n';     // true
    
    std::vector<std::string> strs4 = { "e", "ee", "eee", "eeee", "eeeee", "eeeeee" };
    std::cout << can_construct_func("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", strs4) << '\n';     // false
}
//
// COUNT CONSTRUCT RECURSION
//
int count_construct(std::string target, std::vector<std::string> word_bank)
{
    if(target == "") return 1;
    
    int total_count = 0;
    
    for(std::string word : word_bank){
        if(target.find(word) == 0){
            std::string suffix = target;
            suffix.erase(0, word.size());
            int num_ways_for_rest = count_construct(suffix, word_bank);
            total_count += num_ways_for_rest;
        }
    }
    return total_count;
}
//
// COUNT CONSTRUCT MEMOIZATION
//
int count_construct_memo(std::string target, std::vector<std::string> word_bank, std::map<std::string, int> &memo)
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

int count_construct_memo(std::string target, std::vector<std::string> word_bank)
{
    std::map<std::string, int> memo;
    return count_construct_memo(target, word_bank, memo);
}
//
// COUNT CONSTRUCT TABULATION
//
int count_construct_tab(std::string target, std::vector<std::string> word_bank)
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

void run_count_construct(int(*count_construct_func)(std::string, std::vector<std::string>))
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
std::vector<std::vector<std::string>> all_construct(std::string target, std::vector<std::string> word_bank)
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
            std::vector<std::vector<std::string>> suffix_ways = all_construct(suffix, word_bank);
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
std::vector<std::vector<std::string>> all_construct_memo(std::string target, std::vector<std::string> word_bank, std::map<std::string, std::vector<std::vector<std::string>>> &memo)
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
            // std::cout << suffix << '\n';
            std::vector<std::vector<std::string>> suffix_ways = all_construct_memo(suffix, word_bank, memo);
            // printv(suffix_ways);
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
std::vector<std::vector<std::string>> all_construct_memo(std::string target, std::vector<std::string> word_bank)
{
    std::map<std::string, std::vector<std::vector<std::string>>> memo;
    return all_construct_memo(target, word_bank, memo);
}
//
// ALL CONSTRUCT TABULATION
//
std::vector<std::vector<std::string>> all_construct_tab(std::string target, std::vector<std::string> word_bank)
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

void run_all_construct(std::vector<std::vector<std::string>>(*all_construct_func)(std::string, std::vector<std::string>))
{
    std::vector<std::string> strs1 = { "purp", "p", "ur", "le", "purpl" };
    printv(all_construct("purple", strs1));
    // {
    //     {"purp", "le"},
    //     {"p", "ur", "p", "le"}
    // }
    
    std::vector<std::string> strs2 = { "ab", "abc", "cd", "def", "abcd" , "ef", "c"};
    printv(all_construct("abcdef", strs2));
    // {
    //     {"ab", "cd", "ef"},
    //     {"ab", "c", "def"},
    //     {"abc", "def"},
    //     {"abcd", "ef"}
    // }
    
    std::vector<std::string> strs3 = { "bo", "rd", "ate", "t", "ska", "sk", "boar" }; 
    printv(all_construct("skateboard", strs3));
    // { }
    
    std::vector<std::string> strs4 = { "a", "aa", "aaa", "aaaa", "aaaaa" };
    printv(all_construct("aaaaaaaaaaaaaaaaaaaaaaaaaaaz", strs4));
    // { }
}

// 2d vector
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

int main()
{
    // printv_test1();
    // printv_test2();
    printv_test3();
    std::cout << "    indent\n";
    std::cout << "        indent";
    std::cin.ignore();
}