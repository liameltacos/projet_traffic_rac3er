#include <citro2d.h>
#include <3ds.h>

int main() {
    // Initialisation
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_BUFSIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    // Chargement de TA voiture car1.png
    C2D_SpriteSheet spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/car1.png");
    
    if (!spriteSheet) {
        // Écran bleu si l'image ne charge pas (pratique pour débugger)
        while (aptMainLoop()) {
            C3D_FrameBegin(C3D_FRAME_SYNCHRPP);
            C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 1.0f, 1.0f));
            C3D_FrameEnd(0);
        }
    }

    C2D_Image voiture = C2D_SpriteSheetGetImage(spriteSheet, 0);

    while (aptMainLoop()) {
        hidScanInput();
        if (hidKeysDown() & KEY_START) break; 

        C3D_FrameBegin(C3D_FRAME_SYNCHRPP);
        C2D_TargetClear(top, C2D_Color32f(0.3f, 0.3f, 0.3f, 1.0f)); // Gris route
        C2D_SceneBegin(top);

        // AFFICHAGE AU MILIEU
        // Écran 2DS haut : 400x240
        // On met l'échelle à 1.5f pour qu'elle soit "assez grande mais pas trop"
        // On centre avec 200 (X) et 120 (Y)
        C2D_DrawImageAt(voiture, 200, 120, 0.5f, NULL, 1.5f, 1.5f);

        C3D_FrameEnd(0);
    }

    C2D_SpriteSheetFree(spriteSheet);
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}
