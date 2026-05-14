#include <citro2d.h>
#include <3ds.h>

int main(int argc, char* argv[]) {
    // 1. Initialisation des services graphiques
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_BUFSIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    // On crée la cible de rendu pour l'écran du haut
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    // 2. Chargement de la voiture
    // Le chemin "romfs:/gfx/car1.PNG" correspond à ton dossier gfx
    C2D_SpriteSheet spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/car1.PNG");
    
    // Sécurité : si l'image ne charge pas, on affiche un écran bleu pour le savoir
    if (!spriteSheet) {
        while (aptMainLoop()) {
            C3D_FrameBegin(C3D_FRAME_SYNCHRPP);
            C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 1.0f, 1.0f)); // Bleu = Erreur image
            C3D_FrameEnd(0);
        }
    }

    // On récupère la première image de la feuille de sprites
    C2D_Image voiture = C2D_SpriteSheetGetImage(spriteSheet, 0);

    // 3. Boucle principale du jeu
    while (aptMainLoop()) {
        // Scanner les entrées (boutons)
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break; // Quitter le jeu avec START

        // Rendu de l'image
        C3D_FrameBegin(C3D_FRAME_SYNCHRPP);
        C2D_TargetClear(top, C2D_Color32f(0.3f, 0.3f, 0.3f, 1.0f)); // Fond gris bitume
        C2D_SceneBegin(top);

        // On dessine la voiture au centre de l'écran (400x240)
        // Les coordonnées 170, 100 placent la voiture à peu près au milieu
        C2D_DrawImageAt(voiture, 170.0f, 100.0f, 0.5f, NULL, 1.0f, 1.0f);

        C3D_FrameEnd(0);
    }

    // 4. Nettoyage de la mémoire avant de quitter
    C2D_SpriteSheetFree(spriteSheet);
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}
