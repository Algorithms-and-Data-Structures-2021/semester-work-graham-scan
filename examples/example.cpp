#include <iostream>

#include "algorithm.hpp"

using namespace itis;

int main(int argc, char *argv[]) {
  // Создаем объект алгоритма
  Graham g;

  // Добавляем точки
  g.add_point(1, 2);
  g.add_point(2, 5);
  g.add_point(-1, 3);
  g.add_point(0, 0);
  g.add_point(-3, -3);
  g.add_point(3, -4);
  g.add_point(4, 4);

  // Метод convex_hull записывает результат в стек, но не выводит его,
  // Метод convex_hull_print записывает результат в стек и выводит его
  g.convex_hull_print();
  return 0;
}