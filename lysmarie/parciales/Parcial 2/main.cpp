#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979

void color3f(float r, float g, float b) { glColor3f(r, g, b); }
void drawCircle(float cx, float cy, float r, int segments,
                float cr, float cg, float cb)
{
    color3f(cr, cg, cb);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(cx + r * cosf(angle), cy + r * sinf(angle));
    }
    glEnd();
}

void drawFondo()
{
    // --- Cielo nocturno (GL_QUADS) ---
    color3f(0.05f, 0.05f, 0.18f);
    glBegin(GL_QUADS);
        glVertex2f(0,   350);
        glVertex2f(1000,350);
        glVertex2f(1000,700);
        glVertex2f(0,   700);
    glEnd();

    // --- Suelo / cesped principal (GL_QUADS) ---
    color3f(0.13f, 0.50f, 0.13f);
    glBegin(GL_QUADS);
        glVertex2f(0,   200);
        glVertex2f(1000,200);
        glVertex2f(1000,350);
        glVertex2f(0,   350);
    glEnd();

    color3f(0.08f, 0.45f, 0.80f);
    glBegin(GL_QUADS);
        glVertex2f(0,   0);
        glVertex2f(1000,0);
        glVertex2f(1000,215);
        glVertex2f(0,   215);
    glEnd();


    color3f(0.60f, 0.46f, 0.28f);
    glBegin(GL_QUADS);
        glVertex2f(0,   60);
        glVertex2f(1000,60);
        glVertex2f(1000,110);
        glVertex2f(0,   110);
    glEnd();


    color3f(0.20f, 0.65f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(0,   110);
        glVertex2f(1000,110);
        glVertex2f(1000,215);
        glVertex2f(0,   215);
    glEnd();

    // --- Estrellas (GL_POINTS) ---
    srand(42);
    glPointSize(2.0f);
    color3f(1.0f, 1.0f, 0.95f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 120; i++)
    {
        float sx = (float)(rand() % 1000);
        float sy = 370.0f + (float)(rand() % 320);
        glVertex2f(sx, sy);
    }
    glEnd();
    glPointSize(1.0f);
}
void drawMaceta(float x, float y)
{
    // Arbusto bajo redondeado sin maceta
    drawCircle(x,    y+10, 18, 32, 0.10f, 0.42f, 0.10f);
    drawCircle(x-16, y+7,  14, 32, 0.08f, 0.36f, 0.08f);
    drawCircle(x+16, y+7,  14, 32, 0.08f, 0.36f, 0.08f);
    drawCircle(x-8,  y+16, 12, 32, 0.12f, 0.48f, 0.12f);
    drawCircle(x+8,  y+16, 12, 32, 0.12f, 0.48f, 0.12f);
}

void drawLuna()
{
    drawCircle(820, 620, 55, 64, 1.0f, 0.98f, 0.70f);
}

void drawMontanas()
{
    // Montana derecha grande - oscura
    color3f(0.25f, 0.20f, 0.18f);
    glBegin(GL_TRIANGLES);
        glVertex2f(750, 350);
        glVertex2f(950, 350);
        glVertex2f(870, 530);
    glEnd();

    // Montana derecha mediana - mas clara
    color3f(0.35f, 0.28f, 0.22f);
    glBegin(GL_TRIANGLES);
        glVertex2f(680, 350);
        glVertex2f(870, 350);
        glVertex2f(790, 490);
    glEnd();

    // Montana izquierda atras
    color3f(0.20f, 0.18f, 0.16f);
    glBegin(GL_TRIANGLES);
        glVertex2f(820, 350);
        glVertex2f(1000,350);
        glVertex2f(920, 470);
    glEnd();
}

void drawArbol(float x, float baseY, float escala)
{
    float w = 40 * escala;
    float h = 55 * escala;

    // Tronco (GL_QUADS)
    color3f(0.36f, 0.22f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(x - 6*escala, baseY);
        glVertex2f(x + 6*escala, baseY);
        glVertex2f(x + 6*escala, baseY + 20*escala);
        glVertex2f(x - 6*escala, baseY + 20*escala);
    glEnd();

    // Capa inferior (GL_TRIANGLES)
    color3f(0.10f, 0.42f, 0.10f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - w,        baseY + 10*escala);
        glVertex2f(x + w,        baseY + 10*escala);
        glVertex2f(x,            baseY + 10*escala + h);
    glEnd();

    // Capa media (GL_TRIANGLES)
    color3f(0.12f, 0.50f, 0.12f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - w*0.80f,  baseY + 28*escala);
        glVertex2f(x + w*0.80f,  baseY + 28*escala);
        glVertex2f(x,            baseY + 28*escala + h*0.80f);
    glEnd();

    // Capa superior (GL_TRIANGLES)
    color3f(0.15f, 0.55f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - w*0.55f,  baseY + 48*escala);
        glVertex2f(x + w*0.55f,  baseY + 48*escala);
        glVertex2f(x,            baseY + 48*escala + h*0.60f);
    glEnd();
}

void drawEdificio(float x, float y, float w, float h,
                  float r, float g, float b)
{
    // Cuerpo principal (GL_QUADS)
    color3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x,   y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y+h);
        glVertex2f(x,   y+h);
    glEnd();

    // Contorno (GL_LINE_LOOP)
    color3f(r*0.6f, g*0.6f, b*0.6f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,   y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y+h);
        glVertex2f(x,   y+h);
    glEnd();
    glLineWidth(1.0f);
}

void drawVentana(float x, float y, float w, float h, bool luz)
{
    if (luz)
        color3f(1.0f, 0.95f, 0.60f);   // ventana iluminada
    else
        color3f(0.15f, 0.15f, 0.25f);  // ventana apagada

    glBegin(GL_QUADS);
        glVertex2f(x,   y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y+h);
        glVertex2f(x,   y+h);
    glEnd();
}

void drawEdificios()
{
    // --- Edificio izquierdo alto ---
    drawEdificio(40, 350, 130, 250, 0.85f, 0.68f, 0.35f);
    // ventanas con patron de luces (GL_QUADS)
    bool luces1[4][3] = {{1,0,1},{0,1,0},{1,1,0},{0,0,1}};
    for (int fila = 0; fila < 4; fila++)
        for (int col = 0; col < 3; col++)
            drawVentana(55 + col*38, 360 + fila*48, 28, 32, luces1[fila][col]);

    // --- Edificio central mediano ---
    drawEdificio(180, 350, 110, 180, 0.80f, 0.65f, 0.32f);
    bool luces2[3][2] = {{1,0},{0,1},{1,1}};
    for (int fila = 0; fila < 3; fila++)
        for (int col = 0; col < 2; col++)
            drawVentana(196 + col*46, 360 + fila*46, 34, 30, luces2[fila][col]);

    // --- Edificio derecho pequeno ---
    drawEdificio(295, 350, 80, 130, 0.88f, 0.72f, 0.38f);
    for (int fila = 0; fila < 2; fila++)
        for (int col = 0; col < 2; col++)
            drawVentana(308 + col*34, 360 + fila*44, 24, 28, (fila+col)%2==0);
}

void drawParada(float x, float y)
{
    // Base / piso (GL_QUADS)
    color3f(0.60f, 0.60f, 0.62f);
    glBegin(GL_QUADS);
        glVertex2f(x,      y);
        glVertex2f(x+90,   y);
        glVertex2f(x+90,   y+5);
        glVertex2f(x,      y+5);
    glEnd();

    // Columnas laterales (GL_LINES)
    color3f(0.50f, 0.50f, 0.52f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(x+5,  y+5);  glVertex2f(x+5,  y+72);
        glVertex2f(x+85, y+5);  glVertex2f(x+85, y+72);
    glEnd();
    glLineWidth(1.0f);

    // Techo mas largo y rojo (GL_QUADS)
    color3f(0.85f, 0.12f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(x-5,   y+68);
        glVertex2f(x+95,  y+68);
        glVertex2f(x+95,  y+80);
        glVertex2f(x-5,   y+80);
    glEnd();

    // Panel trasero transparente (GL_LINE_LOOP)
    color3f(0.75f, 0.75f, 0.80f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x+5,  y+5);
        glVertex2f(x+85, y+5);
        glVertex2f(x+85, y+68);
        glVertex2f(x+5,  y+68);
    glEnd();
    glLineWidth(1.0f);

    // Letrero rojo en panel (GL_QUADS)
    color3f(0.85f, 0.10f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(x+15, y+45);
        glVertex2f(x+75, y+45);
        glVertex2f(x+75, y+58);
        glVertex2f(x+15, y+58);
    glEnd();

    // --- Señal circular roja en poste separado ---
    // Poste (GL_LINES)
    color3f(0.25f, 0.25f, 0.25f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(x+108, y);
        glVertex2f(x+108, y+55);
    glEnd();
    glLineWidth(1.0f);

    // Circulo rojo (GL_POLYGON)
    drawCircle(x+108, y+68, 16, 32, 0.85f, 0.08f, 0.08f);
    // Borde blanco interior
    drawCircle(x+108, y+68, 11, 32, 0.95f, 0.95f, 0.95f);
    // Linea horizontal (señal de prohibido) (GL_LINES)
    color3f(0.85f, 0.08f, 0.08f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(x+94,  y+68);
        glVertex2f(x+122, y+68);
    glEnd();
    glLineWidth(1.0f);
}

void drawCarretera()
{
    // Asfalto (GL_QUADS)
    color3f(0.28f, 0.28f, 0.28f);
    glBegin(GL_QUADS);
        glVertex2f(0,   210);
        glVertex2f(1000,210);
        glVertex2f(1000,350);
        glVertex2f(0,   350);
    glEnd();

    // Linea central discontinua (GL_LINES)
    color3f(0.9f, 0.85f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 1000; i += 60)
    {
        glVertex2f(i,      280);
        glVertex2f(i+35,   280);
    }
    glEnd();
    glLineWidth(1.0f);

    // Borde superior de carretera (GL_LINE_LOOP usado como linea de borde)
    color3f(0.55f, 0.55f, 0.55f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(0,   350);
        glVertex2f(1000,350);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(0,   210);
        glVertex2f(1000,210);
    glEnd();
    glLineWidth(1.0f);

// --- Paso de cebra (GL_LINES) ---
    color3f(0.95f, 0.95f, 0.95f);
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 7; i++)
    {
        float ly = 220 + i * 20;
        glVertex2f(460, ly);
        glVertex2f(560, ly);
    }
    glEnd();
    glLineWidth(1.0f);
}

void drawCarro(float x, float y)
{
    // Carroceria inferior (GL_QUADS)
    color3f(0.80f, 0.10f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(x,      y);
        glVertex2f(x+140,  y);
        glVertex2f(x+140,  y+35);
        glVertex2f(x,      y+35);
    glEnd();

    // Cabina (GL_QUADS)
    color3f(0.70f, 0.08f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(x+25,   y+35);
        glVertex2f(x+115,  y+35);
        glVertex2f(x+105,  y+65);
        glVertex2f(x+35,   y+65);
    glEnd();

    // Ventanas (GL_QUADS)
    color3f(0.55f, 0.80f, 0.90f);
    glBegin(GL_QUADS);
        glVertex2f(x+38,  y+38);
        glVertex2f(x+70,  y+38);
        glVertex2f(x+68,  y+58);
        glVertex2f(x+38,  y+58);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x+74,  y+38);
        glVertex2f(x+106, y+38);
        glVertex2f(x+102, y+58);
        glVertex2f(x+74,  y+58);
    glEnd();

    // Ruedas (GL_POLYGON)
    drawCircle(x+28,  y,    18, 32, 0.15f, 0.15f, 0.15f);
    drawCircle(x+112, y,    18, 32, 0.15f, 0.15f, 0.15f);
    drawCircle(x+28,  y,     8, 32, 0.40f, 0.40f, 0.42f);
    drawCircle(x+112, y,     8, 32, 0.40f, 0.40f, 0.42f);

    // Faro delantero (GL_QUADS)
    color3f(1.0f, 1.0f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(x+130, y+10);
        glVertex2f(x+140, y+10);
        glVertex2f(x+140, y+22);
        glVertex2f(x+130, y+22);
    glEnd();

    // Contorno carro (GL_LINE_LOOP)
    color3f(0.50f, 0.05f, 0.05f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,      y+18);
        glVertex2f(x+140,  y+18);
        glVertex2f(x+140,  y+35);
        glVertex2f(x+115,  y+35);
        glVertex2f(x+105,  y+65);
        glVertex2f(x+35,   y+65);
        glVertex2f(x+25,   y+35);
        glVertex2f(x,      y+35);
    glEnd();
    glLineWidth(1.0f);
}

void drawBanca(float x, float y)
{
    // Asiento
    color3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(x,    y+10);
        glVertex2f(x+60, y+10);
        glVertex2f(x+60, y+18);
        glVertex2f(x,    y+18);
    glEnd();
    color3f(0.30f, 0.15f, 0.05f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(x+8,  y);    glVertex2f(x+8,  y+10);
        glVertex2f(x+52, y);    glVertex2f(x+52, y+10);
    glEnd();
    glLineWidth(1.0f);
    color3f(0.25f, 0.12f, 0.04f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,    y+10);
        glVertex2f(x+60, y+10);
        glVertex2f(x+60, y+18);
        glVertex2f(x,    y+18);
    glEnd();
    glLineWidth(1.0f);
}
void drawVelero(float x, float y, float s)
{
    // Casco del barco (GL_QUADS)
    color3f(0.55f, 0.18f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(x,        y+10*s);
        glVertex2f(x+80*s,   y+10*s);
        glVertex2f(x+70*s,   y);
        glVertex2f(x+10*s,   y);
    glEnd();

    // Mastil (GL_LINES)
    color3f(0.70f, 0.60f, 0.40f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(x+40*s, y+10*s);
        glVertex2f(x+40*s, y+70*s);
    glEnd();
    glLineWidth(1.0f);

    // Vela izquierda (GL_TRIANGLES)
    color3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x+40*s, y+65*s);
        glVertex2f(x+40*s, y+15*s);
        glVertex2f(x+5*s,  y+15*s);
    glEnd();

    // Vela derecha (GL_TRIANGLES)
    color3f(0.88f, 0.88f, 0.88f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x+40*s, y+65*s);
        glVertex2f(x+40*s, y+15*s);
        glVertex2f(x+75*s, y+15*s);
    glEnd();

    // Contorno casco (GL_LINE_LOOP)
    color3f(0.35f, 0.10f, 0.03f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,        y+10*s);
        glVertex2f(x+80*s,   y+10*s);
        glVertex2f(x+70*s,   y);
        glVertex2f(x+10*s,   y);
    glEnd();
    glLineWidth(1.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Fondo: cielo, suelo, agua (GL_QUADS + GL_POINTS)
    drawFondo();

    // 2. Luna (GL_POLYGON)
    drawLuna();

    // 3. Montanas (GL_TRIANGLES)
    drawMontanas();

    // 4. Edificios (GL_QUADS + GL_LINE_LOOP)
    drawEdificios();

    // 5. Parada de autobus (GL_QUADS + GL_LINES + GL_LINE_LOOP)
    drawParada(580, 350);

    // 6. Arboles - minimo tres (GL_TRIANGLES + GL_QUADS)
    drawArbol(390, 350, 1.4f);
    drawArbol(450, 350, 1.1f);
    drawArbol(510, 350, 1.3f);
    drawArbol(750, 350, 1.0f);  // arbol izquierdo de la parada
    drawArbol(820, 350, 1.2f);  // arbol derecho de la parada

    // 7. Carretera (GL_QUADS + GL_LINES + GL_LINE_LOOP)
    drawCarretera();

    // 8. Carro rojo (GL_QUADS + GL_POLYGON + GL_LINE_LOOP)
    drawCarro(80, 228);

    // 9. Bancas (GL_QUADS + GL_LINES + GL_LINE_LOOP)
    drawBanca(150, 120);
    drawBanca(720, 120);

    drawMaceta(0, 185);
    drawMaceta(50, 185);
    drawMaceta(100, 185);
    drawMaceta(150, 185);
    drawMaceta(200, 185);
    drawMaceta(250, 185);
    drawMaceta(300, 185);
    drawMaceta(350, 185);

    drawVelero(320, 30, 3.0f);

    drawMaceta(650, 185);
    drawMaceta(700, 185);
    drawMaceta(750, 185);
    drawMaceta(800, 185);
    drawMaceta(850, 185);
    drawMaceta(900, 185);
    drawMaceta(950, 185);
    drawMaceta(1000, 185);


    glFlush();
}

void init()
{
    glClearColor(0.05f, 0.05f, 0.18f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 700);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Parcial OpenGL - Escena Nocturna");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
