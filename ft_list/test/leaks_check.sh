#! /bin/zsh

  clang++ -Wall -Wextra -Werror ft_list_test.cpp -o user_bin_for_leaks &&
  ./user_bin_for_leaks
