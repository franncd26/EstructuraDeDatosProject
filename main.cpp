#include <iostream>

using namespace std;
struct Recursos {
    string nombre;
    string descripcion;

    Recursos *sig;
    Recursos *ant;
    Recursos(string n, string g, string d) {
        nombre = n;
        descripcion = d;
        sig = NULL;
        ant = NULL;
    }
}*primeroRecursos;

struct Organizadores {
    int ID;
    string nombre;
    string departamento;
    string eventosAcargo;
    Organizadores *sig;
    Organizadores *ant;
    estructIntermedioEventos * sublista;
    Organizadores(int id, string n, string d, string eac) {
        ID = id;
        nombre = n;
        departamento = d;
        eventosAcargo = eac;
        sig = NULL;
        ant = NULL;
    }
};

struct eventos {
    int ID;
    string nombre;
    string fecha;
    string lugar;
    string tipo;
    eventos *sig;
    eventos(int id, string n, string fe, string l, string t, string o) {
        ID = id;
        nombre = n;
        fecha = fe;
        lugar = l;
        tipo = t;
        sig = NULL;
    }
};

struct participantes {
    int ID;
    string nombre;
    string carrera;
    string eventosInscrito;
    participantes *sig;
    participantes *ant;
    participantes(int id, string n, string c, string ei) {
        ID = id;
        nombre = n;
        carrera = c;
        eventosInscrito = ei;
        sig = NULL;
        ant = NULL;
    }
};

struct categorias {
    int ID;
    string nombre;
    string descripcion;
    categorias *sig;
    categorias(int id, string n, string d) {
        ID = id;
        nombre = n;
        descripcion = d;
        sig = NULL;
    }
};
struct historial_eventos {
    int ID;
    string fecha;
    historial_eventos *sig;
    historial_eventos(int id, string f) {
        ID = id;
        fecha = f;
        sig = NULL;
    }
}*primeroC;

int main() {
    std::cout << "Hola Mundo" << std::endl;
    return 0;
}