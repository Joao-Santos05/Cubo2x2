#ifndef BUSCAMAIN_H
#define BUSCAMAIN_H

#include "Estado.h"
#include "FronteiraBusca.h"
#include <string>

// Declaração da função genérica baseada na Regra de Ouro do laço imutável.
std::string resolverCubo(const Estado& inicial, FronteiraBusca* fronteira, long long& estadosVisitados);

#endif // BUSCAMAIN_H
