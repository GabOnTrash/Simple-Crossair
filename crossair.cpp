#include "crossair.hpp"

Crossair::Crossair()
	: active(true), crossSize(40.0f), thickness(crossSize / 7), menuAttivo(false), f2Premuto(false), numeroMenu(0), windowWidth(static_cast<int>(crossSize)), windowHeight(static_cast<int>(crossSize)), coloreCorrente{ 0.5f, 0.0f, 0.5f }
{
    if (!glfwInit())
    {
        glfwTerminate();
        return;
    }

    mappaColore = {

        { GLFW_KEY_R, { 0.5f, 0.0f, 0.0f } },
        { GLFW_KEY_O, { 0.5f, 0.30f, 0.13f } },
        { GLFW_KEY_Y, { 0.5f, 0.45f, 0.2f } },
        { GLFW_KEY_G, { 0.0f, 0.5f, 0.0f } },
        { GLFW_KEY_B, { 0.0f, 0.2f, 0.5f } },
        { GLFW_KEY_P, { 0.5f, 0.0f, 0.5f } },
        { GLFW_KEY_W, { 1.0f, 1.0f, 1.0f } },
        { GLFW_KEY_K, { 0.0f, 0.0f, 0.0f } },
        { GLFW_KEY_M, { 0.5f, 0.5f, 0.5f } } 
    };

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);                                                                         // Finestra senza decorazioni
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);                                                                           // Finestra sempre in primo piano
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);                                                              // Framebuffer trasparente
    window = glfwCreateWindow(windowWidth, windowHeight, "Crossair", nullptr, nullptr);


    mode = glfwGetVideoMode(glfwGetPrimaryMonitor());                                                // fa return della modalità dello schermo, quello principale, e restituisce lo stato della finestra, schermo intero, iconificata ecc...
    screenWidth = mode->width;                                                                                      // otteniamo la larghezza dello schermo
    screenHeight = mode->height;                                                                                    // otteniamo la altezza dello schermo
    glfwSetWindowPos(window, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);

    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Crossair::Start()
{
    while (!glfwWindowShouldClose(window))
    {
        // Aggiorna l'area di visualizzazione e il sistema di coordinate
        glClear(GL_COLOR_BUFFER_BIT);                                                                                   // pulisce il background, usando il colore definito da glClearColor
        glViewport(0, 0, windowWidth, windowHeight);                                                                    // adatta tutti i pixel della finestra alla viewport, in caso la grandezza della finestra cambi
        glMatrixMode(GL_PROJECTION);                                                                                    // si occupa, attraverso una matrice di trasformare le coordinate della scena in coordinate dello schermo, PROIEZIONE
        glLoadIdentity();                                                                                               // resetta la matrice di PROIEZIONE per "pulirla" in modo da renderla pronta per ricevere nuove trasformazioni        
        glOrtho(0, windowWidth, windowHeight, 0, -1, 1);                                                                // imposta una proiezione ortografica, orizzontale per i primi due parametri, verticale con param 3 e 4 e -1 e 1 per il range di profondità (la freccia è 2d)
        glMatrixMode(GL_MODELVIEW);                                                                                     // si occupa di rendere 3D il modello, e le trasformazioni verranno applicate da quel punto in avanti
        glLoadIdentity();

        // Switch del menù
        if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
            f2Premuto = true;
        else if (f2Premuto && glfwGetKey(window, GLFW_KEY_F2) == GLFW_RELEASE)  // lo switch si sviluppa sull'else if, dopo aver premuto f2, non si verifica subito l'altra condizione, ma si aspetta un giro, e poi si verifica se esso è attivo e viene rilasciato il tasto
        {
            f2Premuto = false;
            menuAttivo = !menuAttivo; // Switch del menu
        }
        if (menuAttivo)
            menu(crossSize, thickness, active, numeroMenu, coloreCorrente, mappaColore, window);

        // Aggiorna la finestra per mantenere la croce centrata
        windowWidth = static_cast<int>(crossSize);
        windowHeight = static_cast<int>(crossSize);
        glfwSetWindowSize(window, windowWidth, windowHeight);                                                           // setta la grandezza della finestra
        glfwSetWindowPos(window, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);                   // setta la posizione dello schermo

        // disegna la croce
        drawCross(thickness, crossSize, windowWidth, windowHeight, coloreCorrente);

        glfwSwapBuffers(window);
        glfwPollEvents();                                                                                               // chiama tutti gli eventi e garantisce che tutte le funzioni di callback restituiscano un valore (funzioni di input)
    }

    glfwDestroyWindow(window);                                                                                          // elimina la finestra
    glfwTerminate();                                                                                                    // termina le funzionalità glfw e openGl
}

void Crossair::drawCross(float thickness, float crossSize, int windowWidth, int windowHeight, Colore& coloreCorrente)
{
    glPushMatrix();

    // Trasla la croce al centro della finestra
    glTranslatef(windowWidth / 2.0f, windowHeight / 2.0f, 0.0f);

    // Imposta il colore usando la funzione che punta al primo elemento dell'array, glColor3fv poi si sposta di 4 byte sulla memoria del puntatore fornito, per ottenere gli altri colori float, essendo essi dichiarati in modo contiguo
    glColor3fv(coloreCorrente.Array());

    // Disegna la parte orizzontale della croce
    glBegin(GL_QUADS);
    glVertex2f(-crossSize / 2.0f, thickness / 2.0f);
    glVertex2f(crossSize / 2.0f, thickness / 2.0f);
    glVertex2f(crossSize / 2.0f, -thickness / 2.0f);
    glVertex2f(-crossSize / 2.0f, -thickness / 2.0f);
    glEnd();

    // Disegna la parte verticale della croce
    glBegin(GL_QUADS);
    glVertex2f(-thickness / 2.0f, crossSize / 2.0f);
    glVertex2f(thickness / 2.0f, crossSize / 2.0f);
    glVertex2f(thickness / 2.0f, -crossSize / 2.0f);
    glVertex2f(-thickness / 2.0f, -crossSize / 2.0f);
    glEnd();

    glPopMatrix();
}
void Crossair::menu(float& crossSize, float& thickness, bool& active, int& numeroMenu, Colore& coloreCorrente, std::map<int, Colore>& mappaColore, GLFWwindow* window)
{
    if (active == true && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        active = false;
        crossSize += 20.0f;

        if (crossSize >= 170.0f) crossSize = 170.0f; // Limita la dimensione massima
        thickness = crossSize / 7.0f;
    }
    if (active == true && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        active = false;
        crossSize -= 20.0f;
        if (crossSize < 20.0f) crossSize = 20.0f; // Limita la dimensione minima
        thickness = crossSize / 7.0f;
    }

    if (active)
    {
        for (const auto& [tasto, RGB] : mappaColore)    // foreach loop di tipo const auto, la reference è usata per sopperire alla grandezza della mappa, si itera nella mappa colore
        {
            if (glfwGetKey(window, tasto) == GLFW_PRESS)
            {
                active = false;
                coloreCorrente = RGB;
                break;
            }
        }
    }

    numeroMenu++;
    if (numeroMenu >= 30)
    {
        active = true;
        numeroMenu = 0;
    }
}
