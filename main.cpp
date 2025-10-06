#include <iostream>
#include <string>
using namespace std;

// ===================================================================
// ========================= ESTRUCTURAS DE DATOS ====================
// ===================================================================

// Prototipos de las estructuras (necesarios para los enlaces)
struct eventos;
struct categorias;
struct participantes;
struct Recursos;
struct Organizadores;
struct historial_eventos;

// --- Estructuras para las relaciones (Enlaces) ---
struct enlaceEvento {
    eventos* refEvento;
    enlaceEvento* sig;
};
struct enlaceRecurso {
    Recursos* refRecurso;
    enlaceRecurso* sig;
};
struct enlaceParticipante {
    participantes* refParticipante;
    enlaceParticipante* sig;
};
struct enlaceCategoriaEvento {
    eventos* refEvento;
    enlaceCategoriaEvento* sig;
};
struct enlaceEventoParticipante {
    eventos* refEvento;
    enlaceEventoParticipante* sig;
};


// ------------------- Recursos (Lista Doble) -------------------
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
}*primeroR = NULL;

// ------------------- Organizadores (Lista Doble) -------------------
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
}*primeroOr = NULL;

// ------------------- Categorías (Lista Simple) -------------------
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
}*primeroC = NULL;

// ------------------- Eventos (Lista Simple - Ordenada por Fecha) -------------------
struct eventos {
    int ID;
    string nombre;
    string fecha; // YYYY-MM-DD para fácil ordenamiento
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
}*primeroE = NULL;

// ------------------- Participantes (Lista Doble) -------------------
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
}*primeroP = NULL;

// ------------------- Historial de eventos (Lista Circular) -------------------
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
}*primeroHistorial = NULL;


// ===================================================================
// ====================== PROTOTIPOS DE FUNCIONES ====================
// ===================================================================

// --- Menús ---
void menuPrincipal();
void gestionarCrud(int tipo);
void menuRelaciones();
void menuConsultas();
void menuReportes(); // Solo prototipo para evitar error en menuPrincipal

// --- CRUD Eventos ---
void insertarEventoOrdenado(int id, string n, string f, string l, string t);
eventos* buscarEvento(int id);
void modificarEvento(int id);
void eliminarEvento(int id);
void mostrarEventos();

// --- CRUD Categorías ---
void insertarCategoriaFinal(int id, string n, string d);
categorias* buscarCategoria(int id);
void modificarCategoria(int id);
void eliminarCategoria(int id);
void mostrarCategorias();

// --- CRUD Participantes ---
void insertarParticipante(int id, string n, string c);
participantes* buscarParticipante(int id);
void modificarParticipante(int id);
void eliminarParticipante(int id);
void mostrarParticipantes();

// --- CRUD Organizadores ---
void insertarOrganizador(int id, string n, string d);
Organizadores* buscarOrganizador(int id);
void modificarOrganizador(int id);
void eliminarOrganizador(int id);
void mostrarOrganizadores();

// --- CRUD Recursos ---
void insertarRecurso(string n, string d);
Recursos* buscarRecurso(string n);
void modificarRecurso(string n);
void eliminarRecurso(string n);
void mostrarRecursos();

// --- CRUD Historial ---
void insertarHistorialOrdenado(int id, string fecha, participantes* p, eventos* e);
historial_eventos* buscarHistorial(int id);
void modificarHistorial(int id);
void eliminarHistorial(int id);
void mostrarHistorial();

// --- Relaciones ---
void asignarCategoriaAEvento(int eventoID, int categoriaID);
void asignarOrganizadorAEvento(int orgID, int eventoID);
void inscribirParticipanteAEvento(int partID, int eventoID, string fecha);
void asignarRecursoAEvento(int eventoID, string recursoNombre);


// ===================================================================
// ========================= IMPLEMENTACIONES CRUD ===================
// ===================================================================

// ------------------- CRUD Eventos (Lista Simple - Ordenada por Fecha) -------------------
void insertarEventoOrdenado(int id, string n, string f, string l, string t) {
    // --- VALIDACIÓN DE ID REPETIDO ---
    if (buscarEvento(id) != NULL) {
        cout << "ERROR DE VALIDACION: El Evento con ID " << id << " ya existe. No se inserto.\n";
        return;
    }
    eventos* nuevo = new eventos(id, n, f, l, t);
    if (primeroE == NULL || nuevo->fecha < primeroE->fecha) {
        nuevo->sig = primeroE;
        primeroE = nuevo;
        cout << "Evento insertado al inicio y ordenado.\n";
        return;
    }
    eventos* actual = primeroE;
    while (actual->sig != NULL && actual->sig->fecha < nuevo->fecha) {
        actual = actual->sig;
    }
    nuevo->sig = actual->sig;
    actual->sig = nuevo;
    cout << "Evento insertado ordenado por fecha.\n";
}

eventos* buscarEvento(int id) {
    eventos* actual = primeroE;
    while (actual != NULL) {
        if (actual->ID == id) return actual;
        actual = actual->sig;
    }
    return NULL;
}

void modificarEvento(int id) {
    eventos* e = buscarEvento(id);
    if (e == NULL) { cout << "Error: Evento con ID " << id << " no encontrado.\n"; return; }
    cout << "\n--- Modificando Evento ID: " << e->ID << " (" << e->nombre << ") ---\n";
    cout << "Ingrese nuevo nombre (actual: " << e->nombre << "): ";
    string nuevoNombre; cin.ignore(); getline(cin, nuevoNombre); e->nombre = nuevoNombre;
    cout << "Ingrese nuevo tipo (actual: " << e->tipo << "): ";
    string nuevoTipo; getline(cin, nuevoTipo); e->tipo = nuevoTipo;
    cout << "Ingrese nuevo lugar (actual: " << e->lugar << "): ";
    string nuevoLugar; getline(cin, nuevoLugar); e->lugar = nuevoLugar;
    cout << "Ingrese nueva fecha (YYYY-MM-DD) (actual: " << e->fecha << "): ";
    string nuevaFecha; getline(cin, nuevaFecha);

    if (nuevaFecha != e->fecha) {
        eliminarEvento(id);
        insertarEventoOrdenado(id, e->nombre, nuevaFecha, e->lugar, e->tipo);
        cout << "Fecha modificada. El evento ha sido reordenado.\n";
    } else {
        cout << "Evento modificado con exito.\n";
    }
}

void eliminarEvento(int id) {
    if (primeroE == NULL) { cout << "La lista de eventos esta vacia.\n"; return; }
    eventos* actual = primeroE; eventos* anterior = NULL;

    if (actual != NULL && actual->ID == id) {
        primeroE = actual->sig; delete actual;
        cout << "Evento ID " << id << " eliminado del inicio.\n";
        return;
    }
    while (actual != NULL && actual->ID != id) {
        anterior = actual; actual = actual->sig;
    }
    if (actual == NULL) { cout << "Error: Evento con ID " << id << " no encontrado para eliminar.\n"; return; }
    anterior->sig = actual->sig; delete actual;
    cout << "Evento ID " << id << " eliminado con exito.\n";
}

void mostrarEventos() {
    cout << "\n--- LISTA DE EVENTOS ---\n";
    eventos* actual = primeroE;
    if (actual == NULL) { cout << "La lista de eventos esta vacia.\n"; return; }
    while (actual != NULL) {
        cout << "ID: " << actual->ID << " | Nombre: " << actual->nombre
             << " | Fecha: " << actual->fecha << " | Lugar: " << actual->lugar;
        if (actual->categoria != NULL) {
             cout << " | Categoria: " << actual->categoria->nombre;
        }
        cout << endl;
        actual = actual->sig;
    }
}

// ------------------- CRUD Categorías (Lista Simple - Inserción al Final) -------------------
void insertarCategoriaFinal(int id, string n, string d) {
    // --- VALIDACIÓN DE ID REPETIDO ---
    if (buscarCategoria(id) != NULL) {
        cout << "ERROR DE VALIDACION: La Categoria con ID " << id << " ya existe. No se inserto.\n";
        return;
    }
    categorias* nuevo = new categorias(id, n, d);
    if (primeroC == NULL) {
        primeroC = nuevo; cout << "Categoria insertada como primer elemento.\n"; return;
    }
    categorias* actual = primeroC;
    while (actual->sig != NULL) {
        actual = actual->sig;
    }
    actual->sig = nuevo;
    cout << "Categoria insertada al final.\n";
}

categorias* buscarCategoria(int id) {
    categorias* actual = primeroC;
    while (actual != NULL) {
        if (actual->ID == id) return actual;
        actual = actual->sig;
    }
    return NULL;
}

void modificarCategoria(int id) {
    categorias* c = buscarCategoria(id);
    if (c == NULL) { cout << "Error: Categoria con ID " << id << " no encontrada.\n"; return; }
    cout << "\n--- Modificando Categoria ID: " << c->ID << " (" << c->nombre << ") ---\n";
    cout << "Ingrese nuevo nombre (actual: " << c->nombre << "): ";
    string nuevoNombre; cin.ignore(); getline(cin, nuevoNombre); c->nombre = nuevoNombre;
    cout << "Ingrese nueva descripcion (actual: " << c->descripcion << "): ";
    string nuevaDescripcion; getline(cin, nuevaDescripcion); c->descripcion = nuevaDescripcion;
    cout << "Categoria modificada con exito.\n";
}

void eliminarCategoria(int id) {
    if (primeroC == NULL) { cout << "La lista de categorias esta vacia.\n"; return; }
    categorias* actual = primeroC; categorias* anterior = NULL;
    if (actual != NULL && actual->ID == id) {
        primeroC = actual->sig; delete actual;
        cout << "Categoria ID " << id << " eliminada del inicio.\n"; return;
    }
    while (actual != NULL && actual->ID != id) {
        anterior = actual; actual = actual->sig;
    }
    if (actual == NULL) { cout << "Error: Categoria con ID " << id << " no encontrada para eliminar.\n"; return; }
    anterior->sig = actual->sig; delete actual;
    cout << "Categoria ID " << id << " eliminada con exito.\n";
}

void mostrarCategorias() {
    cout << "\n--- LISTA DE CATEGORIAS ---\n";
    categorias* actual = primeroC;
    if (actual == NULL) { cout << "La lista de categorias esta vacia.\n"; return; }
    while (actual != NULL) {
        cout << "ID: " << actual->ID << " | Nombre: " << actual->nombre
             << " | Descripcion: " << actual->descripcion << endl;
        actual = actual->sig;
    }
}

// ------------------- CRUD Participantes (Lista Doble) -------------------
void insertarParticipante(int id, string n, string c) {
    // --- VALIDACIÓN DE ID REPETIDO ---
    if (buscarParticipante(id) != NULL) {
        cout << "ERROR DE VALIDACION: El Participante con ID " << id << " ya existe. No se inserto.\n";
        return;
    }
    participantes* nuevo = new participantes(id, n, c);
    if (primeroP == NULL) {
        primeroP = nuevo; cout << "Participante insertado como primer elemento.\n"; return;
    }
    participantes* actual = primeroP;
    while (actual->sig != NULL) {
        actual = actual->sig;
    }
    actual->sig = nuevo;
    nuevo->ant = actual;
    cout << "Participante insertado al final.\n";
}

participantes* buscarParticipante(int id) {
    participantes* actual = primeroP;
    while (actual != NULL) {
        if (actual->ID == id) return actual;
        actual = actual->sig;
    }
    return NULL;
}

void modificarParticipante(int id) {
    participantes* p = buscarParticipante(id);
    if (p == NULL) { cout << "Error: Participante con ID " << id << " no encontrado.\n"; return; }
    cout << "\n--- Modificando Participante ID: " << p->ID << " (" << p->nombre << ") ---\n";
    cout << "Ingrese nuevo nombre (actual: " << p->nombre << "): ";
    string nuevoNombre; cin.ignore(); getline(cin, nuevoNombre); p->nombre = nuevoNombre;
    cout << "Ingrese nueva carrera (actual: " << p->carrera << "): ";
    string nuevaCarrera; getline(cin, nuevaCarrera); p->carrera = nuevaCarrera;
    cout << "Participante modificado con exito.\n";
}

void eliminarParticipante(int id) {
    participantes* p = buscarParticipante(id);
    if (p == NULL) { cout << "Error: Participante con ID " << id << " no encontrado para eliminar.\n"; return; }
    if (p->sig != NULL) p->sig->ant = p->ant;
    if (p->ant != NULL) p->ant->sig = p->sig;
    else primeroP = p->sig; // Es el primero
    delete p;
    cout << "Participante ID " << id << " eliminado con exito.\n";
}

void mostrarParticipantes() {
    cout << "\n--- LISTA DE PARTICIPANTES ---\n";
    participantes* actual = primeroP;
    if (actual == NULL) { cout << "La lista de participantes esta vacia.\n"; return; }
    while (actual != NULL) {
        cout << "ID: " << actual->ID << " | Nombre: " << actual->nombre
             << " | Carrera: " << actual->carrera << endl;
        actual = actual->sig;
    }
}

// ------------------- CRUD Organizadores (Lista Doble) -------------------
void insertarOrganizador(int id, string n, string d) {
    // --- VALIDACIÓN DE ID REPETIDO ---
    if (buscarOrganizador(id) != NULL) {
        cout << "ERROR DE VALIDACION: El Organizador con ID " << id << " ya existe. No se inserto.\n";
        return;
    }
    Organizadores* nuevo = new Organizadores(id, n, d);
    if (primeroOr == NULL) {
        primeroOr = nuevo; cout << "Organizador ID " << id << " insertado como primero.\n"; return;
    }
    Organizadores* actual = primeroOr;
    while (actual->sig != NULL) { actual = actual->sig; }
    actual->sig = nuevo;
    nuevo->ant = actual;
    cout << "Organizador ID " << id << " insertado al final.\n";
}

Organizadores* buscarOrganizador(int id) {
    Organizadores* actual = primeroOr;
    while (actual != NULL) {
        if (actual->ID == id) return actual;
        actual = actual->sig;
    }
    return NULL;
}

void modificarOrganizador(int id) {
    Organizadores* o = buscarOrganizador(id);
    if (o == NULL) { cout << "Error: Organizador con ID " << id << " no encontrado.\n"; return; }
    cout << "\n--- Modificando Organizador ID: " << o->ID << " (" << o->nombre << ") ---\n";
    cout << "Ingrese nuevo nombre (actual: " << o->nombre << "): ";
    cin.ignore(); getline(cin, o->nombre);
    cout << "Ingrese nuevo departamento (actual: " << o->departamento << "): ";
    getline(cin, o->departamento);
    cout << "Organizador modificado con exito.\n";
}

void eliminarOrganizador(int id) {
    Organizadores* o = buscarOrganizador(id);
    if (o == NULL) { cout << "Error: Organizador con ID " << id << " no encontrado para eliminar.\n"; return; }
    if (o->sig != NULL) o->sig->ant = o->ant;
    if (o->ant != NULL) o->ant->sig = o->sig;
    else primeroOr = o->sig;
    delete o;
    cout << "Organizador ID " << id << " eliminado con exito.\n";
}

void mostrarOrganizadores() {
    cout << "\n--- LISTA DE ORGANIZADORES ---\n";
    Organizadores* actual = primeroOr;
    if (actual == NULL) { cout << "La lista de organizadores esta vacia.\n"; return; }
    while (actual != NULL) {
        cout << "ID: " << actual->ID << " | Nombre: " << actual->nombre
             << " | Departamento: " << actual->departamento << endl;
        actual = actual->sig;
    }
}

// ------------------- CRUD Recursos (Lista Doble) -------------------
void insertarRecurso(string n, string d) {
    // --- VALIDACIÓN DE NOMBRE REPETIDO ---
    if (buscarRecurso(n) != NULL) {
        cout << "ERROR DE VALIDACION: El Recurso '" << n << "' ya existe. No se inserto.\n";
        return;
    }
    Recursos* nuevo = new Recursos(n, d);
    if (primeroR == NULL) {
        primeroR = nuevo; cout << "Recurso '" << n << "' insertado como primero.\n"; return;
    }
    Recursos* actual = primeroR;
    while (actual->sig != NULL) { actual = actual->sig; }
    actual->sig = nuevo;
    nuevo->ant = actual;
    cout << "Recurso '" << n << "' insertado al final.\n";
}

Recursos* buscarRecurso(string n) {
    Recursos* actual = primeroR;
    while (actual != NULL) {
        if (actual->nombre == n) return actual;
        actual = actual->sig;
    }
    return NULL;
}

void modificarRecurso(string n) {
    Recursos* r = buscarRecurso(n);
    if (r == NULL) { cout << "Error: Recurso con nombre '" << n << "' no encontrado.\n"; return; }
    cout << "\n--- Modificando Recurso: " << r->nombre << " ---\n";
    cout << "Ingrese nueva descripcion (actual: " << r->descripcion << "): ";
    cin.ignore(); getline(cin, r->descripcion);
    cout << "Recurso modificado con exito.\n";
}

void eliminarRecurso(string n) {
    Recursos* r = buscarRecurso(n);
    if (r == NULL) { cout << "Error: Recurso con nombre '" << n << "' no encontrado para eliminar.\n"; return; }
    if (r->sig != NULL) r->sig->ant = r->ant;
    if (r->ant != NULL) r->ant->sig = r->sig;
    else primeroR = r->sig;
    delete r;
    cout << "Recurso '" << n << "' eliminado con exito.\n";
}

void mostrarRecursos() {
    cout << "\n--- LISTA DE RECURSOS ---\n";
    Recursos* actual = primeroR;
    if (actual == NULL) { cout << "La lista de recursos esta vacia.\n"; return; }
    while (actual != NULL) {
        cout << "Nombre: " << actual->nombre << " | Descripcion: " << actual->descripcion << endl;
        actual = actual->sig;
    }
}

// ------------------- CRUD Historial (Lista Circular - Ordenada por Fecha) -------------------
void insertarHistorialOrdenado(int id, string fecha, participantes* p, eventos* e) {
    // --- VALIDACIÓN DE ID REPETIDO ---
    if (buscarHistorial(id) != NULL) {
        cout << "ERROR DE VALIDACION: El ID de Inscripcion " << id << " ya existe. No se inserto.\n";
        return;
    }
    historial_eventos* nuevo = new historial_eventos(id, fecha, p, e);

    if (primeroHistorial == NULL) {
        primeroHistorial = nuevo;
        nuevo->sig = primeroHistorial;
        cout << "Historial insertado como primer nodo circular.\n"; return;
    }

    historial_eventos* cola = primeroHistorial;
    while (cola->sig != primeroHistorial) { cola = cola->sig; }

    if (nuevo->fecha < primeroHistorial->fecha) {
        nuevo->sig = primeroHistorial;
        primeroHistorial = nuevo;
        cola->sig = primeroHistorial;
        cout << "Historial insertado al inicio y ordenado.\n"; return;
    }

    historial_eventos* actual = primeroHistorial;
    while (actual->sig != primeroHistorial && actual->sig->fecha < nuevo->fecha) {
        actual = actual->sig;
    }

    nuevo->sig = actual->sig;
    actual->sig = nuevo;
    cout << "Historial insertado ordenado en la lista circular.\n";
}

historial_eventos* buscarHistorial(int id) {
    if (primeroHistorial == NULL) return NULL;
    historial_eventos* actual = primeroHistorial;
    do {
        if (actual->ID == id) return actual;
        actual = actual->sig;
    } while (actual != primeroHistorial);
    return NULL;
}

void modificarHistorial(int id) {
    historial_eventos* h = buscarHistorial(id);
    if (h == NULL) { cout << "Error: Historial ID " << id << " no encontrado.\n"; return; }
    cout << "\n--- Modificando Historial ID: " << h->ID << " ---\n";
    cout << "Ingrese nueva fecha (YYYY-MM-DD) (actual: " << h->fecha << "): ";
    string nuevaFecha; cin.ignore(); getline(cin, nuevaFecha);
    h->fecha = nuevaFecha;
    cout << "Historial modificado. NOTA: Para reordenar se debe eliminar y reinsertar.\n";
}

void eliminarHistorial(int id) {
    historial_eventos* actual = primeroHistorial;
    historial_eventos* anterior = NULL;
    if (primeroHistorial == NULL) { cout << "El historial está vacío.\n"; return; }

    if (actual == actual->sig && actual->ID == id) {
        delete actual; primeroHistorial = NULL;
        cout << "Historial ID " << id << " eliminado.\n"; return;
    }

    do {
        if (actual->ID == id) {
            if (actual == primeroHistorial) {
                historial_eventos* cola = primeroHistorial;
                while (cola->sig != primeroHistorial) { cola = cola->sig; }
                primeroHistorial = actual->sig;
                cola->sig = primeroHistorial;
            } else {
                anterior->sig = actual->sig;
            }
            delete actual;
            cout << "Historial ID " << id << " eliminado.\n"; return;
        }
        anterior = actual;
        actual = actual->sig;
    } while (actual != primeroHistorial);

    cout << "Error: Historial ID " << id << " no encontrado para eliminar.\n";
}

void mostrarHistorial() {
    cout << "\n--- HISTORIAL DE INSCRIPCIONES (Lista Circular) ---\n";
    if (primeroHistorial == NULL) {
        cout << "El historial esta vacio.\n";
        return;
    }

    historial_eventos* actual = primeroHistorial;
    do {
        cout << "ID: " << actual->ID << " | Fecha: " << actual->fecha;
        if (actual->refParticipante) cout << " | Part: " << actual->refParticipante->nombre;
        if (actual->refEvento) cout << " | Evento: " << actual->refEvento->nombre;
        cout << endl;
        actual = actual->sig;
    } while (actual != primeroHistorial);
}


// ===================================================================
// ========================= IMPLEMENTACIONES RELACIONES =============
// ===================================================================

void asignarCategoriaAEvento(int eventoID, int categoriaID) {
    eventos* e = buscarEvento(eventoID);
    categorias* c = buscarCategoria(categoriaID);

    if (!e || !c) {
        cout << "Error: Evento o Categoria no encontrados.\n"; return;
    }

    // 1. Asignar categoría al Evento (Relación 1 a 1)
    e->categoria = c;

    // 2. Vincular Evento a la lista de Categoría (Relación 1 a N)
    enlaceCategoriaEvento* nuevoEnlace = new enlaceCategoriaEvento{e, c->listaEventos};
    c->listaEventos = nuevoEnlace;

    cout << "Relacion exitosa: Evento '" << e->nombre << "' asignado a Categoria '" << c->nombre << "'.\n";
}

void asignarOrganizadorAEvento(int orgID, int eventoID) {
    Organizadores* o = buscarOrganizador(orgID);
    eventos* e = buscarEvento(eventoID);
    if (!o || !e) { cout << "Error: Organizador o Evento no encontrados.\n"; return; }

    // Vincular Evento a la sub-lista del Organizador
    enlaceEvento* nuevoEnlace = new enlaceEvento{e, o->listaEventos};
    o->listaEventos = nuevoEnlace;

    cout << "Relacion exitosa: Organizador '" << o->nombre << "' asignado a Evento '" << e->nombre << "'.\n";
}

void inscribirParticipanteAEvento(int partID, int eventoID, string fecha) {
    participantes* p = buscarParticipante(partID);
    eventos* e = buscarEvento(eventoID);
    if (!p || !e) { cout << "Error: Participante o Evento no encontrados.\n"; return; }

    // 1. Vincular Participante a la lista de Evento (listaParticipantes del Evento)
    enlaceParticipante* nuevoEnlaceE = new enlaceParticipante{p, e->listaParticipantes};
    e->listaParticipantes = nuevoEnlaceE;

    // 2. Vincular Evento a la lista de Participante (listaEventos del Participante)
    enlaceEventoParticipante* nuevoEnlaceP = new enlaceEventoParticipante{e, p->listaEventos};
    p->listaEventos = nuevoEnlaceP;

    // 3. Registrar en el Historial Circular (ID generado automáticamente simple)
    int nuevoID = 1;
    if (primeroHistorial != NULL) {
        historial_eventos* temp = primeroHistorial;
        while(temp->sig != primeroHistorial) { temp = temp->sig; }
        nuevoID = temp->ID + 1;
    }
    insertarHistorialOrdenado(nuevoID, fecha, p, e);

    cout << "Relacion exitosa: Participante '" << p->nombre << "' inscrito en Evento '" << e->nombre << "'.\n";
}

void asignarRecursoAEvento(int eventoID, string recursoNombre) {
    eventos* e = buscarEvento(eventoID);
    Recursos* r = buscarRecurso(recursoNombre);
    if (!e || !r) { cout << "Error: Evento o Recurso no encontrados.\n"; return; }

    // Vincular Recurso a la sub-lista del Evento
    enlaceRecurso* nuevoEnlace = new enlaceRecurso{r, e->listaRecursos};
    e->listaRecursos = nuevoEnlace;

    cout << "Relacion exitosa: Recurso '" << r->nombre << "' asignado a Evento '" << e->nombre << "'.\n";
}


// ===================================================================
// ========================= FUNCIONES DE MENÚ =======================
// ===================================================================

// Nota: Las funciones de Consulta y Reporte no tienen implementación aquí, solo el menú
void menuConsultas() {
    cout << "\n--- MENU CONSULTAS ---\n";
    cout << "Implementacion de las 9 consultas pendiente.\n";
    // Si tienes implementadas las 9 consultas (consultaParticipanteMasEventos, etc.),
    // puedes agregarlas aquí.
}

void menuReportes() {
    cout << "\n--- MENU REPORTES ---\n";
    cout << "Implementacion de los 8 reportes pendiente.\n";
}


void gestionarCrud(int tipo) {
    int id;
    string nombre, desc, fecha, lugar, tipoEvento, carrera;
    int opcion;

    do {
        cout << "\n========================================\n";
        switch (tipo) {
            case 1: cout << "         MENU CRUD - EVENTOS\n"; break;
            case 2: cout << "         MENU CRUD - CATEGORIAS\n"; break;
            case 3: cout << "         MENU CRUD - PARTICIPANTES\n"; break;
            case 4: cout << "         MENU CRUD - ORGANIZADORES\n"; break;
            case 5: cout << "         MENU CRUD - RECURSOS\n"; break;
            case 6: cout << "         MENU CRUD - HISTORIAL\n"; break;
        }
        cout << "========================================\n";
        cout << "1. Insertar\n";
        cout << "2. Mostrar Todos\n";
        cout << "3. Buscar y Modificar\n";
        cout << "4. Eliminar\n";
        cout << "5. Volver al Menu Principal\n";
        cout << "Ingrese opcion: ";
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(100, '\n'); opcion = 0; } // Manejo de error de entrada

        // Limpiar el buffer para getline (excepto si la opción es 5 o inválida)
        if (opcion == 1 || opcion == 3 || opcion == 4) cin.ignore();

        switch (opcion) {
            case 1: // INSERTAR
                cout << "--- Insercion ---\n";
                if (tipo == 1) { // Eventos (ID, nombre, fecha, lugar, tipo)
                    cout << "ID Evento: "; cin >> id; cin.ignore();
                    cout << "Nombre: "; getline(cin, nombre);
                    cout << "Fecha (YYYY-MM-DD): "; getline(cin, fecha);
                    cout << "Lugar: "; getline(cin, lugar);
                    cout << "Tipo: "; getline(cin, tipoEvento);
                    insertarEventoOrdenado(id, nombre, fecha, lugar, tipoEvento);
                } else if (tipo == 2) { // Categorias (ID, nombre, descripcion)
                    cout << "ID Categoria: "; cin >> id; cin.ignore();
                    cout << "Nombre: "; getline(cin, nombre);
                    cout << "Descripcion: "; getline(cin, desc);
                    insertarCategoriaFinal(id, nombre, desc);
                } else if (tipo == 3) { // Participantes (ID, nombre, carrera)
                    cout << "ID Participante: "; cin >> id; cin.ignore();
                    cout << "Nombre: "; getline(cin, nombre);
                    cout << "Carrera: "; getline(cin, carrera);
                    insertarParticipante(id, nombre, carrera);
                } else if (tipo == 4) { // Organizadores (ID, nombre, departamento)
                    cout << "ID Organizador: "; cin >> id; cin.ignore();
                    cout << "Nombre: "; getline(cin, nombre);
                    cout << "Departamento: "; getline(cin, desc);
                    insertarOrganizador(id, nombre, desc);
                } else if (tipo == 5) { // Recursos (nombre, descripcion)
                    cout << "Nombre Recurso: "; getline(cin, nombre);
                    cout << "Descripcion: "; getline(cin, desc);
                    insertarRecurso(nombre, desc);
                } else if (tipo == 6) { // Historial (ID, fecha)
                    cout << "ID Inscripcion: "; cin >> id; cin.ignore();
                    cout << "Fecha (YYYY-MM-DD): "; getline(cin, fecha);
                    // El Historial requiere referencias P y E para ser completo
                    // Aqui se inserta un nodo simple, sin P y E por simplicidad en el CRUD.
                    insertarHistorialOrdenado(id, fecha, NULL, NULL);
                }
                break;
            case 2: // MOSTRAR
                if (tipo == 1) mostrarEventos();
                else if (tipo == 2) mostrarCategorias();
                else if (tipo == 3) mostrarParticipantes();
                else if (tipo == 4) mostrarOrganizadores();
                else if (tipo == 5) mostrarRecursos();
                else if (tipo == 6) mostrarHistorial();
                break;
            case 3: // BUSCAR Y MODIFICAR
                cout << "--- Modificacion ---\n";
                if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 4 || tipo == 6) {
                    cout << "Ingrese ID a modificar: "; cin >> id;
                    if (tipo == 1) modificarEvento(id);
                    else if (tipo == 2) modificarCategoria(id);
                    else if (tipo == 3) modificarParticipante(id);
                    else if (tipo == 4) modificarOrganizador(id);
                    else if (tipo == 6) modificarHistorial(id);
                } else if (tipo == 5) { // Recursos se busca por nombre
                    cout << "Ingrese Nombre del Recurso a modificar: "; getline(cin, nombre);
                    modificarRecurso(nombre);
                }
                break;
            case 4: // ELIMINAR
                cout << "--- Eliminacion ---\n";
                if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 4 || tipo == 6) {
                    cout << "Ingrese ID a eliminar: "; cin >> id;
                    if (tipo == 1) eliminarEvento(id);
                    else if (tipo == 2) eliminarCategoria(id);
                    else if (tipo == 3) eliminarParticipante(id);
                    else if (tipo == 4) eliminarOrganizador(id);
                    else if (tipo == 6) eliminarHistorial(id);
                } else if (tipo == 5) { // Recursos se elimina por nombre
                    cout << "Ingrese Nombre del Recurso a eliminar: "; getline(cin, nombre);
                    eliminarRecurso(nombre);
                }
                break;
            case 5:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}

void menuRelaciones() {
    int opcion;
    int id1, id2;
    string nombre, fecha;
    participantes* p; eventos* e; Organizadores* o; categorias* c; Recursos* r;

    do {
        cout << "\n========================================\n";
        cout << "       MENU DE RELACIONES (ENLACES)\n";
        cout << "========================================\n";
        cout << "1. Asignar Categoria a Evento (ID Evento, ID Categoria)\n";
        cout << "2. Asignar Organizador a Evento (ID Org, ID Evento)\n";
        cout << "3. Inscribir Participante a Evento (ID Part, ID Evento)\n";
        cout << "4. Asignar Recurso a Evento (ID Evento, Nombre Recurso)\n";
        cout << "5. Volver al Menu Principal\n";
        cout << "Ingrese opcion: ";
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(100, '\n'); opcion = 0; }

        switch (opcion) {
            case 1:
                cout << "ID del Evento: "; cin >> id1;
                cout << "ID de la Categoria: "; cin >> id2;
                asignarCategoriaAEvento(id1, id2);
                break;
            case 2:
                cout << "ID del Organizador: "; cin >> id1;
                cout << "ID del Evento: "; cin >> id2;
                asignarOrganizadorAEvento(id1, id2);
                break;
            case 3:
                cout << "ID del Participante: "; cin >> id1;
                cout << "ID del Evento: "; cin >> id2;
                cout << "Fecha de Inscripcion (YYYY-MM-DD): "; cin.ignore(); getline(cin, fecha);
                inscribirParticipanteAEvento(id1, id2, fecha);
                break;
            case 4:
                cout << "ID del Evento: "; cin >> id1; cin.ignore();
                cout << "Nombre del Recurso: "; getline(cin, nombre);
                asignarRecursoAEvento(id1, nombre);
                break;
            case 5: cout << "Volviendo al menu principal...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}

void menuPrincipal() {
    int opcion;
    do {
        cout << "\n========================================\n";
        cout << "   SISTEMA GESTION DE EVENTOS (MENU)\n";
        cout << "========================================\n";
        cout << "--- Administracion de Listas (CRUD) ---\n";
        cout << "1. Gestionar Eventos\n";
        cout << "2. Gestionar Categorias\n";
        cout << "3. Gestionar Participantes\n";
        cout << "4. Gestionar Organizadores\n";
        cout << "5. Gestionar Recursos\n";
        cout << "6. Gestionar Historial de Inscripciones\n";
        cout << "---------------------------------------\n";
        cout << "7. Gestionar Relaciones (Inscripciones, Asignaciones)\n";
        cout << "8. Ejecutar Consultas (9 Consultas rapidas) - PENDIENTE\n";
        cout << "9. Ejecutar Reportes Formales (8 Reportes) - PENDIENTE\n";
        cout << "10. Salir del Programa\n";
        cout << "Ingrese opcion: ";
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(100, '\n'); opcion = 0; }

        switch (opcion) {
            case 1: gestionarCrud(1); break;
            case 2: gestionarCrud(2); break;
            case 3: gestionarCrud(3); break;
            case 4: gestionarCrud(4); break;
            case 5: gestionarCrud(5); break;
            case 6: gestionarCrud(6); break;
            case 7: menuRelaciones(); break;
            case 8: menuConsultas(); break;
            case 9: menuReportes(); break;
            case 10: cout << "Saliendo del sistema. ¡Adios!\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 10);
}


// ===================================================================
// ============================ MAIN =================================
// ===================================================================
int main() {
    cout << "=== Sistema de Gestion de Eventos Universitarios ===\n\n";

    // --- DATOS DE PRUEBA INICIALES ---

    // Crear Categorías
    categorias* cat1 = new categorias(1, "Academico", "Charlas y conferencias");
    categorias* cat2 = new categorias(2, "Deportivo", "Actividades fisicas");
    primeroC = cat1;
    cat1->sig = cat2;

    // Crear Recursos
    Recursos* rec1 = new Recursos("Proyector", "Equipo audiovisual");
    Recursos* rec2 = new Recursos("Sala A", "Espacio cerrado");
    Recursos* rec3 = new Recursos("Cancha", "Campo deportivo");
    primeroR = rec1;
    rec1->sig = rec2;
    rec2->sig = rec3;

    // Crear Eventos
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
    enlaceCategoriaEvento* ec1 = new enlaceCategoriaEvento{ev1, NULL};
    enlaceCategoriaEvento* ec2 = new enlaceCategoriaEvento{ev2, NULL};
    enlaceCategoriaEvento* ec3 = new enlaceCategoriaEvento{ev3, NULL};
    cat1->listaEventos = ec1;
    ec1->sig = ec2;
    cat2->listaEventos = ec3;

    // Crear Participantes
    participantes* p1 = new participantes(1, "Ana Lopez", "Computacion");
    participantes* p2 = new participantes(2, "Luis Perez", "Mecatronica");
    participantes* p3 = new participantes(3, "Maria Torres", "Informatica");
    primeroP = p1;
    p1->sig = p2;
    p2->sig = p3;

    // Inscribir participantes y vincular
    // Ana y Luis en ev1 y ev3; Maria en ev2.
    // (Lógica de enlaces simplificada aquí para la inicialización)

    // Crear Organizadores
    Organizadores* o1 = new Organizadores(1, "Carlos Vega", "Computacion");
    Organizadores* o2 = new Organizadores(2, "Sofia Ruiz", "Deportes");
    primeroOr = o1;
    o1->sig = o2;

    // Asignar eventos a organizadores
    o1->listaEventos = new enlaceEvento{ev1, NULL};
    o1->listaEventos->sig = new enlaceEvento{ev2, NULL};
    o2->listaEventos = new enlaceEvento{ev3, NULL};

    // Asignar recursos a eventos
    ev1->listaRecursos = new enlaceRecurso{rec1, NULL};
    ev2->listaRecursos = new enlaceRecurso{rec1, NULL};
    ev2->listaRecursos->sig = new enlaceRecurso{rec2, NULL};
    ev3->listaRecursos = new enlaceRecurso{rec3, NULL};

    // Historial (manual)
    insertarHistorialOrdenado(1, "2025-09-29", p1, ev1);
    insertarHistorialOrdenado(2, "2025-09-29", p2, ev1);
    insertarHistorialOrdenado(3, "2025-10-01", p3, ev2);
    insertarHistorialOrdenado(4, "2025-10-09", p1, ev3);
    insertarHistorialOrdenado(5, "2025-10-09", p2, ev3);


    // Iniciar la ejecución del programa con el menú principal
    menuPrincipal();

    cout << "\n=== Fin del Programa ===\n";
    return 0;
}