#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>
#include "PerlinNoise.c"

using namespace std;

int main( int argc, char** argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    atexit( SDL_Quit );

    SDL_Window* window = SDL_CreateWindow
        (
        "SDL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        600, 600,
        SDL_WINDOW_SHOWN
        );

    SDL_Renderer* renderer = SDL_CreateRenderer
        (
        window,
        -1,
        SDL_RENDERER_ACCELERATED
        );

    SDL_RendererInfo info;
    SDL_GetRendererInfo( renderer, &info );
    cout << "Renderer name: " << info.name << endl;
    cout << "Texture formats: " << endl;
    for( Uint32 i = 0; i < info.num_texture_formats; i++ )
    {
        cout << SDL_GetPixelFormatName( info.texture_formats[i] ) << endl;
    }

    const unsigned int texWidth = 1024;
    const unsigned int texHeight = 1024;
    SDL_Texture* texture = SDL_CreateTexture
        (
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        texWidth, texHeight
        );

    vector< unsigned char > pixels( texWidth * texHeight * 4, 0 );

    SDL_Event event;
    bool running = true;

    for(int i = 0; i < texWidth; i++){
      for(int j = 0; j < texHeight; j++){
	unsigned int offset = texWidth * 4 * j + i * 4;
	double theNoise = (PerlinNoise(i/10.0, j/10.0, 10, .01) + 1)/2;
	pixels[ offset + 0 ] = theNoise * 256;        // b
	pixels[ offset + 1 ] = theNoise * 256;        // g
	pixels[ offset + 2 ] = theNoise * 256;
	pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a
      }
    }
    while( running )
    {
        const Uint64 start = SDL_GetPerformanceCounter();

        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );

        while( SDL_PollEvent( &event ) )
        {
            if( ( SDL_QUIT == event.type ) ||
                ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
            {
                running = false;
                break;
            }
        }


        // splat down some random pixels

        // for( unsigned int i = 0; i < 10000; i++ )
        // {
        //     const unsigned int x = rand() % texWidth;
        //     const unsigned int y = rand() % texHeight;

        //     const unsigned int offset = ( texWidth * 4 * y ) + x * 4;
        //     pixels[ offset + 0 ] = rand() % 256;        // b
        //     pixels[ offset + 1 ] = rand() % 256;        // g
        //     pixels[ offset + 2 ] = rand() % 256;        // r
        //     pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a
        // }

        //unsigned char* lockedPixels;
        //int pitch;
        //SDL_LockTexture
        //    (
        //    texture,
        //    NULL,
        //    reinterpret_cast< void** >( &lockedPixels ),
        //    &pitch
        //    );
        //std::copy( pixels.begin(), pixels.end(), lockedPixels );
        //SDL_UnlockTexture( texture );

        SDL_UpdateTexture
            (
            texture,
            NULL,
            &pixels[0],
            texWidth * 4
            );

        SDL_RenderCopy( renderer, texture, NULL, NULL );
        SDL_RenderPresent( renderer );

        const Uint64 end = SDL_GetPerformanceCounter();
        const static Uint64 freq = SDL_GetPerformanceFrequency();
        const double seconds = ( end - start ) / static_cast< double >( freq );
        cout << "Frame time: " << seconds * 1000.0 << "ms" << endl;
    }
    

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}
