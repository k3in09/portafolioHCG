#include <windows.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// ---- Variables globales ----
float posX = -100.0f;
float posY = 20.0f;      // Carril inferior (izq a der)
int opcion = 2;
float colorShift = 0.0f;
float angulo = 0.0f;

// --- VARIABLES PARA LOS CARROS EXTRA ---
// Carro 2: Azul, carril superior, mirando y viajando hacia la izquierda
float carro2_X = 1100.0f;
float carro2_Y = 125.0f;

// Carro 3: Amarillo, carril central, mirando y viajando hacia la derecha
float carro3_X = -300.0f;
float carro3_Y = 65.0f;

// ---- TEXTO ----
void drawText(float x, float y, float scale, const char* text) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
    for (size_t i = 0; i < strlen(text); i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    glPopMatrix();
}

// ---- AUXILIARES ----
void dibujarCirculo(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float ang = 2.0f * 3.14159f * i / 100;
        glVertex2f(cx + r * cos(ang), cy + r * sin(ang));
    }
    glEnd();
}

void dibujarCirculoContorno(float cx, float cy, float r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 60; i++) {
        float ang = 2.0f * 3.14159f * i / 60;
        glVertex2f(cx + r * cos(ang), cy + r * sin(ang));
    }
    glEnd();
}

void dibujarEstrellaRin(float cx, float cy, float rMax, float rMin) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 10; i++) {
        float ang = i * (2.0f * 3.14159f / 10.0f) - (3.14159f / 2.0f);
        float r = (i % 2 == 0) ? rMax : rMin;
        glVertex2f(cx + r * cos(ang), cy + r * sin(ang));
    }
    glEnd();
}

// ---- LUNA ----
void dibujarLuna(float x, float y) {
    glColor3f(1.0f, 0.98f, 0.85f);
    dibujarCirculo(x, y, 28);
    glColor3f(0.05f, 0.05f, 0.18f);
    dibujarCirculo(x + 14, y + 5, 24);
    glColor4f(1.0f, 0.98f, 0.75f, 0.08f);
    dibujarCirculo(x, y, 42);
}

// ---- PLANTILLA DE CARRO ----
void dibujarCarroParametrizado(float px, float py, float ang, float r, float g, float b, int rotar180) {
    glPushMatrix();
    glTranslatef(px, py, 0);

    if (rotar180) {
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    }

    glRotatef(ang, 0, 0, 1);

    // Sombra del carro en el suelo
    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(-88, -3); glVertex2f(88, -3);
        glVertex2f(82, 6);   glVertex2f(-82, 6);
    glEnd();

    // ---- CUERPO PRINCIPAL ----
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
        glVertex2f(-88, 10);  glVertex2f(-88, 28);
        glVertex2f(-75, 36);  glVertex2f(-55, 38);
        glVertex2f(-8,  38);  glVertex2f(-5,  48);
        glVertex2f(20,  62);  glVertex2f(55,  62);
        glVertex2f(68,  52);  glVertex2f(78,  42);
        glVertex2f(88,  38);  glVertex2f(88,  14);
        glVertex2f(78,  10);
    glEnd();

    // Techo más oscuro
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(-5,  48);  glVertex2f(20,  63);
        glVertex2f(55,  63);  glVertex2f(68,  52);
        glVertex2f(50,  48);  glVertex2f(10,  48);
    glEnd();

    // Franja lateral plateada
    glColor3f(0.75f, 0.75f, 0.80f);
    glBegin(GL_POLYGON);
        glVertex2f(-86, 16); glVertex2f(84, 16);
        glVertex2f(84, 20);  glVertex2f(-86, 20);
    glEnd();

    // PARABRISAS DELANTERO
    glColor3f(0.1f, 0.15f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(-6, 39);   glVertex2f(-3, 48);
        glVertex2f(18, 61);   glVertex2f(14, 61);
        glVertex2f(-8, 48);   glVertex2f(-10, 39);
    glEnd();

    // Reflejo en parabrisas
    glColor3f(0.4f, 0.5f, 0.75f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-4, 42); glVertex2f(12, 57);
    glEnd();

    // VENTANA LATERAL
    glColor3f(0.1f, 0.15f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(14,  61);  glVertex2f(50,  61);
        glVertex2f(62,  52);  glVertex2f(52,  49);
        glVertex2f(16,  49);
    glEnd();

    // LÍNEAS DE CARROCERÍA
    glColor3f(r*0.5f, g*0.5f, b*0.5f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(-10, 10); glVertex2f(-10, 38);
        glVertex2f(52,  10); glVertex2f(55, 50);
    glEnd();

    // SPOILER TRASERO
    glColor3f(0.10f, 0.10f, 0.10f);
    glBegin(GL_POLYGON);
        glVertex2f(60, 62); glVertex2f(88, 62);
        glVertex2f(88, 66); glVertex2f(60, 66);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2f(66, 62); glVertex2f(68, 42);
        glVertex2f(82, 62); glVertex2f(80, 42);
    glEnd();

    // FARO DELANTERO LED
    glColor3f(r*0.6f, g*0.6f, b*0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-88, 28); glVertex2f(-72, 30);
        glVertex2f(-68, 22); glVertex2f(-86, 20);
    glEnd();
    glColor3f(0.95f, 0.97f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-87, 27); glVertex2f(-73, 29);
        glVertex2f(-70, 23); glVertex2f(-85, 21);
    glEnd();
    glColor3f(1.0f, 0.65f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-88, 18); glVertex2f(-70, 18);
        glVertex2f(-70, 21); glVertex2f(-88, 21);
    glEnd();

    // LUZ TRASERA LED
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(72, 36); glVertex2f(88, 38);
        glVertex2f(88, 26); glVertex2f(76, 26);
    glEnd();
    glColor3f(1.0f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(75, 35); glVertex2f(88, 37);
        glVertex2f(88, 33); glVertex2f(75, 31);
    glEnd();

    // DIFUSOR TRASERO
    glColor3f(0.08f, 0.08f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(72, 10); glVertex2f(88, 10);
        glVertex2f(88, 16); glVertex2f(72, 14);
    glEnd();

    // ENTRADA DE AIRE LATERAL
    glColor3f(0.08f, 0.08f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(28, 30); glVertex2f(46, 30);
        glVertex2f(46, 36); glVertex2f(28, 36);
    glEnd();

    // MANIJA PUERTA
    glColor3f(0.8f, 0.8f, 0.85f);
    glBegin(GL_QUADS);
        glVertex2f(18, 44); glVertex2f(28, 44);
        glVertex2f(28, 46); glVertex2f(18, 46);
    glEnd();

    // LOGO
    glColor3f(0.85f, 0.85f, 0.9f);  dibujarCirculo(-35, 38, 5);
    glColor3f(0.5f, 0.0f, 0.0f);     dibujarCirculo(-35, 38, 3);

    // LLANTAS
    glColor3f(0.08f, 0.08f, 0.08f);  dibujarCirculo(-50, 10, 23);
    glColor3f(0.45f, 0.45f, 0.50f);  dibujarCirculo(-50, 10, 15);
    glColor3f(0.12f, 0.12f, 0.12f);  dibujarEstrellaRin(-50, 10, 14, 6);
    glColor3f(0.85f, 0.85f, 0.9f);   dibujarCirculo(-50, 10, 4);
    glColor3f(0.3f, 0.3f, 0.35f);    dibujarCirculoContorno(-50, 10, 21);

    glColor3f(0.08f, 0.08f, 0.08f);  dibujarCirculo(56, 10, 23);
    glColor3f(0.45f, 0.45f, 0.50f);  dibujarCirculo(56, 10, 15);
    glColor3f(0.12f, 0.12f, 0.12f);  dibujarEstrellaRin(56, 10, 14, 6);
    glColor3f(0.85f, 0.85f, 0.9f);   dibujarCirculo(56, 10, 4);
    glColor3f(0.3f, 0.3f, 0.35f);    dibujarCirculoContorno(56, 10, 21);

    glPopMatrix();
}

// ---- EDIFICIO GENÉRICO ----
void dibujarEdificio(float x, float baseY, float w, float h, float r, float g, float b, int filaVentanas, int colVentanas) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
        glVertex2f(x, baseY); glVertex2f(x+w, baseY);
        glVertex2f(x+w, baseY+h); glVertex2f(x, baseY+h);
    glEnd();
    glColor3f(r*0.6f, g*0.6f, b*0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(x+w, baseY); glVertex2f(x+w+8, baseY+12);
        glVertex2f(x+w+8, baseY+h+12); glVertex2f(x+w, baseY+h);
    glEnd();
    glColor3f(r*0.5f, g*0.5f, b*0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(x, baseY+h); glVertex2f(x+w, baseY+h);
        glVertex2f(x+w+8, baseY+h+12); glVertex2f(x+8, baseY+h+12);
    glEnd();

    float wVent = (w - (colVentanas+1)*6.0f) / colVentanas;
    float hVent = 10.0f;
    float xGap = 6.0f;
    float yGap = 14.0f;
    for(int row = 0; row < filaVentanas; row++) {
        for(int col = 0; col < colVentanas; col++) {
            float vx = x + xGap + col*(wVent+xGap);
            float vy = baseY + yGap + row*(hVent+yGap);
            if(vy + hVent < baseY + h) {
                if((row+col)%3 != 0)
                    glColor3f(0.95f, 0.9f, 0.5f);
                else
                    glColor3f(0.1f, 0.12f, 0.18f);
                glBegin(GL_QUADS);
                    glVertex2f(vx, vy); glVertex2f(vx+wVent, vy);
                    glVertex2f(vx+wVent, vy+hVent); glVertex2f(vx, vy+hVent);
                glEnd();
            }
        }
    }
}

// ---- TORRE / ANTENA ----
void dibujarTorre(float x, float baseY) {
    glColor3f(0.35f, 0.38f, 0.42f);
    glBegin(GL_POLYGON);
        glVertex2f(x-8, baseY); glVertex2f(x+8, baseY);
        glVertex2f(x+5, baseY+180); glVertex2f(x-5, baseY+180);
    glEnd();
    glColor3f(0.45f, 0.48f, 0.52f);
    glBegin(GL_POLYGON);
        glVertex2f(x-22, baseY+160); glVertex2f(x+22, baseY+160);
        glVertex2f(x+18, baseY+195); glVertex2f(x-18, baseY+195);
    glEnd();
    glColor3f(0.7f, 0.1f, 0.1f);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(x, baseY+195); glVertex2f(x, baseY+240);
    glEnd();
    float bright = (sin(colorShift * 3) + 1) * 0.5f;
    glColor3f(bright, 0.0f, 0.0f);
    dibujarCirculo(x, baseY+240, 4);

    glColor3f(0.3f, 0.32f, 0.36f);
    glLineWidth(2);
    for(int i = 0; i < 4; i++) {
        float ty = baseY + 30 + i*35;
        glBegin(GL_LINES);
            glVertex2f(x - (7 - i), ty); glVertex2f(x-28, ty);
            glVertex2f(x + (7 - i), ty); glVertex2f(x+28, ty);
        glEnd();
    }
}

// ---- MONTAÑA EN SILUETA ----
void dibujarMontania(float x, float baseY, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, baseY); glVertex2f(x + w/2, baseY + h); glVertex2f(x + w, baseY);
    glEnd();
    glColor3f(0.85f, 0.88f, 0.92f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x + w*0.35f, baseY + h*0.72f); glVertex2f(x + w/2, baseY + h); glVertex2f(x + w*0.65f, baseY + h*0.72f);
    glEnd();
}

// ---- PUENTE ----
void dibujarPuente(float x, float y) {
    glColor3f(0.28f, 0.28f, 0.32f);
    glBegin(GL_POLYGON);
        glVertex2f(x, y); glVertex2f(x+200, y);
        glVertex2f(x+200, y+18); glVertex2f(x, y+18);
    glEnd();
    glColor3f(0.5f, 0.52f, 0.56f);
    glLineWidth(1.5f);
    float torres[2] = {x+40.0f, x+160.0f};
    for(int t = 0; t < 2; t++) {
        glBegin(GL_LINES);
            glVertex2f(torres[t], y+18); glVertex2f(torres[t], y+70);
        glEnd();
    }
    glLineWidth(1);
    for(int i = 0; i <= 12; i++) {
        float cx = x + 10 + i*15;
        float midH = y + 18 + 20 - abs(i - 6)*3;
        glBegin(GL_LINES);
            glVertex2f(cx, y+18); glVertex2f(cx, midH);
        glEnd();
    }
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i <= 20; i++) {
        float t = i / 20.0f;
        float cx = x + t*200;
        float cy = y + 70 - 52*4*(t - 0.5f)*(t - 0.5f);
        glVertex2f(cx, cy);
    }
    glEnd();
}

// ---- PAISAJE COMPLETO ----
void paisaje() {
    // CIELO NOCTURNO
    glBegin(GL_POLYGON);
        glColor3f(0.02f, 0.02f, 0.10f); glVertex2f(0, 600);
        glColor3f(0.02f, 0.02f, 0.10f); glVertex2f(1000, 600);
        glColor3f(0.05f, 0.08f, 0.22f); glVertex2f(1000, 300);
        glColor3f(0.05f, 0.08f, 0.22f); glVertex2f(0, 300);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.05f, 0.08f, 0.22f); glVertex2f(0, 300);
        glColor3f(0.05f, 0.08f, 0.22f); glVertex2f(1000, 300);
        glColor3f(0.08f, 0.14f, 0.30f); glVertex2f(1000, 150);
        glColor3f(0.08f, 0.14f, 0.30f); glVertex2f(0, 150);
    glEnd();

    // ESTRELLAS
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    int sx[] = {50,120,200,280,340,410,490,560,620,700,780,850,930,80,160,250,330,470,540,610,690,760,840,910,30,140,220,360,430,510,580,660,740,820,960};
    int sy[] = {520,540,510,560,535,520,545,530,555,540,520,510,525,480,495,470,490,465,488,475,495,470,480,460,420,435,415,440,428,415,432,445,418,450,430};
    for(int i = 0; i < 35; i++) {
        float b = 0.6f + 0.4f * sin(colorShift * 1.5f + i * 0.8f);
        glColor3f(b, b, b*0.9f);
        glVertex2f(sx[i], sy[i]);
    }
    glEnd();

    dibujarLuna(870, 510);

    // MONTAÑAS
    dibujarMontania(-40, 150, 380, 220, 0.10f, 0.11f, 0.18f);
    dibujarMontania(120, 150, 320, 190, 0.08f, 0.09f, 0.15f);
    dibujarMontania(350, 150, 300, 200, 0.09f, 0.10f, 0.17f);
    dibujarMontania(600, 150, 350, 180, 0.07f, 0.08f, 0.14f);
    dibujarMontania(750, 150, 280, 210, 0.10f, 0.11f, 0.19f);

    // EDIFICIOS LEJANOS
    dibujarEdificio(20,  150, 55, 120, 0.10f, 0.10f, 0.16f, 5, 2);
    dibujarEdificio(90,  150, 40,  90, 0.09f, 0.09f, 0.15f, 4, 1);
    dibujarEdificio(840, 150, 50, 110, 0.10f, 0.10f, 0.16f, 4, 2);
    dibujarEdificio(900, 150, 45, 135, 0.09f, 0.09f, 0.14f, 6, 2);
    dibujarEdificio(950, 150, 60,  95, 0.08f, 0.08f, 0.13f, 4, 2);

    // EDIFICIOS PRINCIPALES
    dibujarEdificio(0,   150, 70, 180, 0.18f, 0.18f, 0.26f, 7, 2);
    dibujarEdificio(80,  150, 55, 145, 0.15f, 0.16f, 0.24f, 6, 2);
    dibujarEdificio(145, 150, 80, 200, 0.20f, 0.18f, 0.28f, 8, 3);
    dibujarEdificio(390, 150, 65, 160, 0.16f, 0.16f, 0.24f, 6, 2);
    dibujarEdificio(465, 150, 75, 220, 0.22f, 0.20f, 0.30f, 9, 3);
    dibujarEdificio(550, 150, 60, 175, 0.18f, 0.18f, 0.26f, 7, 2);
    dibujarEdificio(700, 150, 75, 190, 0.19f, 0.18f, 0.27f, 7, 2);
    dibujarEdificio(785, 150, 55, 150, 0.16f, 0.16f, 0.24f, 6, 2);

    dibujarTorre(500, 270);
    dibujarPuente(300, 148);

    // LETRERO NEÓN
    float r = (sin(colorShift) + 1) / 2;
    float g = (sin(colorShift + 2.1f) + 1) / 2;
    float b = (sin(colorShift + 4.2f) + 1) / 2;

    glColor3f(0.25f, 0.25f, 0.30f);
    glLineWidth(6);
    glBegin(GL_LINES);
        glVertex2f(305, 340); glVertex2f(305, 380);
        glVertex2f(695, 340); glVertex2f(695, 380);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(205, 370); glVertex2f(795, 370);
        glVertex2f(795, 480); glVertex2f(205, 480);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
        glColor3f(r, g, b); glVertex2f(208, 373);
        glColor3f(b, r, g); glVertex2f(792, 373);
        glColor3f(g, b, r); glVertex2f(792, 477);
        glColor3f(r, b, g); glVertex2f(208, 477);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glColor3f(g, r, b); glVertex2f(216, 381);
        glColor3f(r, b, g); glVertex2f(784, 381);
        glColor3f(b, g, r); glVertex2f(784, 469);
        glColor3f(g, b, r); glVertex2f(216, 469);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);      drawText(252, 410, 0.32f, "THE MULTIFUNTION");
    glColor3f(r, g, b);               drawText(250, 412, 0.32f, "THE MULTIFUNTION");

    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(g, b, r); glVertex2f(280, 358);
        glColor3f(b, r, g); glVertex2f(720, 358);
    glEnd();

    glColor3f(r, g, b);
    dibujarCirculo(208, 373, 4); dibujarCirculo(792, 373, 4);
    dibujarCirculo(208, 477, 4); dibujarCirculo(792, 477, 4);

    // FAROLAS
    float farX[] = {80, 200, 400, 600, 800, 950};
    for(int i = 0; i < 6; i++) {
        glColor3f(0.35f, 0.35f, 0.40f);
        glLineWidth(3);
        glBegin(GL_LINES);
            glVertex2f(farX[i], 150); glVertex2f(farX[i], 265);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(farX[i], 265); glVertex2f(farX[i]+18, 270);
        glEnd();
        float brightFar = 0.85f + 0.15f * sin(colorShift + i);
        glColor3f(brightFar, brightFar*0.85f, brightFar*0.3f);
        dibujarCirculo(farX[i]+18, 270, 6);
        glColor4f(1.0f, 0.9f, 0.4f, 0.04f);
        dibujarCirculo(farX[i]+18, 150, 40);
    }

    // CARRETERA
    glColor3f(0.10f, 0.10f, 0.11f);
    glBegin(GL_POLYGON);
        glVertex2f(0, 0); glVertex2f(1000, 0);
        glVertex2f(1000, 150); glVertex2f(0, 150);
    glEnd();

    glColor3f(0.9f, 0.75f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(0, 148); glVertex2f(1000, 148);
    glEnd();

    glColor3f(0.85f, 0.70f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(0, 82); glVertex2f(1000, 82);
        glVertex2f(0, 76); glVertex2f(1000, 76);
    glEnd();

    // Líneas intermitentes blancas
    glColor3f(0.92f, 0.92f, 0.92f);
    for(int i = -20; i < 1050; i += 90) {
        glBegin(GL_QUADS);
            glVertex2f(i, 38); glVertex2f(i+55, 38);
            glVertex2f(i+55, 44); glVertex2f(i, 44);
        glEnd();
    }

    // Líneas intermitentes blancas
    for(int i = 10; i < 1050; i += 90) {
        glBegin(GL_QUADS);
            glVertex2f(i, 108); glVertex2f(i+55, 108);
            glVertex2f(i+55, 114); glVertex2f(i, 114);
        glEnd();
    }

    // Borde inferior
    glColor3f(0.25f, 0.25f, 0.28f);
    glBegin(GL_POLYGON);
        glVertex2f(0, 0); glVertex2f(1000, 0);
        glVertex2f(1000, 5); glVertex2f(0, 5);
    glEnd();
}

// ---- DISPLAY ----
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    if(opcion == 1) {
        paisaje();
    } else if(opcion == 2) {
        paisaje();

        // Carro 1: Rojo
        dibujarCarroParametrizado(posX, posY, angulo, 0.85f, 0.05f, 0.05f, 1);

        // Carro 2: Azul
        dibujarCarroParametrizado(carro2_X, carro2_Y, 0.0f, 0.05f, 0.35f, 0.85f, 0);

        // Carro 3: Amarillo
        dibujarCarroParametrizado(carro3_X, carro3_Y, 0.0f, 0.90f, 0.75f, 0.0f, 1);

    } else if(opcion == 3) {
        paisaje();
        glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
        glBegin(GL_POLYGON);
            glVertex2f(200, 150); glVertex2f(800, 150);
            glVertex2f(800, 320); glVertex2f(200, 320);
        glEnd();
        float r = (sin(colorShift) + 1) / 2;
        float g = (sin(colorShift + 2) + 1) / 2;
        float b = (sin(colorShift + 4) + 1) / 2;
        glColor3f(r, g, b);
        drawText(260, 260, 0.28f, "PROYECTO 2");
        glColor3f(0.8f, 0.8f, 0.8f);
        drawText(300, 210, 0.20f, "GRUPO: THE MULTIFUNTION");
    }

    glutSwapBuffers();
}

// ---- TIMER ----
void timer(int value) {
    colorShift += 0.04f;

    if(opcion == 2) {
        // Carro 1 (Rojo): Va de frente hacia la derecha
        posX += 3.8f;
        if(posX > 1150.0f) posX = -120.0f;

        // Carro 2 (Azul): Carril superior
        carro2_X -= 4.2f;
        if(carro2_X < -150.0f) carro2_X = 1150.0f;

        // Carro 3 (Amarillo):Carril central
        carro3_X += 5.0f;
        if(carro3_X > 1150.0f) carro3_X = -150.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ---- TECLADO ESPECIAL ----
void specialKeyInput(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:  posX -= 12; angulo =  1.5f; break;
        case GLUT_KEY_RIGHT: posX += 12; angulo = -1.5f; break;
        case GLUT_KEY_UP:    posY += 8;  break;
        case GLUT_KEY_DOWN:  posY -= 8;  break;
    }
    glutPostRedisplay();
}

// ---- MENÚ ----
void menu(int value) {
    if(value == 4) exit(0);
    opcion = value;
    glutPostRedisplay();
}

// ---- MAIN ----
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("The Multifuntion - Proyecto 2");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeyInput);
    glutTimerFunc(0, timer, 0);

    glutCreateMenu(menu);
    glutAddMenuEntry("Solo Paisaje Nocturno", 1);
    glutAddMenuEntry("Ver Trafico de Autos", 2);
    glutAddMenuEntry("Pantalla de Creditos", 3);
    glutAddMenuEntry("Salir", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
