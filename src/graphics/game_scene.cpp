#include "../utils/utils.hpp"
#include "../utils/cube_exceptions.hpp"
#include "../utils/logger_manager.hpp"
#include "../game_config.hpp"
#include "game_scene.hpp"
#include "text.hpp"

cube::GameScene::GameScene(const cube::GameConfig &gameConfig) try:
    p_Surface(utils::sdl_safe_create_surface(gameConfig.width,gameConfig.height), &SDL_FreeSurface)
{

}
catch (const cubeexcept::SdlSurfaceCreateException &e) {
    LoggerManager::GetInstance().GetLogger()->error(e.what());
}
cube::GameScene::~GameScene() {}

void cube::GameScene::UpdateScene() {
    p_Renderer->PrepareScene();


    p_Renderer->Render();
    DrawScene();
}

void cube::GameScene::EventKeyPressed(SDL_Keycode key) {
    OnKeyPressed(key);
}


void cube::GameScene::WriteText(int x, int y, const std::string &text,const cube::color_t &color)
{
    Text textWriter;
    textWriter.SetRenderMethod(Text::ETextRenderMethod::TextRenderSolid);

    Text::Font font("/usr/share/fonts/TTF/DejaVuSans.ttf",25,TTF_STYLE_BOLD,TTF_HINTING_NORMAL);

    SDL_Surface  *surface = textWriter.SetText(25,25,text,font,color,color);
    p_Renderer->RenderText(surface);
    SDL_FreeSurface(surface);
}

void cube::GameScene::SetRenderer(RenderManager* renderer) {
    p_Renderer.reset(renderer);
}

void cube::GameScene::DrawLine(int x1, int y1, int x2, int y2,const cube::color_t &color) {

    p_Renderer->RenderLine(x1,y1,x2,y2,color);
}
