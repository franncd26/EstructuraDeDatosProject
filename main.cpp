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
struct enlaceEvento; // forward declaration

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
struct enlaceRecurso; // forward declaration
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

// Un evento puede estar en una categoría
struct enlaceCategoria {
    categorias* refCategoria;
    enlaceCategoria* sig;
};


int main() {
    std::cout << "Hola Mundo" << std::endl;
    return 0;
}