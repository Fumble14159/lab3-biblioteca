// tests/test_novedad.cpp — PRUEBAS UNITARIAS de Novedad (CAJA BLANCA).
#include <gtest/gtest.h>
#include <memory>
#include "novedad.hpp"

TEST(NovedadTest, SinRecargoConSeisDias) { // camino 1: el if NO se cumple
Novedad n(3, "Dune");
EXPECT_DOUBLE_EQ(n.multa(6), 6.0); // 6 x 1 EUR, sin recargo
}

TEST(NovedadTest, ConRecargoJustoConSieteDias) {    // camino 2, en el LÍMITE exacto
    Novedad n(3, "Dune");
    EXPECT_DOUBLE_EQ(n.multa(7), 12.0);    // 7 * 200 = 1400, menos el 10 %
}

TEST(NovedadTest, ConRecargoConDiezDias) {          // camino 2, lejos del límite
    Novedad n(3, "Dune");
    EXPECT_DOUBLE_EQ(n.multa(10), 15.0);
}

TEST(NovedadTest, DiasNegativosLanzaExcepcion) {           // Novedad reutiliza la validación de la base
    Novedad n(3, "Dune");
    EXPECT_THROW(n.multa(-1), std::invalid_argument);
}

// Polimorfismo: a través de un puntero a la base se llama a la versión de Novedad.
TEST(NovedadTest, PolimorfismoDesdeUnPunteroALaBase) {
    std::unique_ptr<Libro> h = std::make_unique<Novedad>(3, "Dune");
    EXPECT_EQ(h->tipo(), "Novedad");
    EXPECT_DOUBLE_EQ(h->multa(6), 6.0);
}
