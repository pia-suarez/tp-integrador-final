#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#define ALTA_ARTISTA        1
#define BAJA_ARTISTA        2
#define MODIF_ARTISTA       3
#define ALTA_ESCENARIO      4
#define BAJA_ESCENARIO      5
#define MODIF_ESCENARIO     6
#define ALTA_PRESENTACION   7
#define BAJA_PRESENTACION   8
#define MODIF_PRESENTACION  9

typedef struct
{
    int id;
    char nombre[50];
    char genero[30];
    int baja;
} artista;

typedef struct
{
    int id;
    char nombre[50];
    int estado;
} escenario;

typedef struct
{
    int horas;
    int minutos;
    int esValido;
} horario;

typedef struct
{
    int horas;
    int minutos;
    int esValido;
} duracion;

typedef struct
{
    int id;
    int idArtista;
    int idEscenario;
    horario Inicio;
    duracion duracionn;
    int baja;
} presentacion;

const char nombre_arch[]= "archivo.bin";

void mostrarHistorial(Pila p);
artista cargarArtista(int cantArtistas);
escenario cargaEscenario();
horario cargaHorario();
duracion cargaDuracion();
int buscarPresentacionPorId(presentacion arrPresentaciones[], int cantPresentaciones, int id);
int buscarArtistaPorId(artista arregloArtistas[], int cantArtistas, int id);
int buscarEscenarioPorId(escenario arrEsc[], int cantEsc, int id);
presentacion cargaPresentacion(int cantPresentaciones, artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios);
void ordenarArtistasPorNombre(artista arr[], int cant);
void ordenarEscenariosPorNombre(escenario arr[], int cant);
void ordenarPresentacionesPorNombre(presentacion arr[], int cant, artista arrArt[], int cantArt);
escenario* crearEscenario(escenario *arr, int *cant, Pila *historial);
escenario* borrarEscenario(escenario *arr, int *cant, presentacion arrPres[], int cantPres, int id, Pila *historial);
void modificarEscenario(escenario *arr, int cant, int id, Pila *historial);
void mostrarEscenarios(escenario *arr, int cant);
void agregarArtista(artista arregloArtistas[], int *cantArtistas, Pila *historial);
void modificarArtista(artista arregloArtistas[], int cantArtistas, Pila *historial);
artista modificarDatosArtista(artista a);
void bajaArtista(artista arrArtistas[], int cantArtistas, presentacion arrPresentaciones[], int cantPresentaciones, int id, Pila *historial);
void mostrarArtistas(artista arr[], int cant);
int aMinutos(horario h);
horario horarioFin(horario inicio, duracion dur);
int seSolapan(presentacion a, presentacion b);
int hayConflictoEscenario(presentacion nueva, presentacion arr[], int cant);
int hayConflictoArtista(presentacion nueva, presentacion arr[], int cant);
void agregarPresentacion(presentacion arrPresentaciones[], int *cantPresentaciones, artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios, Pila *historial);
void bajaPresentacion(presentacion arrPresentaciones[], int cantPresentaciones, artista arrArtistas[], int cantArtistas, Pila *historial);
void modificarPresentacion(presentacion arrPresentaciones[], int cantPresentaciones, artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios, Pila *historial);
void mostrarPresentaciones(presentacion arrPres[], int cantPres, artista arrArt[], int cantArt, escenario arrEsc[], int cantEsc);
void mostrarPresentacionesArtista(presentacion arrPres[], int cantPres, int idArtista, artista arrArt[], int cantArt, escenario arrEsc[], int cantEsc);
void mostrarPresentacionesEscenario(presentacion arrPres[], int cantPres, artista arrArt[], int cantArt, escenario arrEsc[], int cantEsc, int idEscenario);
void guardarTodo(artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios, presentacion arrPresentaciones[], int cantPresentaciones);
escenario* cargarTodo(artista arrArtistas[], int *cantArtistas, escenario **arrEscenarios, int *cantEscenarios, presentacion arrPresentaciones[], int *cantPresentaciones);
void reasignarPresentaciones(presentacion arrPres[], int cantPres, int idViejo, int idNuevo);
int escTienePresentaciones(presentacion arrPres[], int cantPres, int idEscenario);


int main()
{
    escenario *escenarios = NULL;
    int cantEscenarios = 0;
    artista arrArtistas[100];
    int cantArtistas = 0;
    presentacion arrPresentaciones[40];
    int cantPresentaciones = 0;
    Pila historial;
    inicpila(&historial);

    escenarios = cargarTodo(arrArtistas, &cantArtistas, &escenarios, &cantEscenarios, arrPresentaciones, &cantPresentaciones);

    int opcion;
    do
    {
        printf("============================\n");
        printf("|   FESTIVAL DE MUSICA     |\n");
        printf("============================\n");
        printf("| ARTISTAS                 |\n");
        printf("|  1. Agregar artista      |\n");
        printf("|  2. Modificar artista    |\n");
        printf("|  3. Baja artista         |\n");
        printf("|  4. Listar artistas      |\n");
        printf("| ESCENARIOS               |\n");
        printf("|  5. Agregar escenario    |\n");
        printf("|  6. Modificar escenario  |\n");
        printf("|  7. Baja escenario       |\n");
        printf("|  8. Listar escenarios    |\n");
        printf("| PRESENTACIONES           |\n");
        printf("|  9. Agregar presentacion |\n");
        printf("| 10. Modificar pres.      |\n");
        printf("| 11. Baja presentacion    |\n");
        printf("| 12. Listar pres.         |\n");
        printf("| 13. Pres. por artista    |\n");
        printf("| 14. Pres. por escenario  |\n");
        printf("| SISTEMA                  |\n");
        printf("| 15. Guardar              |\n");
        printf("| 16. Cargar desde archivo |\n");
        printf("| 17. Historial acciones   |\n");
        printf("|  0. Salir                |\n");
        printf("============================\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        int id;

        switch (opcion)
        {
        case 1:
            agregarArtista(arrArtistas, &cantArtistas, &historial);
            break;
        case 2:
            modificarArtista(arrArtistas, cantArtistas, &historial);
            break;
        case 3:
            printf("Ingrese el ID del artista a dar de baja: ");
            scanf("%d", &id);
            bajaArtista(arrArtistas, cantArtistas, arrPresentaciones, cantPresentaciones, id, &historial);
            break;
        case 4:
            ordenarArtistasPorNombre(arrArtistas, cantArtistas);
            mostrarArtistas(arrArtistas, cantArtistas);
            break;
        case 5:
            escenarios = crearEscenario(escenarios, &cantEscenarios, &historial);
            break;
        case 6:
            printf("Ingrese el ID del escenario a modificar: ");
            scanf("%d", &id);
            modificarEscenario(escenarios, cantEscenarios, id, &historial);
            break;
        case 7:
            printf("Ingrese el ID del escenario a dar de baja: ");
            scanf("%d", &id);
            escenarios = borrarEscenario(escenarios, &cantEscenarios, arrPresentaciones, cantPresentaciones, id, &historial);
            break;
        case 8:
            ordenarEscenariosPorNombre(escenarios, cantEscenarios);
            mostrarEscenarios(escenarios, cantEscenarios);
            break;
        case 9:
            agregarPresentacion(arrPresentaciones, &cantPresentaciones, arrArtistas, cantArtistas, escenarios, cantEscenarios, &historial);
            break;
        case 10:
            modificarPresentacion(arrPresentaciones, cantPresentaciones, arrArtistas, cantArtistas, escenarios, cantEscenarios, &historial);
            break;
        case 11:
            bajaPresentacion(arrPresentaciones, cantPresentaciones, arrArtistas, cantArtistas, &historial);
            break;
        case 12:
            ordenarPresentacionesPorNombre(arrPresentaciones, cantPresentaciones, arrArtistas, cantArtistas);
            mostrarPresentaciones(arrPresentaciones, cantPresentaciones, arrArtistas, cantArtistas, escenarios, cantEscenarios);
            break;
        case 13:
            printf("Ingrese el ID del artista: ");
            scanf("%d", &id);
            mostrarPresentacionesArtista(arrPresentaciones, cantPresentaciones, id, arrArtistas, cantArtistas, escenarios, cantEscenarios);
            break;
        case 14:
            printf("Ingrese el ID del escenario: ");
            scanf("%d", &id);
            mostrarPresentacionesEscenario(arrPresentaciones, cantPresentaciones, arrArtistas, cantArtistas, escenarios, cantEscenarios, id);
            break;
        case 15:
            guardarTodo(arrArtistas, cantArtistas, escenarios, cantEscenarios, arrPresentaciones, cantPresentaciones);
            break;
        case 16:
            guardarTodo(arrArtistas, cantArtistas, escenarios, cantEscenarios, arrPresentaciones, cantPresentaciones);
            escenarios = cargarTodo(arrArtistas, &cantArtistas, &escenarios, &cantEscenarios, arrPresentaciones, &cantPresentaciones);
            break;
        case 17:
            mostrarHistorial(historial);
            break;
        case 0:
            guardarTodo(arrArtistas, cantArtistas, escenarios, cantEscenarios, arrPresentaciones, cantPresentaciones);
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }
    }
    while (opcion != 0);

    free(escenarios);
    return 0;
}

void mostrarHistorial(Pila p)
{
    if (pilavacia(&p))
    {
        printf("No hay acciones registradas.\n");
        return;
    }
    printf("============================\n");
    printf("|  HISTORIAL DE ACCIONES  |\n");
    printf("============================\n");
    while (!pilavacia(&p))
    {
        int accion = desapilar(&p);
        switch (accion)
        {
        case ALTA_ARTISTA:
            printf("| Alta de artista\n");
            break;
        case BAJA_ARTISTA:
            printf("| Baja de artista\n");
            break;
        case MODIF_ARTISTA:
            printf("| Modificacion de artista\n");
            break;
        case ALTA_ESCENARIO:
            printf("| Alta de escenario\n");
            break;
        case BAJA_ESCENARIO:
            printf("| Baja de escenario\n");
            break;
        case MODIF_ESCENARIO:
            printf("| Modificacion de escenario\n");
            break;
        case ALTA_PRESENTACION:
            printf("| Alta de presentacion\n");
            break;
        case BAJA_PRESENTACION:
            printf("| Baja de presentacion\n");
            break;
        case MODIF_PRESENTACION:
            printf("| Modificacion de presentacion\n");
            break;
        }
    }
    printf("============================\n");
}

artista cargarArtista(int cantArtistas)
{
    artista a;
    a.id = cantArtistas + 1;
    a.baja=0;
    int opcionGenero;
    printf("============================\n");
    printf("|     DATOS DEL ARTISTA    |\n");
    printf("============================\n");
    printf("ID asignado: %i\n", a.id);
    printf("Nombre: ");
    scanf(" ");
    fgets(a.nombre, sizeof(a.nombre), stdin);
    a.nombre[strcspn(a.nombre, "\n")] = '\0';
    do
    {
        printf("\n============================\n");
        printf("|    GENEROS DISPONIBLES   |\n");
        printf("============================\n");
        printf("|  1. Rock                 |\n");
        printf("|  2. Pop                  |\n");
        printf("|  3. Jazz                 |\n");
        printf("|  4. Clasica              |\n");
        printf("|  5. Hip-Hop              |\n");
        printf("|  6. Electronica          |\n");
        printf("|  7. Reggaeton            |\n");
        printf("|  8. Blues                |\n");
        printf("|  9. Metal                |\n");
        printf("|  10. Otro                |\n");
        printf("============================\n");
        printf("Seleccione un genero: ");
        scanf("%i", &opcionGenero);
        if (opcionGenero < 1 || opcionGenero > 10)
            printf("Opcion invalida. Intente nuevamente.\n");
    }
    while (opcionGenero < 1 || opcionGenero > 10);
    switch (opcionGenero)
    {
    case 1:
        strcpy(a.genero, "Rock");
        break;
    case 2:
        strcpy(a.genero, "Pop");
        break;
    case 3:
        strcpy(a.genero, "Jazz");
        break;
    case 4:
        strcpy(a.genero, "Clasica");
        break;
    case 5:
        strcpy(a.genero, "Hip-Hop");
        break;
    case 6:
        strcpy(a.genero, "Electronica");
        break;
    case 7:
        strcpy(a.genero, "Reggaeton");
        break;
    case 8:
        strcpy(a.genero, "Blues");
        break;
    case 9:
        strcpy(a.genero, "Metal");
        break;
    case 10:
        strcpy(a.genero, "Otro");
        break;
    }
    printf("\n============================\n");
    printf("| Artista cargado con exito|\n");
    printf("============================\n");
    return a;
}

escenario cargaEscenario()
{
    escenario a;
    printf("============================\n");
    printf("|    DATOS DEL ESCENARIO   |\n");
    printf("============================\n");
    printf("Nombre: ");
    scanf(" ");
    fgets(a.nombre, sizeof(a.nombre), stdin);
    a.nombre[strcspn(a.nombre, "\n")] = '\0';
    a.estado = 1;
    printf("\n============================\n");
    printf("|Escenario cargado con exito  |\n");
    printf("============================\n");
    return a;
}

horario cargaHorario()
{
    horario a;
    printf("============================\n");
    printf("|     HORARIO DE INICIO    |\n");
    printf("============================\n");
    printf("Ingrese las horas: ");
    scanf("%i", &a.horas);
    printf("Ingrese los minutos: ");
    scanf("%i", &a.minutos);
    if (a.horas >= 0 && a.horas <= 23 && a.minutos >= 0 && a.minutos <= 59)
    {
        a.esValido = 1;
        return a;
    }
    else
    {
        a.esValido = 0;
        printf("\n[!] El horario es incorrecto. Intente de nuevo.\n\n");
        return cargaHorario();
    }
}


horario horarioFin(horario inicio, duracion duracion)
{
    int minutosInicio = inicio.horas * 60 + inicio.minutos;
    int minutosDuracion = duracion.horas * 60 + duracion.minutos;
    int minutosFin = minutosInicio + minutosDuracion;
    horario fin;
    fin.horas = (minutosFin / 60) % 24;
    fin.minutos = minutosFin % 60;
    fin.esValido = 1;
    return fin;
}

duracion cargaDuracion()
{
    duracion a;
    printf("============================\n");
    printf("| DURACION DE PRESENTACION |\n");
    printf("============================\n");
    printf("Ingrese la cantidad de horas que durara: ");
    scanf("%i", &a.horas);
    printf("Ingrese la cantidad de minutos que durara: ");
    scanf("%i", &a.minutos);
    int totalMinutos = a.horas * 60 + a.minutos;
    if (totalMinutos > 0 && totalMinutos <= 1500 && a.minutos <= 59)
    {
        a.esValido = 1;
        return a;
    }
    else
    {
        a.esValido = 0;
        printf("\n[!] La duracion es incorrecta. Intente de nuevo.\n\n");
        return cargaDuracion();
    }
}

int buscarPresentacionPorId(presentacion arrPresentaciones[], int cantPresentaciones, int id)
{
    for (int i = 0; i < cantPresentaciones; i++)
    {
        if (arrPresentaciones[i].id == id)
            return i;
    }
    return -1;
}

presentacion cargaPresentacion(int cantPresentaciones, artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios)
{
    presentacion p;
    int indice;
    p.id = cantPresentaciones + 1;
    int hayArtistas = 0;
    for (int i = 0; i < cantArtistas; i++)
    {
        if (arrArtistas[i].baja == 0)
        {
            hayArtistas = 1;
            break;
        }
    }

    int hayEscenarios = 0;
    for (int i = 0; i < cantEscenarios; i++)
    {
        if (arrEscenarios[i].estado == 1)
        {
            hayEscenarios = 1;
            break;
        }

    }

    if (!hayArtistas || !hayEscenarios)
    {
        printf("Error: no hay artistas o escenarios disponibles.\n");
        p.id = -1;
        return p;
    }
    p.baja = 0;
    printf("============================\n");
    printf("|    NUEVA PRESENTACION    |\n");
    printf("============================\n");
    printf("ID asignado: %i\n", p.id);
    do
    {
        printf("Ingrese el ID del artista: ");
        scanf("%i", &p.idArtista);
        indice = buscarArtistaPorId(arrArtistas, cantArtistas, p.idArtista);
        if (indice == -1)
            printf("No existe un artista con ID %i. Intente nuevamente.\n", p.idArtista);
        else if (arrArtistas[indice].baja == 1)
            printf("El artista con ID %i esta dado de baja. Intente nuevamente.\n", p.idArtista);
    }
    while (indice == -1 || arrArtistas[indice].baja == 1);
    do
    {
        printf("Ingrese el ID del escenario: ");
        scanf("%i", &p.idEscenario);
        indice = buscarEscenarioPorId(arrEscenarios, cantEscenarios, p.idEscenario);
        if (indice == -1)
            printf("No existe un escenario con ID %i. Intente nuevamente.\n", p.idEscenario);
        else if (arrEscenarios[indice].estado == 0)
            printf("El escenario con ID %i esta dado de baja. Intente nuevamente.\n", p.idEscenario);
    }
    while (indice == -1 || arrEscenarios[indice].estado == 0);
    p.Inicio = cargaHorario();
    p.duracionn = cargaDuracion();
    return p;
}

int buscarArtistaPorId(artista arregloArtistas[], int cantArtistas, int id)
{
    for (int i = 0; i < cantArtistas; i++)
    {
        if (arregloArtistas[i].id == id)
            return i;
    }
    return -1;
}

void agregarArtista(artista arregloArtistas[], int *cantArtistas, Pila *historial)
{

    if (*cantArtistas >= 100)
    {
        printf("No hay espacio para mas artistas.\n");
        return;
    }
    artista nuevo = cargarArtista(*cantArtistas);
    arregloArtistas[*cantArtistas] = nuevo;
    (*cantArtistas)++;
    printf("Artista agregado correctamente.\n");
    apilar(historial, ALTA_ARTISTA);
}

void modificarArtista(artista arregloArtistas[], int cantArtistas, Pila *historial)
{
    int idBuscar;
    printf("Ingrese el ID del artista a modificar: ");
    scanf("%i", &idBuscar);
    int indice = buscarArtistaPorId(arregloArtistas, cantArtistas, idBuscar);
    if (indice == -1)
    {
        printf("No se encontro un artista con ID %i.\n", idBuscar);
        return;
    }
    printf("============================\n");
    printf("|     MODIFICAR ARTISTA    |\n");
    printf("============================\n");
    printf("ID actual     : %i\n", arregloArtistas[indice].id);
    printf("Nombre actual : %s\n", arregloArtistas[indice].nombre);
    printf("Genero actual : %s\n", arregloArtistas[indice].genero);
    printf("============================\n");
    int idOriginal = arregloArtistas[indice].id;
    arregloArtistas[indice] = modificarDatosArtista(arregloArtistas[indice]);
    arregloArtistas[indice].id = idOriginal;
    printf("Artista modificado correctamente.\n");
    apilar(historial, MODIF_ARTISTA);
}

artista modificarDatosArtista(artista a)
{
    int opcionGenero;
    printf("Nombre: ");
    scanf(" ");
    fgets(a.nombre, sizeof(a.nombre), stdin);
    a.nombre[strcspn(a.nombre, "\n")] = '\0';
    do
    {
        printf("\n============================\n");
        printf("|    GENEROS DISPONIBLES   |\n");
        printf("============================\n");
        printf("|  1. Rock                 |\n");
        printf("|  2. Pop                  |\n");
        printf("|  3. Jazz                 |\n");
        printf("|  4. Clasica              |\n");
        printf("|  5. Hip-Hop              |\n");
        printf("|  6. Electronica          |\n");
        printf("|  7. Reggaeton            |\n");
        printf("|  8. Blues                |\n");
        printf("|  9. Metal                |\n");
        printf("|  10. Otro                |\n");
        printf("============================\n");
        printf("Seleccione un genero: ");
        scanf("%i", &opcionGenero);
        if (opcionGenero < 1 || opcionGenero > 10)
            printf("Opcion invalida. Intente nuevamente.\n");
    }
    while (opcionGenero < 1 || opcionGenero > 10);
    switch (opcionGenero)
    {
    case 1:
        strcpy(a.genero, "Rock");
        break;
    case 2:
        strcpy(a.genero, "Pop");
        break;
    case 3:
        strcpy(a.genero, "Jazz");
        break;
    case 4:
        strcpy(a.genero, "Clasica");
        break;
    case 5:
        strcpy(a.genero, "Hip-Hop");
        break;
    case 6:
        strcpy(a.genero, "Electronica");
        break;
    case 7:
        strcpy(a.genero, "Reggaeton");
        break;
    case 8:
        strcpy(a.genero, "Blues");
        break;
    case 9:
        strcpy(a.genero, "Metal");
        break;
    case 10:
        strcpy(a.genero, "Otro");
        break;
    }
    return a;
}

void bajaArtista(artista arregloArtistas[], int cantArtistas, presentacion arrPresentaciones[], int cantPresentaciones, int id, Pila *historial)
{
    int indice = buscarArtistaPorId(arregloArtistas, cantArtistas, id);
    if (indice == -1)
    {
        printf("No se encontro un artista con ID %i.\n", id);
        return;
    }
    if (arregloArtistas[indice].baja == 1)
    {
        printf("El artista '%s' ya esta dado de baja.\n", arregloArtistas[indice].nombre);
        return;
    }
    for (int i = 0; i < cantPresentaciones; i++)
    {
        if (arrPresentaciones[i].idArtista == id && arrPresentaciones[i].baja == 0)
        {
            printf("ERROR: El artista '%s' tiene una presentacion activa.\n", arregloArtistas[indice].nombre);
            printf("No se puede dar de baja.\n");
            return;
        }
    }
    arregloArtistas[indice].baja = 1;
    printf("El artista '%s' fue dado de baja correctamente.\n", arregloArtistas[indice].nombre);
    apilar(historial, BAJA_ARTISTA);
}

void mostrarArtistas(artista arr[], int cant)
{
    printf("============================\n");
    printf("|   LISTADO DE ARTISTAS    |\n");
    printf("============================\n");
    if (cant == 0)
    {
        printf("No hay artistas cargados.\n");
        printf("============================\n");
        return;
    }
    for (int i = 0; i < cant; i++)
    {
        if (arr[i].baja == 0)
        {
            printf("ID: %d | Nombre: %s | Genero: %s\n", arr[i].id, arr[i].nombre, arr[i].genero);
            printf("============================\n");
        }
    }
}

escenario* crearEscenario(escenario *arr, int *cant, Pila *historial)
{
    arr = realloc(arr, (*cant + 1) * sizeof(escenario));
    arr[*cant] = cargaEscenario();
    arr[*cant].id = *cant + 1;
    (*cant)++;
    apilar(historial, ALTA_ESCENARIO);
    return arr;
}

void reasignarPresentaciones(presentacion arrPres[], int cantPres, int idViejo, int idNuevo)
{
    for (int i = 0; i < cantPres; i++)
    {
        if (arrPres[i].idEscenario == idViejo)
            arrPres[i].idEscenario = idNuevo;
    }
}

int escTienePresentaciones(presentacion arrPres[], int cantPres, int idEscenario)
{
    int i = 0;
    while (i < cantPres)
    {
        if (arrPres[i].idEscenario == idEscenario && arrPres[i].baja == 0)
            return 1;
        i++;
    }
    return 0;
}

escenario* borrarEscenario(escenario *arr, int *cant, presentacion arrPres[], int cantPres, int id, Pila *historial)
{
    int encontrado = 0;
    if (escTienePresentaciones(arrPres, cantPres, id))
    {
        printf("\nEl escenario posee presentaciones asociadas.\n");
        printf("Debe crear un nuevo escenario para reasignarlas.\n");
        arr = crearEscenario(arr, cant, historial);
        int idNuevo = arr[*cant - 1].id;
        reasignarPresentaciones(arrPres, cantPres, id, idNuevo);
        printf("\nPresentaciones reasignadas correctamente.\n");
    }
    for (int i = 0; i < *cant; i++)
    {
        if (arr[i].id == id && arr[i].estado == 1)
        {
            arr[i].estado = 0;
            encontrado = 1;
            printf("\nEscenario dado de baja correctamente.\n");
        }
    }
    if (!encontrado)
        printf("== No se encontro el escenario con id %d ==\n", id);
    else
        apilar(historial, BAJA_ESCENARIO);
    return arr;
}

void modificarEscenario(escenario *arr, int cant, int id, Pila *historial)
{
    int encontrado = 0;
    for (int i = 0; i < cant; i++)
    {
        if (arr[i].id == id)
        {
            encontrado = 1;
            printf("============================\n");
            printf("|    MODIFICAR ESCENARIO   |\n");
            printf("============================\n");
            printf("ID actual     : %d\n", arr[i].id);
            printf("Nombre actual : %s\n", arr[i].nombre);
            printf("============================\n");
            int idGuardado = arr[i].id;
            arr[i] = cargaEscenario();
            arr[i].id = idGuardado;
            printf("Escenario modificado correctamente.\n");
            apilar(historial, MODIF_ESCENARIO);
        }
    }
    if (!encontrado)
        printf("== No se encontro el escenario con id %d ==\n", id);
}

void mostrarEscenarios(escenario *arr, int cant)
{
    printf("============================\n");
    printf("|   LISTADO DE ESCENARIOS  |\n");
    printf("============================\n");
    if (cant == 0)
    {
        printf("No hay escenarios cargados.\n");
        printf("============================\n");
        return;
    }
    for (int i = 0; i < cant; i++)
    {
        if (arr[i].estado == 1)
        {
            printf("ID: %d | Nombre: %s\n", arr[i].id, arr[i].nombre);
            printf("============================\n");
        }
    }
}

int aMinutos(horario h)
{
    return h.horas * 60 + h.minutos;
}

int seSolapan(presentacion a, presentacion b)
{
    int inicioA = aMinutos(a.Inicio);
    int finA    = aMinutos(horarioFin(a.Inicio, a.duracionn));
    int inicioB = aMinutos(b.Inicio);
    int finB    = aMinutos(horarioFin(b.Inicio, b.duracionn));
    return (finA > inicioB && finB > inicioA);
}

int hayConflictoEscenario(presentacion nueva, presentacion arr[], int cant)
{
    for (int i = 0; i < cant; i++)
    {
        if (arr[i].idEscenario == nueva.idEscenario && arr[i].baja == 0)
        {
            if (seSolapan(nueva, arr[i]))
                return 1;
        }
    }
    return 0;
}

int hayConflictoArtista(presentacion nueva, presentacion arr[], int cant)
{
    for (int i = 0; i < cant; i++)
    {
        if (arr[i].idArtista == nueva.idArtista && arr[i].baja == 0)
            if (seSolapan(nueva, arr[i]))
                return 1;
    }
    return 0;
}

void agregarPresentacion(presentacion arrPresentaciones[], int *cantPresentaciones, artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios, Pila *historial)
{
    if (*cantPresentaciones >= 40)
    {
        printf("No hay espacio para mas presentaciones.\n");
        return;
    }
    presentacion nueva = cargaPresentacion(*cantPresentaciones, arrArtistas, cantArtistas, arrEscenarios, cantEscenarios);
    if (nueva.id == -1) return;

    if (hayConflictoEscenario(nueva, arrPresentaciones, *cantPresentaciones))
    {
        printf("Error: el escenario ya tiene una presentacion en ese horario.\n");
    }
    else if (hayConflictoArtista(nueva, arrPresentaciones, *cantPresentaciones))
    {
        printf("Error: el artista ya tiene una presentacion en ese horario.\n");
    }
    else
    {
        arrPresentaciones[*cantPresentaciones] = nueva;
        (*cantPresentaciones)++;
        printf("Presentacion agregada correctamente.\n");
        apilar(historial, ALTA_PRESENTACION);
    }
}

void modificarPresentacion(presentacion arrPresentaciones[], int cantPresentaciones, artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios, Pila *historial)
{
    int idBuscar;
    int indice;
    do
    {
        printf("Ingrese el ID de la presentacion a modificar: ");
        scanf("%i", &idBuscar);
        indice = buscarPresentacionPorId(arrPresentaciones, cantPresentaciones, idBuscar);
        if (indice == -1)
            printf("No se encontro una presentacion con ID %i. Intente nuevamente.\n", idBuscar);
    }
    while (indice == -1);
    printf("============================\n");
    printf("|  MODIFICAR PRESENTACION  |\n");
    printf("============================\n");
    printf("ID actual        : %i\n", arrPresentaciones[indice].id);
    printf("ID Artista actual: %i\n", arrPresentaciones[indice].idArtista);
    printf("ID Escenario act.: %i\n", arrPresentaciones[indice].idEscenario);
    printf("Inicio actual    : %02i:%02i\n", arrPresentaciones[indice].Inicio.horas, arrPresentaciones[indice].Inicio.minutos);
    printf("Duracion actual  : %02i:%02i\n", arrPresentaciones[indice].duracionn.horas, arrPresentaciones[indice].duracionn.minutos);
    printf("============================\n");
    int idOriginal = arrPresentaciones[indice].id;
    arrPresentaciones[indice] = cargaPresentacion(cantPresentaciones, arrArtistas, cantArtistas, arrEscenarios, cantEscenarios);
    arrPresentaciones[indice].id = idOriginal;
    printf("Presentacion modificada correctamente.\n");
    apilar(historial, MODIF_PRESENTACION);
}

void bajaPresentacion(presentacion arrPresentaciones[], int cantPresentaciones, artista arrArtistas[], int cantArtistas, Pila *historial)
{
    int id;
    int indice;
    do
    {
        printf("Ingrese el ID de la presentacion a dar de baja: ");
        scanf("%i", &id);
        indice = buscarPresentacionPorId(arrPresentaciones, cantPresentaciones, id);
        if (indice == -1)
            printf("No se encontro una presentacion con ID %i. Intente nuevamente.\n", id);
    }
    while (indice == -1);
    if (arrPresentaciones[indice].baja == 1)
    {
        printf("La presentacion con ID %i ya esta dada de baja.\n", id);
        return;
    }
    int idArtista = arrPresentaciones[indice].idArtista;
    arrPresentaciones[indice].baja = 1;
    int tienePresentaciones = 0;
    for (int i = 0; i < cantPresentaciones; i++)
    {
        if (arrPresentaciones[i].idArtista == idArtista && arrPresentaciones[i].baja == 0)
        {
            tienePresentaciones = 1;
            break;
        }
    }
    if (!tienePresentaciones)
    {
        int indiceArtista = buscarArtistaPorId(arrArtistas, cantArtistas, idArtista);
        if (indiceArtista != -1)
            arrArtistas[indiceArtista].baja = 1;
        printf("El artista asociado no tiene mas presentaciones activas y fue dado de baja.\n");
    }
    printf("Presentacion dada de baja correctamente.\n");
    apilar(historial, BAJA_PRESENTACION);
}

void mostrarPresentaciones(presentacion arrPres[], int cantPres, artista arrArt[], int cantArt, escenario arrEsc[], int cantEsc)
{
    printf("\n=======================================================\n");
    printf(" LISTADO DE PRESENTACIONES\n");
    printf("=======================================================\n");
    if (cantPres == 0)
    {
        printf("No hay presentaciones cargadas.\n");
        printf("=======================================================\n");
        return;
    }
    for (int i = 0; i < cantPres; i++)
    {
        if (arrPres[i].baja == 0)
        {
            int posArtista   = buscarArtistaPorId(arrArt, cantArt, arrPres[i].idArtista);
            int posEscenario = buscarEscenarioPorId(arrEsc, cantEsc, arrPres[i].idEscenario);
            printf("\nID Presentacion: %d\n", arrPres[i].id);
            if (posArtista != -1)
                printf("Artista: %s\n", arrArt[posArtista].nombre);
            if (posEscenario != -1)
                printf("Escenario: %s\n", arrEsc[posEscenario].nombre);
            printf("Inicio: %02d:%02d\n", arrPres[i].Inicio.horas, arrPres[i].Inicio.minutos);
            printf("Duracion: %02d:%02d\n", arrPres[i].duracionn.horas, arrPres[i].duracionn.minutos);
        }
    }
    printf("=======================================================\n");
}

int buscarEscenarioPorId(escenario arrEsc[], int cantEsc, int id)
{
    for (int i = 0; i < cantEsc; i++)
    {
        if (arrEsc[i].id == id && arrEsc[i].estado == 1)
            return i;
    }
    return -1;
}

void mostrarPresentacionesArtista(presentacion arrPres[], int cantPres, int idArtista, artista arrArt[], int cantArt, escenario arrEsc[], int cantEsc)
{
    int encontrado = 0;
    int posArtista = buscarArtistaPorId(arrArt, cantArt, idArtista);
    if (posArtista == -1)
    {
        printf("\n=============================================\n");
        printf(" Error: No existe el artista con ID %d.\n", idArtista);
        printf("=============================================\n");
        return;
    }
    printf("\n=======================================================\n");
    printf(" PRESENTACIONES PARA EL ARTISTA: %s\n", arrArt[posArtista].nombre);
    printf("=======================================================\n");
    for (int i = 0; i < cantPres; i++)
    {
        if (arrPres[i].idArtista == idArtista && arrPres[i].baja == 0)
        {
            encontrado = 1;
            int posEscenario = buscarEscenarioPorId(arrEsc, cantEsc, arrPres[i].idEscenario);
            printf("\nID Presentacion: %d\n", arrPres[i].id);
            if (posEscenario != -1)
                printf("Escenario: %s\n", arrEsc[posEscenario].nombre);
            printf("Inicio: %02d:%02d\n", arrPres[i].Inicio.horas, arrPres[i].Inicio.minutos);
            printf("Duracion: %02d:%02d\n", arrPres[i].duracionn.horas, arrPres[i].duracionn.minutos);
        }
    }
    if (!encontrado)
        printf("El artista no posee presentaciones.\n");
    printf("=======================================================\n");
}

void mostrarPresentacionesEscenario(presentacion arrPres[], int cantPres, artista arrArt[], int cantArt, escenario arrEsc[], int cantEsc, int idEscenario)
{
    int encontrado = 0;
    int posEscenario = buscarEscenarioPorId(arrEsc, cantEsc, idEscenario);
    if (posEscenario == -1)
    {
        printf("\n=============================================\n");
        printf(" Error: No existe el escenario con ID %d.\n", idEscenario);
        printf("=============================================\n");
        return;
    }
    printf("\n=======================================================\n");
    printf(" PRESENTACIONES EN EL ESCENARIO: %s \n", arrEsc[posEscenario].nombre);
    printf("=======================================================\n");
    for (int i = 0; i < cantPres; i++)
    {
        if (arrPres[i].idEscenario == idEscenario && arrPres[i].baja == 0)
        {
            encontrado = 1;
            int posArtista = buscarArtistaPorId(arrArt, cantArt, arrPres[i].idArtista);
            printf("\nID Presentacion: %d\n", arrPres[i].id);
            if (posArtista != -1)
                printf("Artista: %s\n", arrArt[posArtista].nombre);
            else
                printf("Artista ID: %d\n", arrPres[i].idArtista);
            printf("Inicio: %02d:%02d\n", arrPres[i].Inicio.horas, arrPres[i].Inicio.minutos);
            printf("Duracion: %02d:%02d\n", arrPres[i].duracionn.horas, arrPres[i].duracionn.minutos);
        }
    }
    if (!encontrado)
        printf("No hay presentaciones para este escenario.\n");
    printf("=======================================================\n");
}

void ordenarArtistasPorNombre(artista arr[], int cant)
{
    int minIdx;
    for (int i = 0; i < cant - 1; i++)
    {
        minIdx = i;
        for (int j = i + 1; j < cant; j++)
        {
            if (strcmp(arr[minIdx].nombre, arr[j].nombre) > 0)
                minIdx = j;
        }
        artista temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

void ordenarEscenariosPorNombre(escenario arr[], int cant)
{
    int minIdx;
    for (int i = 0; i < cant - 1; i++)
    {
        minIdx = i;
        for (int j = i + 1; j < cant; j++)
        {
            if (strcmp(arr[minIdx].nombre, arr[j].nombre) > 0)
                minIdx = j;
        }
        escenario temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

void ordenarPresentacionesPorNombre(presentacion arr[], int cant, artista arrArt[], int cantArt)
{
    int minIdx;
    for (int i = 0; i < cant - 1; i++)
    {
        minIdx = i;
        for (int j = i + 1; j < cant; j++)
        {
            int idxA = buscarArtistaPorId(arrArt, cantArt, arr[minIdx].idArtista);
            int idxB = buscarArtistaPorId(arrArt, cantArt, arr[j].idArtista);
            if (idxA != -1 && idxB != -1 && strcmp(arrArt[idxA].nombre, arrArt[idxB].nombre) > 0)
                minIdx = j;
        }
        presentacion temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

void guardarTodo(artista arrArtistas[], int cantArtistas, escenario arrEscenarios[], int cantEscenarios, presentacion arrPresentaciones[], int cantPresentaciones)
{
    ordenarArtistasPorNombre(arrArtistas, cantArtistas);
    ordenarEscenariosPorNombre(arrEscenarios, cantEscenarios);
    ordenarPresentacionesPorNombre(arrPresentaciones, cantPresentaciones, arrArtistas, cantArtistas);

    FILE *f = fopen(nombre_arch, "wb");
    if (f == NULL)
    {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    fwrite(&cantArtistas, sizeof(int), 1, f);
    fwrite(arrArtistas, sizeof(artista), cantArtistas, f);
    fwrite(&cantEscenarios, sizeof(int), 1, f);
    fwrite(arrEscenarios, sizeof(escenario), cantEscenarios, f);
    fwrite(&cantPresentaciones, sizeof(int), 1, f);
    fwrite(arrPresentaciones, sizeof(presentacion), cantPresentaciones, f);
    fclose(f);
    printf("Datos guardados correctamente.\n");
}

escenario* cargarTodo(artista arrArtistas[], int *cantArtistas, escenario **arrEscenarios, int *cantEscenarios, presentacion arrPresentaciones[], int *cantPresentaciones)
{
    FILE *f = fopen(nombre_arch, "rb");
    if (f == NULL)
    {
        *cantArtistas = 0;
        *cantEscenarios = 0;
        *cantPresentaciones = 0;
        return *arrEscenarios;
    }
    fread(cantArtistas, sizeof(int), 1, f);
    fread(arrArtistas, sizeof(artista), *cantArtistas, f);
    fread(cantEscenarios, sizeof(int), 1, f);
    *arrEscenarios = realloc(*arrEscenarios, *cantEscenarios * sizeof(escenario));
    fread(*arrEscenarios, sizeof(escenario), *cantEscenarios, f);
    fread(cantPresentaciones, sizeof(int), 1, f);
    fread(arrPresentaciones, sizeof(presentacion), *cantPresentaciones, f);
    fclose(f);
    printf("Datos cargados correctamente.\n");
    return *arrEscenarios;
}
