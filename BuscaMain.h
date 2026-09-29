#ifndef BUSCAMAIN_H
#define BUSCAMAIN_H
#include "Estado.h"
#include "FronteiraBusca.h"
#include <string>

std::string resolverCubo(const Estado& inicial, FronteiraBusca* fronteira, long long& estadosVisitados);
#endif 
