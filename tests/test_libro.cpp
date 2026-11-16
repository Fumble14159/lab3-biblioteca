// tests/test_libro.cpp — PRUEBAS UNITARIAS de Libro (CAJA NEGRA).
// De momento solo hay UN test de ejemplo. Vuestro trabajo: escribir el resto copiando
// y adaptando los de tests/test_habitacion.cpp del repositorio de REFERENCIA (pp-lab3-tests-referencia).
//
// Cada test sigue tres pasos: PREPARAR (crear objetos), ACTUAR (llamar al método)
// y COMPROBAR (EXPECT_...).
#include <gtest/gtest.h>
#include <stdexcept>
#include "libro.hpp"

TEST(LibroTest, ConstructorGuardaLosDatos) {
    Libro l(1, "El Quijote");                     // PREPARAR
    EXPECT_EQ(l.getCodigo(), 1);                  // COMPROBAR
    EXPECT_EQ(l.getTitulo(), "El Quijote");
    EXPECT_FALSE(l.estaPrestado());               // un libro nuevo está disponible
}

// >>> AQUÍ <<<  Vuestros tests de Libro (guía, paso 4).

TEST(LibroTest, PrecioCeroLanzaExcepcion) {             // valor límite: 0 NO es válido
    EXPECT_THROW(Libro(0, "El Quijote"), std::invalid_argument);
}

TEST(LibroTest, PrecioMinimoPositivoNoLanza) {          // valor límite: el primero válido
    EXPECT_NO_THROW(Libro(1, "El Quijote"));
}

TEST(LibroTest, NumeroNegativoLanzaExcepcion) {
    EXPECT_THROW(Libro(-5, "El Quijote"), std::invalid_argument);
}

// ---- Reservar y liberar ----------------------------------------------------------
TEST(LibroTest, PrestarCambiaElEstado) {
    Libro l(1, "El Quijote");
    EXPECT_TRUE(l.prestar());                    // ACTUAR y COMPROBAR a la vez
    EXPECT_TRUE(l.estaPrestado());
}

TEST(LibroTest, PrestarDosVecesDevuelveFalse) {
    Libro l(1, "El Quijote");
    l.prestar();
    EXPECT_FALSE(l.prestar());                   // la segunda vez ya estaba prestada
    EXPECT_TRUE(l.estaPrestado());
}

TEST(LibroTest, DevolverDejaElLibroDisponible) {
    Libro l(1, "El Quijote");
    l.prestar();
    l.devolver();
    EXPECT_FALSE(l.estaPrestado());
}

// ---- Precio de la estancia ---------------------------------------------------------
TEST(LibroTest, MultaMultiplicaporDias) {
    Libro l(1, "El Quijote");
    EXPECT_DOUBLE_EQ(l.multa(4), 2.0);
}

TEST(LibroTest, MultaconCeroDiasesCero) {   // valor límite
    Libro l(1, "El Quijote");
    EXPECT_DOUBLE_EQ(l.multa(0), 0.0);
}

TEST(LibroTest, MultaConDiasNegativosLanzaExcepcion) {   // valor límite
    Libro l(1, "El Quijote");
    EXPECT_THROW(l.multa(-1), std::invalid_argument);
}