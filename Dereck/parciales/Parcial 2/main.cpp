#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Sol, Ruedas, Faros (Función Auxiliar)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void init()
{
    glClearColor(0.52, 0.80, 0.98, 1.0); // Azul cielo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 700);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //  Cielo, Pasto y Estrellas

    // Suelo / Pasto Verde
    glColor3f(0.40, 0.90, 0.40);
    glBegin(GL_QUADS);
        glVertex2f(0, 260);
        glVertex2f(1000, 260);
        glVertex2f(1000, 460);
        glVertex2f(0, 460);
    glEnd();

    // Estrellas / Puntos de luz en el cielo
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
        glVertex2f(100, 620);
        glVertex2f(250, 650);
        glVertex2f(400, 610);
        glVertex2f(550, 660);
    glEnd();

    // 2. MONTAÑAS Y SOL

    // Montaña grande trasera
    glColor3f(0.45, 0.25, 0.08);
    glBegin(GL_TRIANGLES);
        glVertex2f(500, 460);
        glVertex2f(900, 460);
        glVertex2f(720, 630);
    glEnd();

    // Montaña pequeña lateral
    glColor3f(0.40, 0.20, 0.05);
    glBegin(GL_TRIANGLES);
        glVertex2f(750, 460);
        glVertex2f(1000, 460);
        glVertex2f(880, 540);
    glEnd();

    // El Sol naranja
    glColor3f(1.0, 0.50, 0.0);
    drawCircle(840, 620, 35, 32);

    //  CASAS Y DETALLES

    // CASA 1 (Azul y Morada)
    // Cuerpo morado
    glColor3f(0.52, 0.00, 0.52);
    glBegin(GL_QUADS);
        glVertex2f(180, 280);
        glVertex2f(300, 280);
        glVertex2f(300, 370);
        glVertex2f(180, 370);
    glEnd();
    // Techo Azul
    glColor3f(0.00, 0.00, 1.00);
    glBegin(GL_TRIANGLES);
        glVertex2f(160, 350);
        glVertex2f(320, 350);
        glVertex2f(240, 460);
    glEnd();
    // Puerta Amarilla
    glColor3f(1.00, 1.00, 0.00);
    glBegin(GL_QUADS);
        glVertex2f(225, 280);
        glVertex2f(255, 280);
        glVertex2f(255, 330);
        glVertex2f(225, 330);
    glEnd();

    // CASA 2 (Naranja y Morada)
    // Cuerpo morado
    glColor3f(0.52, 0.00, 0.52);
    glBegin(GL_QUADS);
        glVertex2f(340, 305);
        glVertex2f(460, 305);
        glVertex2f(460, 390);
        glVertex2f(340, 390);
    glEnd();
    // Techo Naranja
    glColor3f(1.00, 0.55, 0.00);
    glBegin(GL_TRIANGLES);
        glVertex2f(320, 370);
        glVertex2f(480, 370);
        glVertex2f(400, 485);
    glEnd();
    // Puerta Amarilla
    glColor3f(1.00, 1.00, 0.00);
    glBegin(GL_QUADS);
        glVertex2f(385, 305);
        glVertex2f(415, 305);
        glVertex2f(415, 355);
        glVertex2f(385, 355);
    glEnd();

    // Parada de Autobús
    glColor3f(0.2, 0.2, 0.2);
    glLineWidth(3.0);
    glBegin(GL_LINES);
        glVertex2f(520, 260); glVertex2f(520, 310);
        glVertex2f(570, 260); glVertex2f(570, 310);
    glEnd();
    glColor3f(0.7, 0.1, 0.1);
    glBegin(GL_QUADS);
        glVertex2f(510, 310); glVertex2f(580, 310);
        glVertex2f(580, 320); glVertex2f(510, 320);
    glEnd();

    //  ÁRBOLES

    // ÁRBOLES IZQUIERDA
    // Árbol 1
    glColor3f(0.45, 0.2, 0.0); glBegin(GL_QUADS); glVertex2f(50, 280); glVertex2f(65, 280); glVertex2f(65, 340); glVertex2f(50, 340); glEnd();
    glColor3f(0.0, 0.5, 0.0); glBegin(GL_TRIANGLES); glVertex2f(30, 340); glVertex2f(85, 340); glVertex2f(57, 390);
                                      glVertex2f(35, 370); glVertex2f(80, 370); glVertex2f(57, 420); glEnd();
    // Árbol 2
    glColor3f(0.45, 0.2, 0.0); glBegin(GL_QUADS); glVertex2f(110, 280); glVertex2f(125, 280); glVertex2f(125, 340); glVertex2f(110, 340); glEnd();
    glColor3f(0.0, 0.5, 0.0); glBegin(GL_TRIANGLES); glVertex2f(90, 340); glVertex2f(145, 340); glVertex2f(117, 390);
                                      glVertex2f(95, 370); glVertex2f(140, 370); glVertex2f(117, 420); glEnd();

    // ÁRBOLES DERECHA
    // Árbol 3
    glColor3f(0.45, 0.2, 0.0); glBegin(GL_QUADS); glVertex2f(740, 320); glVertex2f(755, 320); glVertex2f(755, 390); glVertex2f(740, 390); glEnd();
    glColor3f(0.0, 0.5, 0.0); glBegin(GL_TRIANGLES); glVertex2f(715, 390); glVertex2f(780, 390); glVertex2f(747, 450);
                                      glVertex2f(725, 420); glVertex2f(770, 420); glVertex2f(747, 480); glEnd();
    // Árbol 4
    glColor3f(0.45, 0.2, 0.0); glBegin(GL_QUADS); glVertex2f(830, 290); glVertex2f(845, 290); glVertex2f(845, 360); glVertex2f(830, 360); glEnd();
    glColor3f(0.0, 0.5, 0.0); glBegin(GL_TRIANGLES); glVertex2f(805, 360); glVertex2f(870, 360); glVertex2f(837, 420);
                                      glVertex2f(815, 390); glVertex2f(860, 390); glVertex2f(837, 450); glEnd();
    // Árbol 5
    glColor3f(0.45, 0.2, 0.0); glBegin(GL_QUADS); glVertex2f(920, 330); glVertex2f(935, 330); glVertex2f(935, 400); glVertex2f(920, 400); glEnd();
    glColor3f(0.0, 0.5, 0.0); glBegin(GL_TRIANGLES); glVertex2f(895, 400); glVertex2f(960, 400); glVertex2f(927, 460);
                                      glVertex2f(905, 430); glVertex2f(950, 430); glVertex2f(927, 490); glEnd();

    // MAR / RÍO Y SUS DOS BARCOS

    // El Mar Azul
    glColor3f(0.00, 0.45, 0.90);
    glBegin(GL_QUADS);
        glVertex2f(0, 130);
        glVertex2f(1000, 130);
        glVertex2f(1000, 260);
        glVertex2f(0, 260);
    glEnd();

    // Barco 1 (Izquierda)
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(420, 150); glVertex2f(530, 150);
        glVertex2f(560, 180); glVertex2f(390, 180);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(445, 180); glVertex2f(505, 180);
        glVertex2f(505, 210); glVertex2f(445, 210);
    glEnd();

    // Barco 2 (Derecha)
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(580, 170); glVertex2f(690, 170);
        glVertex2f(720, 200); glVertex2f(550, 200);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(605, 200); glVertex2f(665, 200);
        glVertex2f(665, 230); glVertex2f(605, 230);
    glEnd();

    // CARRETERA Y CAMIÓN


    // Carretera Gris Asfalto
    glColor3f(0.35, 0.35, 0.35);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(1000, 0);
        glVertex2f(1000, 130);
        glVertex2f(0, 130);
    glEnd();

    // Línea de borde superior
    glColor3f(0.70, 0.70, 0.70);
    glLineWidth(4.0);
    glBegin(GL_LINES);
        glVertex2f(0, 125); glVertex2f(1000, 125);
    glEnd();

    // Líneas discontinuas de la calle
    glColor3f(1.0, 1.0, 1.0);
    for (int x = 20; x < 1000; x += 90) {
        glBegin(GL_QUADS);
            glVertex2f(x, 10); glVertex2f(x + 45, 10);
            glVertex2f(x + 45, 16); glVertex2f(x, 16);
        glEnd();
    }

    // El Camión Repartidor
    // Vagón de carga (Blanco)
    glColor3f(0.92, 0.92, 0.92);
    glBegin(GL_QUADS);
        glVertex2f(90, 45); glVertex2f(230, 45);
        glVertex2f(230, 135); glVertex2f(90, 135);
    glEnd();

    // Cabina (Negra)
    glColor3f(0.15, 0.15, 0.15);
    glBegin(GL_QUADS);
        glVertex2f(230, 45); glVertex2f(300, 45);
        glVertex2f(300, 105); glVertex2f(230, 105);
    glEnd();

    // Ventana de la cabina
    glColor3f(0.85, 0.85, 0.85);
    glBegin(GL_QUADS);
        glVertex2f(245, 75); glVertex2f(285, 75);
        glVertex2f(285, 98); glVertex2f(245, 98);
    glEnd();

    // Ruedas Negras
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(130, 45, 18, 20);
    drawCircle(260, 45, 18, 20);

    // Faro Amarillo
    glColor3f(1.0, 0.85, 0.0);
    drawCircle(295, 65, 7, 12);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Parcial 2 - Kevin Campines, Dereck Moreno");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
