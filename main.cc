#include "biton.hh"

int main()
{
  std::vector<int> vec;
  size_t vec_size{};

  std::cin >> vec_size;
  if (!std::cin.good())
  {
    std::cout << "Invalid character at stdin" << std::endl;
    return -1;
  }

  vec.resize(vec_size);

  for (auto &el : vec)
  {
    std::cin >> el;
    if (!std::cin.good())
    {
      std::cout << "Invalid character at stdin" << std::endl;
      return -1;
    }
  }

  BTS::bsort(vec);

  for (auto el : vec)
    std::cout << el << std::endl;

  return 0;
}