#include <gePrerequisitesUtil.h>

#if GE_PLATFORM == GE_PLATFORM_WIN32
# include <Win32/geWin32Windows.h>
#endif

#include <geRTTIPlainField.h>
#include <geException.h>
#include <geMath.h>

#include <geCrashHandler.h>
#include <geDynLibManager.h>
#include <geFileSystem.h>
#include <geTime.h>
#include <geUnicode.h>

#include <SFML/Graphics.hpp>

#include <commdlg.h>
#include <imgui.h>
#include <imgui-sfml.h>

#include <lua.hpp>

#include "RTSConfig.h"
#include "RTSApplication.h"
#include "RTSTiledMap.h"



void
loadMapFromFile(RTSApplication* pApp);

void
mainMenu(RTSApplication* pApp);

RTSApplication::RTSApplication()
  : m_window(nullptr),
    m_fpsTimer(0.0f),
    m_fpsCounter(0.0f),
    m_framesPerSecond(0.0f)
{}

RTSApplication::~RTSApplication() {}

int32
RTSApplication::run() {
  CrashHandler::startUp();
  DynLibManager::startUp();
  Time::startUp();
  GameOptions::startUp();

  __try {
    initSystems();
    gameLoop();
    destroySystems();
  }
  __except (g_crashHandler().reportCrash(GetExceptionInformation())) {
    PlatformUtility::terminate(true);
  }

  GameOptions::shutDown();
  Time::shutDown();
  DynLibManager::shutDown();
  CrashHandler::shutDown();

  return 0;
}

void
RTSApplication::initSystems() {
  if (nullptr != m_window) {  //Window already initialized
    return; //Shouldn't do anything
  }

  initScriptSystem();

  //Create the application window
  m_window = ge_new<sf::RenderWindow>(sf::VideoMode(GameOptions::s_Resolution.x,
                                                    GameOptions::s_Resolution.y),
                                      "RTS Game",
                                      sf::Style::Titlebar);
  if (nullptr == m_window) {
    GE_EXCEPT(InvalidStateException, "Couldn't create Application Window");
  }

  m_arialFont = ge_new<sf::Font>();
  if (nullptr == m_arialFont) {
    GE_EXCEPT(InvalidStateException, "Couldn't create a Font");
  }
  
  
  if (!m_arialFont->loadFromFile("Fonts/arial.ttf")) {
    GE_EXCEPT(FileNotFoundException, "Arial font not found");
  }

  //m_window->setVerticalSyncEnabled(true);
  initGUI();
}

void
RTSApplication::initGUI() {
  ImGui::SFML::Init(*m_window);
}

void
RTSApplication::destroySystems() {
  lua_close(m_luaState);

  ImGui::SFML::Shutdown();

  if (nullptr != m_window) {
    m_window->close();
    ge_delete(m_window);
  }

  if (nullptr != m_arialFont) {
    ge_delete(m_arialFont);
  }
}

void
RTSApplication::gameLoop() {
  if (nullptr == m_window) {  //Windows not yet initialized
    return; //Shouldn't do anything
  }

  postInit();

  while (m_window->isOpen()) {
    sf::Event event;
    while (m_window->pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);
      if (event.type == sf::Event::Closed) {
        m_window->close();
      }
    }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
      {
        if (s_terrain == 4)
        {


          m_gameWorld.getPathfinder()->m_InitialPos = 
          { 
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY 
          };
          m_gameWorld.getTiledMap()->getMapGridCell(m_gameWorld.getTiledMap()->m_selectedTileX, m_gameWorld.getTiledMap()->m_selectedTileY).setTentativeCost(0);
          m_gameWorld.getPathfinder()->m_currentTile =
            m_gameWorld.getPathfinder()->m_InitialPos;
          if (m_gameWorld.getPathfinder()->m_path.size() != 1)
          {
            m_gameWorld.getTiledMap()->setStartTile(m_gameWorld.getTiledMap()->m_selectedTileX,
              m_gameWorld.getTiledMap()->m_selectedTileY);
            m_gameWorld.getTiledMap()->getMapGridCell(m_gameWorld.getTiledMap()->m_selectedTileX, m_gameWorld.getTiledMap()->m_selectedTileY).setCost(0);
            m_gameWorld.getPathfinder()->m_path.push_front(
              m_gameWorld.getPathfinder()->m_currentTile);

          }
        }
        if (s_terrain == 5)
        {
          m_gameWorld.getTiledMap()->setFinalTile(m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY);
          m_gameWorld.getPathfinder()->m_FinalPos = 
          {
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY 
          };
        }

        switch (s_terrain)
        {
        case TERRAIN_TYPE::E::kGrass :
          m_gameWorld.getTiledMap()->setCost(
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY,
            1
          );
          m_gameWorld.getTiledMap()->setType(m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY, TERRAIN_TYPE::E::kGrass);
          break;
        case TERRAIN_TYPE::E::kWater :
          m_gameWorld.getTiledMap()->m_water.push_back(Vector2I(
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY
          ));
          m_gameWorld.getTiledMap()->setCost(
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY,
            2 );
          m_gameWorld.getTiledMap()->setType(m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY, TERRAIN_TYPE::E::kWater);
          break;
        case TERRAIN_TYPE::E::kMarsh :
          m_gameWorld.getTiledMap()->setCost(
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY,
            3
          );
          m_gameWorld.getTiledMap()->setType(m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY, TERRAIN_TYPE::E::kMarsh);
          break;
        case TERRAIN_TYPE::E::kObstacle :
          m_gameWorld.getTiledMap()->m_obstacles.push_back(Vector2I(
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY
          ));
          m_gameWorld.getTiledMap()->setCost(
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY,
            10
          );
          m_gameWorld.getTiledMap()->setType(m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY, TERRAIN_TYPE::E::kObstacle);
          break;

        default:
          break;
        }

        m_gameWorld.getTiledMap()->m_tiles.push_back(
          Vector2I{
            m_gameWorld.getTiledMap()->m_selectedTileX,
            m_gameWorld.getTiledMap()->m_selectedTileY
          });
      }
    g_time()._update();
    ge_frame_mark();
    updateFrame();
    renderFrame();
    ge_frame_clear();
  }

  postDestroy();
}

void
RTSApplication::updateFrame() {
  float deltaTime = g_time().getFrameDelta();
  
  m_fpsTimer += deltaTime;
  if (1.0f < m_fpsTimer) {
    m_framesPerSecond = m_fpsCounter;
    m_fpsCounter = 0.0f;
    m_fpsTimer = 0.0f;
  }
  m_fpsCounter += 1.0f;

  //Update the interface
  sf::Clock myClock;
  ImGui::SFML::Update(*m_window, myClock.getElapsedTime());

  //Begin the menu 
  mainMenu(this);

  //Check for camera movement
  Vector2 axisMovement(FORCE_INIT::kForceInitToZero);
  Vector2I mousePosition;
  mousePosition.x = sf::Mouse::getPosition(*m_window).x;
  mousePosition.y = sf::Mouse::getPosition(*m_window).y;

  if (0 == mousePosition.x ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
#ifdef MAP_IS_ISOMETRIC
    axisMovement += Vector2(-1.f, 1.f);
#else
    axisMovement += Vector2(-1.f, 0.f);
#endif
  }
  if (GameOptions::s_Resolution.x -1 == mousePosition.x ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
#ifdef MAP_IS_ISOMETRIC
    axisMovement += Vector2(1.f, -1.f);
#else
    axisMovement += Vector2(1.f, 0.f);
#endif
  }
  if (0 == mousePosition.y ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
#ifdef MAP_IS_ISOMETRIC
    axisMovement += Vector2(-1.f, -1.f);
#else
    axisMovement += Vector2(0.f, -1.f);
#endif
  }
  if (GameOptions::s_Resolution.y - 1 == mousePosition.y ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
#ifdef MAP_IS_ISOMETRIC
    axisMovement += Vector2(1.f, 1.f);
#else
    axisMovement += Vector2(0.f, 1.f);
#endif
  }

  axisMovement *= GameOptions::s_MapMovementSpeed * deltaTime;

  m_gameWorld.getTiledMap()->moveCamera(axisMovement.x, axisMovement.y);
  
  if (m_resetPos)
  {
    m_gameWorld.getTiledMap()->m_InitialPos = Vector2I::ZERO;
    m_gameWorld.getTiledMap()->m_FinalPos = Vector2I::ZERO;
    m_resetPos = false;
  }
  //Update the world
  m_gameWorld.update(deltaTime);
}

void
RTSApplication::renderFrame() {
  m_window->clear(sf::Color::Blue);

  m_gameWorld.render();

  ImGui::SFML::Render(*m_window);

  /*
  sf::Text text;
  text.setPosition(0.f, 30.f);
  text.setFont(*m_arialFont);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Red);
  text.setString( toString(1.0f/g_time().getFrameDelta()).c_str() );
  m_window->draw(text);
  */
  m_window->display();
}

void
RTSApplication::postInit() {
  m_gameWorld.init(m_window);
  m_gameWorld.updateResolutionData();
}

void
RTSApplication::postDestroy() {
  m_gameWorld.destroy();
}



void
loadMapFromFile(RTSApplication* pApp) {
  OPENFILENAMEW ofn = { 0 };

  WString fileName;
  fileName.resize(MAX_PATH);
  bool bMustLoad = false;

  Path currentDirectory = FileSystem::getWorkingDirectoryPath();

  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = nullptr;
  ofn.lpstrDefExt = L".bmp";
  ofn.lpstrFilter = L"Bitmap File\0*.BMP\0All\0*.*\0";
  ofn.lpstrInitialDir = L"Maps\\";
  ofn.lpstrFile = &fileName[0];
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if (GetOpenFileNameW(&ofn)) {
    if (fileName.size() > 0) {
      bMustLoad = true;
    }
  }

  SetCurrentDirectoryW(UTF8::toWide(currentDirectory.toString()).c_str());

  if (bMustLoad) {
    pApp->getWorld()->getTiledMap()->loadFromImageFile(pApp->getRenderWindow(),
                                                       toString(fileName));
  }
}

void
mainMenu(RTSApplication* pApp) {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("Map")) {
      if (ImGui::MenuItem("Load...", "CTRL+O")) {
        loadMapFromFile(pApp);
      }
      if (ImGui::MenuItem("Save...", "CTRL+S")) {

      }
      ImGui::Separator();

      if (ImGui::MenuItem("Quit", "CTRL+Q")) {
        pApp->getRenderWindow()->close();
      }

      ImGui::EndMenu();
    }
    
    ImGui::EndMainMenuBar();
  }

  ImGui::Begin("Game Options");
  {
    ImGui::Text("Framerate: %f", pApp->getFPS());

    ImGui::SliderFloat("Map movement speed X",
      &GameOptions::s_MapMovementSpeed.x,
      0.0f,
      10240.0f);
    ImGui::SliderFloat("Map movement speed Y",
      &GameOptions::s_MapMovementSpeed.y,
      0.0f,
      10240.0f);

    ImGui::Checkbox("Show grid", &GameOptions::s_MapShowGrid);
    ImGui::Checkbox("Show influence", &pApp->getWorld()->getTiledMap()->m_isPropoagation);
    ImGui::SliderFloat("Decay",
      &pApp->getWorld()->getTiledMap()->m_decay,
      0.01f,
      1.0f);
    ImGui::SliderFloat("Momentum",
      &pApp->getWorld()->getTiledMap()->m_momentum,
      0.01f,
      1.1f);
  }
  ImGui::End();

  ImGui::Begin("Game Options");
  {
    const char* items[] = {  "Water", "Grass", "Marsh", "Obstacle" , "Inital Position", "Final Position", };
    static const char* current_item = NULL;
    ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;

    ImGuiStyle& style = ImGui::GetStyle();
    float w = ImGui::CalcItemWidth();
    float spacing = style.ItemInnerSpacing.x;
    float button_sz = ImGui::GetFrameHeight();
    ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
    if (ImGui::BeginCombo("##custom combo", current_item))
    {
      for (int n = 0; n < IM_ARRAYSIZE(items); n++)
      {
        bool is_selected = (current_item == items[n]);
        if (ImGui::Selectable(items[n], is_selected))
        {
          current_item = items[n];
          pApp->getTerrainID() = n;
        }
        if (is_selected)
        {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Left))
    {
    }
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Right))
    {
    }
    ImGui::SameLine(0, style.ItemInnerSpacing.x);
    ImGui::Text("Terrain");
  }
  ImGui::End();

  /**
  * @brief Change pathfinding mode
  */
  ImGui::Begin("Game Options");
  {
    const char* items[] = { "DepthFirstSearch", "BreathFirstSearch", "BestFirstSearch", "Dijkstra" };
    static const char* current_item = NULL;
    ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;

    ImGuiStyle& style = ImGui::GetStyle();
    float w = ImGui::CalcItemWidth();
    float spacing = style.ItemInnerSpacing.x;
    float button_sz = ImGui::GetFrameHeight();
    ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
    if (ImGui::BeginCombo("##Pathfinding Mode", current_item))
    {
      for (int n = 0; n < IM_ARRAYSIZE(items); n++)
      {
        bool is_selected = (current_item == items[n]);
        if (ImGui::Selectable(items[n], is_selected))
        {
          current_item = items[n];
          pApp->getPathfinderID() = n;
          pApp->getWorld()->getPathfinder()->m_Pathfinding_state = n;
        }
        if (is_selected)
        {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Left))
    {
    }
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Right))
    {
    }
    ImGui::SameLine(0, style.ItemInnerSpacing.x);
    ImGui::Text("Pathfinding");
  }
  ImGui::End();

  ImGui::Begin("Game Options");
  {
    const char* items[] = { "LAND", "AQUATIC", "AIR",};
    static const char* current_item = NULL;
    ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;

    ImGuiStyle& style = ImGui::GetStyle();
    float w = ImGui::CalcItemWidth();
    float spacing = style.ItemInnerSpacing.x;
    float button_sz = ImGui::GetFrameHeight();
    ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
    if (ImGui::BeginCombo("##Unit Quality Mode", current_item))
    {
      for (int n = 0; n < IM_ARRAYSIZE(items); n++)
      {
        bool is_selected = (current_item == items[n]);
        if (ImGui::Selectable(items[n], is_selected))
        {
          current_item = items[n];
          pApp->getPathfinderID() = n;
          pApp->getWorld()->getPathfinder()->Unit.setQuality(n);
        }
        if (is_selected)
        {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Left))
    {
    }
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Right))
    {
    }
    ImGui::SameLine(0, style.ItemInnerSpacing.x);
    ImGui::Text("Unit Quality");
  }
  ImGui::End();


  ImGui::Begin("Game Options");
  {
    if (ImGui::Button("Start Search")) {
      pApp->getWorld()->getTiledMap()->clearMapTiles();
      pApp->getWorld()->getTiledMap()->setTilesCost();
      Vector2I pos = pApp->getWorld()->getPathfinder()->m_path[0];
      pApp->getWorld()->getTiledMap()->getMapGridCell(pos.x, pos.y).setTentativeCost(0);
      pApp->getWorld()->getTiledMap()->getMapGridCell(pos.x, pos.y).setCost(0);
      pApp->getWorld()->getPathfinder()->clearPathfindingSearch2(*pApp->getWorld()->getTiledMap());
      pApp->getWorld()->getPathfinder()->m_isSearching = true;
      pApp->getWorld()->getPathfinder()->m_currentTile = pos;
      pApp->getWorld()->getPathfinder()->m_path.push_back(pos);
      //pApp->getWorld()->getPathfinder()->m_FinalPos = { 
      //  pApp->getWorld()->getTiledMap()->getFinalTile()->getIndexX(), 
      //  pApp->getWorld()->getTiledMap()->getFinalTile()->getIndexY() };
    }
  }
  ImGui::End();

  ImGui::Begin("Game Options");
  {
    if (ImGui::Button("Reset Pathfinding")) {
      pApp->getWorld()->getTiledMap()->clearMapTiles();
      pApp->getWorld()->getTiledMap()->setTilesCost();
      pApp->getWorld()->getPathfinder()->clearPathfindingSearch(*pApp->getWorld()->getTiledMap());
    }
  }
  ImGui::End();

  ImGui::Begin("Game Options");
  {
    if (pApp->getWorld()->getTiledMap()->mousePosition.x != -1 || pApp->getWorld()->getTiledMap()->mousePosition.y != -1)
    {

      ImGui::Text("Mouse x: %f", pApp->getWorld()->getTiledMap()->tileposX);
      ImGui::Text("Mouse y: %f", pApp->getWorld()->getTiledMap()->tileposY);
      ImGui::Text("Selected tile by index: %f", pApp->getWorld()->getTiledMap()->m_selectedTileByIndex);
    }
  }
  ImGui::End();

}

/*
int TestLUA(lua_State* L)
{
  int argUno = (int)lua_tointeger(L, 1);
  int argDos = (int)lua_tointeger(L, 2);

  lua_Integer result = argUno + argDos;
  lua_pushinteger(L, result);
  std::cout << result;
  return 1;
}
*/

int
SetResolution(lua_State* L) {
  int32 width = (int32)lua_tointeger(L, 1);
  int32 height = (int32)lua_tointeger(L, 2);

  GameOptions::s_Resolution.x = width;
  GameOptions::s_Resolution.y = height;
  
  return 0;
}

bool
RTSApplication::initScriptSystem() {
  // Initialize LUA
  m_luaState = luaL_newstate();
  if (nullptr == m_luaState) {
    return false;
  }
  //Add default libs
  luaL_openlibs(m_luaState);

  //Register a new function
  lua_register(m_luaState,
               "SetResolution",
               &SetResolution);

  luaL_dofile(m_luaState, "LUA/gameConfig.lua");
  luaL_dostring(m_luaState, "ConfigGame()");

  return true;
}
