/*
Estudiantes:
            Fabricio Solano Rojas B77447.
            Miguel Zamora Torres B78542.

Este programa permite crear una interfaz gráfica que representa
un juego de gato, en la interfaz se presenta 10 botones, un botón
de reinicio y 9 botones que representan el tablero del juego. Hay
dos jugadores, uno usa el caracter 'X' y el otro el caracter 'O',
el primer caracter se escoge de manera aleatoria.
*/

// Biblioteca que utiliza la herramienta gtk para crear la interfaz
#include <gtk/gtk.h>
// Biblioteca de uso general, por ejemplo para crear numeros aleatorios
#include <stdlib.h>
// Biblioteca para utilizar variables boolenadas
#include <stdbool.h>

char get_state(char (*matriz)[3]) {
  /*
  Esta función devuelve el estado del juego
  */

  // Esta variable boolena permite comprobar si hay un ganador
  bool sinGanador = true;
  // Esta variable representa el estado del juego, vacio para pendiente,
  // caracter 'E' para empate, caracter 'X' ganador X y caracter 'O' ganador O
  char estado = ' ';

  // Se verifica si hay un ganador al revisar las filas
  if (sinGanador) {
    for (int i=0; i<3; i++) {
      // Contador de filas
      int contFilaX = 0;
      int contFilaO = 0;

      for (int j=0; j<3; j++) {
        // Revision de filas
        if (matriz[i][j] == 'X') {
          contFilaX = contFilaX + 1;
        } else if (matriz[i][j] == 'O') {
          contFilaO = contFilaO + 1;
        }
      }
      // Si el contador es 3 significa que hay un ganador
      if (contFilaX == 3) {
        estado = 'X';
        sinGanador = false;
        break;
      } else if (contFilaO == 3) {
        estado = 'O';
        sinGanador = false;
        break;
      }
    }
  };
  // Se verifica si hay un ganador al revisar las columnas
  if (sinGanador) {
    for (int i=0; i<3; i++) {
      // Contador de columnas
      int contColX = 0;
      int contColO = 0;

      for (int j=0; j<3; j++) {
        // Revisión de columnas
        if (matriz[j][i] == 'X') {
          contColX = contColX + 1;
        } else if (matriz[j][i] == 'O') {
          contColO = contColO + 1;
        }
      }
      // Si el contador es 3 significa que hay un ganador
      if (contColX == 3) {
        estado = 'X';
        sinGanador = false;
        break;
      } else if (contColO == 3) {
        estado = 'O';
        sinGanador = false;
        break;
      }
    }
  };
  // Se verifica si hay un ganador al revisar las dos diagonales
  if (sinGanador) {
    // contador diagonal 1
    int contDiagX1 = 0;
    int contDiagO1 = 0;
    // contador diagonal 2
    int contDiagX2 = 0;
    int contDiagO2 = 0;

    for (int i=0; i<3; i++) {
      // Revisión diagonal 1
      if (matriz[i][i] == 'X') {
        contDiagX1 = contDiagX1 + 1;
      } else if (matriz[i][i] == 'O') {
        contDiagO1 = contDiagO1 + 1;
      }
      // Revisión diagonal 2
      if (matriz[i][2-i] == 'X') {
        contDiagX2 = contDiagX2 + 1;
      } else if (matriz[i][2-i] == 'O') {
        contDiagO2 = contDiagO2 + 1;
      }
    }
    // Si el contador es 3 significa que hay un ganador
    if (contDiagX1 == 3) {
      estado = 'X';
      sinGanador = false;
    } else if (contDiagO1 == 3) {
      estado = 'O';
      sinGanador = false;
    } else if (contDiagX2 == 3) {
      estado = 'X';
      sinGanador = false;
    } else if (contDiagO2 == 3) {
      estado = 'O';
      sinGanador = false;
    }
  };
  // Se verifica si hay un empate
  if (sinGanador) {
    // Contador de espacios vacíos
    int contVacio = 0;
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
        if (matriz[i][j] == '-') {
          contVacio = contVacio + 1;
        }
      }
    }
    // Si el contador es 0 significa que hay un empate
    if (contVacio == 0) {
      estado = 'E';
      sinGanador = false;
    }
  };
  // Se retorna el estado del juego
  return estado;

}

struct datos {
  /*
  Se crea una estructura con diferentes tipos de datos a partir
  de sus punteros, los cuales son comunes y se pueden modificar
  en las funciones on_button_clicked y restart
  */

  GtkWidget *label;
  char (*matriz)[3];
  GtkWidget *(*botones)[3];
  int *pjugador;
  bool *pseguirJuego;
};


void on_button_clicked(GtkWidget *widget, struct datos *iniciales) {
  /*
  Esta función permite que cuando se haga click en los botones
  se muestre el caracter respectivo, también permite que los
  caracteres se turnen al hacer click a botones seguidos
  */
  GtkLabel *label = (GtkLabel*) iniciales->label;

  char (*matriz)[3];
  matriz = iniciales->matriz;

  GtkWidget *(*botones)[3];
  botones = iniciales->botones;

  int *pjugador;
  pjugador = iniciales->pjugador;

  bool *pseguirJuego;
  pseguirJuego = iniciales->pseguirJuego;

  // Estas variables permiten obtener la posición actual de la
  // matriz del botón clickeado
  int fila;
  int colum;
  // Se revisa cual botón fue clickeado
  for(int a=0; a<3; a++) {
    for(int b=0; b<3; b++) {
      // Se obtiene el botón clickeado
      if (widget == botones[a][b]) {
        fila = a;
        colum = b;
        break;
      }
    }
  };
  // Se imprime los posiciones del botón clickeado
  printf("fila: %d y columna: %d\n", fila, colum);

  // Se sustituye el caracter 'X' o 'O' al botón clickeado,
  // si *pjugador es 1 el caracter asignado es 'X',
  // si *pjugador es 2 el caracter asignado es 'O'
  if (*pjugador == 1 && matriz[fila][colum] == '-' && *pseguirJuego) {
    // Se cambia el valor de *pjugador a 2 para que el próximo botón
    // clickeado se asigne el caracter 'O'
    *pjugador = 2;
    // Se asigna el caracter 'X' a la matriz de referencia
    matriz[fila][colum] = 'X';
    // Caracter 'X' que se mostrará en el botón
    char *caracter = g_strdup_printf (
                                        "<span font=\"40\" color=\"blue\">"
                                        "<b>%s</b>"
                                        "</span>",
                                        "X"
                                      );
      // Se obtiene el widget del botón
      GtkButton *boton = (GtkButton*) widget;
      // Se obtiene el ID del botón
      GtkLabel *boton_ID =(GtkLabel*) gtk_bin_get_child(GTK_BIN(boton));
      // Se sustituye el caracter en el botón
      gtk_label_set_markup (GTK_LABEL (boton_ID), caracter);
      // Se libera la memoría del caracter creado
      g_free (caracter);

      // Se obtiene el estado actual del juego
      char estadoActual = get_state(matriz);

      // Si el estado actual es un empate, ganador jugador X
      // o ganador jugador O, se muestra el estado y se termina el juego
      if (estadoActual == 'E') {
        gtk_label_set_text(label, "Empate");
        *pseguirJuego = false;
      } else if (estadoActual == 'X') {
        gtk_label_set_text(label, "Ganador: Jugador X");
        *pseguirJuego = false;
      } else if (estadoActual == 'O') {
        gtk_label_set_text(label, "Ganador: Jugador O");
        *pseguirJuego = false;
      };


  } else if (*pjugador == 2 && matriz[fila][colum] == '-' && *pseguirJuego) {
    // Se cambia el valor de *pjugador a 1 para que el próximo botón
    // clickeado se asigne el caracter 'X'
    *pjugador = 1;
    // Se asigna el caracter 'O' a la matriz de referencia
    matriz[fila][colum] = 'O';
    // Caracter 'O' que se mostrará en el botón
    char *caracter = g_strdup_printf (
                                        "<span font=\"40\" color=\"green\">"
                                        "<b>%s</b>"
                                        "</span>",
                                        "O"
                                      );
      // Se obtiene el widget del botón
      GtkButton *boton = (GtkButton*) widget;
      // Se obtiene el ID del botón
      GtkLabel *boton_ID =(GtkLabel*) gtk_bin_get_child(GTK_BIN(boton));
      // Se sustituye el caracter en el botón
      gtk_label_set_markup (GTK_LABEL (boton_ID), caracter);
      // Se libera la memoría del caracter creado
      g_free (caracter);

      // Se obtiene el estado actual del juego
      char estadoActual = get_state(matriz);

      // Si el estado actual es un empate, ganador jugador X
      // o ganador jugador O, se muestra el estado y se termina el juego
      if (estadoActual == 'E') {
        gtk_label_set_text(label, "Empate");
        *pseguirJuego = false;
      } else if (estadoActual == 'X') {
        gtk_label_set_text(label, "Ganador: Jugador X");
        *pseguirJuego = false;
      } else if (estadoActual == 'O') {
        gtk_label_set_text(label, "Ganador: Jugador O");
        *pseguirJuego = false;
      }

  };

  // Se imprime la matriz de referencia
  for(int i=0; i<3; ++i) {
    for(int j=0; j<3; ++j){
      printf("[%c]", matriz[i][j]);
    }
    printf("\n");
  };

};

void restart(GtkWidget *widget, struct datos *iniciales) {
  /*
  Esta función permite que al hacer click en el botón reiniciar,
  los diferentes datos comunes vuelven a los valores iniciales
  */
  GtkLabel *label = (GtkLabel*) iniciales->label;

  char (*matriz)[3];
  matriz = iniciales->matriz;

  GtkWidget *(*botones)[3];
  botones = iniciales->botones;

  int *pjugador;
  pjugador = iniciales->pjugador;

  bool *pseguirJuego;
  pseguirJuego = iniciales->pseguirJuego;

  // El estado mostrado en la interfaz vuelve a vacío
  gtk_label_set_text(label, " ");
  // Caracter vacío que se mostrará en cada botón
  char *caracter = g_strdup_printf (
                                      "<span font=\"40\" color=\"blue\">"
                                      "<b>%s</b>"
                                      "</span>",
                                      " "
                                    );
  // La matriz de referencia y caracter de los botones vuleven al estado
  // inicial, también imprime la matriz de referencia
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++){
      matriz[i][j] = '-';
      printf("[%c]", matriz[i][j]);
      GtkButton *boton = (GtkButton*) botones[i][j];
      GtkLabel *boton_ID =(GtkLabel*) gtk_bin_get_child(GTK_BIN(boton));
      gtk_label_set_markup (GTK_LABEL (boton_ID), caracter);
    }
    printf("\n");
  }

  // Se estable un valor aleatorio para la variable jugador
  // 1 representa caracter 'X' y 2 representa caracter 'O'
  int jugador;
  jugador = 1 + rand() % 2;
  *pjugador = jugador;

  // Se establece el valor inicial de seguirJuego
  *pseguirJuego = true;


}

// -----------------------------------------------
int main(int argc, char* argv[]) {
  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *botones[3][3];
  GtkWidget *botonReiniciar;
  GtkWidget *label;

  // Variable booleana que permite seguir juegando
  bool seguirJuego = true;
  bool *pseguirJuego = &seguirJuego;

  // Variable que permite cual caracter utilizar al inicio del juego,
  // por medio del valor aleaotrio entre 1 y 2, donde 1 -> 'X 'y 2 -> 'O'
  srand (time(NULL));
  int jugador;
  jugador = 1 + rand() % 2;
  int *pjugador = &jugador;

  // Matriz de caracteres de referecnia
  // lleva las posiciones de los caracteres 'X' y 'O' durante el juego
  char matriz[3][3];
  // Se imprime matriz de referecnia
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++){
      matriz[i][j] = '-';
      printf("[%c]", matriz[i][j]);
    }
    printf("\n");
  }


  gtk_init(&argc, &argv);

  // Se define el builder utilizadno la base de la interfaz de glade
  builder = gtk_builder_new_from_file("template.glade");
  // Se obtiene la ventana de la interfaz
  window = GTK_WIDGET(
    gtk_builder_get_object(builder, "main_window")
  );
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Se obtiene todos los widgets utilizandos cada ID
  botonReiniciar = GTK_WIDGET(gtk_builder_get_object(builder, "button_1"));
  botones[0][0] = GTK_WIDGET(gtk_builder_get_object(builder, "button_2"));
  botones[0][1] = GTK_WIDGET(gtk_builder_get_object(builder, "button_3"));
  botones[0][2] = GTK_WIDGET(gtk_builder_get_object(builder, "button_4"));
  botones[1][0] = GTK_WIDGET(gtk_builder_get_object(builder, "button_5"));
  botones[1][1] = GTK_WIDGET(gtk_builder_get_object(builder, "button_6"));
  botones[1][2] = GTK_WIDGET(gtk_builder_get_object(builder, "button_7"));
  botones[2][0] = GTK_WIDGET(gtk_builder_get_object(builder, "button_8"));
  botones[2][1] = GTK_WIDGET(gtk_builder_get_object(builder, "button_9"));
  botones[2][2] = GTK_WIDGET(gtk_builder_get_object(builder, "button_10"));
  label = GTK_WIDGET(gtk_builder_get_object(builder, "label_2"));

  // Se define la estructura con los datos iniciales
  struct datos iniciales = {
    .label = label,
    .matriz = matriz,
    .botones = botones,
    .pjugador = pjugador,
    .pseguirJuego = pseguirJuego
  };

  // Se define la función asociada a cada botón cuando se presente
  // un click y se pasa los datos iniciales por medio del struct
  g_signal_connect(
                    botonReiniciar,
                    "clicked",
                    G_CALLBACK(restart),
                    &iniciales
                  );
  g_signal_connect(
                    botones[0][0],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );
  g_signal_connect(
                    botones[0][1],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );
  g_signal_connect(
                    botones[0][2],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );
  g_signal_connect(
                    botones[1][0],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );
  g_signal_connect(
                    botones[1][1],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );
  g_signal_connect(
                    botones[1][2],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );
  g_signal_connect(
                   botones[2][0],
                   "clicked",
                   G_CALLBACK(on_button_clicked),
                   &iniciales
                 );
  g_signal_connect(
                    botones[2][1],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );
  g_signal_connect(
                    botones[2][2],
                    "clicked",
                    G_CALLBACK(on_button_clicked),
                    &iniciales
                  );


  // Se ejecuta el ciclo principal de GTK
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
