// Using std::accumulate() function from https://en.cppreference.com/w/cpp/algorithm/accumulate
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
 
int main()
{
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
  // Calculate the sum
  int sum = std::accumulate(v.begin(), v.end(),0);
  std::cout << "sum: " << sum << '\n';

  // Calculate the product
  int product = std::accumulate(v.begin(), v.end(),1, std::multiplies<int>());
  std::cout << "product: " << product << '\n';

  // Lambda function to make a dash-separated string on each element on the vector
  auto dash_fold =  [](std::string a, int b) { 
                      return std::move(a) + "-" + std::to_string(b);
                    };

  // Make a dash-separated string of 1-2-3-... on all the elements of the vector
  std::string s = std::accumulate(std::next(v.begin()),v.end(), // std::next() to avoid repeat the first element
                                  std::to_string(v.front()), // Start with the first element, equivalent to v.at(0)
                                  dash_fold);
  
  std::cout << "dash-separated string: " << s << '\n';

    // Make a dash-separated string of 10-9-8-... on all the elements of the vector
  std::string rs = std::accumulate(std::next(v.rbegin()),v.rend(), // std::next() to avoid repeat the last element
                                  std::to_string(v.back()), // Start with the last element, equivalent to v.at(v.size()-1)
                                  dash_fold);
  
  std::cout << "dash-separated string (right folded): " << rs << '\n';

}