#include <iostream>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace std;

void buscarAlumno(sql::Connection* con) {
    int id;

    cout << "Ingrese ID: ";
    cin >> id;

    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("SELECT * FROM alumnos WHERE id = ?")
    );

    pstmt->setInt(1, id);

    unique_ptr<sql::ResultSet> res(
        pstmt->executeQuery()
    );

    if (res->next()) {
        cout << "\n--- Alumno ---\n";
        cout << "Nombre: "
             << res->getString("nombre") << " "
             << res->getString("apellido") << endl;

        cout << "Celular: "
             << res->getString("celular") << endl;

        cout << "Nota: "
             << res->getDouble("nota_final") << endl;
    } else {
        cout << "No encontrado.\n";
    }
}

void cuadroHonor(sql::Connection* con) {
    unique_ptr<sql::Statement> stmt(
        con->createStatement()
    );

    unique_ptr<sql::ResultSet> res(
        stmt->executeQuery(
            "SELECT * FROM alumnos "
            "ORDER BY nota_final DESC LIMIT 5"
        )
    );

    cout << "\n--- Cuadro de Honor ---\n";

    while (res->next()) {
        cout << res->getString("nombre") << " "
             << res->getString("apellido")
             << " - Nota: "
             << res->getDouble("nota_final")
             << endl;
    }
}

void alumnosRiesgo(sql::Connection* con) {
    unique_ptr<sql::Statement> stmt(
        con->createStatement()
    );

    unique_ptr<sql::ResultSet> res(
        stmt->executeQuery(
            "SELECT * FROM alumnos WHERE nota_final < 4"
        )
    );

    cout << "\n--- Alumnos en Riesgo ---\n";

    while (res->next()) {
        cout << res->getString("nombre") << " "
             << res->getString("apellido")
             << " - Nota: "
             << res->getDouble("nota_final")
             << endl;
    }
}

void actualizarNota(sql::Connection* con) {
    int id;
    double nuevaNota;

    cout << "ID del alumno: ";
    cin >> id;

    cout << "Nueva nota: ";
    cin >> nuevaNota;

    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement(
            "UPDATE alumnos SET nota_final = ? WHERE id = ?"
        )
    );

    pstmt->setDouble(1, nuevaNota);
    pstmt->setInt(2, id);

    int filas = pstmt->executeUpdate();

    cout << "Filas afectadas: "
         << filas << endl;
}

void actualizarCelular(sql::Connection* con) {
    int id;
    string celular;

    cout << "ID del alumno: ";
    cin >> id;

    cout << "Nuevo celular: ";
    cin >> celular;

    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement(
            "UPDATE alumnos SET celular = ? WHERE id = ?"
        )
    );

    pstmt->setString(1, celular);
    pstmt->setInt(2, id);

    int filas = pstmt->executeUpdate();

    cout << "Filas afectadas: "
         << filas << endl;
}

int main() {
    try {
        sql::mysql::MySQL_Driver* driver;
        unique_ptr<sql::Connection> con;

        driver = sql::mysql::get_mysql_driver_instance();

        con.reset(
            driver->connect(
                "tcp://127.0.0.1:3306",
                "root",
                "TU_PASSWORD"
            )
        );

        con->setSchema("nexus_academy");

        int opcion;

        do {
            cout << "\n===== NEXUS ACADEMY =====\n";
            cout << "1. Buscar alumno\n";
            cout << "2. Cuadro de honor\n";
            cout << "3. Alumnos en riesgo\n";
            cout << "4. Actualizar nota\n";
            cout << "5. Actualizar celular\n";
            cout << "0. Salir\n";
            cout << "Opcion: ";

            cin >> opcion;

            switch (opcion) {
                case 1:
                    buscarAlumno(con.get());
                    break;

                case 2:
                    cuadroHonor(con.get());
                    break;

                case 3:
                    alumnosRiesgo(con.get());
                    break;

                case 4:
                    actualizarNota(con.get());
                    break;

                case 5:
                    actualizarCelular(con.get());
                    break;

                case 0:
                    cout << "Saliendo...\n";
                    break;

                default:
                    cout << "Opcion invalida\n";
            }

        } while (opcion != 0);

    } catch (sql::SQLException &e) {
        cout << "Error: "
             << e.what() << endl;
    }

    return 0;
}