//conexion a base de datos.cpp : this file contain the 'main' funtion. Program execution begins and ends there. 
// 

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>

using namespace std;

int main() {
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLRETURN ret;

	//asignar un gestor de entorno 
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

	// asignar un gestor de conexion 
	ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	// conectarse a la base de datos 
	ret = SQLConnect(hDbc, (SQLWCHAR*)L"actividad 2", SQL_NTS, (SQLWCHAR*)L"username", SQL_NTS, (SQLWCHAR*)L"password", SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		cout << "conectado a la base de datos exitosamente" << endl;
		

		//ejemplo de consulta
		SQLHSTMT hStmt;
		ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

		cout << "+---------------------+----------------------+------------------------------+" << endl;
		cout << "| NO. Empleado        " << "| Nombre               " << "|  Apellido paterno            |" << endl;
		cout << "+---------------------+----------------------+------------------------------+" << endl;

		//ejemplo de consulta select 
		ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"select * from datos_empleados", SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			int num_empleado;
			SQLCHAR name[255];
			SQLCHAR last_name[255];
						
			while (SQLFetch(hStmt) == SQL_SUCCESS) {
				SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
				SQLGetData(hStmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
				SQLGetData(hStmt, 3, SQL_C_CHAR, last_name, sizeof(last_name), NULL);
							
				cout << "|        " << num_empleado << "            |" << name << "                  |" << last_name << "                      |" << endl;
			}


		}
		// liberar el manejador	de conexion 
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		cout << "fallo la conexion a la base de datos" << endl;

	}
	//desconectar y liberar gestores de entorno 
	SQLDisconnect(hEnv);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	
	return 0;


}