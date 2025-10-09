#include <iostream>
#include <string>
using namespace std;


// Prototipos de Structs para referencias mutuas
struct enlaceEvento;
struct enlaceRecurso;
struct enlaceParticipante;
struct categorias;
struct eventos;
struct participantes;
struct enlaceCategoriaEvento;
struct enlaceEventoParticipante;

// ------------------- Recursos (lista doble) -------------------
/*
  Representa un recurso físico o lógico utilizado por eventos.
  Lista doblemente enlazada: permite recorrer adelante/atrás.
  Complejidad de inserción al final: O(n).
*/
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

// ------------------- Organizadores (lista doble) -------------------
/*
  Representa a personas que organizan eventos.
  Cada organizador mantiene una sublista (enlaceEvento*) que referencia
  los eventos a su cargo. Lista doble para la colección principal.
*/
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

// ------------------- Eventos (lista simple) -------------------
/*
  Nodo base del sistema. Lista simple ORDENADA por fecha (string YYYY-MM-DD).
  Relaciones:
    - categoria: puntero a 'categorias' (UNO a UNO).
    - listaRecursos: sublista de recursos asignados.
    - listaParticipantes: sublista de participantes inscritos.
*/
struct eventos {
    int ID;
    string nombre;
    string fecha;
    string lugar;
    string tipo;
    categorias* categoria;                  // cada evento pertenece a UNA categoría
    enlaceRecurso* listaRecursos;           // Recursos asignados al evento
    enlaceParticipante* listaParticipantes; // Participantes inscritos en el evento
    eventos* sig;                           // Para la lista simple de eventos

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

// ------------------- Participantes (lista doble) -------------------
/*
  Representa a estudiantes/participantes. Lista doble.
  'listaEventos' mantiene una sublista de enlaces a eventos donde está inscrito.
*/
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

// ------------------- Categorías (lista simple) -------------------
/*
  Agrupan eventos por temática. Cada categoría conserva sublista de sus eventos.
*/
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

// ------------------- Historial de eventos (lista circular) -------------------
/*
  Registro de (participante, evento, fecha) ya realizados o inscritos.
  Lista circular: facilita recorridos cíclicos. Inserción ordenada por fecha (string).
*/
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

// ------------------- Enlaces para las relaciones -------------------
/*
  Estructuras de "arista" para modelar relaciones N:M sin duplicar nodos.
*/
struct enlaceEvento {
    eventos* refEvento;
    enlaceEvento* sig = NULL;
};

struct enlaceRecurso {
    Recursos* refRecurso;
    enlaceRecurso* sig = NULL;
};

struct enlaceParticipante {
    participantes* refParticipante;
    enlaceParticipante* sig = NULL;
};

struct enlaceCategoriaEvento {
    eventos* refEvento;
    enlaceCategoriaEvento* sig = NULL;
};

struct enlaceEventoParticipante {
    eventos* refEvento;
    enlaceEventoParticipante* sig = NULL;
};

// ===================================================================
// ====================== PROTOTIPOS DE FUNCIONES ====================
// ===================================================================

// Funciones de busqueda (recorren listas, O(n))
eventos* buscarEvento(int id);
categorias* buscarCategoria(int id);
participantes* buscarParticipante(int id);
Organizadores* buscarOrganizador(int id);
Recursos* buscarRecurso(string n);

// ==== Validaciones / Exists ====
bool str_vacia(const string& s);
bool id_invalido(int id);
bool existeEventoID(int id);
bool existeCategoriaID(int id);
bool existeParticipanteID(int id);
bool existeOrganizadorID(int id);
bool existeRecursoNombre(const string& n);

bool esFechaValida(const string& f);
bool esTextoRazonable(const string& s);

// Wrappers de inserción con validación interactiva
void insertarEventoInteractivo(); // wrapper que valida en bucle
void insertarCategoriaInteractivo();

// Historial
bool existeRegistroHistorial(int partID, int eventoID);
int siguienteHistID();
void registrarHistorialSoloConEvento();

// Funciones CRUD (Insertar) - cada una valida y conecta a su lista
void insertarEventoOrdenado(int id, string n, string f, string l, string t);
void insertarCategoriaFinal(int id, string n, string d);
void insertarParticipante(int id, string n, string c);
void insertarOrganizador(int id, string n, string d);
void insertarRecurso(string n, string d);
void insertarHistorialOrdenado(int id, string f, participantes* p, eventos* e);

// ==== MODIFICAR ==== (devuelven true/false según éxito)
bool modificarEvento(int id, string nuevoNombre, string nuevaFecha, string nuevoLugar, string nuevoTipo);
bool modificarCategoria(int id, string nuevoNombre, string nuevaDesc);
bool modificarParticipante(int id, string nuevoNombre, string nuevaCarrera);
bool modificarOrganizador(int id, string nuevoNombre, string nuevoDepto);
bool modificarRecurso(const string& nombreActual, string nuevoNombre, string nuevaDesc);

// ==== ELIMINAR ====
bool eliminarEvento(int id);
bool eliminarCategoria(int id);
bool eliminarParticipante(int id);
bool eliminarOrganizador(int id);
bool eliminarRecurso(const string& nombre);
bool eliminarHistorial(int id); // opcional

// Funciones de Relación (crean enlaces en sublistas)
void asignarOrganizadorEvento(int orgID, int eventoID);
void inscribirParticipanteEvento(int partID, int eventoID);
void asignarRecursoEvento(int eventoID, string recursoNombre);
void asignarCategoriaEvento(int eventoID, int categoriaID);
void registrarHistorial(int historialID, string fecha, int partID, int eventoID);

// Funciones Mostrar (Debug/Reportes Simples)
void mostrarEventos();
void mostrarRecursos();
void mostrarHistorial();
void mostrarCategorias();
void mostrarOrganizadores();
void mostrarParticipantes();

// Funciones de Consultas (9) — KPIs y agregaciones
void consultaParticipanteMasEventos();
void consultaOrganizadorMasEventos();
void consultaTipoEventoFrecuente();
void consultaCategoriaMayorParticipacion();
void consultaRecursoMasUtilizado();
void consultaLugarMasEventos();
void consultaEventoMasParticipantes();
void consultaOrganizadorMasCategorias();
void consultaPorcentajeParticipacion();

// Funciones de Reportes (8 de la rúbrica + auxiliares existentes)
void reporteParticipantesPorApellido(bool ascendente); // 1
void reporteEventosPorOrganizador(int idOrganizador);  // 2
void reporteEventosPorCategoria(int idCategoria);      // 3
void reporteRecursosPorEvento(int idEvento);           // 4
void reporteEventosPorLugar(string lugarX);            // 5
void reporteTalleresPorDepartamento(string deptoX);    // 6
void reporteHistorialCompleto();                       // 7
void reporteOrganizadoresSinEventos();                 // 8

// Reportes extra utilitarios
void reporteEventosPorFecha(string fechaBuscada);
void reporteParticipantesMultiInscripcion();
void reporteOrganizadoresPorDepartamento(string deptoBuscado);
void reporteHistorialPorParticipante(int idParticipante);
void reporteEventosPorLugarFecha();

// Funciones de utilidad
void swapData(participantes* a, participantes* b);
void swapDataEventos(eventos* a, eventos* b);
string obtenerApellido(string nombreCompleto);
void cargarDatosIniciales();

void imprimirTodasLasConsultas();
void imprimirTodosLosReportes();

bool agregarParticipanteEventoSiNoExiste(int eventoID, int partID);
bool agregarRecursoEventoSiNoExiste(int eventoID, const string& recursoNombre);

// (si ya los tienes, no los dupliques)
bool yaInscritoEvento(participantes* p, eventos* e);
bool yaAsignadoRecursoEvento(int eventoID, const string& recursoNombre);

// Reemplazos de campos básicos (utilizan modificarEvento y validaciones)
bool reemplazarNombreEvento(int eventoID, const string& nombreActual, const string& nombreNuevo);
bool reemplazarFechaEvento(int eventoID, const string& fechaActual, const string& fechaNueva);
bool reemplazarLugarEvento(int eventoID, const string& lugarActual, const string& lugarNuevo);
bool reemplazarTipoEvento(int eventoID, const string& tipoActual, const string& tipoNuevo);

// Reemplazos de relaciones (manejan enlaces y consistencia)
bool reemplazarCategoriaEvento(int eventoID, int catActualID, int catNuevaID); // usar -1 para quitar
bool reemplazarOrganizadorEvento(int eventoID, int orgActualID, int orgNuevoID);
bool reemplazarParticipanteEvento(int eventoID, int partActualID, int partNuevoID);
bool reemplazarRecursoEvento(int eventoID, const string& recursoActual, const string& recursoNuevo);

// Helpers necesarios (si ya existen en tu código, no los dupliques)
void desasignarOrganizadorEvento(int orgID, int eventoID);
void desinscribirParticipanteEvento(int partID, int eventoID);
void desasignarRecursoEvento(int eventoID, const string& nombre);
bool yaAsignadoOrganizador(int orgID, int eventoID);
bool yaInscrito(participantes* p, eventos* e);
bool yaAsignadoRecurso(int eventoID, const string& recursoNombre);
bool agregarOrganizadorEventoSiNoExiste(int eventoID, int orgID);

string organizadoresDelEvento(eventos* e);

// ===================================================================
// ======================== IMPLEMENTACIÓN CRUD ======================
// ===================================================================

// Implementaciones de Búsqueda
/*
  Todas estas funciones recorren linealmente la lista correspondiente (O(n))
  y retornan el puntero al nodo si lo encuentran; en caso contrario, NULL.
*/
eventos* buscarEvento(int id) {
    eventos* aux = primeroE;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL;
}
categorias* buscarCategoria(int id) {
    categorias* aux = primeroC;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL;
}
participantes* buscarParticipante(int id) {
    participantes* aux = primeroP;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL;
}
Organizadores* buscarOrganizador(int id) {
    Organizadores* aux = primeroOr;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL;
}
Recursos* buscarRecurso(string n) {
    Recursos* aux = primeroR;
    while (aux != NULL) {
        if (aux->nombre == n) return aux;
        aux = aux->sig;
    }
    return NULL;
}

// ==== Validaciones / Exists ====
// str_vacia: true si solo hay espacios/saltos; id_invalido: IDs positivos requeridos
bool str_vacia(const string& s){ return s.find_first_not_of(" \t\n\r") == string::npos; }
bool id_invalido(int id){ return id <= 0; }

// Comprobaciones de existencia (reutilizan las búsquedas)
bool existeEventoID(int id){ return buscarEvento(id) != NULL; }
bool existeCategoriaID(int id){ return buscarCategoria(id) != NULL; }
bool existeParticipanteID(int id){ return buscarParticipante(id) != NULL; }
bool existeOrganizadorID(int id){ return buscarOrganizador(id) != NULL; }
bool existeRecursoNombre(const string& n){ return buscarRecurso(n) != NULL; }

// Implementación de Inserción (con validaciones)
/*
  insertarEventoOrdenado:
    - Valida datos de entrada.
    - Inserta en la lista de eventos manteniendo el ORDEN por FECHA.
    - Complejidad: O(n) al buscar el punto de inserción.
*/
void insertarEventoOrdenado(int id, string n, string f, string l, string t) {
    if (id_invalido(id)) { cout << " ID invalido al insertar Evento.\n"; return; }
    if (str_vacia(n))    { cout << " Nombre de evento vacio.\n"; return; }
    if (!esFechaValida(f)){ cout << " Fecha invalida. Use formato YYYY-MM-DD.\n"; return; }
    if (str_vacia(l) || !esTextoRazonable(l)) { cout << " Lugar invalido. Debe ser texto.\n"; return; }
    if (str_vacia(t) || !esTextoRazonable(t)) { cout << " Tipo invalido. Debe ser texto.\n"; return; }
    if (existeEventoID(id)) { cout << " ID de Evento repetido.\n"; return; }

    eventos* nuevo = new eventos(id, n, f, l, t);
    if (primeroE == NULL) { primeroE = nuevo; return; }
    if (nuevo->fecha < primeroE->fecha) { nuevo->sig = primeroE; primeroE = nuevo; return; }
    eventos* actual = primeroE;
    while (actual->sig != NULL && actual->sig->fecha < nuevo->fecha) actual = actual->sig;
    nuevo->sig = actual->sig; actual->sig = nuevo;
}

/*
  insertarCategoriaFinal:
    - Inserta al final de la lista simple de categorías.
    - Valida duplicidad de ID y campos no vacíos.
*/
void insertarCategoriaFinal(int id, string n, string d) {
    if (id_invalido(id) || str_vacia(n) || str_vacia(d)) {
        cout << " Datos invalidos al insertar Categoria.\n"; return;
    }
    if (existeCategoriaID(id)) { cout << " ID de Categoria repetido.\n"; return; }

    categorias* nuevo = new categorias(id, n, d);
    if (primeroC == NULL) { primeroC = nuevo; return; }
    categorias* actual = primeroC; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo;
}

/*
  insertarParticipante:
    - Inserta al final de la lista doble de participantes.
*/
void insertarParticipante(int id, string n, string c) {
    if (id_invalido(id) || str_vacia(n) || str_vacia(c)) {
        cout << " Datos invalidos al insertar Participante.\n"; return;
    }
    if (existeParticipanteID(id)) { cout << " ID de Participante repetido.\n"; return; }

    participantes* nuevo = new participantes(id, n, c);
    if (primeroP == NULL) { primeroP = nuevo; return; }
    participantes* actual = primeroP; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo; nuevo->ant = actual;
}

/*
  insertarOrganizador:
    - Inserta al final de la lista doble de organizadores.
*/
void insertarOrganizador(int id, string n, string d) {
    if (id_invalido(id) || str_vacia(n) || str_vacia(d)) {
        cout << " Datos invalidos al insertar Organizador.\n"; return;
    }
    if (existeOrganizadorID(id)) { cout << " ID de Organizador repetido.\n"; return; }

    Organizadores* nuevo = new Organizadores(id, n, d);
    if (primeroOr == NULL) { primeroOr = nuevo; return; }
    Organizadores* actual = primeroOr; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo; nuevo->ant = actual;
}

/*
  insertarRecurso:
    - Inserta al final de la lista doble de recursos.
    - Evita nombres duplicados.
*/
void insertarRecurso(string n, string d) {
    if (str_vacia(n) || str_vacia(d)) {
        cout << " Datos invalidos al insertar Recurso.\n"; return;
    }
    if (existeRecursoNombre(n)) { cout << " Nombre de Recurso repetido.\n"; return; }

    Recursos* nuevo = new Recursos(n, d);
    if (primeroR == NULL) { primeroR = nuevo; return; }
    Recursos* actual = primeroR; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo; nuevo->ant = actual;
}

/*
  insertarHistorialOrdenado:
    - Inserta en lista circular de historial manteniendo orden por fecha (string).
    - Maneja los casos: lista vacía, insertar antes del primero, o en el medio.
*/
void insertarHistorialOrdenado(int id, string f, participantes* p, eventos* e) {
    if (id_invalido(id) || str_vacia(f) || p==NULL || e==NULL) {
        cout << " Datos invalidos al insertar Historial.\n"; return;
    }
    historial_eventos* nuevo = new historial_eventos(id, f, p, e);
    if (primeroHistorial == NULL) { primeroHistorial = nuevo; nuevo->sig = nuevo; return; }

    historial_eventos* curr = primeroHistorial;
    historial_eventos* prev = NULL;
    do {
        if (f < curr->fecha) break;
        prev = curr; curr = curr->sig;
    } while (curr != primeroHistorial);

    if (prev == NULL) {
        // insertar antes del primero
        historial_eventos* ult = primeroHistorial;
        while (ult->sig != primeroHistorial) ult = ult->sig;
        nuevo->sig = primeroHistorial;
        primeroHistorial = nuevo;
        ult->sig = primeroHistorial;
    } else {
        prev->sig = nuevo; nuevo->sig = curr;
    }
}


// Implementaciones de Relación
/*
  Todas crean enlaces unidireccionales en las sublistas correspondientes.
  No eliminan ni duplican nodos principales.
*/
void asignarOrganizadorEvento(int orgID, int eventoID) {
    Organizadores* org = buscarOrganizador(orgID);
    eventos* ev = buscarEvento(eventoID);
    if (!org || !ev) return;
    enlaceEvento* nuevoEnlace = new enlaceEvento{ev, org->listaEventos};
    org->listaEventos = nuevoEnlace;
}
void inscribirParticipanteEvento(int partID, int eventoID) {
    participantes* part = buscarParticipante(partID);
    eventos* ev = buscarEvento(eventoID);
    if (!part || !ev) return;
    // Participante -> Evento
    enlaceEventoParticipante* nuevoEnlaceP = new enlaceEventoParticipante{ev, part->listaEventos};
    part->listaEventos = nuevoEnlaceP;
    // Evento -> Participante
    enlaceParticipante* nuevoEnlaceE = new enlaceParticipante{part, ev->listaParticipantes};
    ev->listaParticipantes = nuevoEnlaceE;
}
void asignarRecursoEvento(int eventoID, string recursoNombre) {
    eventos* ev = buscarEvento(eventoID);
    Recursos* rec = buscarRecurso(recursoNombre);
    if (!ev || !rec) return;
    enlaceRecurso* nuevoEnlace = new enlaceRecurso{rec, ev->listaRecursos};
    ev->listaRecursos = nuevoEnlace;
}
void asignarCategoriaEvento(int eventoID, int categoriaID) {
    eventos* ev = buscarEvento(eventoID);
    categorias* cat = buscarCategoria(categoriaID);
    if (!ev || !cat) return;
    ev->categoria = cat;
    enlaceCategoriaEvento* nuevoEnlace = new enlaceCategoriaEvento{ev, cat->listaEventos};
    cat->listaEventos = nuevoEnlace;
}
void registrarHistorial(int historialID, string fecha, int partID, int eventoID) {
    participantes* p = buscarParticipante(partID);
    eventos* e = buscarEvento(eventoID);
    if (!p || !e) return;

    if(existeRegistroHistorial(partID, eventoID)){
        cout << " Ya existia este registro en historial.\n";
        return;
    }
    insertarHistorialOrdenado(historialID, fecha, p, e);
}


// ===================================================================
// ========================= MODIFICAR / ELIMINAR ====================
// ===================================================================

// ------------------- VALIDACIONES EXTRA -------------------
/*
  esFechaValida:
    - Verifica formato "YYYY-MM-DD": longitud, guiones en posiciones 4 y 7,
      y dígitos en el resto. No valida meses cortos ni bisiestos.
*/
bool esFechaValida(const string& f){
    // Formato esperado: YYYY-MM-DD => longitud 10, guiones en 4 y 7
    if (f.size() != 10) return false;
    if (f[4] != '-' || f[7] != '-') return false;

    // Todos los otros deben ser dígitos
    for (int i = 0; i < 10; ++i){
        if (i == 4 || i == 7) continue;
        char c = f[i];
        if (c < '0' || c > '9') return false;
    }

    int y = stoi(f.substr(0,4));
    int m = stoi(f.substr(5,2));
    int d = stoi(f.substr(8,2));

    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false;

    // (Simple: no validamos meses de 30/31 ni bisiesto; si quieres lo añadimos)
    return true;
}

/*
  esTextoRazonable:
    - Acepta al menos una letra (ASCII o con acento básico).
    - Evita entradas puramente numéricas o símbolos sueltos.
*/
bool esTextoRazonable(const string& s){
    // Debe tener al menos una letra (evita entradas como "56" o "5")
    for(char c : s){
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= char(160))) {
            // permite letras ASCII y también acentos simples (>=160)
            return true;
        }
    }
    return false;
}


/*
  modificarEvento:
    - Actualiza nombre/fecha/lugar/tipo con validaciones.
    - Si cambia la fecha, reubica el nodo para mantener ORDEN por fecha.
    - Complejidad: O(n) para localización/reinserción.
*/
bool modificarEvento(int id, string nuevoNombre, string nuevaFecha, string nuevoLugar, string nuevoTipo){
    eventos* e = buscarEvento(id);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }

    if (str_vacia(nuevoNombre))                { cout<<" Nombre vacio.\n"; return false; }
    if (!esFechaValida(nuevaFecha))            { cout<<" Fecha invalida. Use formato YYYY-MM-DD.\n"; return false; }
    if (str_vacia(nuevoLugar) || !esTextoRazonable(nuevoLugar)) { cout<<" Lugar invalido. Debe ser texto.\n"; return false; }
    if (str_vacia(nuevoTipo)  || !esTextoRazonable(nuevoTipo))  { cout<<" Tipo invalido. Debe ser texto.\n"; return false; }

    bool cambiaOrden = (nuevaFecha != e->fecha);
    e->nombre = nuevoNombre; e->lugar = nuevoLugar; e->tipo = nuevoTipo;
    if (!cambiaOrden){ e->fecha = nuevaFecha; return true; }

    // quitar nodo y reinsertar por fecha
    eventos* dummy = new eventos(-1,"","","","");
    dummy->sig = primeroE;
    eventos* prev = dummy;
    while(prev->sig && prev->sig != e) prev = prev->sig;
    if(prev->sig == e){ prev->sig = e->sig; }
    primeroE = dummy->sig; delete dummy;

    e->sig = NULL; e->fecha = nuevaFecha;
    if (primeroE == NULL || e->fecha < primeroE->fecha){ e->sig = primeroE; primeroE = e; return true; }
    eventos* a = primeroE; while(a->sig && a->sig->fecha < e->fecha) a = a->sig;
    e->sig = a->sig; a->sig = e; return true;
}

/*
  modificarCategoria/Participante/Organizador/Recurso:
    - Cambian campos básicos con validaciones de no vacío/duplicados.
*/
bool modificarCategoria(int id, string nuevoNombre, string nuevaDesc){
    categorias* c = buscarCategoria(id); if(!c){ cout<<" Categoria no encontrada.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevaDesc)){ cout<<" Datos invalidos.\n"; return false; }
    c->nombre = nuevoNombre; c->descripcion = nuevaDesc; return true;
}
bool modificarParticipante(int id, string nuevoNombre, string nuevaCarrera){
    participantes* p = buscarParticipante(id); if(!p){ cout<<" Participante no encontrado.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevaCarrera)){ cout<<" Datos invalidos.\n"; return false; }
    p->nombre = nuevoNombre; p->carrera = nuevaCarrera; return true;
}
bool modificarOrganizador(int id, string nuevoNombre, string nuevoDepto){
    Organizadores* o = buscarOrganizador(id); if(!o){ cout<<" Organizador no encontrado.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevoDepto)){ cout<<" Datos invalidos.\n"; return false; }
    o->nombre = nuevoNombre; o->departamento = nuevoDepto; return true;
}
bool modificarRecurso(const string& nombreActual, string nuevoNombre, string nuevaDesc){
    Recursos* r = buscarRecurso(nombreActual); if(!r){ cout<<" Recurso no encontrado.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevaDesc)){ cout<<" Datos invalidos.\n"; return false; }
    if (nuevoNombre != nombreActual && existeRecursoNombre(nuevoNombre)){ cout<<" Ya existe un recurso con ese nombre.\n"; return false; }
    r->nombre = nuevoNombre; r->descripcion = nuevaDesc; return true;
}

// ---- Eliminar ----
/*
  eliminarEvento:
    - Desconecta TODAS las referencias a este evento:
        1) desde todos los organizadores (sublista de eventos a cargo),
        2) desde participantes y su lista de eventos,
        3) desde la sublista de recursos del evento,
        4) desde historial (lista circular),
        5) finalmente, lo retira de la lista principal 'primeroE'.
    - Complejidad total: O(n + m + ...), lineal en el tamaño de las relaciones.
*/
bool eliminarEvento(int id){
    eventos* target = buscarEvento(id); if(!target){ cout<<" Evento no encontrado.\n"; return false; }

    // 1) quitar referencias desde Organizadores
    Organizadores* o = primeroOr;
    while(o){
        enlaceEvento* prev=NULL; enlaceEvento* cur=o->listaEventos;
        while(cur){
            if(cur->refEvento==target){
                if(prev) prev->sig = cur->sig; else o->listaEventos = cur->sig;
                delete cur; break;
            }
            prev = cur; cur = cur->sig;
        }
        o = o->sig;
    }

    // 2) quitar referencias desde Participantes y liberar listaParticipantes del evento
    enlaceParticipante* ep = target->listaParticipantes;
    while(ep){
        participantes* p = ep->refParticipante;
        enlaceEventoParticipante* prev=NULL; enlaceEventoParticipante* ce=p->listaEventos;
        while(ce){
            if(ce->refEvento==target){
                if(prev) prev->sig = ce->sig; else p->listaEventos = ce->sig;
                delete ce; break;
            }
            prev=ce; ce=ce->sig;
        }
        enlaceParticipante* tmp = ep; ep=ep->sig; delete tmp;
    }
    target->listaParticipantes=NULL;

    // 3) liberar enlaces de recursos del evento
    enlaceRecurso* er = target->listaRecursos;
    while(er){ enlaceRecurso* tmp=er; er=er->sig; delete tmp; }
    target->listaRecursos=NULL;

    // 4) quitar del historial (manejar circular, casos de único nodo / cabeza)
    if(primeroHistorial){
        historial_eventos* curr=primeroHistorial; historial_eventos* prev=NULL;
        do{
            if(curr->refEvento==target){
                if(curr==primeroHistorial){
                    if(primeroHistorial->sig==primeroHistorial){ delete curr; primeroHistorial=NULL; break; }
                    historial_eventos* ult=primeroHistorial;
                    while(ult->sig!=primeroHistorial) ult=ult->sig;
                    primeroHistorial = curr->sig;
                    ult->sig = primeroHistorial;
                    historial_eventos* toDel = curr; curr = curr->sig; delete toDel;
                    continue;
                }else{
                    prev->sig = curr->sig; delete curr; curr = prev->sig; continue;
                }
            }
            prev = curr; curr = curr->sig;
        } while(curr && curr!=primeroHistorial);
    }

    // 5) quitar de la lista simple primeroE
    eventos* dummy = new eventos(-1,"","","","");
    dummy->sig = primeroE;
    eventos* pr = dummy;
    while(pr->sig && pr->sig!=target) pr = pr->sig;
    if(pr->sig==target){ pr->sig = target->sig; }
    primeroE = dummy->sig; delete dummy;

    delete target;
    return true;
}

/*
  eliminarCategoria:
    - Desasocia todos los eventos que apuntan a ella.
    - Libera sublista de enlaces de la categoría.
    - Remueve el nodo de la lista principal.
*/
bool eliminarCategoria(int id){
    categorias* c = buscarCategoria(id); if(!c){ cout<<" Categoria no encontrada.\n"; return false; }
    // desasociar eventos que apuntan a esta categoria
    eventos* e = primeroE;
    while(e){ if(e->categoria==c) e->categoria=NULL; e=e->sig; }
    // liberar sublista de enlaces de la categoria
    enlaceCategoriaEvento* ce = c->listaEventos;
    while(ce){ enlaceCategoriaEvento* tmp=ce; ce=ce->sig; delete tmp; }
    // quitar de lista simple
    categorias* dummy = new categorias(-1,"","");
    dummy->sig = primeroC;
    categorias* pr = dummy; while(pr->sig && pr->sig!=c) pr=pr->sig;
    if(pr->sig==c){ pr->sig = c->sig; }
    primeroC = dummy->sig; delete dummy; delete c; return true;
}

/*
  eliminarParticipante:
    - Quita enlaces en cada evento y su propia sublista de eventos.
    - Quita entradas del historial donde aparece.
    - Remueve de la lista doble principal.
*/
bool eliminarParticipante(int id){
    participantes* p = buscarParticipante(id); if(!p){ cout<<" Participante no encontrado.\n"; return false; }
    // quitar en cada evento su enlaceParticipante y su lista de eventos
    enlaceEventoParticipante* evp = p->listaEventos;
    while(evp){
        eventos* e = evp->refEvento;
        enlaceParticipante* prev=NULL; enlaceParticipante* cur=e->listaParticipantes;
        while(cur){
            if(cur->refParticipante==p){
                if(prev) prev->sig = cur->sig; else e->listaParticipantes = cur->sig;
                delete cur; break;
            }
            prev=cur; cur=cur->sig;
        }
        enlaceEventoParticipante* tmp=evp; evp=evp->sig; delete tmp;
    }
    // quitar del historial (circular)
    if(primeroHistorial){
        historial_eventos* curr=primeroHistorial; historial_eventos* prev=NULL;
        do{
            if(curr->refParticipante==p){
                if(curr==primeroHistorial){
                    if(primeroHistorial->sig==primeroHistorial){ delete curr; primeroHistorial=NULL; break; }
                    historial_eventos* ult=primeroHistorial; while(ult->sig!=primeroHistorial) ult=ult->sig;
                    primeroHistorial = curr->sig; ult->sig = primeroHistorial; delete curr; curr=primeroHistorial; prev=NULL; continue;
                } else { prev->sig = curr->sig; delete curr; curr=prev->sig; continue; }
            }
            prev=curr; curr=curr->sig;
        } while(curr && curr!=primeroHistorial);
    }
    // quitar de lista doble
    if(p->ant) p->ant->sig = p->sig; else primeroP = p->sig;
    if(p->sig) p->sig->ant = p->ant;
    delete p; return true;
}

/*
  eliminarOrganizador:
    - Libera sus enlaces a eventos (no borra los eventos).
    - Remueve el organizador de la lista doble.
*/
bool eliminarOrganizador(int id){
    Organizadores* o = buscarOrganizador(id); if(!o){ cout<<" Organizador no encontrado.\n"; return false; }
    // liberar su sublista de eventos (solo enlaces, no borrar eventos)
    enlaceEvento* le = o->listaEventos; while(le){ enlaceEvento* tmp=le; le=le->sig; delete tmp; }
    // quitar de lista doble
    if(o->ant) o->ant->sig = o->sig; else primeroOr = o->sig;
    if(o->sig) o->sig->ant = o->ant;
    delete o; return true;
}

/*
  eliminarRecurso:
    - Quita referencia del recurso en todos los eventos donde esté.
    - Remueve el recurso de la lista doble de recursos.
*/
bool eliminarRecurso(const string& nombre){
    Recursos* r = buscarRecurso(nombre); if(!r){ cout<<" Recurso no encontrado.\n"; return false; }
    // quitar de todos los eventos donde aparezca
    eventos* e = primeroE;
    while(e){
        enlaceRecurso* prev=NULL; enlaceRecurso* cur=e->listaRecursos;
        while(cur){
            if(cur->refRecurso==r){
                if(prev) prev->sig = cur->sig; else e->listaRecursos = cur->sig;
                delete cur; break;
            }
            prev=cur; cur=cur->sig;
        }
        e=e->sig;
    }
    // quitar de lista doble
    if(r->ant) r->ant->sig = r->sig; else primeroR = r->sig;
    if(r->sig) r->sig->ant = r->ant;
    delete r; return true;
}

/*
  eliminarHistorial:
    - Elimina por ID de la lista circular.
    - Maneja los casos especiales (único nodo, cabeza).
*/
bool eliminarHistorial(int id){
    if(!primeroHistorial){ cout<<" Historial vacio.\n"; return false; }
    historial_eventos* curr=primeroHistorial; historial_eventos* prev=NULL;
    do{
        if(curr->ID==id){
            if(curr==primeroHistorial){
                if(primeroHistorial->sig==primeroHistorial){ delete curr; primeroHistorial=NULL; return true; }
                historial_eventos* ult=primeroHistorial; while(ult->sig!=primeroHistorial) ult=ult->sig;
                primeroHistorial = curr->sig; ult->sig = primeroHistorial; delete curr; return true;
            } else {
                prev->sig = curr->sig; delete curr; return true;
            }
        }
        prev=curr; curr=curr->sig;
    } while(curr && curr!=primeroHistorial);
    cout<<" ID de historial no encontrado.\n"; return false;
}

// ===================================================================
// ==================== IMPLEMENTACIÓN CONSULTAS =====================
// ===================================================================

// 1️⃣ Participante que ha asistido a más eventos
void consultaParticipanteMasEventos() {
    if (primeroP == NULL) { cout << " No hay participantes registrados.\n"; return; }
    participantes* p = primeroP; participantes* mayor = NULL; int maxEventos = 0;
    while (p != NULL) {
        int contador = 0; enlaceEventoParticipante* aux = p->listaEventos;
        while (aux != NULL) { contador++; aux = aux->sig; }
        if (contador > maxEventos) { maxEventos = contador; mayor = p; }
        p = p->sig;
    }
    if (mayor != NULL)
        cout << " Participante con mas eventos: " << mayor->nombre << " (" << maxEventos << " eventos)\n";
    else
        cout << " No hay inscripciones registradas.\n";
}

// 2️⃣ Organizador con más eventos a cargo
void consultaOrganizadorMasEventos() {
    if (primeroOr == NULL) { cout << " No hay organizadores registrados.\n"; return; }
    Organizadores* o = primeroOr; Organizadores* mayor = NULL; int maxEventos = 0;
    while (o != NULL) {
        int contador = 0; enlaceEvento* aux = o->listaEventos;
        while (aux != NULL) { contador++; aux = aux->sig; }
        if (contador > maxEventos) { maxEventos = contador; mayor = o; }
        o = o->sig;
    }
    if (mayor != NULL)
        cout << " Organizador con mas eventos: " << mayor->nombre << " | Eventos: " << maxEventos << endl;
    else
        cout << " No hay organizadores con eventos.\n";
}

// 3️⃣ Tipo de evento más frecuente
void consultaTipoEventoFrecuente() {
    if (primeroE == NULL) { cout << " No hay eventos registrados.\n"; return; }

    struct TipoCont { string tipo; int cantidad; };
    TipoCont tipos[100]; int nTipos = 0;

    // contar por tipo (Charla, Taller, Feria, etc.)
    eventos* e = primeroE;
    while (e != NULL) {
        bool found = false;
        for (int i = 0; i < nTipos; ++i) {
            if (tipos[i].tipo == e->tipo) { tipos[i].cantidad++; found = true; break; }
        }
        if (!found && nTipos < 100) {
            tipos[nTipos].tipo = e->tipo;
            tipos[nTipos].cantidad = 1;
            nTipos++;
        }
        e = e->sig;
    }

    // hallar máximo
    int maxCant = 0;
    for (int i = 0; i < nTipos; ++i) if (tipos[i].cantidad > maxCant) maxCant = tipos[i].cantidad;

    // contar empatados
    int empatados = 0;
    for (int i = 0; i < nTipos; ++i) if (tipos[i].cantidad == maxCant) empatados++;

    if (empatados > 1) {
        cout << " Tipos de evento mas frecuentes (empate con " << maxCant << " eventos):\n";
        for (int i = 0; i < nTipos; ++i)
            if (tipos[i].cantidad == maxCant)
                cout << "  - " << tipos[i].tipo << "\n";
    } else {
        for (int i = 0; i < nTipos; ++i)
            if (tipos[i].cantidad == maxCant) {
                cout << " Tipo de evento mas frecuente: " << tipos[i].tipo
                     << " (" << maxCant << " eventos)\n";
                break;
            }
    }
}



// 4️⃣ Categoría con mayor participación estudiantil
void consultaCategoriaMayorParticipacion() {
    if (primeroC == NULL) { cout << "4️⃣ No hay categorias registradas.\n"; return; }
    categorias* c = primeroC; categorias* mayor = NULL; int maxParticipantes = 0;
    while (c != NULL) {
        int total = 0; enlaceCategoriaEvento* ev = c->listaEventos;
        while (ev != NULL) {
            enlaceParticipante* p = ev->refEvento->listaParticipantes;
            while (p != NULL) { total++; p = p->sig; }
            ev = ev->sig;
        }
        if (total > maxParticipantes) { maxParticipantes = total; mayor = c; }
        c = c->sig;
    }
    if (mayor != NULL)
        cout << " Categoria con mayor participacion: " << mayor->nombre << " (" << maxParticipantes << " participantes)\n";
    else
        cout << " No hay categorias con eventos inscritos.\n";
}

// 5️⃣ Recurso más utilizado en eventos
void consultaRecursoMasUtilizado() {
    if (primeroR == NULL) { cout << " No hay recursos registrados.\n"; return; }
    Recursos* r = primeroR; Recursos* masUsado = NULL; int maxUso = 0;
    while (r != NULL) {
        int contador = 0; eventos* e = primeroE;
        while (e != NULL) {
            enlaceRecurso* aux = e->listaRecursos;
            while (aux != NULL) {
                if (aux->refRecurso == r) contador++;
                aux = aux->sig;
            }
            e = e->sig;
        }
        if (contador > maxUso) { maxUso = contador; masUsado = r; }
        r = r->sig;
    }
    if (masUsado != NULL)
        cout << " Recurso mas utilizado: " << masUsado->nombre << " (" << maxUso << " eventos)\n";
    else
        cout << "Ningun recurso ha sido usado.\n";
}

// 6️⃣ Lugar que ha albergado más eventos
void consultaLugarMasEventos() {
    if (primeroE == NULL) { cout << " No hay eventos registrados.\n"; return; }

    struct LugarContador { string lugar; int cantidad; };
    LugarContador lugares[100];
    int totalLugares = 0;

    eventos* e1 = primeroE;
    while (e1 != NULL) {
        bool encontrado = false;
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].lugar == e1->lugar) { lugares[i].cantidad++; encontrado = true; break; }
        }
        if (!encontrado && totalLugares < 100) {
            lugares[totalLugares].lugar = e1->lugar;
            lugares[totalLugares].cantidad = 1;
            totalLugares++;
        }
        e1 = e1->sig;
    }

    int max = 0;
    for (int i = 0; i < totalLugares; i++) {
        if (lugares[i].cantidad > max) max = lugares[i].cantidad;
    }

    int empates = 0;
    for (int i = 0; i < totalLugares; i++) { if (lugares[i].cantidad == max) empates++; }

    if (empates > 1) {
        cout << " Hay varios lugares empatados con " << max << " eventos:\n";
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].cantidad == max) cout << " - " << lugares[i].lugar << endl;
        }
    } else {
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].cantidad == max) {
                cout << " Lugar con mas eventos: " << lugares[i].lugar << " (" << max << " eventos)\n";
                break;
            }
        }
    }
}

// 7️⃣ Evento con la mayor cantidad de participantes inscritos
void consultaEventoMasParticipantes() {
    if (primeroE == NULL) { cout << " No hay eventos registrados.\n"; return; }
    eventos* e = primeroE; eventos* mayor = NULL; int maxPart = -1;

    while (e != NULL) {
        int contador = 0; enlaceParticipante* aux = e->listaParticipantes;
        while (aux != NULL) { contador++; aux = aux->sig; }

        if (contador > maxPart) { maxPart = contador; mayor = e; }
        e = e->sig;
    }

    if (mayor != NULL && maxPart > 0)
        cout << " Evento con mas participantes: " << mayor->nombre << " (Fecha: " << mayor->fecha << ", " << maxPart << " inscritos)\n";
    else
        cout << " No se encontraron eventos con participantes inscritos.\n";
}

// 8️⃣ Organizador que ha gestionado eventos en más categorías distintas
void consultaOrganizadorMasCategorias() {
    if (primeroOr == NULL) { cout << " No hay organizadores registrados.\n"; return; }

    // 1) primera pasada: hallar el máximo número de categorías distintas
    int maxCategorias = -1;
    for (Organizadores* org = primeroOr; org != NULL; org = org->sig) {
        categorias* cats[200]; int nCats = 0;
        for (enlaceEvento* ev = org->listaEventos; ev != NULL; ev = ev->sig) {
            if (ev->refEvento && ev->refEvento->categoria) {
                categorias* c = ev->refEvento->categoria;
                bool existe = false;
                for (int i = 0; i < nCats; ++i) if (cats[i] == c) { existe = true; break; }
                if (!existe && nCats < 200) cats[nCats++] = c;
            }
        }
        if (nCats > maxCategorias) maxCategorias = nCats;
    }

    if (maxCategorias <= 0) {
        cout << " No hay organizadores con eventos asignados a categorias.\n";
        return;
    }

    // 2) segunda pasada: imprimir TODOS los empatados + su lista de categorías
    cout << " Organizadores con mas categorias distintas (" << maxCategorias << "):\n";
    for (Organizadores* org = primeroOr; org != NULL; org = org->sig) {
        categorias* cats[200]; int nCats = 0;
        for (enlaceEvento* ev = org->listaEventos; ev != NULL; ev = ev->sig) {
            if (ev->refEvento && ev->refEvento->categoria) {
                categorias* c = ev->refEvento->categoria;
                bool existe = false;
                for (int i = 0; i < nCats; ++i) if (cats[i] == c) { existe = true; break; }
                if (!existe && nCats < 200) cats[nCats++] = c;
            }
        }
        if (nCats == maxCategorias) {
            cout << "  - " << org->nombre << " (" << org->departamento << ") | Categorias: ";
            for (int i = 0; i < nCats; ++i) {
                if (i) cout << ", ";
                cout << cats[i]->nombre;
            }
            cout << "\n";
        }
    }
}


//  Porcentaje de estudiantes que han participado en al menos un evento vs. los que no
void consultaPorcentajeParticipacion() {
    if (primeroP == NULL) { cout << " No hay participantes registrados.\n"; return; }
    int totalParticipantes = 0; int conEventos = 0; participantes* p = primeroP;

    while (p != NULL) {

        totalParticipantes++;
        if (p->listaEventos != NULL) { conEventos++; }
        p = p->sig;
    }

    int sinEventos = totalParticipantes - conEventos;
    float porcCon = (totalParticipantes > 0) ? (conEventos * 100.0f) / totalParticipantes : 0.0f;
    float porcSin = (totalParticipantes > 0) ? (sinEventos * 100.0f) / totalParticipantes : 0.0f;

    mostrarParticipantes();
    cout << " Participacion estudiantil:\n";
    cout << "   - Con al menos 1 evento: " << conEventos << " (" << porcCon << "%)\n";
    cout << "   - Sin eventos: " << sinEventos << " (" << porcSin << "%)\n";
}

// ===================================================================
// ===================== IMPLEMENTACIÓN REPORTES =====================
// ===================================================================

// ------------------- Auxiliares para Reportes -------------------
/*
  obtenerApellido:
    - Devuelve la subcadena posterior al último espacio (heurística de apellido).
*/
string obtenerApellido(string nombreCompleto) {
    int lastSpaceIndex = -1;
    for (int i = 0; i < (int)nombreCompleto.length(); i++) {
        if (nombreCompleto[i] == ' ') { lastSpaceIndex = i; }
    }
    if (lastSpaceIndex != -1) { return nombreCompleto.substr(lastSpaceIndex + 1); }
    return nombreCompleto;
}

/*
  swapData / swapDataEventos:
    - Intercambian los campos de dos nodos (sin mover punteros de la lista).
    - Se usan para ordenamientos "in-place" por intercambio de datos.
*/
void swapData(participantes* a, participantes* b) {
    int tempID = a->ID; string tempNombre = a->nombre; string tempCarrera = a->carrera;
    enlaceEventoParticipante* tempLista = a->listaEventos;
    a->ID = b->ID; a->nombre = b->nombre; a->carrera = b->carrera; a->listaEventos = b->listaEventos;
    b->ID = tempID; b->nombre = tempNombre; b->carrera = tempCarrera; b->listaEventos = tempLista;
}
void swapDataEventos(eventos* a, eventos* b) {
    int tempID = a->ID; string tempNombre = a->nombre; string tempFecha = a->fecha;
    string tempLugar = a->lugar; string tempTipo = a->tipo;
    categorias* tempCategoria = a->categoria; enlaceRecurso* tempRecursos = a->listaRecursos;
    enlaceParticipante* tempParticipantes = a->listaParticipantes;

    a->ID = b->ID; a->nombre = b->nombre; a->fecha = b->fecha; a->lugar = b->lugar; a->tipo = b->tipo;
    a->categoria = b->categoria; a->listaRecursos = b->listaRecursos; a->listaParticipantes = b->listaParticipantes;

    b->ID = tempID; b->nombre = tempNombre; b->fecha = tempFecha; b->lugar = tempLugar; b->tipo = tempTipo;
    b->categoria = tempCategoria; b->listaRecursos = tempRecursos; b->listaParticipantes = tempParticipantes;
}

// 1) Participantes ordenados por apellido A/D
void reporteParticipantesPorApellido(bool ascendente) {
    if (primeroP == NULL) {
        cout << "1. Reporte Participantes: Lista vacia.\n";
        return;
    }

    // --- ordenamiento por apellido (burbuja sobre lista doble con swapData) ---
    bool intercambio;
    participantes *actual, *siguiente;
    do {
        intercambio = false;
        actual = primeroP;
        while (actual->sig != NULL) {
            siguiente = actual->sig;
            string apActual    = obtenerApellido(actual->nombre);
            string apSiguiente = obtenerApellido(siguiente->nombre);
            bool condicion = ascendente ? (apActual > apSiguiente)
                                        : (apActual < apSiguiente);
            if (condicion) {
                swapData(actual, siguiente);
                intercambio = true;
            }
            actual = actual->sig;
        }
    } while (intercambio);

    // --- impresión DETALLADA con lista de eventos del participante ---
    cout << "\n--- REPORTE 1: PARTICIPANTES ORDENADOS POR APELLIDO ---\n";
    participantes* aux = primeroP;
    while (aux != NULL) {
        cout << "ID: " << aux->ID
             << " | Nombre: " << aux->nombre
             << " | Carrera: " << aux->carrera << "\n   Eventos: ";

        int k = 0;
        for (enlaceEventoParticipante* le = aux->listaEventos; le; le = le->sig) {
            if (k++) cout << ", ";
            cout << (le->refEvento ? le->refEvento->nombre : "(evento?)");
        }
        if (k == 0) cout << "(sin eventos)";
        cout << "\n";

        aux = aux->sig;
    }
    cout << "---------------------------------------------------------\n";
}


// 2) Eventos organizados por una persona X (Organizador)
// 2) Eventos organizados por una persona X (DETALLADO)
void reporteEventosPorOrganizador(int idOrganizador){
    Organizadores* o = buscarOrganizador(idOrganizador);
    if(!o){
        cout << "2. Reporte: Organizador ID " << idOrganizador << " no encontrado.\n";
        return;
    }

    cout << "\n--- REPORTE 2: EVENTOS A CARGO DE "
         << o->nombre << " (" << o->departamento << ") ---\n";

    if(!o->listaEventos){
        cout << "   No tiene eventos a cargo.\n";
        cout << "-----------------------------------------------------------------\n";
        return;
    }

    int idx = 0;
    for(enlaceEvento* le = o->listaEventos; le; le = le->sig){
        eventos* ev = le->refEvento;
        idx++;

        cout << idx << ") ID: " << ev->ID << " | " << ev->nombre << "\n";
        cout << "   Fecha: " << ev->fecha
             << " | Lugar: " << ev->lugar
             << " | Tipo: "  << ev->tipo << "\n";

        cout << "   Categoria: "
             << (ev->categoria ? ev->categoria->nombre : "(sin categoria)") << "\n";

        // Co-organizadores del evento (si hay varios)
        cout << "   Organizadores: " << organizadoresDelEvento(ev) << "\n";

        // Recursos
        cout << "   Recursos: ";
        if(!ev->listaRecursos){
            cout << "(ninguno)\n";
        }else{
            bool first = true;
            for(enlaceRecurso* lr = ev->listaRecursos; lr; lr = lr->sig){
                if(!first) cout << ", ";
                cout << lr->refRecurso->nombre;
                first = false;
            }
            cout << "\n";
        }

        // Participantes (lista + conteo)
        int cnt = 0;
        cout << "   Participantes: ";
        if(!ev->listaParticipantes){
            cout << "(ninguno)\n";
        }else{
            bool first = true;
            for(enlaceParticipante* lp = ev->listaParticipantes; lp; lp = lp->sig){
                if(!first) cout << ", ";
                cout << lp->refParticipante->nombre;
                first = false;
                cnt++;
            }
            cout << "  [" << cnt << " inscritos]\n";
        }
    }
    cout << "-----------------------------------------------------------------\n";
}


// 3) Eventos de una categoria X
// 3) Eventos de una categoria X (AHORA MUESTRA ORGANIZADOR/ES)
void reporteEventosPorCategoria(int idCategoria) {
    categorias* cat = buscarCategoria(idCategoria);
    if (cat == NULL) {
        cout << "3. Reporte Eventos: Categoria ID " << idCategoria << " no encontrada.\n";
        return;
    }

    cout << "\n--- REPORTE 3: EVENTOS DE LA CATEGORIA: " << cat->nombre << " ---\n";
    enlaceCategoriaEvento* aux = cat->listaEventos;
    if (aux == NULL) {
        cout << "   No hay eventos asociados.\n";
        return;
    }

    while (aux != NULL) {
        eventos* ev = aux->refEvento;
        cout << "ID: " << ev->ID
             << " | Nombre: " << ev->nombre
             << " | Fecha: " << ev->fecha
             << " | Tipo: "  << ev->tipo
             << " | Lugar: " << ev->lugar << "\n";

        // NUEVA línea solicitada por la rúbrica: organizador(es)
        cout << "   Organizadores: " << organizadoresDelEvento(ev) << "\n";

        aux = aux->sig;
    }
    cout << "--------------------------------------------------------\n";
}


// 4) Recursos asignados a un evento X
void reporteRecursosPorEvento(int idEvento) {
    eventos* ev = buscarEvento(idEvento);
    if (ev == NULL) { cout << "4. Reporte Recursos: Evento ID " << idEvento << " no encontrado.\n"; return; }
    cout << "\n--- REPORTE 4: RECURSOS ASIGNADOS AL EVENTO: " << ev->nombre << " ---\n";
    enlaceRecurso* aux = ev->listaRecursos;
    if (aux == NULL) { cout << "   No hay recursos asignados.\n"; }
    else {
        while (aux != NULL) {
            cout << " - Nombre: " << aux->refRecurso->nombre << " | Descripcion: " << aux->refRecurso->descripcion << endl;
            aux = aux->sig;
        }
    }
    cout << "---------------------------------------------------------------------\n";
}

// 5) Eventos realizados en un LUGAR X
void reporteEventosPorLugar(string lugarX){
    cout << "\n--- REPORTE 5: EVENTOS EN EL LUGAR: " << lugarX << " ---\n";
    eventos* e = primeroE; bool alguno=false;
    while(e){
        if(e->lugar == lugarX){
            cout << "ID: "<<e->ID<<" | "<<e->nombre<<" | Fecha: "<<e->fecha<<" | Tipo: "<<e->tipo<<"\n";
            alguno=true;
        }
        e=e->sig;
    }
    if(!alguno) cout<<"   No hay eventos en ese lugar.\n";
    cout << "----------------------------------------------------------\n";
}

// 6) Eventos de tipo TALLER por DEPARTAMENTO X
void reporteTalleresPorDepartamento(string deptoX){
    cout << "\n--- REPORTE 6: TALLERES ORGANIZADOS POR DEPARTAMENTO: " << deptoX << " ---\n";
    Organizadores* o = primeroOr; bool alguno=false;
    while(o){
        if(o->departamento == deptoX){
            enlaceEvento* le = o->listaEventos;
            while(le){
                if(le->refEvento->tipo == "Taller"){
                    eventos* ev = le->refEvento;
                    cout << "Evento: "<<ev->nombre<<" | Fecha: "<<ev->fecha<<" | Organizador: "<<o->nombre<<" | Lugar: "<<ev->lugar<<"\n";
                    alguno=true;
                }
                le=le->sig;
            }
        }
        o=o->sig;
    }
    if(!alguno) cout<<"   No se encontraron talleres para ese departamento.\n";
    cout << "----------------------------------------------------------------\n";
}

// 7) Historial COMPLETO (circular)
void reporteHistorialCompleto(){
    cout << "\n--- REPORTE 7: HISTORIAL COMPLETO DE INSCRIPCIONES (por fecha) ---\n";
    if(!primeroHistorial){ cout<<"   Historial vacio.\n"; return; }
    historial_eventos* h = primeroHistorial;
    do{
        cout << "ID: "<<h->ID<<" | Fecha: "<<h->fecha<<" | Estudiante: "<<h->refParticipante->nombre<<" | Evento: "<<h->refEvento->nombre<<"\n";
        h = h->sig;
    } while(h != primeroHistorial);
    cout << "-------------------------------------------------------------------\n";
}

// 8) Organizadores sin eventos
void reporteOrganizadoresSinEventos(){
    cout << "\n--- REPORTE 8: ORGANIZADORES SIN EVENTOS ---\n";
    bool alguno=false;
    Organizadores* o = primeroOr;
    while(o){
        if(o->listaEventos == NULL){
            cout << "Nombre: "<<o->nombre<<" | Departamento: "<<o->departamento<<"\n";
            alguno=true;
        }
        o=o->sig;
    }
    if(!alguno) cout<<"   Todos los organizadores tienen eventos.\n";
    cout << "-------------------------------------------\n";
}

// --------- Reportes extra útiles (se mantienen como utilitarios) ---------
void reporteEventosPorFecha(string fechaBuscada) {
    eventos* aux = primeroE; bool encontrado = false;
    cout << "\n--- REPORTE: EVENTOS EN LA FECHA " << fechaBuscada << " ---\n";
    while (aux != NULL) {
        if (aux->fecha == fechaBuscada) {
            cout << "ID: " << aux->ID << " | Nombre: " << aux->nombre << " | Lugar: " << aux->lugar << endl;
            encontrado = true;
        }
        aux = aux->sig;
    }
    if (!encontrado) { cout << "   No se encontraron eventos.\n"; }
    cout << "--------------------------------------------------------\n";
}
void reporteParticipantesMultiInscripcion() {
    participantes* p = primeroP; bool encontrado = false;
    cout << "\n--- REPORTE: PARTICIPANTES CON MAS DE UNA INSCRIPCION ---\n";
    while (p != NULL) {
        int contador = 0; enlaceEventoParticipante* aux = p->listaEventos;
        while (aux != NULL) { contador++; aux = aux->sig; }
        if (contador > 1) {
            cout << "ID: " << p->ID << " | Nombre: " << p->nombre << " | Inscripciones: " << contador << endl;
            encontrado = true;
        }
        p = p->sig;
    }
    if (!encontrado) { cout << "   Ningun participante tiene mas de una inscripcion.\n"; }
    cout << "------------------------------------------------------------------\n";
}
void reporteOrganizadoresPorDepartamento(string deptoBuscado) {
    Organizadores* aux = primeroOr; bool encontrado = false;
    cout << "\n--- REPORTE: ORGANIZADORES DEL DEPARTAMENTO: " << deptoBuscado << " ---\n";
    while (aux != NULL) {
        if (aux->departamento == deptoBuscado) {
            cout << "ID: " << aux->ID << " | Nombre: " << aux->nombre << endl;
            encontrado = true;
        }
        aux = aux->sig;
    }
    if (!encontrado) { cout << "   No se encontraron organizadores en " << deptoBuscado << ".\n"; }
    cout << "----------------------------------------------------------------------\n";
}
void reporteHistorialPorParticipante(int idParticipante) {
    participantes* p = buscarParticipante(idParticipante);
    if (primeroHistorial == NULL) { cout << "Reporte Historial: Historial vacio.\n"; return; }
    if (p == NULL) { cout << "Reporte Historial: Participante ID " << idParticipante << " no encontrado.\n"; return; }
    cout << "\n--- REPORTE: HISTORIAL DE INSCRIPCIONES DE: " << p->nombre << " ---\n";
    historial_eventos* aux = primeroHistorial; bool encontrado = false;
    do {
        if (aux->refParticipante == p) {
            cout << "ID Historial: " << aux->ID << " | Fecha: " << aux->fecha << " | Evento: " << aux->refEvento->nombre << endl;
            encontrado = true;
        }
        aux = aux->sig;
    } while (aux != primeroHistorial);
    if (!encontrado) { cout << "   No se encontraron inscripciones para este participante.\n"; }
    cout << "------------------------------------------------------------------------------\n";
}
void reporteEventosPorLugarFecha() {
    if (primeroE == NULL) { cout << "Reporte: Lista de Eventos vacia.\n"; return; }
    bool intercambio; eventos *actual, *siguiente;
    do {
        intercambio = false; actual = primeroE;
        while (actual->sig != NULL) {
            siguiente = actual->sig;
            bool condicion = false;
            if (actual->lugar > siguiente->lugar) { condicion = true; }
            else if (actual->lugar == siguiente->lugar && actual->fecha > siguiente->fecha) { condicion = true; }
            if (condicion) { swapDataEventos(actual, siguiente); intercambio = true; }
            actual = actual->sig;
        }
    } while (intercambio);

    cout << "\n--- REPORTE: EVENTOS ORDENADOS POR LUGAR Y FECHA ---\n";
    eventos* aux = primeroE;
    while (aux != NULL) {
        cout << "Lugar: " << aux->lugar << " | Fecha: " << aux->fecha << " | Nombre: " << aux->nombre << endl;
        aux = aux->sig;
    }
    cout << "--------------------------------------------------------\n";
}

// ===================================================================
// ==================== IMPLEMENTACIÓN CARGA INICIAL =================
// ===================================================================

/*
  cargarDatosIniciales:
    - Población de datos de ejemplo (IDs, fechas, nombres y relaciones).
    - Útil para probar menús/reportes/consultas sin necesidad de capturar todo.
*/
void cargarDatosIniciales() {


    // 1. Categorías
    insertarCategoriaFinal(1212, "Cultural", "Exploran lo que la gente hace, aborda campos como el arte,musica,costumbres etc.");
    insertarCategoriaFinal(1414, "Academico", "Area especificada del conocimiento que abarca el conjunto de objetivos y competencias a desarrollar.");
    insertarCategoriaFinal(1313, "Deportivo", "Cursos Academicos relacionados con el deporte y la actividad fisica.");

    // 2. Recursos
    insertarRecurso("Proyector", "Dispositivo que permite emitir imagenes e informacion visual.");
    insertarRecurso("Piscina", "Espacio con agua para practicar deportes acuaticos.");
    insertarRecurso("Gimnasio", "Espacio techado donde se practican actividades fisicas.");
    insertarRecurso("Parlante","Dispositivo que permite emitir sonido");
    // 3. Eventos (ordenados por fecha al insertarse)
    insertarEventoOrdenado(2122, "Noche de Peliculas", "2025-10-05", "AULA-CUL1", "Entretenimiento");
    insertarEventoOrdenado(2190, "Principios en Unity", "2025-10-04", "C-TEC", "Charla");
    insertarEventoOrdenado(2129, "Torneo de Futbol Sala", "2025-10-03", "Gimnasio TEC", "Recreativa");
    insertarEventoOrdenado(2134, "Torneo de Natacion", "2025-10-02", "Piscina TEC", "Recreativa");
    insertarEventoOrdenado(2178, "Aprendiendo Folclore", "2025-10-07", "AULA-CUL2", "Taller");

    // 4. Participantes
    insertarParticipante(204560789, "Francisco Castillo", "Ingenieria en Computacion");
    insertarParticipante(207760654, "Dylan Mendez", "Agronomia");
    insertarParticipante(208770567, "Danny Gonzalez", "Ingenieria en Computacion");

    // 5. Organizadores
    insertarOrganizador(207380123, "Javier Perez", "Culturales");
    insertarOrganizador(207120993, "Pedro Huertas", "Deportivas");
    insertarOrganizador(23850472, "Lorena Lopez", "Academicas");

    // 6. Asignación de Relaciones
    asignarCategoriaEvento(2122, 1212);
    asignarCategoriaEvento(2129, 1313);
    asignarCategoriaEvento(2134, 1313);
    asignarCategoriaEvento(2178, 1212);
    asignarCategoriaEvento(2190, 1414);


    asignarOrganizadorEvento(207380123, 2122);
    asignarOrganizadorEvento(207380123, 2178);
    asignarOrganizadorEvento(207120993, 2129);
    asignarOrganizadorEvento(207120993, 2134);
    asignarOrganizadorEvento(23850472, 2190);

    inscribirParticipanteEvento(204560789, 2122);
    inscribirParticipanteEvento(204560789, 2190);
    inscribirParticipanteEvento(207760654, 2129);
    inscribirParticipanteEvento(208770567, 2134);
    inscribirParticipanteEvento(208770567, 2178);


    asignarRecursoEvento(2122, "Proyector");
    asignarRecursoEvento(2190, "Proyector");
    asignarRecursoEvento(2129, "Gimnasio");
    asignarRecursoEvento(2134, "Piscina");
    asignarRecursoEvento(2178, "Parlante");
    asignarRecursoEvento(2122, "Gimnasio");

    registrarHistorial(2121, "2025-09-21", 208770567, 2178);
    registrarHistorial(3434, "2025-09-21", 208770567, 2134);
    registrarHistorial(4784, "2025-09-22", 207760654, 2129);
    registrarHistorial(4444, "2025-09-22", 204560789, 2190);
    registrarHistorial(5432, "2025-09-23", 204560789, 2122);

}

// ===================================================================
// ==================== MENÚ Y FUNCIONES DE IMPRESIÓN ================
// ===================================================================

/*
  imprimirTodasLasConsultas:
    - Ejecuta e imprime los 9 indicadores/consultas principales.
*/
void imprimirTodasLasConsultas() {
    cout << "\n=============================================\n";
    cout << "         RESULTADOS DE LAS 9 CONSULTAS         \n";
    cout << "=============================================\n";

    consultaParticipanteMasEventos();
    consultaOrganizadorMasEventos();
    consultaTipoEventoFrecuente();
    consultaCategoriaMayorParticipacion();
    consultaRecursoMasUtilizado();
    consultaLugarMasEventos();
    consultaEventoMasParticipantes();
    consultaOrganizadorMasCategorias();
    consultaPorcentajeParticipacion();

    cout << "---------------------------------------------\n";
}

/*
  imprimirTodosLosReportes:
    - Ejecuta e imprime los 8 reportes de la rúbrica (con IDs/lugares fijos).
    - Útil como demostración, pero en el menú real se piden datos al usuario.
*/
void imprimirTodosLosReportes() {
    cout << "\n=============================================\n";
    cout << "         IMPRESION DE LOS 8 REPORTES         \n";
    cout << "=============================================\n";

    // 1) Participantes ordenados por apellido (ASC)
    reporteParticipantesPorApellido(true);

    // 2) Eventos por organizador X (usa 301)
    reporteEventosPorOrganizador(301);

    // 3) Eventos por categoria X (101 Academico)
    reporteEventosPorCategoria(101);

    // 4) Recursos de un evento X (1)
    reporteRecursosPorEvento(1);

    // 5) Eventos en un lugar X
    reporteEventosPorLugar("Auditorio A");

    // 6) Talleres por departamento X
    reporteTalleresPorDepartamento("Departamento de TI");

    // 7) Historial completo (circular)
    reporteHistorialCompleto();

    // 8) Organizadores sin eventos
    reporteOrganizadoresSinEventos();

    cout << "---------------------------------------------\n";
}


// ===================================================
// =============== INPUTS Y MOSTRAR ==================
// ===================================================

/*
  leerEntero:
    - Solicita entero seguro (maneja fallos de extracción de cin).
*/
int leerEntero(const string& msg){
    cout << msg;
    int x;
    while(!(cin >> x)){
        cout << "Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(10000,'\n');
    }
    cin.ignore(10000,'\n'); // limpiar \n restante
    return x;
}

/*
  leerLinea:
    - Captura línea completa (incluye espacios).
*/
string leerLinea(const string& msg){
    cout << msg;
    string s;
    getline(cin, s);
    return s;
}

/*
  organizadoresDelEvento:
    - Construye un string con los nombres de los organizadores para un evento
      buscando en la lista de organizadores y sus sublistas de enlaces.
*/
string organizadoresDelEvento(eventos* e){
    if(!e) return "(error)";
    string res;
    bool first = true;

    Organizadores* o = primeroOr;
    while(o){
        for(enlaceEvento* le = o->listaEventos; le; le = le->sig){
            if(le->refEvento == e){
                if(!first) res += ", ";
                res += o->nombre;
                first = false;
                break; // ya encontramos este organizador para este evento
            }
        }
        o = o->sig;
    }
    if(first) return "(ninguno)";
    return res;
}


// Mostrar simples (usando las listas ya existentes)
/*
  mostrarEventos:
    - Imprime todos los eventos con sus relaciones (recursos, organizadores, participantes).
*/
void mostrarEventos(){
    cout << "\n--- EVENTOS (lista por fecha asc) ---\n";
    if(!primeroE){
        cout << "   (vacio)\n";
        return;
    }

    eventos* e = primeroE;
    while(e){
        cout << "ID:" << e->ID
             << " | " << e->nombre
             << " | Fecha:" << e->fecha
             << " | Lugar:" << e->lugar
             << " | Tipo:" << e->tipo;

        if(e->categoria)
            cout << " | Cat:" << e->categoria->nombre;

        // --- Recursos asignados a este evento ---
        cout << "\n   Recursos: ";
        if(!e->listaRecursos){
            cout << "(ninguno)";
        } else {
            enlaceRecurso* lr = e->listaRecursos;
            bool primero = true;
            while(lr){
                if(!primero) cout << ", ";
                cout << lr->refRecurso->nombre;
                primero = false;
                lr = lr->sig;
            }
        }
        cout << "\n   Organizadores: " << organizadoresDelEvento(e);

        // --- (Opcional) Participantes inscritos en este evento ---
        cout << "\n   Participantes: ";
        if(!e->listaParticipantes){
            cout << "no hay participantes en este evento";
        } else {
            enlaceParticipante* lp = e->listaParticipantes;
            bool primero = true;
            while(lp){
                if(!primero) cout << ", ";
                cout << lp->refParticipante->nombre;
                primero = false;
                lp = lp->sig;
            }
        }

        cout << "\n";
        e = e->sig;
    }
}

/*
  mostrarRecursos/Categorias/Organizadores/Participantes/Historial:
    - Vistas compactas de cada lista para facilitar selección en menús.
*/
void mostrarRecursos(){
    cout << "\n--- RECURSOS (lista doble) ---\n";
    if(!primeroR){ cout << "   (vacio)\n"; return; }
    Recursos* r = primeroR;
    while(r){
        cout << "- " << r->nombre << " | " << r->descripcion << "\n";
        r = r->sig;
    }
}

void mostrarHistorial(){
    cout << "\n--- HISTORIAL (circular por fecha) ---\n";
    if(!primeroHistorial){ cout << "   (vacio)\n"; return; }
    historial_eventos* h = primeroHistorial;
    do{
        cout << "ID:" << h->ID << " | Fecha:" << h->fecha;
        if(h->refParticipante) cout << " | Est:" << h->refParticipante->nombre;
        if(h->refEvento) cout << " | Ev:" << h->refEvento->nombre;
        cout << "\n";
        h = h->sig;
    }while(h != primeroHistorial);
}

void mostrarCategorias(){
    cout << "\n--- CATEGORIAS DISPONIBLES ---\n";
    if(!primeroC){
        cout << "   (vacio)\n";
        return;
    }
    categorias* c = primeroC;
    while(c){
        cout << "ID:" << c->ID << " | " << c->nombre << " | " << c->descripcion << "\n";
        c = c->sig;
    }
}

/*
  yaInscritoEvento / yaAsignadoRecursoEvento:
    - Chequeos de existencia en sublistas (evitan duplicados).
*/
bool yaInscritoEvento(participantes* p, eventos* e){
    if(!p || !e) return false;
    for(enlaceEventoParticipante* aux = p->listaEventos; aux; aux = aux->sig)
        if(aux->refEvento == e) return true;
    return false;
}

bool yaAsignadoRecursoEvento(int eventoID, const string& recursoNombre){
    eventos* e = buscarEvento(eventoID);
    Recursos* r = buscarRecurso(recursoNombre);
    if(!e || !r) return false;
    for(enlaceRecurso* lr = e->listaRecursos; lr; lr = lr->sig)
        if(lr->refRecurso == r) return true;
    return false;
}

/*
  agregarParticipanteEventoSiNoExiste / agregarRecursoEventoSiNoExiste:
    - Validan existencia y duplicados antes de crear el enlace.
*/
bool agregarParticipanteEventoSiNoExiste(int eventoID, int partID){
    eventos* e = buscarEvento(eventoID);
    participantes* p = buscarParticipante(partID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(!p){ cout<<" Participante no encontrado.\n"; return false; }
    if(yaInscrito(p, e)){ cout<<" Ese participante ya esta inscrito en el evento.\n"; return false; }

    inscribirParticipanteEvento(partID, eventoID);
    cout<<" Participante agregado al evento.\n";
    return true;
}

bool agregarRecursoEventoSiNoExiste(int eventoID, const string& recursoNombre){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(!existeRecursoNombre(recursoNombre)){ cout<<" Recurso no encontrado.\n"; return false; }
    if(yaAsignadoRecurso(eventoID, recursoNombre)){
        cout<<" Ese recurso ya estaba asignado al evento.\n";
        return false;
    }

    asignarRecursoEvento(eventoID, recursoNombre);
    cout<<" Recurso agregado al evento.\n";
    return true;
}


/*
  menuReemplazosEvento:
    - Interfaz para reemplazar campos básicos y relaciones de un evento.
    - Usa las funciones de reemplazo que delegan en modificar/borrar/asignar.
*/
void menuReemplazosEvento(){
    mostrarEventos();
    int eid = leerEntero("ID del evento a modificar (reemplazos/agregados): ");
    eventos* e = buscarEvento(eid);
    if(!e){ cout<<" Evento no encontrado.\n"; return; }

    int op;
    do{
        cout << "\n=== MODIFICACIONES DE EVENTOS ===\n";
        cout << "ID:" << e->ID
             << " | Nombre:" << e->nombre
             << " | Fecha:" << e->fecha
             << " | Lugar:" << e->lugar
             << " | Tipo:" << e->tipo
             << " | Categoria:" << (e->categoria? e->categoria->nombre : "(sin)") << "\n";

        cout << " -----REEMPLAZOS------\n";
        cout << "1) Reemplazar NOMBRE (solo escribir el nuevo)\n";
        cout << "2) Reemplazar FECHA (solo escribir la nueva)\n";
        cout << "3) Reemplazar LUGAR (solo escribir el nuevo)\n";
        cout << "4) Reemplazar TIPO (solo escribir el nuevo)\n";
        cout << "5) Reemplazar CATEGORIA (mostrar actual -> elegir nueva)\n";
        cout << "6) Reemplazar ORGANIZADOR (elegir asignado -> elegir no asignado)\n";
        cout << "7) Reemplazar PARTICIPANTE (inscrito -> no inscrito)\n";
        cout << "8) Reemplazar RECURSO (asignado -> no asignado)\n";
        cout << "\n";
        cout << "------AGREGACIONES Y ELIMINACIONES-----\n";
        cout << "9) Agregar ORGANIZADOR (solo no asignados)\n";
        cout << "10) Eliminar ORGANIZADOR (solo asignados)\n";
        cout << "11) Agregar PARTICIPANTE (solo no inscritos)\n";
        cout << "12) Eliminar PARTICIPANTE (solo inscritos)\n";
        cout << "13) Agregar RECURSO (solo no asignados)\n";
        cout << "14) Eliminar RECURSO (solo asignados)\n";
        cout << "0) Volver\n> ";

        if(!(cin>>op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        if(op==1){
            cout << "Nombre ACTUAL: " << e->nombre << "\n";
            string neu = leerLinea("Nombre NUEVO: ");
            reemplazarNombreEvento(eid, e->nombre, neu);
            e = buscarEvento(eid); // refrescar datos en pantalla

        }else if(op==2){
            cout << "Fecha ACTUAL: " << e->fecha << "\n";
            string neu = leerLinea("Fecha NUEVA (YYYY-MM-DD): ");
            reemplazarFechaEvento(eid, e->fecha, neu);
            e = buscarEvento(eid);

        }else if(op==3){
            cout << "Lugar ACTUAL: " << e->lugar << "\n";
            string neu = leerLinea("Lugar NUEVO: ");
            reemplazarLugarEvento(eid, e->lugar, neu);
            e = buscarEvento(eid);

        }else if(op==4){
            cout << "Tipo ACTUAL: " << e->tipo << "\n";
            string neu = leerLinea("Tipo NUEVO: ");
            reemplazarTipoEvento(eid, e->tipo, neu);
            e = buscarEvento(eid);

        }else if(op==5){
            int cAct = e->categoria ? e->categoria->ID : -1;
            cout << "Categoria ACTUAL: "
                 << (e->categoria? e->categoria->nombre : "(sin)")
                 << " (ID " << cAct << ")\n";
            mostrarCategorias();

            int cNew = leerEntero("ID categoria NUEVA: ");
            reemplazarCategoriaEvento(eid, cAct, cNew);
            e = buscarEvento(eid);

        }else if(op==6){
            // Reemplazar ORGANIZADOR
            cout << "\nOrganizadores ASIGNADOS:\n";
            bool hayAsig=false;
            Organizadores* o=primeroOr;
            while(o){
                for(enlaceEvento* le=o->listaEventos; le; le=le->sig){
                    if(le->refEvento==e){ cout<<"  ID:"<<o->ID<<" | "<<o->nombre<<"\n"; hayAsig=true; break; }
                }
                o=o->sig;
            }
            if(!hayAsig){ cout<<"  (ninguno)\n"; }

            cout << "\nOrganizadores NO ASIGNADOS:\n";
            bool hayNoAsig=false;
            o=primeroOr;
            while(o){
                bool asignado=false;
                for(enlaceEvento* le=o->listaEventos; le; le=le->sig){
                    if(le->refEvento==e){ asignado=true; break; }
                }
                if(!asignado){ cout<<"  ID:"<<o->ID<<" | "<<o->nombre<<"\n"; hayNoAsig=true; }
                o=o->sig;
            }
            if(!hayNoAsig){ cout<<"  (ninguno)\n";

            }

            int oAct = leerEntero("ID ORGANIZADOR ACTUAL (de la lista de asignados): ");
            int oNew = leerEntero("ID ORGANIZADOR NUEVO (de la lista de no asignados): ");
            reemplazarOrganizadorEvento(eid, oAct, oNew);

        }else if(op==7){
            // Reemplazar PARTICIPANTE
            cout << "\nParticipantes INSCRITOS:\n";
            bool hayIn=false;
            for(enlaceParticipante* lp=e->listaParticipantes; lp; lp=lp->sig){
                cout<<"  ID:"<<lp->refParticipante->ID<<" | "<<lp->refParticipante->nombre<<"\n"; hayIn=true;
            }
            if(!hayIn) cout<<"  (ninguno)\n";

            cout << "\nParticipantes NO INSCRITOS:\n";
            bool hayOut=false;
            for(participantes* p=primeroP; p; p=p->sig){
                bool ins=false;
                for(enlaceParticipante* lp=e->listaParticipantes; lp; lp=lp->sig){
                    if(lp->refParticipante==p){ ins=true; break; }
                }
                if(!ins){ cout<<"  ID:"<<p->ID<<" | "<<p->nombre<<"\n"; hayOut=true; }
            }
            if(!hayOut) cout<<"  (ninguno)\n";

            int pAct = leerEntero("ID PARTICIPANTE ACTUAL (inscrito): ");
            int pNew = leerEntero("ID PARTICIPANTE NUEVO (no inscrito): ");
            reemplazarParticipanteEvento(eid, pAct, pNew);

        }else if(op==8){
            // Reemplazar RECURSO
            cout << "\nRecursos ASIGNADOS:\n";
            bool hayRA=false;
            for(enlaceRecurso* lr=e->listaRecursos; lr; lr=lr->sig){
                cout<<"  - "<<lr->refRecurso->nombre<<"\n"; hayRA=true;
            }
            if(!hayRA) cout<<"  (ninguno)\n";

            cout << "\nRecursos NO ASIGNADOS:\n";
            bool hayRNA=false;
            for(Recursos* r=primeroR; r; r=r->sig){
                bool asig=false;
                for(enlaceRecurso* lr=e->listaRecursos; lr; lr=lr->sig){
                    if(lr->refRecurso==r){ asig=true; break; }
                }
                if(!asig){ cout<<"  - "<<r->nombre<<"\n"; hayRNA=true; }
            }
            if(!hayRNA) cout<<"  (ninguno)\n";

            string rAct = leerLinea("Nombre EXACTO del RECURSO ACTUAL (asignado): ");
            string rNew = leerLinea("Nombre EXACTO del RECURSO NUEVO (no asignado): ");
            reemplazarRecursoEvento(eid, rAct, rNew);

        }else if(op==9){
            // Agregar ORGANIZADOR
            cout << "\nOrganizadores NO ASIGNADOS:\n";
            bool hay=false;
            for(Organizadores* o=primeroOr; o; o=o->sig){
                if(!yaAsignadoOrganizador(o->ID,eid)){
                    cout<<"  ID:"<<o->ID<<" | "<<o->nombre<<"\n"; hay=true;
                }
            }
            if(!hay) cout<<"  (ninguno)\n";
            int oid = leerEntero("ID a AGREGAR: ");
            agregarOrganizadorEventoSiNoExiste(eid, oid);

        }else if(op==10){
            // Eliminar ORGANIZADOR
            cout << "\nOrganizadores ASIGNADOS:\n";
            bool hay=false;
            for(Organizadores* o=primeroOr; o; o=o->sig){
                if(yaAsignadoOrganizador(o->ID,eid)){
                    cout<<"  ID:"<<o->ID<<" | "<<o->nombre<<"\n"; hay=true;
                }
            }
            if(!hay) cout<<"  (ninguno)\n";
            int oid = leerEntero("ID a ELIMINAR: ");
            desasignarOrganizadorEvento(oid, eid);

        }else if(op==11){
            // Agregar PARTICIPANTE
            cout << "\nParticipantes NO INSCRITOS:\n";
            bool hay=false;
            for(participantes* p=primeroP; p; p=p->sig){
                if(!yaInscrito(p,e)){ cout<<"  ID:"<<p->ID<<" | "<<p->nombre<<"\n"; hay=true; }
            }
            if(!hay) cout<<"  (ninguno)\n";
            int pid = leerEntero("ID a AGREGAR: ");
            agregarParticipanteEventoSiNoExiste(eid, pid);

        }else if(op==12){
            // Eliminar PARTICIPANTE
            cout << "\nParticipantes INSCRITOS:\n";
            bool hay=false;
            for(enlaceParticipante* lp=e->listaParticipantes; lp; lp=lp->sig){
                cout<<"  ID:"<<lp->refParticipante->ID<<" | "<<lp->refParticipante->nombre<<"\n"; hay=true;
            }
            if(!hay) cout<<"  (ninguno)\n";
            int pid = leerEntero("ID a ELIMINAR: ");
            desinscribirParticipanteEvento(pid, eid);

        }else if(op==13){
            // Agregar RECURSO
            cout << "\nRecursos NO ASIGNADOS:\n";
            bool hay=false;
            for(Recursos* r=primeroR; r; r=r->sig){
                if(!yaAsignadoRecurso(eid, r->nombre)){ cout<<"  - "<<r->nombre<<"\n"; hay=true; }
            }
            if(!hay) cout<<"  (ninguno)\n";
            string rn = leerLinea("Nombre EXACTO del recurso a AGREGAR: ");
            agregarRecursoEventoSiNoExiste(eid, rn);

        }else if(op==14){
            // Eliminar RECURSO
            cout << "\nRecursos ASIGNADOS:\n";
            bool hay=false;
            for(enlaceRecurso* lr=e->listaRecursos; lr; lr=lr->sig){
                cout<<"  - "<<lr->refRecurso->nombre<<"\n"; hay=true;
            }
            if(!hay) cout<<"  (ninguno)\n";
            string rn = leerLinea("Nombre EXACTO del recurso a ELIMINAR: ");
            desasignarRecursoEvento(eid, rn);
        }

    }while(op!=0);
}



// ===================================================
// ================= SUBMENÚS CRUD ====================
// ===================================================

/*
  CRUD por entidad:
    - Menús interactivos para Insertar/Modificar/Eliminar/Mostrar.
    - Las opciones delegan en funciones ya documentadas.
*/
void crudEventos(){
    int op;
    do{
        cout << "\n[CRUD Eventos]\n"
             << "1) Insertar\n2) Modificar\n3) Eliminar\n4) Mostrar\n0) Volver\n> ";
        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        if(op==1){
            insertarEventoInteractivo();

        }else if(op==2){
            menuReemplazosEvento();
        }else if(op==3){
            mostrarEventos();
            int id = leerEntero("ID del evento a eliminar: ");
            eliminarEvento(id);
        }else if(op==4){
            mostrarEventos();
        }
    }while(op!=0);
}

void mostrarOrganizadores(){
    cout << "\n--- ORGANIZADORES DISPONIBLES ---\n";
    if(!primeroOr){ cout << "   (vacio)\n"; return; }

    for(Organizadores* o = primeroOr; o; o = o->sig){
        cout << "ID:" << o->ID << " | " << o->nombre << " | " << o->departamento << "\n";
        cout << "   Eventos a cargo: ";
        if(!o->listaEventos){
            cout << "(ninguno)\n";
        }else{
            int k = 0;
            for(enlaceEvento* le = o->listaEventos; le; le = le->sig){
                if(le->refEvento){
                    if(k++) cout << ", ";
                    cout << le->refEvento->nombre << " [" << le->refEvento->fecha << "]";
                }
            }
            if(k == 0) cout << "(ninguno)";
            cout << "\n";
        }
    }
}

void mostrarParticipantes(){
    cout << "\n--- PARTICIPANTES DISPONIBLES ---\n";
    if(!primeroP){ cout << "   (vacio)\n"; return; }

    for(participantes* p = primeroP; p; p = p->sig){
        cout << "ID:" << p->ID << " | " << p->nombre << " | " << p->carrera << "\n";
        cout << "   Eventos inscritos: ";
        if(!p->listaEventos){
            cout << "(ninguno)\n";
        }else{
            int k = 0;
            for(enlaceEventoParticipante* le = p->listaEventos; le; le = le->sig){
                if(le->refEvento){
                    if(k++) cout << ", ";
                    cout << le->refEvento->nombre << " [" << le->refEvento->fecha << "]";
                }
            }
            if(k == 0) cout << "(ninguno)";
            cout << "\n";
        }
    }
}

/*
  insertarEventoInteractivo:
    - Solicita datos con validación y agrega categorías/organizadores/
      participantes/recursos opcionalmente.
*/
void insertarEventoInteractivo(){
    int id;
    string n, f, l, t;

    // ID: positivo y único
    while(true){
        mostrarEventos();
        id = leerEntero("ID (positivo y unico): ");
        if(id_invalido(id)){ cout<<" ID invalido.\n"; continue; }
        if(existeEventoID(id)){ cout<<" ID de Evento repetido. Ingrese otro.\n"; continue; }
        break;
    }

    // Nombre (no vacío)
    do{
        n = leerLinea("Nombre: ");
        if(str_vacia(n)) cout<<" Nombre vacio.\n";
    }while(str_vacia(n));

    // Fecha (YYYY-MM-DD)
    while(true){
        f = leerLinea("Fecha (YYYY-MM-DD): ");
        if(!esFechaValida(f)){ cout<<" Fecha invalida. Use formato YYYY-MM-DD.\n"; continue; }
        break;
    }

    // Lugar (texto razonable)
    while(true){
        l = leerLinea("Lugar: ");
        if(str_vacia(l) || !esTextoRazonable(l)){ cout<<" Lugar invalido. Debe ser texto.\n"; continue; }
        break;
    }

    // Tipo (texto razonable)
    while(true){
        t = leerLinea("Tipo (Charla/Taller/Entretenimiento/Recreativa/...): ");
        if(str_vacia(t) || !esTextoRazonable(t)){ cout<<" Tipo invalido. Debe ser texto.\n"; continue; }
        break;
    }

    insertarEventoOrdenado(id, n, f, l, t);

    // ====== Categoria (opcional, pero valida que exista) ======
    if(!primeroC){
        cout << " No hay categorias disponibles. Cree una primero.\n";
    } else {
        mostrarCategorias(); // <-- usa el void de categorías
        int idc = leerEntero("ID Categoria (existente): ");
        while(!existeCategoriaID(idc)){
            cout << " Categoria no existe.\n";
            idc = leerEntero("Ingrese un ID de categoria valido: ");
        }
        asignarCategoriaEvento(id, idc);
        cout << " Categoria asignada.\n";
    }

    // Inserción (ordenado por fecha)

    cout << " Evento creado: " << n << " (" << f << ") en " << l << ".\n";

    // ====== (Opcional) Organizadores ======
    string orgYN = leerLinea(" Asociar organizadores ahora? (s/n): ");
    if(!orgYN.empty() && (orgYN[0]=='s' || orgYN[0]=='S')){
        if(!primeroOr){
            cout << " No hay organizadores disponibles. Cree uno primero.\n";
        }else{
            string otro = "s";
            while(!otro.empty() && (otro[0]=='s' || otro[0]=='S')){
                mostrarOrganizadores();
                int oid = leerEntero("ID Organizador (existente): ");
                if(!existeOrganizadorID(oid)){
                    cout << " Organizador no existe.\n";
                }else if(yaAsignadoOrganizador(oid, id)){
                    cout << " Ese organizador ya esta asignado a este evento.\n";
                }else{
                    asignarOrganizadorEvento(oid, id);
                    cout << " Organizador asignado.\n";
                }
                otro = leerLinea("Agregar otro organizador? (s/n): ");
            }
        }
    }

    // ====== (Opcional) Participantes ======
    string partYN = leerLinea("Inscribir participantes ahora? (s/n): ");
    if(!partYN.empty() && (partYN[0]=='s' || partYN[0]=='S')){
        if(!primeroP){
            cout << " No hay participantes disponibles. Cree uno primero.\n";
        }else{
            // Para validar duplicados necesitamos el puntero del evento recién creado
            eventos* evPtr = buscarEvento(id);
            string otro = "s";
            while(!otro.empty() && (otro[0]=='s' || otro[0]=='S')){
                mostrarParticipantes();
                int pid = leerEntero("ID Participante (existente): ");
                participantes* pPtr = buscarParticipante(pid);
                if(!pPtr){
                    cout << " Participante no existe.\n";
                }else if(yaInscrito(pPtr, evPtr)){
                    cout << " Ese participante ya esta inscrito en este evento.\n";
                }else{
                    inscribirParticipanteEvento(pid, id);
                    cout << " Participante inscrito al evento.\n";
                }
                otro = leerLinea("Inscribir otro participante? (s/n): ");
            }
        }
    }


    // ====== (Opcional) Recursos ======
    string recYN = leerLinea("Asignar recursos ahora? (s/n): ");
    if(!recYN.empty() && (recYN[0]=='s' || recYN[0]=='S')){
        if(!primeroR){
            cout << " No hay recursos disponibles. Cree uno primero.\n";
        }else{
            string otro = "s";
            while(!otro.empty() && (otro[0]=='s' || otro[0]=='S')){
                mostrarRecursos();
                string rn = leerLinea("Nombre EXACTO del recurso (existente): ");
                if(!existeRecursoNombre(rn)){
                    cout << " Recurso no existe (revise mayusculas/acentos).\n";
                }else if(yaAsignadoRecurso(id, rn)){
                    cout << " Ese recurso ya esta asignado a este evento.\n";
                }else{
                    asignarRecursoEvento(id, rn);
                    cout << " Recurso asignado al evento.\n";
                }
                otro = leerLinea("Asignar otro recurso? (s/n): ");
            }
        }
    }
}


/*
  CRUD Categorías/Participantes/Organizadores/Recursos/Historial:
    - Similar patrón a crudEventos con capturas y validación básica.
*/
void crudCategorias(){
    int op;
    do{
        cout << "\n[CRUD Categorias]\n"
             << "1) Insertar\n2) Modificar\n3) Eliminar\n4) Mostrar\n0) Volver\n> ";
        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        if(op==1){
            mostrarCategorias();
            int id = leerEntero("ID: ");
            string n = leerLinea("Nombre: ");
            string d = leerLinea("Descripcion: ");
            insertarCategoriaFinal(id,n,d);
        }else if(op==2){
            mostrarCategorias();
            int id = leerEntero("ID a modificar: ");
            string n = leerLinea("Nuevo nombre: ");
            string d = leerLinea("Nueva descripcion: ");
            modificarCategoria(id,n,d);
        }else if(op==3){
            mostrarCategorias();
            int id = leerEntero("ID a eliminar: ");
            eliminarCategoria(id);
        }else if(op==4){
            cout << "\n--- CATEGORIAS ---\n";
            if(!primeroC){ cout << "   (vacio)\n"; }
            categorias* c = primeroC;
            while(c){
                cout << "ID:" << c->ID << " | " << c->nombre << " | " << c->descripcion << "\n";
                c = c->sig;
            }
        }
    }while(op!=0);
}

void crudParticipantes(){
    int op;
    do{
        cout << "\n[CRUD Participantes]\n"
             << "1) Insertar\n2) Modificar\n3) Eliminar\n4) Mostrar\n0) Volver\n> ";
        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        if(op==1){
            mostrarParticipantes();
            int id = leerEntero("ID: ");
            string n = leerLinea("Nombre completo: ");
            string c = leerLinea("Carrera: ");
            insertarParticipante(id,n,c);
        }else if(op==2){
            mostrarParticipantes();
            int id = leerEntero("ID a modificar: ");
            string n = leerLinea("Nuevo nombre: ");
            string c = leerLinea("Nueva carrera: ");
            modificarParticipante(id,n,c);
        }else if(op==3){
            mostrarParticipantes();
            int id = leerEntero("ID a eliminar: ");
            eliminarParticipante(id);
        }else if(op==4){
            mostrarParticipantes();

        }
    }while(op!=0);
}

void crudOrganizadores(){
    int op;
    do{
        cout << "\n[CRUD Organizadores]\n"
             << "1) Insertar\n2) Modificar\n3) Eliminar\n4) Mostrar\n0) Volver\n> ";
        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        if(op==1){
            mostrarOrganizadores();
            int id = leerEntero("ID: ");
            string n = leerLinea("Nombre: ");
            string d = leerLinea("Departamento: ");
            insertarOrganizador(id,n,d);
        }else if(op==2){
            mostrarOrganizadores();
            int id = leerEntero("ID a modificar: ");
            string n = leerLinea("Nuevo nombre: ");
            string d = leerLinea("Nuevo departamento: ");
            modificarOrganizador(id,n,d);
        }else if(op==3){
            mostrarOrganizadores();
            int id = leerEntero("ID a eliminar: ");
            eliminarOrganizador(id);
        }else if(op==4){
            mostrarOrganizadores();

        }
    }while(op!=0);
}

void crudRecursos(){
    int op;
    do{
        cout << "\n[CRUD Recursos]\n"
             << "1) Insertar\n2) Modificar\n3) Eliminar\n4) Mostrar\n0) Volver\n> ";
        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        if(op==1){
            mostrarRecursos();
            string n = leerLinea("Nombre: ");
            string d = leerLinea("Descripcion: ");
            insertarRecurso(n,d);
        }else if(op==2){
            mostrarRecursos();
            string actual = leerLinea("Nombre actual: ");
            string n = leerLinea("Nuevo nombre: ");
            string d = leerLinea("Nueva descripcion: ");
            modificarRecurso(actual,n,d);
        }else if(op==3){
            mostrarRecursos();
            string n = leerLinea("Nombre del recurso a eliminar: ");
            eliminarRecurso(n);
        }else if(op==4){
            mostrarRecursos();
        }
    }while(op!=0);
}

void crudHistorial(){
    int op;
    do{
        cout << "\n[CRUD Historial]\n"
             << "1) Insertar (simple: solo ID de evento)\n"
             << "2) Eliminar por ID\n"
             << "3) Mostrar\n"
             << "0) Volver\n> ";
        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        if(op==1){
            registrarHistorialSoloConEvento();
        }else if(op==2){
            mostrarHistorial();
            int id = leerEntero("ID historial a eliminar: ");
            eliminarHistorial(id);
        }else if(op==3){
            mostrarHistorial();
        }
    }while(op!=0);
}


/*
  menuCRUD:
    - Submenú general para acceder a CRUD por entidad.
*/
void menuCRUD(){
    int op;
    do{
        cout << "\n================ SUBMENU CRUD ================\n"
             << "1) Eventos\n"
             << "2) Categorias\n"
             << "3) Participantes\n"
             << "4) Organizadores\n"
             << "5) Recursos\n"
             << "6) Historial\n"
             << "0) Volver al menu principal\n"
             << "==============================================\n> ";
        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n');

        switch(op){
            case 1: crudEventos(); break;
            case 2: crudCategorias(); break;
            case 3: crudParticipantes(); break;
            case 4: crudOrganizadores(); break;
            case 5: crudRecursos(); break;
            case 6: crudHistorial(); break;
            case 0: break;
            default: cout << "Opcion invalida.\n"; break;
        }
    }while(op!=0);
}

/*
  Chequeos de relación (organizador/participante/recurso) ya asignados.
*/
bool yaAsignadoOrganizador(int orgID, int eventoID){
    Organizadores* o = buscarOrganizador(orgID);
    eventos* e = buscarEvento(eventoID);
    if(!o || !e) return false;
    for(enlaceEvento* le=o->listaEventos; le; le=le->sig)
        if(le->refEvento==e) return true;
    return false;
}

bool yaInscrito(participantes* p, eventos* e){
    if(!p || !e) return false;
    for(enlaceEventoParticipante* aux=p->listaEventos; aux; aux=aux->sig)
        if(aux->refEvento==e) return true;
    return false;
}

bool yaAsignadoRecurso(int eventoID, const string& recursoNombre){
    eventos* e = buscarEvento(eventoID);
    Recursos* r = buscarRecurso(recursoNombre);
    if(!e || !r) return false;
    for(enlaceRecurso* lr=e->listaRecursos; lr; lr=lr->sig)
        if(lr->refRecurso==r) return true;
    return false;
}

/*
  desasignar/desinscribir/desasignarRecurso:
    - Remueven enlaces específicos de las sublistas con mensajes de estado.
*/
void desasignarOrganizadorEvento(int orgID, int eventoID){
    Organizadores* o = buscarOrganizador(orgID);
    eventos* e = buscarEvento(eventoID);
    if(!o || !e){ cout<<" Organizador/Evento no encontrado.\n"; return; }
    enlaceEvento* prev=NULL; enlaceEvento* cur=o->listaEventos;
    while(cur){
        if(cur->refEvento==e){
            if(prev) prev->sig = cur->sig; else o->listaEventos = cur->sig;
            delete cur; cout<<" Organizador desasignado.\n"; return;
        }
        prev=cur; cur=cur->sig;
    }
    cout<<" Ese organizador no estaba asignado al evento.\n";
}

void desinscribirParticipanteEvento(int partID, int eventoID){
    participantes* p = buscarParticipante(partID);
    eventos* e = buscarEvento(eventoID);
    if(!p || !e){ cout<<" Participante/Evento no encontrado.\n"; return; }

    // quitar del evento
    enlaceParticipante* prev=NULL; enlaceParticipante* cur=e->listaParticipantes;
    while(cur){
        if(cur->refParticipante==p){
            if(prev) prev->sig = cur->sig; else e->listaParticipantes = cur->sig;
            delete cur; break;
        }
        prev=cur; cur=cur->sig;
    }
    // quitar del participante
    enlaceEventoParticipante* prev2=NULL; enlaceEventoParticipante* cur2=p->listaEventos;
    while(cur2){
        if(cur2->refEvento==e){
            if(prev2) prev2->sig = cur2->sig; else p->listaEventos = cur2->sig;
            delete cur2; break;
        }
        prev2=cur2; cur2=cur2->sig;
    }
    cout<<" Participante desinscrito.\n";
}

void desasignarRecursoEvento(int eventoID, const string& nombre){
    eventos* e = buscarEvento(eventoID);
    Recursos* r = buscarRecurso(nombre);
    if(!e || !r){ cout<<" Evento/Recurso no encontrado.\n"; return; }
    enlaceRecurso* prev=NULL; enlaceRecurso* cur=e->listaRecursos;
    while(cur){
        if(cur->refRecurso==r){
            if(prev) prev->sig = cur->sig; else e->listaRecursos = cur->sig;
            delete cur; cout<<" Recurso quitado del evento.\n"; return;
        }
        prev=cur; cur=cur->sig;
    }
    cout<<" Ese recurso no estaba asignado.\n";
}

/*
  Reemplazos de campos básicos:
    - Validan "actual" coincide con el estado del evento y usan modificarEvento.
*/
bool reemplazarNombreEvento(int eventoID, const string& nombreActual, const string& nombreNuevo){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(e->nombre != nombreActual){ cout<<" El nombre actual no coincide.\n"; return false; }
    if(str_vacia(nombreNuevo)){ cout<<" Nombre nuevo vacio.\n"; return false; }
    return modificarEvento(e->ID, nombreNuevo, e->fecha, e->lugar, e->tipo);
}

bool reemplazarFechaEvento(int eventoID, const string& fechaActual, const string& fechaNueva){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(e->fecha != fechaActual){ cout<<" La fecha actual no coincide.\n"; return false; }
    if(!esFechaValida(fechaNueva)){ cout<<" Fecha nueva invalida (YYYY-MM-DD).\n"; return false; }
    // usar tu modificarEvento para reordenar por fecha si cambia
    return modificarEvento(e->ID, e->nombre, fechaNueva, e->lugar, e->tipo);
}

bool reemplazarLugarEvento(int eventoID, const string& lugarActual, const string& lugarNuevo){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(e->lugar != lugarActual){ cout<<" El lugar actual no coincide.\n"; return false; }
    if(str_vacia(lugarNuevo) || !esTextoRazonable(lugarNuevo)){ cout<<" Lugar nuevo invalido.\n"; return false; }
    return modificarEvento(e->ID, e->nombre, e->fecha, lugarNuevo, e->tipo);
}

bool reemplazarTipoEvento(int eventoID, const string& tipoActual, const string& tipoNuevo){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(e->tipo != tipoActual){ cout<<" El tipo actual no coincide.\n"; return false; }
    if(str_vacia(tipoNuevo) || !esTextoRazonable(tipoNuevo)){ cout<<" Tipo nuevo invalido.\n"; return false; }
    return modificarEvento(e->ID, e->nombre, e->fecha, e->lugar, tipoNuevo);
}

/*
  Reemplazar relaciones (Categoría/Organizador/Participante/Recurso):
    - Mantienen consistencia eliminando el enlace anterior y creando el nuevo.
    - Consideran casos "nuevo ya estaba" -> solo quita el actual.
*/
bool reemplazarCategoriaEvento(int eventoID, int catActualID, int catNuevaID){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }

    int actualID = e->categoria ? e->categoria->ID : -1;
    if(actualID != catActualID){
        cout<<" La categoria ACTUAL indicada no coincide (actual="<< actualID <<").\n";
        return false;
    }

    // quitar enlace de la categoría actual (si hay)
    if(e->categoria){
        categorias* old = e->categoria;
        enlaceCategoriaEvento* prev=NULL; enlaceCategoriaEvento* cur=old->listaEventos;
        while(cur){
            if(cur->refEvento==e){
                if(prev) prev->sig = cur->sig; else old->listaEventos = cur->sig;
                delete cur; break;
            }
            prev=cur; cur=cur->sig;
        }
        e->categoria = NULL;
    }

    if(catNuevaID == -1){
        cout<<" Categoria quitada.\n";
        return true;
    }

    categorias* nueva = buscarCategoria(catNuevaID);
    if(!nueva){ cout<<" Categoria NUEVA no existe.\n"; return false; }

    e->categoria = nueva;
    enlaceCategoriaEvento* nuevo = new enlaceCategoriaEvento{e, nueva->listaEventos};
    nueva->listaEventos = nuevo;
    cout<<" Categoria reemplazada.\n";
    return true;
}

bool reemplazarOrganizadorEvento(int eventoID, int orgActualID, int orgNuevoID){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(!existeOrganizadorID(orgActualID)){ cout<<" Organizador ACTUAL no existe.\n"; return false; }
    if(!existeOrganizadorID(orgNuevoID)){ cout<<" Organizador NUEVO no existe.\n"; return false; }
    if(!yaAsignadoOrganizador(orgActualID, eventoID)){ cout<<" El organizador ACTUAL no esta asignado a este evento.\n"; return false; }

    // si el nuevo ya está, solo quitar el actual
    if(yaAsignadoOrganizador(orgNuevoID, eventoID)){
        desasignarOrganizadorEvento(orgActualID, eventoID);
        cout<<" El organizador nuevo ya estaba asignado; se removio el anterior.\n";
        return true;
    }
    desasignarOrganizadorEvento(orgActualID, eventoID);
    asignarOrganizadorEvento(orgNuevoID, eventoID);
    cout<<" Organizador reemplazado.\n";
    return true;
}

bool reemplazarParticipanteEvento(int eventoID, int partActualID, int partNuevoID){
    eventos* e = buscarEvento(eventoID);
    participantes* pAct = buscarParticipante(partActualID);
    participantes* pNew = buscarParticipante(partNuevoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(!pAct){ cout<<" Participante ACTUAL no existe.\n"; return false; }
    if(!pNew){ cout<<" Participante NUEVO no existe.\n"; return false; }
    if(!yaInscrito(pAct, e)){ cout<<" El participante ACTUAL no esta inscrito en este evento.\n"; return false; }

    if(yaInscrito(pNew, e)){
        desinscribirParticipanteEvento(partActualID, eventoID);
        cout<<" El participante nuevo ya estaba inscrito; se removio el anterior.\n";
        return true;
    }
    desinscribirParticipanteEvento(partActualID, eventoID);
    inscribirParticipanteEvento(partNuevoID, eventoID);
    cout<<" Participante reemplazado.\n";
    return true;
}

bool reemplazarRecursoEvento(int eventoID, const string& recursoActual, const string& recursoNuevo){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(!existeRecursoNombre(recursoActual)){ cout<<" Recurso ACTUAL no existe.\n"; return false; }
    if(!existeRecursoNombre(recursoNuevo)){ cout<<" Recurso NUEVO no existe.\n"; return false; }
    if(!yaAsignadoRecurso(eventoID, recursoActual)){ cout<<" El recurso ACTUAL no esta asignado a este evento.\n"; return false; }

    if(yaAsignadoRecurso(eventoID, recursoNuevo)){
        desasignarRecursoEvento(eventoID, recursoActual);
        cout<<" El recurso nuevo ya estaba asignado; se removio el anterior.\n";
        return true;
    }
    desasignarRecursoEvento(eventoID, recursoActual);
    asignarRecursoEvento(eventoID, recursoNuevo);
    cout<<" Recurso reemplazado.\n";
    return true;
}

/*
  insertarCategoriaInteractivo:
    - Flujo interactivo con validación de ID único, nombre y descripción.
*/
void insertarCategoriaInteractivo(){
    int id;
    string n, d;

    // ID único y válido
    while(true){
        mostrarCategorias(); // para que el usuario vea cuáles existen
        id = leerEntero("ID de categoria (positivo y unico): ");
        if(id_invalido(id)){ cout << " ID invalido.\n"; continue; }
        if(existeCategoriaID(id)){ cout << " ID de Categoria repetido. Ingrese otro.\n"; continue; }
        break;
    }

    // Nombre no vacío y razonable
    while(true){
        n = leerLinea("Nombre: ");
        if(str_vacia(n) || !esTextoRazonable(n)){
            cout << " Nombre invalido.\n";
            continue;
        }
        break;
    }

    // Descripción no vacía y razonable
    while(true){
        d = leerLinea("Descripcion: ");
        if(str_vacia(d) || !esTextoRazonable(d)){
            cout << " Descripcion invalida.\n";
            continue;
        }
        break;
    }

    insertarCategoriaFinal(id, n, d);
    cout << " Categoria creada.\n";
}

/*
  Historial utilidades:
    - existeRegistroHistorial: evita duplicados (participante,evento).
    - siguienteHistID: asigna ID incremental (máximo+1).
*/
bool existeRegistroHistorial(int partID, int eventoID){
    if(!primeroHistorial) return false;
    historial_eventos* h = primeroHistorial;
    do{
        if(h->refParticipante && h->refEvento &&
           h->refParticipante->ID == partID &&
           h->refEvento->ID == eventoID){
            return true;
        }
        h = h->sig;
    }while(h && h != primeroHistorial);
    return false;
}

int siguienteHistID(){
    int maxID = 0;
    if(primeroHistorial){
        historial_eventos* h = primeroHistorial;
        do{
            if(h->ID > maxID) maxID = h->ID;
            h = h->sig;
        }while(h != primeroHistorial);
    }
    return maxID + 1;
}

/*
  registrarHistorialSoloConEvento:
    - Permite registrar en historial tomando el evento y:
      * si hay 1 participante, lo elige automáticamente;
      * si hay varios, solicita ID.
    - Usa la fecha del evento por defecto.
*/
void registrarHistorialSoloConEvento(){
    mostrarEventos();
    int eid = leerEntero("ID evento a registrar en historial: ");
    eventos* ev = buscarEvento(eid);
    if(!ev){ cout << " Evento no encontrado.\n"; return; }

    // contar participantes y capturar si es unico
    int count = 0;
    participantes* unico = NULL;
    for(enlaceParticipante* lp = ev->listaParticipantes; lp; lp = lp->sig){
        count++;
        if(count == 1) unico = lp->refParticipante;
    }

    if(count == 0){
        cout << " Ese evento no tiene participantes inscritos.\n";
        return;
    }

    participantes* elegido = NULL;

    if(count == 1){
        elegido = unico;
        cout << " Seleccion automatica: " << elegido->nombre
             << " (ID " << elegido->ID << ")\n";
    }else{
        cout << " Participantes de este evento:\n";
        for(enlaceParticipante* lp = ev->listaParticipantes; lp; lp = lp->sig){
            cout << "   ID:" << lp->refParticipante->ID
                 << " | "   << lp->refParticipante->nombre
                 << " | "   << lp->refParticipante->carrera << "\n";
        }
        int pid = leerEntero("ID del participante a registrar en historial: ");

        bool ok = false;
        for(enlaceParticipante* lp = ev->listaParticipantes; lp; lp = lp->sig){
            if(lp->refParticipante->ID == pid){
                elegido = lp->refParticipante;
                ok = true; break;
            }
        }
        if(!ok){
            cout << " Ese ID no corresponde a un participante de este evento.\n";
            return;
        }
    }

    // evita duplicar (participante,evento)
    if(existeRegistroHistorial(elegido->ID, ev->ID)){
        cout << " Ya existe un registro de historial para ese participante en este evento.\n";
        return;
    }

    int hid = siguienteHistID();
    // fecha: usa la fecha del evento (o podrías pedir una manual si quieres)
    registrarHistorial(hid, ev->fecha, elegido->ID, ev->ID);
    cout << " Historial agregado (ID " << hid << ") para "
         << elegido->nombre << " en \"" << ev->nombre << "\".\n";
}

// ======================== SUBMENU: REPORTES =========================
/*
  menuReportes:
    - Ofrece 8 reportes principales pidiendo parámetros cuando corresponda.
*/
void menuReportes(){
    int op;
    do{
        cout << "\n==================== MENU DE REPORTES ====================\n"
             << "1) Participantes ordenados por apellido (A/D)\n"
             << "2) Eventos por ORGANIZADOR (ID)\n"
             << "3) Eventos por CATEGORIA (ID)\n"
             << "4) Recursos por EVENTO (ID)\n"
             << "5) Eventos por LUGAR (texto exacto)\n"
             << "6) Talleres por DEPARTAMENTO (texto exacto)\n"
             << "7) Historial COMPLETO\n"
             << "8) Organizadores SIN eventos\n"
             << "0) Volver\n"
             << "==========================================================\n> ";

        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op=-1; }
        cin.ignore(10000,'\n'); // limpiar salto de línea

        switch(op){
            case 1: {
                int modo = leerEntero("Orden (1=Ascendente, 2=Descendente): ");
                bool asc = (modo != 2);
                reporteParticipantesPorApellido(asc);
                break;
            }
            case 2: {
                mostrarOrganizadores();
                int idOrg = leerEntero("ID del ORGANIZADOR: ");
                reporteEventosPorOrganizador(idOrg);
                break;
            }
            case 3: {
                mostrarCategorias();
                int idCat = leerEntero("ID de la CATEGORIA: ");
                reporteEventosPorCategoria(idCat);
                break;
            }
            case 4: {
                mostrarEventos();
                int idEv = leerEntero("ID del EVENTO: ");
                reporteRecursosPorEvento(idEv);
                break;
            }
            case 5: {
                // Te muestro los eventos para que veas los lugares disponibles
                mostrarEventos();
                string lugar = leerLinea("Lugar EXACTO a buscar: ");
                reporteEventosPorLugar(lugar);
                break;
            }
            case 6: {
                // Te muestro organizadores para que veas los departamentos
                mostrarOrganizadores();
                string depto = leerLinea("Departamento EXACTO (tal como aparece): ");
                reporteTalleresPorDepartamento(depto);
                break;
            }
            case 7: {
                reporteHistorialCompleto();
                break;
            }
            case 8: {
                reporteOrganizadoresSinEventos();
                break;
            }
            case 0:
                // volver
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
    }while(op != 0);
}

// ===== Menú de Consultas (9) =====
/*
  menuConsultas:
    - Ejecuta cada una de las 9 consultas o todas en bloque.
*/
void menuConsultas(){
    int op;
    do{
        cout << "\n================= MENU CONSULTAS =================\n"
             << "1) Participante con mas eventos\n"
             << "2) Organizador con mas eventos\n"
             << "3) Tipo de evento mas frecuente\n"
             << "4) Categoria con mayor participacion\n"
             << "5) Recurso mas utilizado\n"
             << "6) Lugar con mas eventos (considera empates)\n"
             << "7) Evento con mas participantes\n"
             << "8) Organizador con mas categorias distintas\n"
             << "9) Porcentaje de participacion estudiantil\n"
             << "10) Ver TODAS las consultas\n"
             << "0) Volver\n"
             << "==================================================\n> ";

        if(!(cin >> op)){ cin.clear(); cin.ignore(10000,'\n'); op = -1; }
        cin.ignore(10000,'\n');

        switch(op){
            case 1:  consultaParticipanteMasEventos();      break;
            case 2:  consultaOrganizadorMasEventos();       break;
            case 3:  consultaTipoEventoFrecuente();         break;
            case 4:  consultaCategoriaMayorParticipacion(); break;
            case 5:  consultaRecursoMasUtilizado();         break;
            case 6:  consultaLugarMasEventos();             break;
            case 7:  consultaEventoMasParticipantes();      break;
            case 8:  consultaOrganizadorMasCategorias();    break;
            case 9:  consultaPorcentajeParticipacion();     break;
            case 10: imprimirTodasLasConsultas();           break;
            case 0:  break;
            default: cout << "Opcion invalida.\n";          break;
        }

        if(op != 0){
            cout << "\nPresione ENTER para continuar...";
            cin.get();
        }
    }while(op != 0);
}

/*
  agregarOrganizadorEventoSiNoExiste:
    - Valida existencia/no duplicado y asigna.
*/
bool agregarOrganizadorEventoSiNoExiste(int eventoID, int orgID){
    eventos* e = buscarEvento(eventoID);
    if(!e){ cout<<" Evento no encontrado.\n"; return false; }
    if(!existeOrganizadorID(orgID)){ cout<<" Organizador no encontrado.\n"; return false; }
    if(yaAsignadoOrganizador(orgID, eventoID)){
        cout<<" Ese organizador ya esta asignado al evento.\n";
        return false;
    }
    asignarOrganizadorEvento(orgID, eventoID);
    cout<<" Organizador agregado al evento.\n";
    return true;
}



// ------------------- FUNCIÓN PRINCIPAL DEL PROGRAMA -------------------
/*
  main:
    - Carga datos de ejemplo.
    - Muestra menú principal para acceder a CRUD/Consultas/Reportes.
*/
int main() {
    // Cargar datos
    cargarDatosIniciales();

    int opcion;
    do {
        cout << "\n===================================================\n";
        cout << "      SISTEMA DE GESTION DE EVENTOS UNIVERSITARIOS   \n";
        cout << "===================================================\n";
        cout << "1. Gestionar Listas \n";
        cout << "2. Ver TODAS las Consultas \n";
        cout << "3. Ver TODOS los Reportes \n";
        cout << "0. Salir del Programa\n";
        cout << "---------------------------------------------------\n";
        cout << "Ingrese su opcion: ";

        if (!(cin >> opcion)) {
            cout << "\n Entrada invalida. Por favor, ingrese un numero.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n'); // Limpiar el buffer

        switch (opcion) {
            case 1:
                menuCRUD();   // <<<<<< reemplaza el demo por esta llamada
                break;
            case 2:
                menuConsultas();
                break;
            case 3:
                menuReportes();   // antes llamabas a imprimirTodosLosReportes();
                break;
            case 0:
                cout << "\nSaliendo del sistema. ¡Adios!\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }

        if (opcion != 0) {
            cout << "\nPresione ENTER para volver al menu principal...";
            cin.get();
        }

    } while (opcion != 0);

    return 0;
}
