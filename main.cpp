#include <iostream>
#include <string>
using namespace std;

// ===================================================================
// ========================= ESTRUCTURAS DE DATOS ====================
// ===================================================================

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

// Funciones de busqueda
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

// Funciones CRUD (Insertar)
void insertarEventoOrdenado(int id, string n, string f, string l, string t);
void insertarCategoriaFinal(int id, string n, string d);
void insertarParticipante(int id, string n, string c);
void insertarOrganizador(int id, string n, string d);
void insertarRecurso(string n, string d);
void insertarHistorialOrdenado(int id, string f, participantes* p, eventos* e);

// ==== MODIFICAR ====
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

// Funciones de Relación
void asignarOrganizadorEvento(int orgID, int eventoID);
void inscribirParticipanteEvento(int partID, int eventoID);
void asignarRecursoEvento(int eventoID, string recursoNombre);
void asignarCategoriaEvento(int eventoID, int categoriaID);
void registrarHistorial(int historialID, string fecha, int partID, int eventoID);

// Funciones Mostrar (Debug/Reportes Simples)
void mostrarEventos();
void mostrarRecursos();
void mostrarHistorial();

// Funciones de Consultas (9)
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
void reporteEventosPorOrganizador(int idOrganizador);  // 2 (nuevo exacto)
void reporteEventosPorCategoria(int idCategoria);      // 3
void reporteRecursosPorEvento(int idEvento);           // 4
void reporteEventosPorLugar(string lugarX);            // 5 (nuevo exacto)
void reporteTalleresPorDepartamento(string deptoX);    // 6 (nuevo exacto)
void reporteHistorialCompleto();                       // 7 (nuevo exacto)
void reporteOrganizadoresSinEventos();                 // 8 (nuevo exacto)

// Reportes extra que ya tenías (los dejamos como utilitarios)
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

// ===================================================================
// ======================== IMPLEMENTACIÓN CRUD ======================
// ===================================================================

// Implementaciones de Búsqueda
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
bool str_vacia(const string& s){ return s.find_first_not_of(" \t\n\r") == string::npos; }
bool id_invalido(int id){ return id <= 0; }

bool existeEventoID(int id){ return buscarEvento(id) != NULL; }
bool existeCategoriaID(int id){ return buscarCategoria(id) != NULL; }
bool existeParticipanteID(int id){ return buscarParticipante(id) != NULL; }
bool existeOrganizadorID(int id){ return buscarOrganizador(id) != NULL; }
bool existeRecursoNombre(const string& n){ return buscarRecurso(n) != NULL; }

// Implementación de Inserción (con validaciones)
void insertarEventoOrdenado(int id, string n, string f, string l, string t) {
    if (id_invalido(id) || str_vacia(n) || str_vacia(f) || str_vacia(l) || str_vacia(t)) {
        cout << "❌ Datos invalidos al insertar Evento.\n"; return;
    }
    if (existeEventoID(id)) { cout << "❌ ID de Evento repetido.\n"; return; }

    eventos* nuevo = new eventos(id, n, f, l, t);
    if (primeroE == NULL) { primeroE = nuevo; return; }
    if (nuevo->fecha < primeroE->fecha) { nuevo->sig = primeroE; primeroE = nuevo; return; }
    eventos* actual = primeroE;
    while (actual->sig != NULL && actual->sig->fecha < nuevo->fecha) actual = actual->sig;
    nuevo->sig = actual->sig; actual->sig = nuevo;
}
void insertarCategoriaFinal(int id, string n, string d) {
    if (id_invalido(id) || str_vacia(n) || str_vacia(d)) {
        cout << "❌ Datos invalidos al insertar Categoria.\n"; return;
    }
    if (existeCategoriaID(id)) { cout << "❌ ID de Categoria repetido.\n"; return; }

    categorias* nuevo = new categorias(id, n, d);
    if (primeroC == NULL) { primeroC = nuevo; return; }
    categorias* actual = primeroC; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo;
}
void insertarParticipante(int id, string n, string c) {
    if (id_invalido(id) || str_vacia(n) || str_vacia(c)) {
        cout << "❌ Datos invalidos al insertar Participante.\n"; return;
    }
    if (existeParticipanteID(id)) { cout << "❌ ID de Participante repetido.\n"; return; }

    participantes* nuevo = new participantes(id, n, c);
    if (primeroP == NULL) { primeroP = nuevo; return; }
    participantes* actual = primeroP; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo; nuevo->ant = actual;
}
void insertarOrganizador(int id, string n, string d) {
    if (id_invalido(id) || str_vacia(n) || str_vacia(d)) {
        cout << "❌ Datos invalidos al insertar Organizador.\n"; return;
    }
    if (existeOrganizadorID(id)) { cout << "❌ ID de Organizador repetido.\n"; return; }

    Organizadores* nuevo = new Organizadores(id, n, d);
    if (primeroOr == NULL) { primeroOr = nuevo; return; }
    Organizadores* actual = primeroOr; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo; nuevo->ant = actual;
}
void insertarRecurso(string n, string d) {
    if (str_vacia(n) || str_vacia(d)) {
        cout << "❌ Datos invalidos al insertar Recurso.\n"; return;
    }
    if (existeRecursoNombre(n)) { cout << "❌ Nombre de Recurso repetido.\n"; return; }

    Recursos* nuevo = new Recursos(n, d);
    if (primeroR == NULL) { primeroR = nuevo; return; }
    Recursos* actual = primeroR; while (actual->sig != NULL) actual = actual->sig;
    actual->sig = nuevo; nuevo->ant = actual;
}
void insertarHistorialOrdenado(int id, string f, participantes* p, eventos* e) {
    if (id_invalido(id) || str_vacia(f) || p==NULL || e==NULL) {
        cout << "❌ Datos invalidos al insertar Historial.\n"; return;
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
    enlaceEventoParticipante* nuevoEnlaceP = new enlaceEventoParticipante{ev, part->listaEventos};
    part->listaEventos = nuevoEnlaceP;
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
    insertarHistorialOrdenado(historialID, fecha, p, e);
}

// ===================================================================
// ========================= MODIFICAR / ELIMINAR ====================
// ===================================================================

bool modificarEvento(int id, string nuevoNombre, string nuevaFecha, string nuevoLugar, string nuevoTipo){
    eventos* e = buscarEvento(id); if(!e){ cout<<"❌ Evento no encontrado.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevaFecha) || str_vacia(nuevoLugar) || str_vacia(nuevoTipo)){
        cout<<"❌ Datos invalidos.\n"; return false;
    }
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
bool modificarCategoria(int id, string nuevoNombre, string nuevaDesc){
    categorias* c = buscarCategoria(id); if(!c){ cout<<"❌ Categoria no encontrada.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevaDesc)){ cout<<"❌ Datos invalidos.\n"; return false; }
    c->nombre = nuevoNombre; c->descripcion = nuevaDesc; return true;
}
bool modificarParticipante(int id, string nuevoNombre, string nuevaCarrera){
    participantes* p = buscarParticipante(id); if(!p){ cout<<"❌ Participante no encontrado.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevaCarrera)){ cout<<"❌ Datos invalidos.\n"; return false; }
    p->nombre = nuevoNombre; p->carrera = nuevaCarrera; return true;
}
bool modificarOrganizador(int id, string nuevoNombre, string nuevoDepto){
    Organizadores* o = buscarOrganizador(id); if(!o){ cout<<"❌ Organizador no encontrado.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevoDepto)){ cout<<"❌ Datos invalidos.\n"; return false; }
    o->nombre = nuevoNombre; o->departamento = nuevoDepto; return true;
}
bool modificarRecurso(const string& nombreActual, string nuevoNombre, string nuevaDesc){
    Recursos* r = buscarRecurso(nombreActual); if(!r){ cout<<"❌ Recurso no encontrado.\n"; return false; }
    if (str_vacia(nuevoNombre) || str_vacia(nuevaDesc)){ cout<<"❌ Datos invalidos.\n"; return false; }
    if (nuevoNombre != nombreActual && existeRecursoNombre(nuevoNombre)){ cout<<"❌ Ya existe un recurso con ese nombre.\n"; return false; }
    r->nombre = nuevoNombre; r->descripcion = nuevaDesc; return true;
}

// ---- Eliminar ----
bool eliminarEvento(int id){
    eventos* target = buscarEvento(id); if(!target){ cout<<"❌ Evento no encontrado.\n"; return false; }

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

    // 4) quitar del historial
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
bool eliminarCategoria(int id){
    categorias* c = buscarCategoria(id); if(!c){ cout<<"❌ Categoria no encontrada.\n"; return false; }
    // desasociar eventos que apuntan a esta categoria
    eventos* e = primeroE;
    while(e){ if(e->categoria==c) e->categoria=NULL; e=e->sig; }
    // liberar sublista de enlaces de la categoria
    enlaceCategoriaEvento* ce = c->listaEventos;
    while(ce){ enlaceCategoriaEvento* tmp=ce; ce=ce->sig; delete tmp; }
    // quitar de lista simple
    categorias* dummy = new categorias(-1,"",""); dummy->sig = primeroC;
    categorias* pr = dummy; while(pr->sig && pr->sig!=c) pr=pr->sig;
    if(pr->sig==c){ pr->sig = c->sig; }
    primeroC = dummy->sig; delete dummy; delete c; return true;
}
bool eliminarParticipante(int id){
    participantes* p = buscarParticipante(id); if(!p){ cout<<"❌ Participante no encontrado.\n"; return false; }
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
    // quitar del historial
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
bool eliminarOrganizador(int id){
    Organizadores* o = buscarOrganizador(id); if(!o){ cout<<"❌ Organizador no encontrado.\n"; return false; }
    // liberar su sublista de eventos (solo enlaces, no borrar eventos)
    enlaceEvento* le = o->listaEventos; while(le){ enlaceEvento* tmp=le; le=le->sig; delete tmp; }
    // quitar de lista doble
    if(o->ant) o->ant->sig = o->sig; else primeroOr = o->sig;
    if(o->sig) o->sig->ant = o->ant;
    delete o; return true;
}
bool eliminarRecurso(const string& nombre){
    Recursos* r = buscarRecurso(nombre); if(!r){ cout<<"❌ Recurso no encontrado.\n"; return false; }
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
bool eliminarHistorial(int id){
    if(!primeroHistorial){ cout<<"❌ Historial vacio.\n"; return false; }
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
    cout<<"❌ ID de historial no encontrado.\n"; return false;
}

// ===================================================================
// ==================== IMPLEMENTACIÓN CONSULTAS =====================
// ===================================================================

// 1️⃣ Participante que ha asistido a más eventos
void consultaParticipanteMasEventos() {
    if (primeroP == NULL) { cout << "1️⃣ No hay participantes registrados.\n"; return; }
    participantes* p = primeroP; participantes* mayor = NULL; int maxEventos = 0;
    while (p != NULL) {
        int contador = 0; enlaceEventoParticipante* aux = p->listaEventos;
        while (aux != NULL) { contador++; aux = aux->sig; }
        if (contador > maxEventos) { maxEventos = contador; mayor = p; }
        p = p->sig;
    }
    if (mayor != NULL)
        cout << "1️⃣ Participante con mas eventos: " << mayor->nombre << " (" << maxEventos << " eventos)\n";
    else
        cout << "1️⃣ No hay inscripciones registradas.\n";
}

// 2️⃣ Organizador con más eventos a cargo
void consultaOrganizadorMasEventos() {
    if (primeroOr == NULL) { cout << "2️⃣ No hay organizadores registrados.\n"; return; }
    Organizadores* o = primeroOr; Organizadores* mayor = NULL; int maxEventos = 0;
    while (o != NULL) {
        int contador = 0; enlaceEvento* aux = o->listaEventos;
        while (aux != NULL) { contador++; aux = aux->sig; }
        if (contador > maxEventos) { maxEventos = contador; mayor = o; }
        o = o->sig;
    }
    if (mayor != NULL)
        cout << "2️⃣ Organizador con mas eventos: " << mayor->nombre << " | Eventos: " << maxEventos << endl;
    else
        cout << "2️⃣ No hay organizadores con eventos.\n";
}

// 3️⃣ Tipo de evento más frecuente
void consultaTipoEventoFrecuente() {
    if (primeroE == NULL) { cout << "3️⃣ No hay eventos registrados.\n"; return; }
    int charlas = 0, talleres = 0, ferias = 0, otros = 0; eventos* e = primeroE;
    while (e != NULL) {
        if (e->tipo == "Charla") charlas++;
        else if (e->tipo == "Taller") talleres++;
        else if (e->tipo == "Feria") ferias++;
        else otros++;
        e = e->sig;
    }
    int max = charlas; string tipo = "Charla";
    if (talleres > max) { max = talleres; tipo = "Taller"; }
    if (ferias > max) { max = ferias; tipo = "Feria"; }
    if (otros > max) { max = otros; tipo = "Otro tipo"; }
    cout << "3️⃣ Tipo de evento mas frecuente: " << tipo << " (" << max << " eventos)\n";
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
        cout << "4️⃣ Categoria con mayor participacion: " << mayor->nombre << " (" << maxParticipantes << " participantes)\n";
    else
        cout << "4️⃣ No hay categorias con eventos inscritos.\n";
}

// 5️⃣ Recurso más utilizado en eventos
void consultaRecursoMasUtilizado() {
    if (primeroR == NULL) { cout << "5️⃣ No hay recursos registrados.\n"; return; }
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
        cout << "5️⃣ Recurso mas utilizado: " << masUsado->nombre << " (" << maxUso << " eventos)\n";
    else
        cout << "5️⃣ Ningun recurso ha sido usado.\n";
}

// 6️⃣ Lugar que ha albergado más eventos (con empates)
void consultaLugarMasEventos() {
    if (primeroE == NULL) { cout << "6️⃣ No hay eventos registrados.\n"; return; }

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
        cout << "6️⃣ Hay varios lugares empatados con " << max << " eventos:\n";
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].cantidad == max) cout << " - " << lugares[i].lugar << endl;
        }
    } else {
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].cantidad == max) {
                cout << "6️⃣ Lugar con mas eventos: " << lugares[i].lugar << " (" << max << " eventos)\n";
                break;
            }
        }
    }
}

// 7️⃣ Evento con la mayor cantidad de participantes inscritos
void consultaEventoMasParticipantes() {
    if (primeroE == NULL) { cout << "7️⃣ No hay eventos registrados.\n"; return; }
    eventos* e = primeroE; eventos* mayor = NULL; int maxPart = -1;

    while (e != NULL) {
        int contador = 0; enlaceParticipante* aux = e->listaParticipantes;
        while (aux != NULL) { contador++; aux = aux->sig; }

        if (contador > maxPart) { maxPart = contador; mayor = e; }
        e = e->sig;
    }

    if (mayor != NULL && maxPart > 0)
        cout << "7️⃣ Evento con mas participantes: " << mayor->nombre << " (Fecha: " << mayor->fecha << ", " << maxPart << " inscritos)\n";
    else
        cout << "7️⃣ No se encontraron eventos con participantes inscritos.\n";
}

// 8️⃣ Organizador que ha gestionado eventos en más categorías distintas
void consultaOrganizadorMasCategorias() {
    if (primeroOr == NULL) { cout << "8️⃣ No hay organizadores registrados.\n"; return; }
    Organizadores* org = primeroOr; Organizadores* mayor = NULL; int maxCategorias = -1;

    while (org != NULL) {
        int categoriasID[100]; int numCategorias = 0;
        enlaceEvento* ev = org->listaEventos;

        while (ev != NULL) {
            if (ev->refEvento->categoria != NULL) {
                int catID = ev->refEvento->categoria->ID;
                bool existe = false;
                for (int i = 0; i < numCategorias; i++) { if (categoriasID[i] == catID) { existe = true; break; } }
                if (!existe && numCategorias < 100) { categoriasID[numCategorias++] = catID; }
            }
            ev = ev->sig;
        }

        if (numCategorias > maxCategorias) { maxCategorias = numCategorias; mayor = org; }
        org = org->sig;
    }

    if (mayor != NULL)
        cout << "8️⃣ Organizador con mas categorias distintas: " << mayor->nombre << " (" << maxCategorias << " categorias)\n";
    else
        cout << "8️⃣ No hay organizadores con eventos asignados a categorias.\n";
}

// 9️⃣ Porcentaje de estudiantes que han participado en al menos un evento vs. los que no
void consultaPorcentajeParticipacion() {
    if (primeroP == NULL) { cout << "9️⃣ No hay participantes registrados.\n"; return; }
    int totalParticipantes = 0; int conEventos = 0; participantes* p = primeroP;

    while (p != NULL) {
        totalParticipantes++;
        if (p->listaEventos != NULL) { conEventos++; }
        p = p->sig;
    }

    int sinEventos = totalParticipantes - conEventos;
    float porcCon = (totalParticipantes > 0) ? (conEventos * 100.0f) / totalParticipantes : 0.0f;
    float porcSin = (totalParticipantes > 0) ? (sinEventos * 100.0f) / totalParticipantes : 0.0f;

    cout << "9️⃣ Participacion estudiantil:\n";
    cout << "   - Con al menos 1 evento: " << conEventos << " (" << porcCon << "%)\n";
    cout << "   - Sin eventos: " << sinEventos << " (" << porcSin << "%)\n";
}

// ===================================================================
// ===================== IMPLEMENTACIÓN REPORTES =====================
// ===================================================================

// ------------------- Auxiliares para Reportes -------------------
string obtenerApellido(string nombreCompleto) {
    int lastSpaceIndex = -1;
    for (int i = 0; i < (int)nombreCompleto.length(); i++) {
        if (nombreCompleto[i] == ' ') { lastSpaceIndex = i; }
    }
    if (lastSpaceIndex != -1) { return nombreCompleto.substr(lastSpaceIndex + 1); }
    return nombreCompleto;
}
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
    if (primeroP == NULL) { cout << "1. Reporte Participantes: Lista vacía.\n"; return; }
    bool intercambio; participantes *actual, *siguiente;
    do {
        intercambio = false; actual = primeroP;
        while (actual->sig != NULL) {
            siguiente = actual->sig;
            string apActual = obtenerApellido(actual->nombre);
            string apSiguiente = obtenerApellido(siguiente->nombre);
            bool condicion = ascendente ? (apActual > apSiguiente) : (apActual < apSiguiente);
            if (condicion) { swapData(actual, siguiente); intercambio = true; }
            actual = actual->sig;
        }
    } while (intercambio);

    cout << "\n--- REPORTE 1: PARTICIPANTES ORDENADOS POR APELLIDO ---\n";
    participantes* aux = primeroP;
    while (aux != NULL) {
        cout << "ID: " << aux->ID << " | Nombre: " << aux->nombre << " | Carrera: " << aux->carrera << endl;
        aux = aux->sig;
    }
    cout << "---------------------------------------------------------\n";
}

// 2) Eventos organizados por una persona X (Organizador)
void reporteEventosPorOrganizador(int idOrganizador){
    Organizadores* o = buscarOrganizador(idOrganizador);
    if(!o){ cout<<"2. Reporte: Organizador ID "<<idOrganizador<<" no encontrado.\n"; return; }
    cout << "\n--- REPORTE 2: EVENTOS ORGANIZADOS POR: " << o->nombre << " ("<<o->departamento<<") ---\n";
    if(!o->listaEventos){ cout<<"   No tiene eventos a cargo.\n"; return; }
    enlaceEvento* aux = o->listaEventos;
    while(aux){
        eventos* ev = aux->refEvento;
        cout << "ID: "<<ev->ID<<" | Nombre: "<<ev->nombre<<" | Fecha: "<<ev->fecha<<" | Tipo: "<<ev->tipo<<" | Lugar: "<<ev->lugar<<"\n";
        aux = aux->sig;
    }
    cout << "-----------------------------------------------------------------\n";
}

// 3) Eventos de una categoria X
void reporteEventosPorCategoria(int idCategoria) {
    categorias* cat = buscarCategoria(idCategoria);
    if (cat == NULL) { cout << "3. Reporte Eventos: Categoria ID " << idCategoria << " no encontrada.\n"; return; }
    cout << "\n--- REPORTE 3: EVENTOS DE LA CATEGORIA: " << cat->nombre << " ---\n";
    enlaceCategoriaEvento* aux = cat->listaEventos;
    if (aux == NULL) { cout << "   No hay eventos asociados.\n"; return; }
    while (aux != NULL) {
        eventos* ev = aux->refEvento;
        cout << "ID: " << ev->ID << " | Nombre: " << ev->nombre << " | Fecha: " << ev->fecha
             << " | Tipo: " << ev->tipo << " | Lugar: " << ev->lugar << endl;
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

void cargarDatosIniciales() {
    cout << "\n=========================================\n";
    cout << "         Cargando Datos Iniciales...       \n";
    cout << "=========================================\n";

    // 1. Categorías
    insertarCategoriaFinal(101, "Academico", "Eventos centrados en conocimiento y ciencia.");
    insertarCategoriaFinal(102, "Cultural", "Actividades de arte, musica y folclore.");
    insertarCategoriaFinal(103, "Deportivo", "Competiciones y juegos.");

    // 2. Recursos
    insertarRecurso("Proyector Epson", "Para presentaciones en salas grandes.");
    insertarRecurso("Microfono Inalambrico", "Para oradores y panelistas.");
    insertarRecurso("Mesa de Sonido", "Control de volumen y multiples entradas.");
    insertarRecurso("Canastas de Baloncesto", "Equipo para partidos en cancha.");

    // 3. Eventos
    insertarEventoOrdenado(1, "Charla de IA", "2025-11-10", "Auditorio A", "Charla");
    insertarEventoOrdenado(2, "Taller de C++", "2025-10-25", "Laboratorio 3", "Taller");
    insertarEventoOrdenado(3, "Festival de Musica", "2025-12-05", "Plaza Central", "Feria");
    insertarEventoOrdenado(4, "Torneo de Futbol", "2025-09-15", "Cancha Principal", "Deportivo");
    insertarEventoOrdenado(5, "Taller de IA", "2025-11-11", "Auditorio A", "Taller");

    // 4. Participantes
    insertarParticipante(2001, "Maria Rojas", "Ing. Computacion");
    insertarParticipante(2002, "Juan Perez", "Ing. Electronica");
    insertarParticipante(2003, "Sofia Castro", "Arquitectura");
    insertarParticipante(2004, "Andres Diaz", "Derecho");

    // 5. Organizadores
    insertarOrganizador(301, "Luis Mena", "Departamento de TI");
    insertarOrganizador(302, "Ana Solano", "Vida Estudiantil");
    insertarOrganizador(303, "Carlos Vega", "Deportes");

    // 6. Asignación de Relaciones
    asignarCategoriaEvento(1, 101); asignarCategoriaEvento(2, 101); asignarCategoriaEvento(5, 101); // Academico
    asignarCategoriaEvento(3, 102); // Cultural
    asignarCategoriaEvento(4, 103); // Deportivo

    asignarOrganizadorEvento(301, 1); asignarOrganizadorEvento(301, 2); asignarOrganizadorEvento(301, 5); // Luis gestiona 3 (Academico)
    asignarOrganizadorEvento(302, 3); // Ana gestiona 1 (Cultural)
    asignarOrganizadorEvento(303, 4); // Carlos gestiona 1 (Deportivo)

    inscribirParticipanteEvento(2001, 1); inscribirParticipanteEvento(2001, 2); inscribirParticipanteEvento(2001, 5); // Maria (3 eventos)
    inscribirParticipanteEvento(2002, 1); // Juan (1 evento)
    inscribirParticipanteEvento(2003, 3); // Sofia (1 evento)
    // 2004 (Andres) sin eventos

    asignarRecursoEvento(1, "Proyector Epson"); asignarRecursoEvento(5, "Proyector Epson"); // Proyector (2 usos)
    asignarRecursoEvento(3, "Microfono Inalambrico"); // Microfono (1 uso)

    registrarHistorial(4001, "2025-08-01", 2001, 1);
    registrarHistorial(4002, "2025-09-01", 2002, 1);

    cout << "✔️ Carga de datos inicial completa con relaciones establecidas.\n";
    cout << "=========================================\n";
}

// ===================================================================
// ==================== MENÚ Y FUNCIONES DE IMPRESIÓN ================
// ===================================================================

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

// ------------------- FUNCIÓN PRINCIPAL DEL PROGRAMA -------------------
int main() {
    // Cargar datos
    cargarDatosIniciales();

    int opcion;
    do {
        cout << "\n===================================================\n";
        cout << "      SISTEMA DE GESTION DE EVENTOS UNIVERSITARIOS   \n";
        cout << "===================================================\n";
        cout << "1. Gestionar Listas (CRUD demo breve)\n";
        cout << "2. Ver TODAS las Consultas (9 impresas de golpe)\n";
        cout << "3. Ver TODOS los Reportes (8 impresos de golpe)\n";
        cout << "0. Salir del Programa\n";
        cout << "---------------------------------------------------\n";
        cout << "Ingrese su opcion: ";

        if (!(cin >> opcion)) {
            cout << "\n❌ Entrada invalida. Por favor, ingrese un numero.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n'); // Limpiar el buffer

        switch (opcion) {
            case 1:
                // Demo mínima de CRUD (puedes reemplazar por submenú real)
                cout << "\n[CRUD demo] Modificar 'Taller de C++' (ID=2) -> lugar 'Laboratorio 5'...\n";
                modificarEvento(2, "Taller de C++", "2025-10-25", "Laboratorio 5", "Taller");
                cout << "[CRUD demo] Eliminar recurso 'Mesa de Sonido'...\n";
                eliminarRecurso("Mesa de Sonido");
                cout << "[CRUD demo] Listo.\n";
                break;
            case 2:
                imprimirTodasLasConsultas();
                break;
            case 3:
                imprimirTodosLosReportes();
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