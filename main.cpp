#include <iostream>
#include <mysql.h>
#include <string>
#include <iomanip>
#include "db_config.h"

using namespace std;
struct Alumno {
    int id;
    string nombre;
    string apellido;
    string celular;
    double nota_final;
    string estado;
};

void buscarAlumno(MYSQL* conn) {
    int id;
    cout << "\nIngrese el ID del alumno: "; cin >> id;
    string query = "SELECT * FROM alumnos WHERE id = " + to_string(id);
    
    if (mysql_query(conn, query.c_str())) return;
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);

    if (row) {
        Alumno al = {stoi(row[0]), row[1], row[2], row[3], stod(row[4]), row[5]};
        cout << "\n--- FICHA DEL ALUMNO ---" << endl;
        cout << "Nombre Completo: " << al.nombre << " " << al.apellido << endl;
        cout << "Celular: " << al.celular << endl;
        cout << "Promedio Actual: " << al.nota_final << endl;
        cout << "Estado: " << al.estado << endl;
    } else {
        cout << "ID no encontrado." << endl;
    }
    mysql_free_result(res);
}

void mostrarRanking(MYSQL* conn, bool cuadroHonor) {

    string query = cuadroHonor ? 
        "SELECT nombre, apellido, nota_final FROM alumnos ORDER BY nota_final DESC LIMIT 5" :
        "SELECT nombre, apellido, nota_final FROM alumnos WHERE nota_final < 5";

    if (mysql_query(conn, query.c_str())) return;
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << (cuadroHonor ? "\n--- CUADRO DE HONOR (TOP 5) ---" : "\n--- ALUMNOS REPROBADOS ---") << endl;
    while ((row = mysql_fetch_row(res))) {
        cout << left << setw(20) << (string(row[0]) + " " + row[1]) << " | Nota: " << row[2] << endl;
    }
    mysql_free_result(res);
}

void actualizarDatos(MYSQL* conn, int tipo) {
    int id;
    cout << "\nID del alumno a modificar: "; cin >> id;
    
    if (tipo == 1) { 
        double nuevaNota;
        cout << "Nueva nota final: "; cin >> nuevaNota;
        
        string nuevoEstado = (nuevaNota >= 5.0) ? "Aprobado" : "Reprobado";

        string query = "UPDATE alumnos SET nota_final = " + to_string(nuevaNota) + 
                       ", estado = '" + nuevoEstado + "' WHERE id = " + to_string(id);
        
        if (!mysql_query(conn, query.c_str())) {
            cout << "Nota actualizada. El alumno ahora esta: " << nuevoEstado << endl;
        } else {
            cout << "Error al actualizar nota: " << mysql_error(conn) << endl;
        }
    } 
    else { 
        string nuevoCel;
        cout << "Nuevo numero de celular: "; cin >> nuevoCel;
        string query = "UPDATE alumnos SET celular = '" + nuevoCel + "' WHERE id = " + to_string(id);
        
        if (!mysql_query(conn, query.c_str())) {
            cout << "Celular actualizado con exito." << endl;
        } else {
            cout << "Error al actualizar celular: " << mysql_error(conn) << endl;
        }
    }
}

int main() {
    MYSQL* conn = mysql_init(0);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0)) {
        cout << "Fallo de conexion: " << mysql_error(conn) << endl;
        return 1;
    }

    int opcion;
    do {
        cout << "\n========= GESTION ACADEMICA (SOLO APROB/REPROB) =========" << endl;
        cout << "1. Buscar Alumno (Ficha)" << endl;
        cout << "2. Cuadro de Honor (Top 5)" << endl;
        cout << "3. Ver Alumnos Reprobados (Nota < 5)" << endl;
        cout << "4. Actualizar Nota (Calcula Estado Auto)" << endl;
        cout << "5. Cambiar Celular" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione: "; cin >> opcion;

        switch(opcion) {
            case 1: buscarAlumno(conn); break;
            case 2: mostrarRanking(conn, true); break;
            case 3: mostrarRanking(conn, false); break;
            case 4: actualizarDatos(conn, 1); break;
            case 5: actualizarDatos(conn, 2); break;
        }
    } while (opcion != 6);

    mysql_close(conn);
    return 0;
}