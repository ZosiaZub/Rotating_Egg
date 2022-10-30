#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <conio.h>

#define M_PI 3.14159265358979323846 // LICZBA PI
typedef float point3[3];
int model = 1;
int n;
float p;


void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// początek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// początek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  początek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();

}


//-------------------------------------------------------------------------------- PUNKTOWE JAJKO JAJKO

void DrawPoints(float*** t, int n)
{
	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na biały

	glBegin(GL_POINTS);
	for (int u = 0; u < n; u++)
	{
		for (int v = 0; v < n; v++)
		{
			glVertex3fv(t[u][v]);
		}
	}
	glEnd();
}


//-------------------------------------------------------------------------------- LINIOWE JAJKO

void LinesPerNode(float*** t, GLint w, GLint k)
{
	//linia pionowa w gore
	glBegin(GL_LINES);

	glVertex3fv(t[w][k]);
	glVertex3fv(t[w - 1][k]);

	glEnd();

	//linia pozioma w prawo
	glBegin(GL_LINES);

	glVertex3fv(t[w][k]);
	glVertex3fv(t[w][k + 1]);

	glEnd();

	//linia na ukos do prawego gornego wierzcholka
	glBegin(GL_LINES);

	glVertex3fv(t[w][k]);
	glVertex3fv(t[w - 1][k + 1]);

	glEnd();
}


void LinesLastColumn(float*** t, GLint w, GLint n)
{
	//linia pionowa w gore
	glBegin(GL_LINES);

	glVertex3fv(t[w][n - 1]);
	glVertex3fv(t[w - 1][n - 1]);

	glEnd();

	//linia pozioma w prawo
	glBegin(GL_LINES);

	glVertex3fv(t[w][n - 1]);
	glVertex3fv(t[n - w - 1][0]);

	glEnd();

	//linia na ukos do prawego gornego wierzcholka
	glBegin(GL_LINES);

	glVertex3fv(t[w][n - 1]);
	glVertex3fv(t[n - w][0]);

	glEnd();
}


void LinesLastRow(float*** t, GLint n)
{
	for (int k = 0; k < n - 1; k++)
	{
		//linia pionowa w gore
		glBegin(GL_LINES);

		glVertex3fv(t[0][k]);
		glVertex3fv(t[n - 1][k]);

		glEnd();

		//linia pozioma w prawo
		glBegin(GL_LINES);

		glVertex3fv(t[0][k]);
		glVertex3fv(t[0][k + 1]);

		glEnd();

		//linia na ukos do prawego gornego wierzcholka
		glBegin(GL_LINES);

		glVertex3fv(t[0][k]);
		glVertex3fv(t[n - 1][k + 1]);

		glEnd();
	}
}


void DrawLines(float*** t, GLint n)
{
	glColor3f(0.0f, 1.0f, 0.0f);	// kolor ustawiony na zielony

	for (int w = 1; w < n; w++)
	{
		for (int k = 0; k < n - 1; k++)
		{
			LinesPerNode(t, w, k);
		}
		LinesLastColumn(t, w, n);
	}
	LinesLastRow(t, n);
}


//-------------------------------------------------------------------------------- TRÓJKĄTNE JAJKO

void TrianglesPerNode(float*** t, GLint w, GLint k)
{
	glBegin(GL_TRIANGLES);

	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w][k]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w - 1][k]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w - 1][k + 1]);

	glEnd();

	glBegin(GL_TRIANGLES);

	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w][k]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w][k + 1]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w - 1][k + 1]);

	glEnd();
}


void TrianglesLastColumn(float*** t, GLint w, GLint n)
{
	glBegin(GL_TRIANGLES);

	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w][n - 1]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w - 1][n - 1]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[n - w][0]);

	glEnd();

	glBegin(GL_TRIANGLES);

	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[w][n - 1]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[n - w - 1][0]);
	glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
	glVertex3fv(t[n - w][0]);

	glEnd();
}


void TrianglesLastRow(float*** t, GLint n)
{
	for (int k = 0; k < n - 1; k++)
	{
		glBegin(GL_TRIANGLES);

		glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
		glVertex3fv(t[0][k]);
		glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
		glVertex3fv(t[n - 1][k]);
		glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
		glVertex3fv(t[n - 1][k + 1]);

		glEnd();

		glBegin(GL_TRIANGLES);

		glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
		glVertex3fv(t[0][k]);
		glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
		glVertex3fv(t[0][k + 1]);
		glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
		glVertex3fv(t[n - 1][k + 1]);

		glEnd();
	}
}


void DrawTriangles(float*** t, GLint n)
{
	for (int w = 1; w < n; w++)
	{
		for (int k = 0; k < n - 1; k++)
		{
			TrianglesPerNode(t, w, k);
		}
		TrianglesLastColumn(t, w, n);
	}
	TrianglesLastRow(t, n);
}


//-------------------------------------------------------------------------------- TABLICA I RYSOWANIE JAJKA

float*** Tab(int n)
{
	float*** tab = new float** [n];
	float u, v;
	for (int i = 0; i < n; i++)
	{
		tab[i] = new float* [n];
		for (int j = 0; j < n; j++)
		{
			u = (float)i / (float)n;
			v = (float)j / (float)n;
			tab[i][j] = new float[3];
			tab[i][j][0] = (-90.0 * pow(u, 5.0) + 225.0 * pow(u, 4.0) - 270.0 * pow(u, 3.0) + 180.0 * pow(u, 2.0) - 45.0 * u) * cos(M_PI * v); // x(u,v)
			tab[i][j][1] = 160.0 * pow(u, 4.0) - 320.0 * pow(u, 3.0) + 160.0 * pow(u, 2.0) - 5;												   // y(u,v)
			tab[i][j][2] = (-90.0 * pow(u, 5.0) + 225.0 * pow(u, 4.0) - 270.0 * pow(u, 3.0) + 180.0 * pow(u, 2.0) - 45.0 * u) * sin(M_PI * v); // z(u,v)
		}
	}
	return tab;
}


void Egg(int n)
{
	float*** tab3 = Tab(n);

	switch (model)
	{
	case 1:
		DrawPoints(tab3, n);
		break;

	case 2:
		DrawLines(tab3, n);
		break;

	case 3:
		DrawTriangles(tab3, n);
		break;

	default:
		std::cout << "do wyboru wypełnienia powierzchni jajka sa tylko opcje 1, 2 lub 3" << std::endl;
	}
}


//-------------------------------------------------------------------------------- OBRACANIE JAJKA

void Spin(GLfloat angle)
{
	glRotatef(angle * (rand() % 101) * 0.01, 1.0, 0.0, 0.0);
	glRotatef(angle * (rand() % 101) * 0.01, 0.0, 1.0, 0.0);
	glRotatef(angle * (rand() % 101) * 0.01, 0.0, 0.0, 1.0);

	glutPostRedisplay();
}


//-------------------------------------------------------------------------------- CZYTANIE ZNAKU Z KLAWIATURY

int ReadSign()
{
	unsigned char znak;
	znak = getchar();
	return static_cast <int>(znak);
}


void Write()
{
	std::cout << "Jak chcesz wypelnic jajko? " << std::endl;
	std::cout << " - punkty		(p)" << std::endl;
	std::cout << " - siatka		(s)" << std::endl;
	std::cout << " - trojkatami		(t)" << std::endl;
}


//-------------------------------------------------------------------------------- RESZTA

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	//glLoadIdentity();
	//// Czyszczenie macierzy bieżącej
	//Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

	//glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na biały
	//glRotated(60.0, 1.0, 1.0, 1.0);  // Obrót o 60 stopni
	//glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty

	Spin(p);

	Egg(n);

	glFlush();
	// Przekazanie poleceń rysujących do wykonania

	glutSwapBuffers();
}


void Keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 's') model = 2;
	if (key == 't') model = 3;

	RenderScene(); // przerysowanie obrazu sceny
}


void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszcący (wypełnienia okna) ustawiono na czarny

}


void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	float size = 7.5;

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  określającej proporcję
	// wymiarów okna

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)
	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji
	glLoadIdentity();
	// Czyszcznie macierzy bieżącej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
	// przestrzeni ograniczającej pozwalającej zachować właściwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczjącej służy funkcja
	// glOrtho(...)
	if (horizontal <= vertical)

		glOrtho(-size, size, -size / AspectRatio, size / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-size * AspectRatio, size * AspectRatio, -size, size, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu

	glLoadIdentity();
	// Czyszcenie macierzy bieżącej
}


void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(700, 700);

	glutCreateWindow("JAJOOO");

	/*Write();
	model = ReadSign();*/

	std::cout << "Podaj liczbe n (wierzcholkow bedzie n^2)" << std::endl;
	std::cin >> n;

	std::cout << "Podaj predkosc obrotu (float) <0-0.6>" << std::endl;
	std::cin >> p;

	

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną
	// (callback function).  Bedzie ona wywoływana za każdym razem
	// gdy zajdzie potrzba przeryswania okna

	glutKeyboardFunc(Keys);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
	// zazmiany rozmiaru okna
	MyInit();
	// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przystąpieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}