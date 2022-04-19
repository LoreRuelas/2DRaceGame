#include <stdio.h>
#include "raylib.h"

typedef struct sprite_struct
{
  Texture2D texture;
  Rectangle mask;
  int frameCount;
}Sprite;

typedef struct player_graphics_struct
{
  Sprite sprites[1];
  int currentFrame;
  float deltaFrame;
  float refreshRate;
}PlayerGraphics;

typedef enum player_state_enum
{
  IDLE,
  PLAYER_STATE_COUNT
}PlayerStatesEnum;

typedef struct player_struct
{
  Vector2 position;
  float speed;
  PlayerStatesEnum state;
  PlayerGraphics graphics;
}Player;

Sprite LoadWalkSprite();
Sprite LoadJumpSprite();
Sprite LoadRunSprite();
Sprite LoadDeathSprite();
Sprite LoadIdleSprite();
//PlayerGraphics UpdatePlayerGraphic(PlayerGraphics g);
Player UpdatePlayer(Player p);

PlayerGraphics LoadPlayerGraphics();
Player LoadPlayer();
Player LoadPlayer2();
void DrawPlayer(Player p);

int main() {

  InitWindow(1000, 700, "DinoGame");
  SetTargetFPS(30);
  bool flag = true;
  //Sprite idle = LoadIdleSprite();
  Player jugador1 = LoadPlayer();
  //PlayerGraphics g = LoadPlayerGraphics();
  bool keyRight = false;
  bool keyUp = false;
  while(!WindowShouldClose())
  {
        jugador1 = UpdatePlayer(jugador1);

        if (IsKeyDown(KEY_RIGHT) && keyRight == false){
            jugador1 = LoadPlayer();
            jugador1.graphics.sprites[0] = LoadWalkSprite();
            jugador1 = UpdatePlayer(jugador1);
            keyRight = true;
        }else if (IsKeyUp(KEY_RIGHT) && keyRight){
            jugador1 = LoadPlayer();
            jugador1.graphics.sprites[0] = LoadIdleSprite();
            jugador1 = UpdatePlayer(jugador1);
            keyRight = false;
        } else if (IsKeyDown(KEY_UP) && keyUp == false){
            jugador1 = LoadPlayer2();
            jugador1.graphics.sprites[0] = LoadJumpSprite();
            jugador1 = UpdatePlayer(jugador1);
            keyUp = true;
        } else if(IsKeyUp(KEY_UP) && keyUp){
            jugador1 = LoadPlayer();
            jugador1.graphics.sprites[0] = LoadIdleSprite();
            jugador1 = UpdatePlayer(jugador1);
            keyUp = false;
        }

        //jugador1 = UpdatePlayer(jugador1);
    /*
    if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
    if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
     if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
      */
    BeginDrawing();
    //DrawTexture(idle, 250,250,WHITE);
    ClearBackground(WHITE);
    DrawPlayer(jugador1);
    EndDrawing();
  }
  CloseWindow();
  
  //printf("Hello, World!\n");
  return 0;
}

Sprite LoadIdleSprite()
{
  Sprite s;

  Texture2D t = LoadTexture("Assets/dino_idle_10.png");
  Rectangle mask;
  mask.width = (float)t.width/10;
  mask.height = (float)t.height;
  mask.x = 0;
  mask.y = 0;
  int frameCount = 10;

  s.texture = t;
  s.mask = mask;
  s.frameCount = frameCount;

  return s;
}

Sprite LoadWalkSprite()
{
    Sprite s;

    Texture2D t = LoadTexture("Assets/dino_walk_10.png");
    Rectangle mask;
    mask.width = (float)t.width/10;
    mask.height = (float)t.height;
    mask.x = 0;
    mask.y = 0;
    int frameCount = 10;

    s.texture = t;
    s.mask = mask;
    s.frameCount = frameCount;

    return s;
}

Sprite LoadRunSprite()
{
    Sprite s;

    Texture2D t = LoadTexture("Assets/dino_run_8.png");
    Rectangle mask;
    mask.width = (float)t.width/8;
    mask.height = (float)t.height;
    mask.x = 0;
    mask.y = 0;
    int frameCount = 8;

    s.texture = t;
    s.mask = mask;
    s.frameCount = frameCount;

    return s;
}

Sprite LoadJumpSprite()
{
    Sprite s;

    Texture2D t = LoadTexture("Assets/dino_jump_122.png");
    Rectangle mask;
    mask.width = (float)t.width/12;
    mask.height = (float)t.height;
    mask.x = 0;
    mask.y = 0;
    int frameCount = 12;

    s.texture = t;
    s.mask = mask;
    s.frameCount = frameCount;

    return s;
}

Sprite LoadDeathSprite()
{
    Sprite s;

    Texture2D t = LoadTexture("Assets/dino_death_8.png");
    Rectangle mask;
    mask.width = (float)t.width/8;
    mask.height = (float)t.height;
    mask.x = 0;
    mask.y = 0;
    int frameCount = 8;

    s.texture = t;
    s.mask = mask;
    s.frameCount = frameCount;

    return s;
}



PlayerGraphics UpdatePlayerGraphics(PlayerGraphics g)
{
  // actualizamos al jugador
  float elapsed = GetFrameTime();
  g.deltaFrame += elapsed;

  if(g.deltaFrame >= g.refreshRate)
  {
    g.deltaFrame = 0;
    g.currentFrame = (g.currentFrame + 1) % g.sprites[0].frameCount;
    g.sprites[0].mask.x = g.sprites[0].mask.width * g.currentFrame;
  }

  return g;
}


PlayerGraphics LoadPlayerGraphics()
{
  PlayerGraphics g;
  g.sprites[0] = LoadIdleSprite();
  g.currentFrame = 0;
  g.deltaFrame = 0;
  g.refreshRate = (float)0.15; // en segundos, cada cuanto queremos actualizar el jugador
  return g;
}

Player LoadPlayer()
{
  Player p;
  p.position.x = 500;
  p.position.y = 350;
  p.speed = 0;
  p.graphics = LoadPlayerGraphics();
  p.state = IDLE;

  return p;
}
Player LoadPlayer2()
{
    Player p;
    p.position.x = 500;
    p.position.y = 156;
    p.speed = 0;
    p.graphics = LoadPlayerGraphics();
    p.state = IDLE;

    return p;
}
void DrawPlayer(Player p)
{
  DrawTextureRec(p.graphics.sprites[p.state].texture,
                 p.graphics.sprites[p.state].mask,
                 p.position,
                 WHITE
  );
}
Player UpdatePlayer(Player p)
{
  //revisar alguna tecla
  p.graphics = UpdatePlayerGraphics(p.graphics);
  return p;
}