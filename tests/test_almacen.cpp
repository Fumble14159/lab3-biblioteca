// tests/test_almacen.cpp — PRUEBAS DE INTEGRACIÓN: Biblioteca + Libro + Novedad + fichero.
#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include <memory>
#include "almacen.hpp"
#include "novedad.hpp"

TEST(AlmacenTest, GuardarYCargarDevuelveLoMismo) {
// PREPARAR: una biblioteca con un Libro y una Novedad prestada, guardada en un fichero
Biblioteca original;
original.anadir(std::make_unique<Libro>(1, "El Quijote"));
original.anadir(std::make_unique<Novedad>(3, "Dune"));
original.prestar(3);
guardarBiblioteca(original, "test_biblioteca.txt");
// ACTUAR: cargarla desde el fichero
Biblioteca cargada = cargarBiblioteca("test_biblioteca.txt");
// COMPROBAR: ha vuelto TODO igual
ASSERT_EQ(cargada.total(), 2u);
Libro* novedad = cargada.buscar(3);
ASSERT_NE(novedad, nullptr);
EXPECT_EQ(novedad->tipo(), "Novedad"); // se ha vuelto a crear como Novedad, no como Libro
EXPECT_EQ(novedad->getTitulo(), "Dune");
EXPECT_TRUE(novedad->estaPrestado());
EXPECT_FALSE(cargada.buscar(1)->estaPrestado());
std::remove("test_biblioteca.txt"); // borrar el fichero de prueba
}

TEST(AlmacenTest, FicheroQueNoExisteLanzaExcepcion) {
EXPECT_THROW(cargarBiblioteca("no_existe.txt"), FicheroException);
}

TEST(AlmacenTest, LineaMalEscritaLanzaExcepcion) {
{
std::ofstream f("test_roto.txt");
f << "Libro;1;El Quijote;0\nLibro;abc;La Regenta;0\n"; // "abc" no es un código
} // aquí se cierra el fichero: ya se puede leer
EXPECT_THROW(cargarBiblioteca("test_roto.txt"), FicheroException);
std::remove("test_roto.txt");
}