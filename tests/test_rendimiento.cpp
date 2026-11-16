#include <gtest/gtest.h>
#include <chrono>
#include <memory>
#include "biblioteca.hpp"
TEST(RendimientoTest, BuscarEnUnaBibliotecaGrandeTardaMenosDeUnSegundo) {
Biblioteca biblioteca;
for (int n = 1; n <= 2000; n++) {
biblioteca.anadir(std::make_unique<Libro>(n, "Libro"));
}
auto inicio = std::chrono::steady_clock::now();
int encontrados = 0;
for (int n = 1; n <= 1000; n++) {
if (biblioteca.buscar(n * 2) != nullptr) encontrados++;
}
auto fin = std::chrono::steady_clock::now();
auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
EXPECT_EQ(encontrados, 1000);
EXPECT_LT(ms, 1000) << "La busqueda ha tardado " << ms << " ms";
}