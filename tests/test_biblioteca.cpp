// tests/test_biblioteca.cpp — PRUEBAS UNITARIAS de Biblioteca con un FIXTURE (TEST_F).
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "biblioteca.hpp"
#include "novedad.hpp"
class BibliotecaTest : public ::testing::Test {
protected:
void SetUp() override { // se ejecuta ANTES de cada TEST_F
biblioteca.anadir(std::make_unique<Libro>(1, "El Quijote"));
biblioteca.anadir(std::make_unique<Libro>(2, "La Regenta"));
biblioteca.anadir(std::make_unique<Novedad>(3, "Dune"));
}
Biblioteca biblioteca;
};
TEST_F(BibliotecaTest, TotalCuentaTodosLosLibros) {
EXPECT_EQ(biblioteca.total(), 3u); // 3u: total() devuelve un size_t (sin signo)
EXPECT_EQ(biblioteca.disponibles(), 3);
}

TEST_F(BibliotecaTest, BuscarUnoQueNoExisteDevuelveNullptr) {
    EXPECT_EQ(biblioteca.buscar(999), nullptr);
}

TEST_F(BibliotecaTest, AnadirUnCodigoRepetidoLanzaExcepcion) {
    EXPECT_THROW(biblioteca.anadir(std::make_unique<Libro>(1, "Otro")), std::invalid_argument);
    EXPECT_EQ(biblioteca.total(), 3u);                 // y no se ha añadido
}

TEST_F(BibliotecaTest, PrestarReduceLosDisponibles) {
    EXPECT_TRUE(biblioteca.prestar(2));
    EXPECT_EQ(biblioteca.disponibles(), 2);
    EXPECT_TRUE(biblioteca.buscar(2)->estaPrestado());
}

TEST_F(BibliotecaTest, PrestarUnoQueNoExisteLanzaExcepcion) {
    EXPECT_THROW(biblioteca.prestar(999), std::out_of_range);
}