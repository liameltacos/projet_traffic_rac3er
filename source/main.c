#include <citro2d.h>
#include <3ds.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // 1. Initialisation des graphismes et de Citro2D
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_BUFSIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    // Création de la cible de rendu (l'écran du haut)
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    // 2. Chargement de la texture
    // On cherche l'image dans le dossier romfs:/gfx/
    C2D_SpriteSheet spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/car1.PNG");
    
    // Si l'image ne charge pas (erreur), on affiche un écran rouge
    if (!spriteSheet) {
        while (aptMainLoop()) {
            C3D_FrameBegin(C3D_FRAME_SYNCHRPP);
            C2D_TargetClear(top, C2D_Color32f(1.0f, 0.0f, 0.0f, 1.0f));
            C3D_FrameEnd(0);
        }
    }

    // On récupère la première image de la planche (index 0)
    C2D_Image voiture = C2D_SpriteSheetGetImage(spriteSheet, 0);

    // 3. Boucle principale du jeu
    while (aptMainLoop()) {
        // Lire les touches pressées
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break; // Appuie sur START pour quitter

        // Début du rendu
        C3D_FrameBegin(C3D_FRAME_SYNCHRPP);
        C2D_TargetClear(top, C2D_Color32f(0.2f, 0.2f, 0.2f, 1.0f)); // Fond gris foncé
        C2D_SceneBegin(top);

        // Dessiner la voiture (X: 160, Y: 100)
        C2D_DrawImageAt(voiture, 160.0f, 100.0f, 0.5f, NULL, 1.0f, 1.0f);

        // Fin du rendu
        C3D_FrameEnd(0);
    }

    // 4. Nettoyage avant de quitter
    C2D_SpriteSheetFree(spriteSheet);
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}
