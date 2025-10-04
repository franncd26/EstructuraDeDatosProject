#include <iostream>

using namespace std;
// ------------------- Recursos (lista doble) -------------------
struct Recursos {
    string nombre;
    string descripcion;
    Recursos *sig;
    Recursos *ant;
    Recursos(string n, string d) {
        nombre = n;
        descripcion = d;
        sig = NULL;
        ant = NULL;
    }
}*primeroR;

// ------------------- Organizadores (lista doble) -------------------
struct enlaceEvento;

struct Organizadores {
    int ID;
    string nombre;
    string departamento;
    enlaceEvento* listaEventos; // relación: eventos a cargo
    Organizadores *sig;
    Organizadores *ant;
    Organizadores(int id, string n, string d) {
        ID = id;
        nombre = n;
        departamento = d;
        listaEventos = NULL;
        sig = NULL;
        ant = NULL;
    }
}*primeroOr;

// ------------------- Eventos (lista simple) -------------------
struct enlaceRecurso;
struct enlaceParticipante;
struct categorias;

struct eventos {
    int ID;
    string nombre;
    string fecha;
    string lugar;
    string tipo;
    categorias* categoria;          // Relación directa: cada evento pertenece a UNA categoría
    enlaceRecurso* listaRecursos;   // Recursos asignados al evento
    enlaceParticipante* listaParticipantes; // Participantes inscritos en el evento
    eventos* sig;                   // Para la lista simple de eventos

    eventos(int id, string n, string fe, string l, string t) {
        ID = id;
        nombre = n;
        fecha = fe;
        lugar = l;
        tipo = t;
        categoria = NULL;
        listaRecursos = NULL;
        listaParticipantes = NULL;
        sig = NULL;
    }
}*primeroE;

// ------------------- Participantes (lista doble) -------------------
struct enlaceEventoParticipante;

struct participantes {
    int ID;
    string nombre;
    string carrera;
    enlaceEventoParticipante* listaEventos; // eventos inscritos
    participantes *sig;
    participantes *ant;
    participantes(int id, string n, string c) {
        ID = id;
        nombre = n;
        carrera = c;
        listaEventos = NULL;
        sig = NULL;
        ant = NULL;
    }
}*primeroP;

// ------------------- Categorías (lista simple) -------------------
struct enlaceCategoriaEvento;

struct categorias {
    int ID;
    string nombre;
    string descripcion;
    enlaceCategoriaEvento* listaEventos; // eventos de esta categoría
    categorias *sig;
    categorias(int id, string n, string d) {
        ID = id;
        nombre = n;
        descripcion = d;
        listaEventos = NULL;
        sig = NULL;
    }
}*primeroC;

// ------------------- Historial de eventos (lista circular) -------------------
struct historial_eventos {
    int ID;
    string fecha;
    historial_eventos *sig;
    participantes* refParticipante;
    eventos* refEvento;
    historial_eventos(int id, string f, participantes* p, eventos* e) {
        ID = id;
        fecha = f;
        refParticipante = p;
        refEvento = e;
        sig = NULL;
    }
}*primeroHistorial;

// ------------------- Enlaces para las relaciones -------------------

// Un organizador puede tener varios eventos
struct enlaceEvento {
    eventos* refEvento;
    enlaceEvento* sig;
};

// Un evento puede tener varios recursos
struct enlaceRecurso {
    Recursos* refRecurso;
    enlaceRecurso* sig;
};

// Un evento puede tener varios participantes
struct enlaceParticipante {
    participantes* refParticipante;
    enlaceParticipante* sig;
};

// Una categoría puede tener varios eventos
struct enlaceCategoriaEvento {
    eventos* refEvento;
    enlaceCategoriaEvento* sig;
};
// Un participante puede estar inscrito en varios eventos
struct enlaceEventoParticipante {
    eventos* refEvento;                // Apunta al evento al que se inscribe
    enlaceEventoParticipante* sig;     // Siguiente enlace
};

// ===================================================================
// ====================== PROTOTIPOS DE FUNCIONES ====================
// ===================================================================

// --- CRUD Eventos ---
void insertarEventoOrdenado(int id, string n, string f, string l, string t);
eventos* buscarEvento(int id);
void eliminarEvento(int id);
void mostrarEventos();

// --- CRUD Categorías ---
void insertarCategoriaFinal(int id, string n, string d);
categorias* buscarCategoria(int id);
void mostrarCategorias();

// --- CRUD Participantes ---
void insertarParticipante(int id, string n, string c);
participantes* buscarParticipante(int id);
void eliminarParticipante(int id);
void mostrarParticipantesAsc();
void mostrarParticipantesDesc();

// --- CRUD Organizadores ---
void insertarOrganizador(int id, string n, string d);
Organizadores* buscarOrganizador(int id);
void eliminarOrganizador(int id);
void mostrarOrganizadores();

// --- CRUD Recursos ---
void insertarRecurso(string n, string d);
Recursos* buscarRecurso(string n);
void eliminarRecurso(string n);
void mostrarRecursos();

// --- CRUD Historial ---
void insertarHistorialOrdenado(int id, string fecha);
void mostrarHistorial();

// --- Relaciones ---
void asignarCategoriaEvento(int eventoID, int categoriaID);
void asignarOrganizadorEvento(int orgID, int eventoID);
void inscribirParticipanteEvento(int partID, int eventoID);
void asignarRecursoEvento(int eventoID, string recursoNombre);

// --- Consultas ---
// 1️⃣ Participante que ha asistido a más eventos
void consultaParticipanteMasEventos() {
    if (primeroP == NULL) {
        cout << "No hay participantes registrados.\n";
        return;
    }

    participantes* p = primeroP;
    participantes* mayor = NULL;
    int maxEventos = 0;

    while (p != NULL) {
        int contador = 0;
        enlaceEventoParticipante* aux = p->listaEventos;
        while (aux != NULL) {
            contador++;
            aux = aux->sig;
        }

        if (contador > maxEventos) {
            maxEventos = contador;
            mayor = p;
        }
        p = p->sig;
    }

    if (mayor != NULL)
        cout << "Participante con mas eventos: " << mayor->nombre
             << " (" << maxEventos << " eventos)\n";
    else
        cout << "No hay inscripciones registradas.\n";
}


// 2️⃣ Organizador con más eventos a cargo
void consultaOrganizadorMasEventos() {
    if (primeroOr == NULL) {
        cout << "No hay organizadores registrados.\n";
        return;
    }

    Organizadores* o = primeroOr;
    Organizadores* mayor = NULL;
    int maxEventos = 0;

    while (o != NULL) {
        int contador = 0;
        enlaceEvento* aux = o->listaEventos;
        while (aux != NULL) {
            contador++;
            aux = aux->sig;
        }

        if (contador > maxEventos) {
            maxEventos = contador;
            mayor = o;
        }
        o = o->sig;
    }

    if (mayor != NULL)
        cout << "Organizador con mas eventos: " << mayor->nombre
             << " | Departamento: " << mayor->departamento
             << " | Eventos: " << maxEventos << endl;
    else
        cout << "No hay organizadores con eventos.\n";
}


// 3️⃣ Tipo de evento más frecuente (versión sencilla)
void consultaTipoEventoFrecuente() {
    if (primeroE == NULL) {
        cout << "No hay eventos registrados.\n";
        return;
    }

    int charlas = 0, talleres = 0, ferias = 0, otros = 0;

    eventos* e = primeroE;
    while (e != NULL) {
        if (e->tipo == "Charla" || e->tipo == "charla") charlas++;
        else if (e->tipo == "Taller" || e->tipo == "taller") talleres++;
        else if (e->tipo == "Feria" || e->tipo == "feria") ferias++;
        else otros++;
        e = e->sig;
    }

    int max = charlas;
    string tipo = "Charla";
    if (talleres > max) { max = talleres; tipo = "Taller"; }
    if (ferias > max) { max = ferias; tipo = "Feria"; }
    if (otros > max) { max = otros; tipo = "Otro tipo"; }

    cout << "Tipo de evento mas frecuente: " << tipo
         << " (" << max << " eventos)\n";
}


// 4️⃣ Categoría con mayor participación estudiantil
void consultaCategoriaMayorParticipacion() {
    if (primeroC == NULL) {
        cout << "No hay categorias registradas.\n";
        return;
    }

    categorias* c = primeroC;
    categorias* mayor = NULL;
    int maxParticipantes = 0;

    while (c != NULL) {
        int total = 0;
        enlaceCategoriaEvento* ev = c->listaEventos;
        while (ev != NULL) {
            enlaceParticipante* p = ev->refEvento->listaParticipantes;
            while (p != NULL) {
                total++;
                p = p->sig;
            }
            ev = ev->sig;
        }

        if (total > maxParticipantes) {
            maxParticipantes = total;
            mayor = c;
        }
        c = c->sig;
    }

    if (mayor != NULL)
        cout << "Categoria con mayor participacion: " << mayor->nombre
             << " (" << maxParticipantes << " participantes)\n";
    else
        cout << "No hay categorias con eventos.\n";
}


// 5️⃣ Recurso más utilizado en eventos
void consultaRecursoMasUtilizado() {
    if (primeroR == NULL) {
        cout << "No hay recursos registrados.\n";
        return;
    }

    Recursos* r = primeroR;
    Recursos* masUsado = NULL;
    int maxUso = 0;

    while (r != NULL) {
        int contador = 0;
        eventos* e = primeroE;
        while (e != NULL) {
            enlaceRecurso* aux = e->listaRecursos;
            while (aux != NULL) {
                if (aux->refRecurso == r)
                    contador++;
                aux = aux->sig;
            }
            e = e->sig;
        }
        if (contador > maxUso) {
            maxUso = contador;
            masUsado = r;
        }
        r = r->sig;
    }

    if (masUsado != NULL)
        cout << "Recurso mas utilizado: " << masUsado->nombre
             << " (" << maxUso << " eventos)\n";
    else
        cout << "Ningun recurso ha sido usado.\n";
}


// 6️⃣ Lugar que ha albergado más eventos
void consultaLugarMasEventos() {
    if (primeroE == NULL) {
        cout << "No hay eventos registrados.\n";
        return;
    }

    string lugarMax;
    int max = 0;

    eventos* e1 = primeroE;
    while (e1 != NULL) {
        int contador = 0;
        eventos* e2 = primeroE;
        while (e2 != NULL) {
            if (e1->lugar == e2->lugar)
                contador++;
            e2 = e2->sig;
        }

        if (contador > max) {
            max = contador;
            lugarMax = e1->lugar;
        }
        e1 = e1->sig;
    }

    cout << "Lugar con mas eventos: " << lugarMax
         << " (" << max << " eventos)\n";
}


// 7️⃣ Evento con más participantes
void consultaEventoMasParticipantes() {
    if (primeroE == NULL) {
        cout << "No hay eventos registrados.\n";
        return;
    }

    eventos* e = primeroE;
    eventos* mayor = NULL;
    int max = 0;

    while (e != NULL) {
        int contador = 0;
        enlaceParticipante* p = e->listaParticipantes;
        while (p != NULL) {
            contador++;
            p = p->sig;
        }

        if (contador > max) {
            max = contador;
            mayor = e;
        }
        e = e->sig;
    }

    if (mayor != NULL)
        cout << "Evento con mas participantes: " << mayor->nombre
             << " | Fecha: " << mayor->fecha
             << " | Participantes: " << max << endl;
    else
        cout << "No hay eventos con participantes.\n";
}


// 8️⃣ Organizador con eventos en más categorías distintas
void consultaOrganizadorMasCategorias() {
    if (primeroOr == NULL) {
        cout << "No hay organizadores registrados.\n";
        return;
    }

    Organizadores* o = primeroOr;
    Organizadores* mayor = NULL;
    int maxCat = 0;

    while (o != NULL) {
        int contador = 0;
        enlaceEvento* e1 = o->listaEventos;
        while (e1 != NULL) {
            bool repetida = false;
            enlaceEvento* e2 = o->listaEventos;
            while (e2 != e1) {
                if (e1->refEvento->categoria == e2->refEvento->categoria)
                    repetida = true;
                e2 = e2->sig;
            }
            if (!repetida && e1->refEvento->categoria != NULL)
                contador++;
            e1 = e1->sig;
        }

        if (contador > maxCat) {
            maxCat = contador;
            mayor = o;
        }
        o = o->sig;
    }

    if (mayor != NULL)
        cout << "Organizador con mas categorias: " << mayor->nombre
             << " (" << maxCat << " categorias distintas)\n";
    else
        cout << "No hay organizadores con categorias registradas.\n";
}


// 9️⃣ Porcentaje de estudiantes que participaron
void consultaPorcentajeParticipacion() {
    if (primeroP == NULL) {
        cout << "No hay participantes registrados.\n";
        return;
    }

    int total = 0, activos = 0;
    participantes* p = primeroP;
    while (p != NULL) {
        total++;
        if (p->listaEventos != NULL) activos++;
        p = p->sig;
    }

    double porcentaje = (total > 0) ? (activos * 100.0 / total) : 0;
    cout << "Participantes activos: " << activos << "/" << total
         << " (" << porcentaje << "% participaron en al menos un evento)\n";
}

// --- Reportes ---
void reporteParticipantesAscDesc();
void reporteEventosPorOrganizador(int orgID);
void reporteEventosPorCategoria(int catID);
void reporteRecursosPorEvento(int eventoID);
void reporteEventosPorLugar(string lugar);
void reporteTalleresPorDepartamento(string depto);
void reporteHistorial();
void reporteOrganizadoresSinEventos();

// ===================================================================
// ============================ MAIN =================================
// ===================================================================
int main() {
    cout << "=== Sistema de Gestion de Eventos Universitarios ===\n\n";

    // --- Crear Categorías ---
    categorias* cat1 = new categorias(1, "Academico", "Charlas y conferencias");
    categorias* cat2 = new categorias(2, "Deportivo", "Actividades fisicas");
    primeroC = cat1;
    cat1->sig = cat2;

    // --- Crear Recursos ---
    Recursos* rec1 = new Recursos("Proyector", "Equipo audiovisual");
    Recursos* rec2 = new Recursos("Sala A", "Espacio cerrado");
    Recursos* rec3 = new Recursos("Cancha", "Campo deportivo");
    primeroR = rec1;
    rec1->sig = rec2;
    rec2->sig = rec3;

    // --- Crear Eventos ---
    eventos* ev1 = new eventos(1, "Charla IA", "2025-09-30", "Auditorio", "Charla");
    eventos* ev2 = new eventos(2, "Taller Robotica", "2025-10-01", "Sala A", "Taller");
    eventos* ev3 = new eventos(3, "Feria Deportiva", "2025-10-10", "Cancha", "Feria");
    primeroE = ev1;
    ev1->sig = ev2;
    ev2->sig = ev3;

    // Asignar categorías
    ev1->categoria = cat1;
    ev2->categoria = cat1;
    ev3->categoria = cat2;

    // Agregar eventos a lista de categorías
    enlaceCategoriaEvento* ec1 = new enlaceCategoriaEvento{ev1, NULL};
    enlaceCategoriaEvento* ec2 = new enlaceCategoriaEvento{ev2, NULL};
    enlaceCategoriaEvento* ec3 = new enlaceCategoriaEvento{ev3, NULL};
    cat1->listaEventos = ec1;
    ec1->sig = ec2;
    cat2->listaEventos = ec3;

    // --- Crear Participantes ---
    participantes* p1 = new participantes(1, "Ana Lopez", "Computacion");
    participantes* p2 = new participantes(2, "Luis Perez", "Mecatronica");
    participantes* p3 = new participantes(3, "Maria Torres", "Informatica");
    primeroP = p1;
    p1->sig = p2;
    p2->sig = p3;

    // Inscribir participantes en eventos
    enlaceParticipante* ep1 = new enlaceParticipante{p1, NULL};
    enlaceParticipante* ep2 = new enlaceParticipante{p2, NULL};
    enlaceParticipante* ep3 = new enlaceParticipante{p3, NULL};
    enlaceParticipante* ep4 = new enlaceParticipante{p1, NULL};
    enlaceParticipante* ep5 = new enlaceParticipante{p2, NULL};

    ev1->listaParticipantes = ep1; // Ana
    ep1->sig = ep2;                // Luis
    ev2->listaParticipantes = ep3; // Maria
    ev3->listaParticipantes = ep4; // Ana
    ep4->sig = ep5;                // Luis

    // Vincular eventos a los participantes (inverso)
    enlaceEventoParticipante* lep1 = new enlaceEventoParticipante{ev1, NULL};
    enlaceEventoParticipante* lep2 = new enlaceEventoParticipante{ev2, NULL};
    enlaceEventoParticipante* lep3 = new enlaceEventoParticipante{ev3, NULL};

    p1->listaEventos = lep1;       // Ana en ev1
    lep1->sig = lep3;              // y ev3
    p2->listaEventos = new enlaceEventoParticipante{ev1, NULL}; // Luis en ev1
    p2->listaEventos->sig = new enlaceEventoParticipante{ev3, NULL}; // y ev3
    p3->listaEventos = lep2;       // Maria en ev2

    // --- Crear Organizadores ---
    Organizadores* o1 = new Organizadores(1, "Carlos Vega", "Computacion");
    Organizadores* o2 = new Organizadores(2, "Sofia Ruiz", "Deportes");
    primeroOr = o1;
    o1->sig = o2;

    // Asignar eventos a organizadores
    o1->listaEventos = new enlaceEvento{ev1, NULL};
    o1->listaEventos->sig = new enlaceEvento{ev2, NULL};
    o2->listaEventos = new enlaceEvento{ev3, NULL};

    // --- Asignar recursos a eventos ---
    ev1->listaRecursos = new enlaceRecurso{rec1, NULL};
    ev2->listaRecursos = new enlaceRecurso{rec1, NULL};
    ev2->listaRecursos->sig = new enlaceRecurso{rec2, NULL};
    ev3->listaRecursos = new enlaceRecurso{rec3, NULL};

    // ====================================================
    // =============== LLAMAR LAS CONSULTAS ================
    // ====================================================
    cout << "\n--- CONSULTAS ---\n\n";
    consultaParticipanteMasEventos();
    consultaOrganizadorMasEventos();
    consultaTipoEventoFrecuente();
    consultaCategoriaMayorParticipacion();
    consultaRecursoMasUtilizado();
    consultaLugarMasEventos();
    consultaEventoMasParticipantes();
    consultaOrganizadorMasCategorias();
    consultaPorcentajeParticipacion();

    cout << "\n=== Fin de las pruebas ===\n";
    return 0;
}


// ===================================================================
// ==================== FUNCIONES (VACÍAS) ===========================
// ===================================================================

// Ejemplo de una función vacía
void insertarEventoOrdenado(int id, string n, string f, string l, string t) {
    cout << "[insertarEventoOrdenado] - Funcion no implementada aun" << endl;
}