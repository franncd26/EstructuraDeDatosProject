#include <iostream>
#include <string>

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

// Las funciones CRUD y Reportes que no tienen implementación en el código original se omiten aquí por brevedad,
// pero se mantienen las Consultas implementadas.

// ------------------- CRUD Eventos (Lista Simple Ordenada por Fecha) -------------------

// Función para insertar un evento de forma ordenada por fecha (ascendente)
void insertarEventoOrdenado(int id, string n, string f, string l, string t) {
    // 1. Crear el nuevo nodo
    eventos* nuevo = new eventos(id, n, f, l, t);

    // 2. Si la lista está vacía
    if (primeroE == NULL) {
        primeroE = nuevo;
        cout << "✔️ Evento " << n << " insertado como primero.\n";
        return;
    }

    // 3. Si el nuevo evento va antes del primero (fecha menor)
    // El orden de strings '2025-09-30' < '2025-10-01' funciona correctamente.
    if (nuevo->fecha < primeroE->fecha) {
        nuevo->sig = primeroE;
        primeroE = nuevo;
        cout << "✔️ Evento " << n << " insertado al inicio (ordenado).\n";
        return;
    }

    // 4. Buscar la posición de inserción
    eventos* actual = primeroE;
    while (actual->sig != NULL && actual->sig->fecha < nuevo->fecha) {
        actual = actual->sig;
    }

    // 5. Insertar
    nuevo->sig = actual->sig;
    actual->sig = nuevo;
    cout << "✔️ Evento " << n << " insertado en orden por fecha.\n";
}

// Función de búsqueda (se necesita para las relaciones y otras operaciones)
eventos* buscarEvento(int id) {
    eventos* aux = primeroE;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL; // No encontrado
}

// Función de eliminación
void eliminarEvento(int id) {
    if (primeroE == NULL) {
        cout << "❌ Lista de Eventos vacia. Imposible eliminar.\n";
        return;
    }

    // Caso 1: Eliminar el primero
    if (primeroE->ID == id) {
        eventos* temp = primeroE;
        primeroE = primeroE->sig;
        delete temp;
        cout << "✔️ Evento ID " << id << " eliminado correctamente.\n";
        return;
    }

    // Caso 2: Buscar y eliminar un nodo intermedio o final
    eventos* actual = primeroE;
    while (actual->sig != NULL && actual->sig->ID != id) {
        actual = actual->sig;
    }

    if (actual->sig != NULL) {
        eventos* temp = actual->sig;
        actual->sig = actual->sig->sig;
        delete temp;
        cout << "✔️ Evento ID " << id << " eliminado correctamente.\n";
    } else {
        cout << "❌ Evento ID " << id << " no encontrado para eliminar.\n";
    }
}

// Función para mostrar (Lectura/Reporte simple)
void mostrarEventos() {
    eventos* aux = primeroE;
    cout << "\n--- LISTA DE EVENTOS (Ordenada por Fecha) ---\n";
    while (aux != NULL) {
        cout << "ID: " << aux->ID << " | Nombre: " << aux->nombre << " | Fecha: " << aux->fecha
             << " | Tipo: " << aux->tipo << " | Lugar: " << aux->lugar << endl;
        aux = aux->sig;
    }
    cout << "-----------------------------------------------\n";
}

// ------------------- CRUD Categorías (Lista Simple con Inserción al Final) -------------------

// Función para insertar una categoría al final de la lista
void insertarCategoriaFinal(int id, string n, string d) {
    // 1. Crear el nuevo nodo
    categorias* nuevo = new categorias(id, n, d);

    // 2. Si la lista está vacía
    if (primeroC == NULL) {
        primeroC = nuevo;
        cout << "✔️ Categoria " << n << " insertada como primera.\n";
        return;
    }

    // 3. Buscar el último nodo
    categorias* actual = primeroC;
    while (actual->sig != NULL) {
        actual = actual->sig;
    }

    // 4. Insertar al final
    actual->sig = nuevo;
    cout << "✔️ Categoria " << n << " insertada al final.\n";
}

// Función de búsqueda
categorias* buscarCategoria(int id) {
    categorias* aux = primeroC;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL; // No encontrado
}

// Función de eliminación
void eliminarCategoria(int id) {
    if (primeroC == NULL) {
        cout << "❌ Lista de Categorias vacia. Imposible eliminar.\n";
        return;
    }

    // Caso 1: Eliminar el primero
    if (primeroC->ID == id) {
        categorias* temp = primeroC;
        primeroC = primeroC->sig;
        delete temp;
        cout << "✔️ Categoria ID " << id << " eliminada correctamente.\n";
        return;
    }

    // Caso 2: Buscar y eliminar un nodo intermedio o final
    categorias* actual = primeroC;
    while (actual->sig != NULL && actual->sig->ID != id) {
        actual = actual->sig;
    }

    if (actual->sig != NULL) {
        categorias* temp = actual->sig;
        actual->sig = actual->sig->sig;
        delete temp;
        cout << "✔️ Categoria ID " << id << " eliminada correctamente.\n";
    } else {
        cout << "❌ Categoria ID " << id << " no encontrada para eliminar.\n";
    }
}

// Función de modificación
void modificarCategoria(int id, string nuevoNombre, string nuevaDescripcion) {
    categorias* c = buscarCategoria(id);
    if (c == NULL) {
        cout << "❌ Categoria ID " << id << " no encontrada para modificar.\n";
        return;
    }
    c->nombre = nuevoNombre;
    c->descripcion = nuevaDescripcion;
    cout << "✔️ Categoria ID " << id << " modificada a " << nuevoNombre << ".\n";
}

// ------------------- CRUD Participantes (Lista Doble) -------------------

// Función para insertar un participante al final
void insertarParticipante(int id, string n, string c) {
    participantes* nuevo = new participantes(id, n, c);

    // Si la lista está vacía
    if (primeroP == NULL) {
        primeroP = nuevo;
        cout << "✔️ Participante " << n << " insertado como primero.\n";
        return;
    }

    // Buscar el último nodo
    participantes* actual = primeroP;
    while (actual->sig != NULL) {
        actual = actual->sig;
    }

    // Insertar al final
    actual->sig = nuevo;
    nuevo->ant = actual;
    cout << "✔️ Participante " << n << " insertado al final.\n";
}

// Función de búsqueda
participantes* buscarParticipante(int id) {
    participantes* aux = primeroP;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL; // No encontrado
}

// Función de eliminación
void eliminarParticipante(int id) {
    participantes* a_borrar = buscarParticipante(id);
    if (a_borrar == NULL) {
        cout << "❌ Participante ID " << id << " no encontrado para eliminar.\n";
        return;
    }

    // El manejo de punteros en la lista doble es crucial
    if (a_borrar->ant == NULL && a_borrar->sig == NULL) { // Único nodo
        primeroP = NULL;
    } else if (a_borrar->ant == NULL) { // Primer nodo
        primeroP = a_borrar->sig;
        if (primeroP != NULL) primeroP->ant = NULL;
    } else if (a_borrar->sig == NULL) { // Último nodo
        a_borrar->ant->sig = NULL;
    } else { // Nodo intermedio
        a_borrar->ant->sig = a_borrar->sig;
        a_borrar->sig->ant = a_borrar->ant;
    }

    delete a_borrar;
    cout << "✔️ Participante ID " << id << " eliminado correctamente.\n";
}

// Función de modificación
void modificarParticipante(int id, string nuevoNombre, string nuevaCarrera) {
    participantes* p = buscarParticipante(id);
    if (p == NULL) {
        cout << "❌ Participante ID " << id << " no encontrado para modificar.\n";
        return;
    }
    p->nombre = nuevoNombre;
    p->carrera = nuevaCarrera;
    cout << "✔️ Participante ID " << id << " modificado a " << nuevoNombre << ".\n";
}

// ------------------- CRUD Organizadores (Lista Doble) -------------------

// Función para insertar un organizador al final
void insertarOrganizador(int id, string n, string d) {
    Organizadores* nuevo = new Organizadores(id, n, d);

    // Si la lista está vacía
    if (primeroOr == NULL) {
        primeroOr = nuevo;
        cout << "✔️ Organizador " << n << " insertado como primero.\n";
        return;
    }

    // Buscar el último nodo
    Organizadores* actual = primeroOr;
    while (actual->sig != NULL) {
        actual = actual->sig;
    }

    // Insertar al final
    actual->sig = nuevo;
    nuevo->ant = actual;
    cout << "✔️ Organizador " << n << " insertado al final.\n";
}

// Función de búsqueda
Organizadores* buscarOrganizador(int id) {
    Organizadores* aux = primeroOr;
    while (aux != NULL) {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    }
    return NULL; // No encontrado
}

// Función de eliminación
void eliminarOrganizador(int id) {
    Organizadores* a_borrar = buscarOrganizador(id);
    if (a_borrar == NULL) {
        cout << "❌ Organizador ID " << id << " no encontrado para eliminar.\n";
        return;
    }

    // El manejo de punteros en la lista doble es el mismo
    if (a_borrar->ant == NULL && a_borrar->sig == NULL) { // Único nodo
        primeroOr = NULL;
    } else if (a_borrar->ant == NULL) { // Primer nodo
        primeroOr = a_borrar->sig;
        if (primeroOr != NULL) primeroOr->ant = NULL;
    } else if (a_borrar->sig == NULL) { // Último nodo
        a_borrar->ant->sig = NULL;
    } else { // Nodo intermedio
        a_borrar->ant->sig = a_borrar->sig;
        a_borrar->sig->ant = a_borrar->ant;
    }

    delete a_borrar;
    cout << "✔️ Organizador ID " << id << " eliminado correctamente.\n";
}

// Función de modificación
void modificarOrganizador(int id, string nuevoNombre, string nuevoDepartamento) {
    Organizadores* o = buscarOrganizador(id);
    if (o == NULL) {
        cout << "❌ Organizador ID " << id << " no encontrado para modificar.\n";
        return;
    }
    o->nombre = nuevoNombre;
    o->departamento = nuevoDepartamento;
    cout << "✔️ Organizador ID " << id << " modificado a " << nuevoNombre << ".\n";
}

// ------------------- CRUD Recursos (Lista Doble) -------------------
// *Nota: Para esta implementación, se asume que 'primeroR' será la cabeza de la lista doble.
// Para manejo eficiente, típicamente se usaría un 'ultimoR' también.

// Función para insertar un recurso al final (típico en listas doblemente enlazadas)
void insertarRecurso(string n, string d) {
    Recursos* nuevo = new Recursos(n, d);

    // Si la lista está vacía
    if (primeroR == NULL) {
        primeroR = nuevo;
        cout << "✔️ Recurso " << n << " insertado como primero.\n";
        return;
    }

    // Buscar el último nodo
    Recursos* actual = primeroR;
    while (actual->sig != NULL) {
        actual = actual->sig;
    }

    // Insertar al final
    actual->sig = nuevo;
    nuevo->ant = actual;
    cout << "✔️ Recurso " << n << " insertado al final.\n";
}

// Función de búsqueda
Recursos* buscarRecurso(string n) {
    Recursos* aux = primeroR;
    while (aux != NULL) {
        if (aux->nombre == n) return aux;
        aux = aux->sig;
    }
    return NULL; // No encontrado
}

// Función de eliminación
void eliminarRecurso(string n) {
    Recursos* a_borrar = buscarRecurso(n);
    if (a_borrar == NULL) {
        cout << "❌ Recurso " << n << " no encontrado para eliminar.\n";
        return;
    }

    // 1. Es el único nodo (ant y sig son NULL)
    if (a_borrar->ant == NULL && a_borrar->sig == NULL) {
        primeroR = NULL;
    }
    // 2. Es el primer nodo (ant es NULL)
    else if (a_borrar->ant == NULL) {
        primeroR = a_borrar->sig;
        if (primeroR != NULL) { // Si queda al menos un nodo
            primeroR->ant = NULL;
        }
    }
    // 3. Es el último nodo (sig es NULL)
    else if (a_borrar->sig == NULL) {
        a_borrar->ant->sig = NULL;
    }
    // 4. Es un nodo intermedio
    else {
        a_borrar->ant->sig = a_borrar->sig;
        a_borrar->sig->ant = a_borrar->ant;
    }

    delete a_borrar;
    cout << "✔️ Recurso " << n << " eliminado correctamente.\n";
}

// Función de modificación
void modificarRecurso(string nombreActual, string nuevoNombre, string nuevaDescripcion) {
    Recursos* r = buscarRecurso(nombreActual);
    if (r == NULL) {
        cout << "❌ Recurso " << nombreActual << " no encontrado para modificar.\n";
        return;
    }
    r->nombre = nuevoNombre;
    r->descripcion = nuevaDescripcion;
    cout << "✔️ Recurso " << nombreActual << " modificado a " << nuevoNombre << ".\n";
}

// Función para mostrar (Lectura/Reporte simple)
void mostrarRecursos() {
    Recursos* aux = primeroR;
    cout << "\n--- LISTA DE RECURSOS (Doble) ---\n";
    while (aux != NULL) {
        cout << "Nombre: " << aux->nombre << " | Desc: " << aux->descripcion << endl;
        aux = aux->sig;
    }
    cout << "---------------------------------\n";
}

// ------------------- CRUD Historial (Lista Circular Ordenada por Fecha) -------------------

// Función para insertar una inscripción de forma ordenada por fecha (ascendente)
void insertarHistorialOrdenado(int id, string f, participantes* p, eventos* e) {
    // 1. Crear el nuevo nodo
    historial_eventos* nuevo = new historial_eventos(id, f, p, e);

    // 2. Si la lista está vacía
    if (primeroHistorial == NULL) {
        primeroHistorial = nuevo;
        nuevo->sig = nuevo; // Se apunta a sí mismo
        cout << "✔️ Historial ID " << id << " insertado como primero (Circular).\n";
        return;
    }

    // 3. Buscar el último nodo (que apunta al primero)
    historial_eventos* ultimo = primeroHistorial;
    while (ultimo->sig != primeroHistorial) {
        ultimo = ultimo->sig;
    }

    // 4. Si el nuevo nodo va antes del primero (fecha menor)
    if (nuevo->fecha < primeroHistorial->fecha) {
        nuevo->sig = primeroHistorial;
        primeroHistorial = nuevo;
        ultimo->sig = primeroHistorial; // El último sigue apuntando al nuevo primero
        cout << "✔️ Historial ID " << id << " insertado al inicio (ordenado circular).\n";
        return;
    }

    // 5. Buscar la posición de inserción
    historial_eventos* actual = primeroHistorial;
    // La condición de parada debe verificar que no volvamos al inicio y que el siguiente sea mayor
    while (actual->sig != primeroHistorial && actual->sig->fecha < nuevo->fecha) {
        actual = actual->sig;
    }

    // 6. Insertar (el nodo 'actual' es el que precede al punto de inserción)
    nuevo->sig = actual->sig;
    actual->sig = nuevo;
    cout << "✔️ Historial ID " << id << " insertado en orden circular.\n";
}

// Función de eliminación
void eliminarHistorial(int id) {
    if (primeroHistorial == NULL) {
        cout << "❌ Lista Historial vacia. Imposible eliminar.\n";
        return;
    }

    historial_eventos* actual = primeroHistorial;
    historial_eventos* anterior = NULL;

    // Buscar el nodo a eliminar
    do {
        if (actual->ID == id) {
            break; // Nodo encontrado
        }
        anterior = actual;
        actual = actual->sig;
    } while (actual != primeroHistorial);

    if (actual->ID != id) {
        cout << "❌ Historial ID " << id << " no encontrado para eliminar.\n";
        return;
    }

    // Caso 1: Único nodo
    if (actual->sig == actual) {
        primeroHistorial = NULL;
    }
    // Caso 2: Primer nodo (y hay más)
    else if (actual == primeroHistorial) {
        // Encontrar el último nodo para que apunte al nuevo primero
        historial_eventos* ultimo = primeroHistorial;
        while (ultimo->sig != primeroHistorial) {
            ultimo = ultimo->sig;
        }
        primeroHistorial = primeroHistorial->sig;
        ultimo->sig = primeroHistorial;
    }
    // Caso 3: Nodo intermedio o final
    else {
        anterior->sig = actual->sig;
    }

    delete actual;
    cout << "✔️ Historial ID " << id << " eliminado correctamente.\n";
}

// Función de búsqueda simple (no se pide en el proyecto, pero es útil)
historial_eventos* buscarHistorial(int id) {
    if (primeroHistorial == NULL) return NULL;

    historial_eventos* aux = primeroHistorial;
    do {
        if (aux->ID == id) return aux;
        aux = aux->sig;
    } while (aux != primeroHistorial);

    return NULL;
}

// Función para mostrar (Lectura/Reporte simple)
void mostrarHistorial() {
    if (primeroHistorial == NULL) {
        cout << "--- LISTA HISTORIAL VACÍA ---\n";
        return;
    }
    historial_eventos* aux = primeroHistorial;
    cout << "\n--- HISTORIAL DE INSCRIPCIONES (Circular Ordenada) ---\n";
    do {
        // Se muestran las referencias al participante y evento para completitud
        cout << "ID: " << aux->ID << " | Fecha: " << aux->fecha
             << " | Part.: " << (aux->refParticipante ? aux->refParticipante->nombre : "N/A")
             << " | Evento: " << (aux->refEvento ? aux->refEvento->nombre : "N/A") << endl;
        aux = aux->sig;
    } while (aux != primeroHistorial);
    cout << "--------------------------------------------------------\n";
}

// --- Relaciones ---
void asignarCategoriaEvento(int eventoID, int categoriaID) { /* ... */ }
void asignarOrganizadorEvento(int orgID, int eventoID) { /* ... */ }
void inscribirParticipanteEvento(int partID, int eventoID) { /* ... */ }
void asignarRecursoEvento(int eventoID, string recursoNombre) { /* ... */ }

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
        cout << "1️⃣ Participante con mas eventos: " << mayor->nombre
             << " (" << maxEventos << " eventos)\n";
    else
        cout << "1️⃣ No hay inscripciones registradas.\n";
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
        cout << "2️⃣ Organizador con mas eventos: " << mayor->nombre
             << " | Departamento: " << mayor->departamento
             << " | Eventos: " << maxEventos << endl;
    else
        cout << "2️⃣ No hay organizadores con eventos.\n";
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
        // Normalización sencilla para contar
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

    cout << "3️⃣ Tipo de evento mas frecuente: " << tipo
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
        cout << "4️⃣ Categoria con mayor participacion: " << mayor->nombre
             << " (" << maxParticipantes << " participantes)\n";
    else
        cout << "4️⃣ No hay categorias con eventos inscritos.\n";
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
                // Compara la referencia del recurso
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
        cout << "5️⃣ Recurso mas utilizado: " << masUsado->nombre
             << " (" << maxUso << " eventos)\n";
    else
        cout << "5️⃣ Ningun recurso ha sido usado.\n";
}

// consulta #6
void consultaLugarMasEventos() {
    if (primeroE == NULL) {
        cout << "No hay eventos registrados.\n";
        return;
    }

    struct LugarContador {
        string lugar;
        int cantidad;
    };

    // Usaremos un arreglo estático de tamaño fijo para simplificar (máximo 100 lugares distintos)
    LugarContador lugares[100];
    int totalLugares = 0;

    eventos* e1 = primeroE;
    while (e1 != NULL) {
        bool encontrado = false;
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].lugar == e1->lugar) {
                lugares[i].cantidad++;
                encontrado = true;
                break;
            }
        }
        // Si el lugar no existe y hay espacio en el array
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

    if (totalLugares == 0) {
        cout << "6️⃣ No hay lugares registrados en los eventos.\n";
        return;
    }

    int empates = 0;
    for (int i = 0; i < totalLugares; i++) {
        if (lugares[i].cantidad == max) empates++;
    }

    if (empates > 1) {
        cout << "6️⃣ Hay varios lugares empatados con " << max << " eventos:\n";
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].cantidad == max)
                cout << " - " << lugares[i].lugar << endl;
        }
    } else {
        for (int i = 0; i < totalLugares; i++) {
            if (lugares[i].cantidad == max) {
                cout << "6️⃣ Lugar con mas eventos: " << lugares[i].lugar
                     << " (" << max << " eventos)\n";
                break;
            }
        }
    }
}


// 7️⃣ Evento con más participantes
void consultaEventoMasParticipantes() {
    if (primeroE == NULL) {
        cout << "No hay eventos registrados.\n";
        return;
    }

    eventos* e = primeroE;
    eventos* mayor = NULL;
    int max = -1; // Se inicializa en -1 para manejar el caso de 0 participantes

    while (e != NULL) {
        int contador = 0;
        enlaceParticipante* p = e->listaParticipantes;
        while (p != NULL) {
            contador++;
            p = p->sig;
        }

        // Si el contador es mayor que el máximo actual o el máximo es -1
        if (contador > max) {
            max = contador;
            mayor = e;
        }
        e = e->sig;
    }

    if (mayor != NULL && max > 0)
        cout << "7️⃣ Evento con mas participantes: " << mayor->nombre
             << " | Fecha: " << mayor->fecha
             << " | Participantes: " << max << endl;
    else
        cout << "7️⃣ No hay eventos con participantes.\n";
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
            // Solo se considera si el evento tiene categoría asignada
            if (e1->refEvento->categoria != NULL) {
                bool repetida = false;
                enlaceEvento* e2 = o->listaEventos;

                // Recorrer los eventos anteriores del mismo organizador
                while (e2 != e1) {
                    // Compara las referencias a la estructura de la categoría
                    if (e1->refEvento->categoria == e2->refEvento->categoria) {
                        repetida = true;
                        break; // Categoría ya contada
                    }
                    e2 = e2->sig;
                }

                if (!repetida)
                    contador++;
            }
            e1 = e1->sig;
        }

        if (contador > maxCat) {
            maxCat = contador;
            mayor = o;
        }
        o = o->sig;
    }

    if (mayor != NULL)
        cout << "8️⃣ Organizador con mas categorias: " << mayor->nombre
             << " (" << maxCat << " categorias distintas)\n";
    else
        cout << "8️⃣ No hay organizadores con categorias registradas.\n";
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
        // Un participante está activo si tiene al menos un evento inscrito
        if (p->listaEventos != NULL) activos++;
        p = p->sig;
    }

    double porcentaje = (total > 0) ? (activos * 100.0 / total) : 0;
    cout.precision(2); // Para mostrar con dos decimales
    cout << fixed; // Usar notación de punto fijo

    cout << "9️⃣ Participantes activos: " << activos << "/" << total
         << " (" << porcentaje << "% participaron en al menos un evento)\n";
}

// --- Reportes (Prototypes only) ---
void reporteParticipantesAscDesc() { /* ... */ }
void reporteEventosPorOrganizador(int orgID) { /* ... */ }
void reporteEventosPorCategoria(int catID) { /* ... */ }
void reporteRecursosPorEvento(int eventoID) { /* ... */ }
void reporteEventosPorLugar(string lugar) { /* ... */ }
void reporteTalleresPorDepartamento(string depto) { /* ... */ }
void reporteHistorial() { /* ... */ }
void reporteOrganizadoresSinEventos() { /* ... */ }


// ===================================================================
// ============================ MAIN =================================
// ===================================================================
int main() {
    cout << "=== Sistema de Gestion de Eventos Universitarios ===\n\n";

    // Reinicializar punteros globales (Buena práctica)
    primeroR = NULL;
    primeroOr = NULL;
    primeroE = NULL;
    primeroP = NULL;
    primeroC = NULL;
    primeroHistorial = NULL;


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

    // Asignar categorías (Relación 1:1)
    ev1->categoria = cat1;
    ev2->categoria = cat1;
    ev3->categoria = cat2;

    // Agregar eventos a lista de categorías (Relación 1:M inversa)
    enlaceCategoriaEvento* ec1 = new enlaceCategoriaEvento{ev1, NULL};
    enlaceCategoriaEvento* ec2 = new enlaceCategoriaEvento{ev2, NULL};
    enlaceCategoriaEvento* ec3 = new enlaceCategoriaEvento{ev3, NULL};
    cat1->listaEventos = ec1;
    ec1->sig = ec2; // Evento 1 y 2 en categoría 1
    cat2->listaEventos = ec3; // Evento 3 en categoría 2

    // --- Crear Participantes ---
    participantes* p1 = new participantes(1, "Ana Lopez", "Computacion");
    participantes* p2 = new participantes(2, "Luis Perez", "Mecatronica");
    participantes* p3 = new participantes(3, "Maria Torres", "Informatica");
    // Añadimos un participante inactivo para la consulta de porcentaje
    participantes* p4 = new participantes(4, "Juan Salas", "Arquitectura");
    primeroP = p1;
    p1->sig = p2;
    p2->sig = p3;
    p3->sig = p4;

    // Inscribir participantes en eventos (Relación M:M en lado del Evento)
    enlaceParticipante* ev1_p1 = new enlaceParticipante{p1, NULL};
    enlaceParticipante* ev1_p2 = new enlaceParticipante{p2, NULL};

    enlaceParticipante* ev2_p3 = new enlaceParticipante{p3, NULL};

    enlaceParticipante* ev3_p1 = new enlaceParticipante{p1, NULL};
    enlaceParticipante* ev3_p2 = new enlaceParticipante{p2, NULL};

    ev1->listaParticipantes = ev1_p1; // Ana en ev1
    ev1_p1->sig = ev1_p2;            // Luis en ev1

    ev2->listaParticipantes = ev2_p3; // Maria en ev2

    ev3->listaParticipantes = ev3_p1; // Ana en ev3
    ev3_p1->sig = ev3_p2;            // Luis en ev3

    // Vincular eventos a los participantes (Relación M:M en lado del Participante)
    enlaceEventoParticipante* p1_e1 = new enlaceEventoParticipante{ev1, NULL};
    enlaceEventoParticipante* p1_e3 = new enlaceEventoParticipante{ev3, NULL};
    p1->listaEventos = p1_e1;       // Ana en ev1
    p1_e1->sig = p1_e3;              // y ev3

    enlaceEventoParticipante* p2_e1 = new enlaceEventoParticipante{ev1, NULL};
    enlaceEventoParticipante* p2_e3 = new enlaceEventoParticipante{ev3, NULL};
    p2->listaEventos = p2_e1;       // Luis en ev1
    p2_e1->sig = p2_e3;             // y ev3

    enlaceEventoParticipante* p3_e2 = new enlaceEventoParticipante{ev2, NULL};
    p3->listaEventos = p3_e2;       // Maria en ev2

    // p4 (Juan Salas) queda con listaEventos = NULL (inactivo)

    // --- Crear Organizadores ---
    Organizadores* o1 = new Organizadores(1, "Carlos Vega", "Computacion");
    Organizadores* o2 = new Organizadores(2, "Sofia Ruiz", "Deportes");
    primeroOr = o1;
    o1->sig = o2;

    // Asignar eventos a organizadores (Relación 1:M)
    o1->listaEventos = new enlaceEvento{ev1, NULL}; // Carlos con ev1
    o1->listaEventos->sig = new enlaceEvento{ev2, NULL}; // Carlos con ev2
    o2->listaEventos = new enlaceEvento{ev3, NULL}; // Sofia con ev3

    // --- Asignar recursos a eventos (Relación M:M en lado Evento) ---
    ev1->listaRecursos = new enlaceRecurso{rec1, NULL}; // ev1 usa Proyector

    ev2->listaRecursos = new enlaceRecurso{rec1, NULL}; // ev2 usa Proyector
    ev2->listaRecursos->sig = new enlaceRecurso{rec2, NULL}; // ev2 usa Sala A

    ev3->listaRecursos = new enlaceRecurso{rec3, NULL}; // ev3 usa Cancha

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

    // Se debería liberar la memoria de todas las estructuras creadas (omitiendo por brevedad)

    return 0;
}