#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int max_jugador;

	
	char consulta [200];
	char nombre[60];
	strcpy (nombre, "'Maria'");
	// reamos una conexion al servidor MYSQL 
	conn= mysql_init(NULL);
	if (conn==NULL)  {
		printf ("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	

	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "bdFireWater",0, NULL, 0);
	if (conn==NULL)  {
		printf ("Error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}


	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	strcpy(consulta, "SELECT MAX(historial.puntos) FROM (jugador, historial) WHERE historial.id_j= (SELECT jugador.id FROM (jugador) WHERE jugador.username = ");
	strcat(consulta, nombre);
	strcat(consulta, ");");

	err = mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	resultado = mysql_store_result (conn);
	
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco. 
	

	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row (resultado);

	// En una fila hay tantas columnas como datos tiene una
	// persona. En nuestro caso hay tres columnas: dni(row[0]),
	// nombre(row[1]) y edad (row[2]).
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
	{
		while (row !=NULL) {
			// la columna 2 contiene una palabra que es la edad
			// la convertimos a entero 
			max_jugador = atoi (row[0]);
			// las columnas 0 y 1 contienen DNI y nombre 
			printf("La maxima puntuacion de Maria es: %d\n", max_jugador);
		
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
			
		}
	}
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
}