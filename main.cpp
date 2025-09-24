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
};

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
};

// ------------------- Eventos (lista simple) -------------------
struct enlaceRecurso;
struct enlaceParticipante;
struct enlaceCategoria;

struct eventos {
    int ID;
    string nombre;
    string fecha;
    string lugar;
    string tipo;
    enlaceRecurso* listaRecursos;           // relación con recursos
    enlaceParticipante* listaParticipantes; // relación con participantes
    enlaceCategoria* categoria;             // relación con categoría (uno a uno o muchos a muchos)
    eventos *sig;
    eventos(int id, string n, string fe, string l, string t) {
        ID = id;
        nombre = n;
        fecha = fe;
        lugar = l;
        tipo = t;
        listaRecursos = NULL;
        listaParticipantes = NULL;
        categoria = NULL;
        sig = NULL;
    }
};

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
};

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
};

// ------------------- Historial de eventos (lista circular) -------------------
struct historial_eventos {
    int ID;
    string fecha;
    historial_eventos *sig;
    historial_eventos(int id, string f) {
        ID = id;
        fecha = f;
        sig = NULL;
    }
} *primeroHistorial;

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

// Un participante puede estar inscrito en varios eventos
struct enlaceEventoParticipante {
    eventos* refEvento;
    enlaceEventoParticipante* sig;
};

// Una categoría puede tener varios eventos
struct enlaceCategoriaEvento {
    eventos* refEvento;
    enlaceCategoriaEvento* sig;
};

// Un evento puede pertenecer a una categoría
struct enlaceCategoria {
    categorias* refCategoria;
    enlaceCategoria* sig;
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
void consultaParticipanteMasEventos();
void consultaOrganizadorMasEventos();
void consultaTipoEventoFrecuente();
void consultaCategoriaMayorParticipacion();
void consultaRecursoMasUtilizado();
void consultaLugarMasEventos();
void consultaEventoMasParticipantes();
void consultaOrganizadorMasCategorias();
void consultaPorcentajeParticipacion();

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
    cout << "Sistema de Gestion de Eventos Universitarios - Esqueleto" << endl;

    // Aquí puedes llamar funciones de prueba
    // insertarEventoOrdenado(1, "Charla IA", "2025-09-30", "Auditorio", "Charla");

    return 0;
}

// ===================================================================
// ==================== FUNCIONES (VACÍAS) ===========================
// ===================================================================

// Ejemplo de una función vacía
void insertarEventoOrdenado(int id, string n, string f, string l, string t) {
    cout << "[insertarEventoOrdenado] - Funcion no implementada aun" << endl;
}