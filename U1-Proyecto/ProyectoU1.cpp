#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#endif

#define NUM_PALOS 4
#define NUM_VAL 13

using namespace std;

int i = 0;
int b = 0;
int palo = 0;
int valor = 0;
int palos[NUM_PALOS * NUM_VAL];
int valores[NUM_PALOS * NUM_VAL];
bool paloRepetido = false;
bool valorRepetido = false;
int multiContador[] = {0, 0, 0, 0};

bool seleccionada = false;
bool mueveP1 = false;
bool mueveP2 = false;
bool mueveP3 = false;
bool mueveP4 = false;
bool mueveP5 = false;
bool mueveP6 = false;
bool mueveP7 = false;

// Globals.
float refresh = 100.0;


class Carta{
	private:
		int palo;
		int valor;
		bool alReves;
	public:
		int posX;
		int posY;
		Carta(){
			palo = -1;
			valor = -1;
			posX = 0;
			posY = 0;
			alReves = false;
		}
		Carta(int p, int v, int x, int y){
			palo = p;
			valor = v;
			posX = x;
			posY = y;
			alReves = false;
		}
		void dibujarCarta();
		void voltear();
};

void Carta::dibujarCarta(){
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glRectf(posX, posY, posX + 8.5, posY + 13.5);

	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectf(posX + 0.2, posY + 0.2, posX + 8.3, posY + 13.3);
}

void Carta::voltear(){
	if(alReves)
		alReves = false;
	else
		alReves = true;
}

vector<Carta> cartas;
vector<Carta>::iterator cartasIterator; 

void dibujarCartas(){
	cartasIterator = cartas.begin();
	while(cartasIterator != cartas.end()){
		cartasIterator -> dibujarCarta();
		cartasIterator++;
	}
}

vector<Carta> P1;
vector<Carta>::iterator cartasIterator1; 

void dibujarCartasP1(){
	cartasIterator1 = P1.begin();
	while(cartasIterator1 != P1.end()){
		cartasIterator1 -> dibujarCarta();
		cartasIterator1++;
	}
}

vector<Carta> P2;
vector<Carta>::iterator cartasIterator2; 

void dibujarCartasP2(){
	cartasIterator2 = P2.begin();
	while(cartasIterator2 != P2.end()){
		cartasIterator2 -> dibujarCarta();
		cartasIterator2++;
	}
}

vector<Carta> P3;
vector<Carta>::iterator cartasIterator3; 

void dibujarCartasP3(){
	cartasIterator3 = P3.begin();
	while(cartasIterator3 != P3.end()){
		cartasIterator3 -> dibujarCarta();
		cartasIterator3++;
	}
}

vector<Carta> P4;
vector<Carta>::iterator cartasIterator4; 

void dibujarCartasP4(){
	cartasIterator4 = P4.begin();
	while(cartasIterator4 != P4.end()){
		cartasIterator4 -> dibujarCarta();
		cartasIterator4++;
	}
}

vector<Carta> P5;
vector<Carta>::iterator cartasIterator5; 

void dibujarCartasP5(){
	cartasIterator5 = P5.begin();
	while(cartasIterator5 != P5.end()){
		cartasIterator5 -> dibujarCarta();
		cartasIterator5++;
	}
}

vector<Carta> P6;
vector<Carta>::iterator cartasIterator6; 

void dibujarCartasP6(){
	cartasIterator6 = P6.begin();
	while(cartasIterator6 != P6.end()){
		cartasIterator6 -> dibujarCarta();
		cartasIterator6++;
	}
}

vector<Carta> P7;
vector<Carta>::iterator cartasIterator7; 

void dibujarCartasP7(){
	cartasIterator7 = P7.begin();
	while(cartasIterator7 != P7.end()){
		cartasIterator7 -> dibujarCarta();
		cartasIterator7++;
	}
}

void writeBitmapString(void *font, char *string)
{  
   char *c;
   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void windowInfo(){
	char valor[10];
	//sprintf(valor, "%f", alpha);
}

void generarMazo(){
	// 4 Palos: 1 - Corazones, 2 - Diamantes, 3 - Treboles, 4 - Picas
	// 13 Valores, 1 / As, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 / J, 12 / Q, 13 / K

	for(int z = 0; z < NUM_PALOS * NUM_VAL; z++){ // Limpiar arrays
		palos[z] = 0;
		valores[z] = 0;
	}

	while(i < NUM_PALOS * NUM_VAL){
		paloRepetido = false;

		if(!valorRepetido){ // Evitar que se cargue otro palo cuando se detecto un valor repetido
			palo = 1 + rand() % NUM_PALOS;
			
			// Un palo solo puede tener 13 cartas, por lo cual se debe solo repetir 13 veces
			// Si toca un palo con 13 cartas se debe ignorar y volver a empezar
			if(palo == 1){
				if(multiContador[0] == 13) paloRepetido = true;
				else multiContador[0]++;
			} else if(palo == 2){
				if(multiContador[1] == 13) paloRepetido = true;
				else multiContador[1]++;
			} else if(palo == 3){
				if(multiContador[2] == 13) paloRepetido = true;
				else multiContador[2]++;
			} else if(palo == 4){
				if(multiContador[3] == 13) paloRepetido = true; 
				else multiContador[3]++;
			}

			if(!paloRepetido) palos[i] = palo; // No es un palo repetido
		}

		if(!paloRepetido){ // Se tiene un palo no repetido
			valor = 1 + rand() % NUM_VAL;
			valorRepetido = false;
			

			if(b == 0){ // No se verifica el valor de la primera iteracion
				valores[i] = valor;
			} else{
				for(int rep = 0; valores[rep]; rep++){ // Se buscan valores repetidos en el mismo palo actual
					if(valores[rep] == valor && palos[rep] == palos[i]){
						valorRepetido = true; // Valor repetido
						break;
					}
				}

				if(!valorRepetido){ // No es un valor repetido en el mismo palo
					valores[i] = valor;
				}
			}

			if(!valorRepetido) i++; // Se tiene un palo y valor no generados, se pasa a la siguiente carta
		}
	}
}

void dibujarTablero(){
	
}

int posicionesTablero[28][2];

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glLoadIdentity();

	// SOLO DE PRUEBA, PERO NO BORRAR
	cout << endl;
	int contador = 0;
	int lim = 7;

	for(int j = 1; j <= 7; j++){
		for(int k = 1; k <= 7; k++){
			cout << "Palo: " << palos[k - 1] << " Valor: " << valores[k - 1] << endl;

			posicionesTablero[k - 1][0] = (95 - 12 * k);
			posicionesTablero[k - 1][1] = (60 - 4 * j);

			/*cartas.push_back(Carta(palos[k - 1], 			// Palo
					       valores[k - 1], 			// Valor
					       posicionesTablero[k - 1][0], 	// Posicion en X
					       posicionesTablero[k - 1][1]));	// Posicion en Y
			dibujarCartas();
			contador++;*/

			if(k==1){
				P1.push_back(Carta(palos[k - 1], 			// Palo
					       valores[k - 1], 			// Valor
					       posicionesTablero[k - 1][0], 	// Posicion en X
					       posicionesTablero[k - 1][1]));	// Posicion en Y
				dibujarCartasP1();
				contador++;
				
			}
			if(k==2){
				P2.push_back(Carta(palos[k - 1], 			// Palo
				      		 valores[k - 1], 			// Valor
				       		posicionesTablero[k - 1][0], 	// Posicion en X
				       		posicionesTablero[k - 1][1]));	// Posicion en Y
				dibujarCartasP2();
				contador++;	
			}
			if(k==3){
				P3.push_back(Carta(palos[k - 1], 			// Palo
				      		 valores[k - 1], 			// Valor
				       		posicionesTablero[k - 1][0], 	// Posicion en X
				       		posicionesTablero[k - 1][1]));	// Posicion en Y
				dibujarCartasP3();
				contador++;	
			}
			if(k==4){
				P4.push_back(Carta(palos[k - 1], 			// Palo
				      		 valores[k - 1], 			// Valor
				       		posicionesTablero[k - 1][0], 	// Posicion en X
				       		posicionesTablero[k - 1][1]));	// Posicion en Y
				dibujarCartasP4();
				contador++;			
			}
			if(k==5){
				P5.push_back(Carta(palos[k - 1], 			// Palo
				      		 valores[k - 1], 			// Valor
				       		posicionesTablero[k - 1][0], 	// Posicion en X
				       		posicionesTablero[k - 1][1]));	// Posicion en Y
				dibujarCartasP5();
				contador++;			
			}
			if(k==6){
				P6.push_back(Carta(palos[k - 1], 			// Palo
				      		 valores[k - 1], 			// Valor
				       		posicionesTablero[k - 1][0], 	// Posicion en X
				       		posicionesTablero[k - 1][1]));	// Posicion en Y
				dibujarCartasP6();
				contador++;			
			}
			if(k==7){
				P7.push_back(Carta(palos[k - 1], 			// Palo
				      		 valores[k - 1], 			// Valor
				       		posicionesTablero[k - 1][0], 	// Posicion en X
				       		posicionesTablero[k - 1][1]));	// Posicion en Y
				dibujarCartasP7();
				contador++;					
			}




			if(contador == lim){
				lim--;
				contador = 0;
				break;
			}
		}
	}

	/*cartasIterator = cartas.begin();
	cartasIterator -> dibujarCarta();
	cout << cartasIterator -> posX << " " << cartasIterator -> posY << endl;*/

	glFlush();
}

// Initialization routine.
void setup(void) 
{
	glClearColor(0.0, 1.0, 0.0, 10.0);

	generarMazo();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 100, 0, 100, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int value) {
	
	glutPostRedisplay();
	glutTimerFunc(refresh, Timer, 0);
}

void mouseControl(int key, int state, int x, int y){
	cout << x << " " << y << endl;
}

void keyInput(unsigned char key, int x, int y)
{
	switch(key) 
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}


void mouseCallBack(int btn, int state, int x, int y)
{
	printf("Mouse call back: button=%d, state=%d, x=%d, y=%d\n", btn, state, x, y);
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){   
		exit(0);
	}
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		
		if(seleccionada == false){
			if(x>=68 && x<=117){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP1=true;				
			}
			else if(x>=138 && x<=189){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP2=true;	
			}
			else if(x>=212 && x<=261){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP3=true;	
			}
			else if(x>=284 && x<=332){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP4=true;		
			}
			else if(x>=356 && x<=405){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP5=true;	
			}
			else if(x>=428 && x<=478){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP6=true;		
			}
			else if(x>=499 && x<=549){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP7=true;	
			}

			/*if(mueveP1==true){
				if(sizeof(P1)>0){
					P1[sizeof(P1)-1].posX=x;
					P1[sizeof(P1)-1].posY=y;
				}			
			}
			if(mueveP2==true){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP2=true;	
			}
			if(mueveP3==true){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP3=true;	
			}
			if(mueveP4==true){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP4=true;		
			}
			if(mueveP5==true){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP5=true;	
			}
			if(mueveP6==true){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP6=true;		
			}
			if(mueveP7==true){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP7=true;	
			}*/		

		}		
	}
	else if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP){

			if(x>=68 && x<=117){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP1=true;				
			}
			else if(x>=138 && x<=189){
				P1[sizeof(P1)].posX=P2[sizeof(P1)].posX;
				//P2.push_back(P1[sizeof(P1)-1])
				//P1.
			}
			else if(x>=212 && x<=261){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP3=true;	
			}
			else if(x>=284 && x<=332){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP4=true;		
			}
			else if(x>=356 && x<=405){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP5=true;	
			}
			else if(x>=428 && x<=478){
				cout<<"\ncarta\n";
				seleccionada=true;
				mueveP6=true;		
			}
			else if(x>=499 && x<=549){
				cout<<"\ncarta\n";	
				seleccionada=true;
				mueveP7=true;	
			}


		seleccionada = false;
		mueveP1 = false;
		mueveP2 = false;
		mueveP3 = false;
		mueveP4 = false;
		mueveP5 = false;
		mueveP6 = false;
		mueveP7 = false;
	}
	glutPostRedisplay();
}

void printInteraction(){
	cout << "Triangle centers" << endl;
	cout << "Author: Oscar Francisco Flores Gallegos" << endl;
	cout << "Use space key for switch the diagrams" << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitContextVersion(2, 1); 
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); 

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("Proyect");
	glutDisplayFunc(drawScene); 
	glutReshapeFunc(resize);  
	//glutMouseFunc(mouseControl);
	glutMouseFunc (mouseCallBack);
	glutKeyboardFunc(keyInput);
	//glutTimerFunc(0, Timer, 0);
	glewInit(); 
	//printInteraction();

	setup(); 

	glutMainLoop();   	
}
