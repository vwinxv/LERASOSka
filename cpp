
#include "Model.hpp"

Model::Model()
{
    SDL_Log("[Model::Model] %p", this);
}

Model::~Model()
{
    SDL_Log("[Model::~Model] %p", this);

}

SDL_AppResult Model::init()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("[Model::init] Couldn't init SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(!SDL_CreateWindowAndRenderer(
            "Model"
            , 480, 360
            , 0
            , &this->window
            , &this->renderer
            )
        )
    {
        SDL_Log("[Model::init] Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    this -> initMechanism();

    return SDL_APP_CONTINUE;
}

SDL_AppResult Model::onEvent(SDL_Event *event)
{
    switch(event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult Model::iterate()
{
    this -> clearWindow();

    this -> renderMechanism();

    SDL_RenderPresent(this -> renderer);
    return SDL_APP_CONTINUE;
}

void Model::clearWindow()
{
    SDL_SetRenderDrawColorFloat(
        this->renderer
        , 0.5f, 0.5f, 0.5f
        , SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(this -> renderer);
}

void Model::initMechanism(){
    this-> t0 = this->createBaseTexture();

    this->p1 = {200.0f, 100.0f};
    this->p2 = {400.0f, 200.0f};
}

void Model::renderMechanism(){
/*    SDL_SetRenderDrawColorFloat(
        this->renderer
        , 0.0f, 0.0f, 0.0f
        , SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderLine(
        this-> renderer
        , this -> p1.x, this -> p1.y, this -> p2.x, this->p2.y
        );
*/
    SDL_FRect r0 = {100.0f,300.0f, 100.0f, 100.0f};
    SDL_RenderTexture( this->renderer, this -> t0, nullptr,&r0);
    SDL_FRect r1 = {300.0f,50.0f, 100.0f, 100.0f};
    SDL_FPoint c1 = {50.0f,50.0f};
    SDL_RenderTextureRotated( this->renderer, this -> t0, nullptr, &r1, -90.0, &c1, SDL_FLIP_NONE);
}

SDL_Texture *Model::createBaseTexture(){
    SDL_Surface *surface = SDL_CreateSurface(
        100, 100,
        SDL_PIXELFORMAT_RGBA32
        );
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);
    SDL_FPoint base[4];
    base[0] = base[3] = {50.0f, 50.0f};
    base[1] = {10.0f, 90.0f};
    base[2] = {90.0f, 90.0f};
    SDL_SetRenderDrawColorFloat(
        renderer
        , 0.0f, 0.0f, 0.0f
        , SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderLines(
        renderer, base, SDL_arraysize(base));

    SDL_RenderPresent(renderer);
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroySurface(surface);
    return texture;
}
