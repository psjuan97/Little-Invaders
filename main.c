// Juego creado por: PsJuan


#include "gfx.h"  // Libreria GFX
#include <cmath> // Para calcular el modulo del vector(colisiones)
#include <cstdlib> // RAND();
#include <iostream>
#include <unistd.h> // usleep();

using namespace std;


// Constantes usadas
const float Kenemy_velocity = 0.5;


//---------------------------- Declaramos estructura y definimos tipos de datos -----------------------

typedef struct {
		char type; // tipo de enemigo
		int life; // vida del enemigo
		float pos_x; // posicion x del enemigo
		float pos_y; // posicion y del enemigo
		float bala[]; // posiciones xy de las balas de los enemigos
}Tfiguras_str;


typedef Tfiguras_str Tfiguras_list[30];




//-------------------------Funcion shot() ------------------
// La funcion shot se encarga de generar una bala, cuando ya no hay otra en la ventana, desde la posicion del jugador

void shot(int x, int y,int mis_balas[], int &n_balas){
	if(n_balas == 0){ // si no existe bala... la creamos en as cordenadas del jugador
		mis_balas[0]=x;
		mis_balas[1]=y;
		n_balas = 1;
	}
}



//-------------------- Funcion bullet() -----------------------------------
//esta funcion se ocupa de generar las balas de los enemigos, en este caso dos. Se basan en una propabilidad del 5%
// para generarse, de esta forma aumentamos el dinamismo del juego y que no sea igual en todas las partidas
void bullet(Tfiguras_list figuras, int i, int n){
	if(rand()%100 < 5 ){ // solo se ejecutara el 5% de la veces

		int x = figuras[i].pos_x;
		int y = figuras[i].pos_y;

		switch(n){
			case 1: // bala 1
						figuras[i].bala[0]=x+5;
						figuras[i].bala[1]=y-40;
			break;

			case 2:	 //bala2
						figuras[i].bala[2]=x+30;
						figuras[i].bala[3]=y-40;
			break;
		}
	}
}



//--------------------------Funcioon colision()------------------------
//esta funcion se ocupa de comprobar si han colisionado dos objetos a traves de sus posiciones
// para ello calculamos el modulo del vector que uno ambos puntos y comprobamos si es menor que un radio, el tamaño de las  naves,
//20 en este caso
bool colision(int pos_x,int pos_y, int u, int v){
	if(sqrt(pow(u-pos_x,2) + pow(v - pos_y,2)) < 20 ){ // comprobamos si el modulo del vector que forman los dos puntos es mayor que 20
		return(1);
	}else {
		return(0);
	}
}


//--------------------------funcion draw_world();--------------------------
//Esta funcion se ocupa de dibujar la mayoria de objetos
void draw_world(Tfiguras_list figuras,float &incremento, int sentido[],int mis_balas[],int &n_balas ){
int a;


 int x;
 int y;


 	for(int i=0; i< n_balas; i++){ // Dibujamos nuestra bala

 		gfx_line(mis_balas[0],mis_balas[1],mis_balas[0],mis_balas[1]+6);

		mis_balas[1] = mis_balas[1] + 5;


		if(mis_balas[1] > 400){ // si la bala desaparece de la pantalla la destruimos
			n_balas = 0;
		}

 	}

    for (int i=0; i<14; i= i+2){ // Dibujamos las naves enemigas
		if(figuras[i].type == 'l' ){

			if(sentido[i]==1){// me muevo a la derecha
				figuras[i].pos_x = figuras[i].pos_x + Kenemy_velocity;

				incremento = incremento + Kenemy_velocity;
			}else if(sentido[i] == -1){ // Me muevo a la izquierda
				figuras[i].pos_x = figuras[i].pos_x - Kenemy_velocity;

				incremento = incremento - Kenemy_velocity;

			}


			if(incremento > 5){  // LLegamos a un limite
				sentido[i] = sentido[i] *-1; // Cambiamos de sentido
				incremento =0;

			}else if(incremento < -5){ // Llegamos a otro limite

				sentido[i] = sentido[i] *-1; // Cambiamos de sentido
				incremento = 0;

			}


			x = figuras[i].pos_x;
			y = figuras[i].pos_y;



			if(figuras[i].life > 0){ // si la nave no esta muerta, a pintaaar!!!

					gfx_line(x+10,y,x+15,y);
					gfx_line(x+10,y,x+10,y-20);
					gfx_line(x,y-5,x+10,y-5);
					gfx_line(x,y-5,x,y-30);
					gfx_line(x+10,y-5,x+10,y-30);
					gfx_line(x,y-30,x+10,y-30);
					gfx_line(x+2.5,y-30,x+2.5,y-35);
					gfx_line(x+7.5,y-30,x+7.5,y-35);
					gfx_line(x+2.5,y-35,x+7.5,y-35);
					gfx_line(x,y-12.5,x-5,y-12.5);
					gfx_line(x,y-20,x-5,y-20);
					gfx_line(x-5,y-12.5,x-5,y-20);

					gfx_line(x+10,y-20,x+15,y-20);
					gfx_line(x+15,y-20,x+15,y-40);
					gfx_line(x+15,y-20,x+15,y-40);
					gfx_line(x+15,y-40,x+25,y-40);
					gfx_line(x+25,y-20,x+25,y-40);
					gfx_line(x+25,y-20,x+30,y-20);
					gfx_line(x+30,y-20,x+30,y-30);
					gfx_line(x+30,y-30,x+40,y-30);
					gfx_line(x+33.5,y-30,x+33.5,y-35);
					gfx_line(x+38.5,y-30,x+38.5,y-35);
					gfx_line(x+38.5,y-35,x+33.5,y-35);

					gfx_line(x+40,y-12.5,x+45,y-12.5);
					gfx_line(x+40,y-18.5,x+45,y-18.5);
					gfx_line(x+45,y-12.5,x+45,y-18.5);

					gfx_line(x+40,y-30,x+40,y-5);
					gfx_line(x+30,y-5,x+40,y-5);
					gfx_line(x+30,y-5,x+30,y-30);
					gfx_line(x+30,y-5,x+30,y);
					gfx_line(x+15,y,x+30,y);


					figuras[i].bala[1]-= 2; // Movemos las balas dos pixeles hacia abajo en el eje Y
					figuras[i].bala[3]-= 2;


					// Dibujamos las balas
					gfx_line(figuras[i].bala[0],figuras[i].bala[1],figuras[i].bala[0],figuras[i].bala[1]-10);

					gfx_line(figuras[i].bala[2],figuras[i].bala[3],figuras[i].bala[2],figuras[i].bala[3]-10);

					gfx_line(x+10,y-20,x+15,y-20);


					// comrpobamos si las balas enemigas han salido del espacio y las destruimos para que vulevan a ser generadas
					if(figuras[i].bala[1] < 0){
						bullet(figuras, i,1);
					}
					if(figuras[i].bala[3] < 0){
						bullet(figuras, i,2);
					}
			}
		}
    }




}




void play(){

	srand(time(NULL));


	// Variables del jugador
	int x = 200, y=45;
	int vidas = 3;
    int mis_balas[2];
    int n_balas = 0;
    int kills;

    // Variables enemigos
    int sentido[14]={-1,0,1,0,-1,0,1,0,-1,0,1,0,-1,0};
    float incremento = 0;
	int l = 50;

	//Variables auxiliares
	bool Vcolision;
	int n;
	char c,g;
	Tfiguras_list figuras;



	gfx_open(720, 400, "Space Invaders");
	gfx_color(0,200,100); // Color verde



    for(int k=0; k < 14; k+=2){ // Generamos los enemigos

	    figuras[k].type = 'l';
	    figuras[k].pos_x = l;
	    figuras[k].pos_y = 350;
	    figuras[k].life = 5;
	    figuras[k].bala[1] = 0;
	    figuras[k].bala[3] = 0;

    	l=l+100; // los desplazamos por el eje X
    }


	do{
		kills =0;

		// Detectamos una tecla pulsada y cual es
		c = gfx_event_waiting();
		if(c == 1){
			g=gfx_wait();
		// Movernos de las letras A - D y salir pulsando el 1 y disparamos del enter

			if(g==97) x-=10;
			if(g==100) x+=10;
			if(g==13) shot(x,y, mis_balas, n_balas);
		}


			gfx_clear();
			draw_world(figuras,incremento, sentido,mis_balas,n_balas);

			for(int i=0;i<14; i+=2){ // Colisiones de proyectiles enemigos al jugador

				Vcolision = colision(figuras[i].bala[0],figuras[i].bala[1],x,45); // Bala1
				if(Vcolision == 1){

					vidas -= 1; // nos bajamos la vida

					figuras[i].bala[1]=0; // Forzamos a que la bala 1 desaparezca

					if(vidas < 0){
						g = 49; //Salimos del bucle
						cout << "-------------------Has perdido-----------------" << endl;
					}

			}

				Vcolision = colision(figuras[i].bala[2],figuras[i].bala[3],x,45); // Bala2
				if(Vcolision == 1){
					vidas -= 1; //nos bajaamos la vida
					figuras[i].bala[3] = 0; // Forzamos a que la bala 2 desaparezca

					if(vidas < 0){
						g = 49; //Salimos del bucle
						cout << "-------------------Has perdido-----------------" << endl;
					}
				}
			}

			for(int i=0;i<14; i+=2){ // Colisiones de proyectiles jugador al enemigo

				Vcolision = colision(mis_balas[0],mis_balas[1],figuras[i].pos_x+20,figuras[i].pos_y); // Bala
				if(Vcolision == 1 && figuras[i].life > 0){

					figuras[i].life -= 1; // nos bajamos la vida

					mis_balas[1]=400; // Forzamos a que la bala  desaparezca

				}



				if(figuras[i].life == 0){ //  Nos anotamos unas muerte al destruir una nave
					kills++;
				}

			}
			gfx_line(x+15,y+6,x+15,y+9);
			gfx_line(x-8,y+10,x-8,y+15);
			gfx_line(x+8,y+10,x+8,y+15);
			gfx_line(x-15,y+6,x-15,y+9);
			gfx_line(x-3,y-1,x-3,y-5);
			gfx_line(x-8,y-1,x-8,y-5);
			gfx_line(x-8,y-5,x-3,y-5);
			gfx_line(x+3,y-1,x+3,y-5);
			gfx_line(x+8,y-1,x+8,y-5);
			gfx_line(x+8,y-5,x+3,y-5);
			gfx_line(x,y,x-15,y);
			gfx_line(x,y+1,x-10,y+1);
			gfx_line(x-15,y,x-15,y+6);
			gfx_line(x,y,x+15,y);
			gfx_line(x,y+1,x+10,y+1);
			gfx_line(x+15,y,x+15,y+6);
			gfx_line(x,y-1,x,y-8);
			gfx_line(x-1,y-1,x-1,y-8);
			gfx_line(x-2,y-1,x-2,y-8);
			gfx_line(x+2,y-1,x+2,y-8);
			gfx_line(x+1,y-1,x+1,y-8);
			gfx_line(x,y,x,y+20);
			gfx_line(x-1,y,x-1,y+15);
			gfx_line(x+1,y,x+1,y+15);
			gfx_line(x-2,y,x-2,y+7);
			gfx_line(x+2,y,x+2,y+7);
			gfx_line(x-3,y,x-3,y+5);
			gfx_line(x+3,y,x+3,y+5);
			gfx_line(x-4,y,x-4,y+5);
			gfx_line(x+4,y,x+4,y+5);
			gfx_line(x-8,y,x-8,y+10);
			gfx_line(x+8,y,x+8,y+10);



			if(kills == 7){ // si hemos mataado a las 7....
				cout << "-----------Has ganado--------------" << endl;
				g = 49;

			}


			usleep(12000);
	}while(g != 49);
}

void intrucciones(){
	cout << "La mecanica del juego consiste en aniquilar todas las naves, la unica forma de lograrlo sera disparando y esquivando los proyectiles enemigos. Cada nave puede resistir a 5 impactos de tus proyectiles mientras que tu solo podras aguantar 4.¿Seras capaz de conseguir la victoria o seras derrotado?" << endl;
	cout << "Los controles son:"<< endl;
	cout << "Tecla 'A': moverse izquierda." << endl;
	cout << "Tecla 'D': moverse derecha." << endl;
	cout << "Tecla ENTER : Disparar." << endl;
	cout << "Tecla '1': Cerrar Juego." << endl;
}

main(){
int n;
do{
	cout << "-------------------------------------------------------" << endl;
	cout << "--------------------Little Invaders---------------------" << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "Elige una opción: " << endl;
	cout << "1- Jugar " << endl;
	cout << "2- Intrucciones " << endl;
	cout << "3- Salir " << endl;

	cin >> n ;

	switch(n){
		case 1:
			play();
			n=3;
		break;
		case 2:
			intrucciones();
		break;
		case 3:
			cout << "Saliendo del Juego..." << endl;
		break;
	}


}while(n != 3);
        return 0;
}
