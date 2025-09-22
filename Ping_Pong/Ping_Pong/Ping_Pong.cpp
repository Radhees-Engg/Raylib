#include <iostream>
#include "raylib.h"

using namespace std;

class Bat
{
public:
	Vector2 speed;
	Vector2 size;
	float pos_x, pos_y;
};
class Ball
{
public:
	float radius;
	Vector2 speed;
	Vector2 position;
};


void game(Ball& ball, bool& space_clicked, Rectangle& rec1, Rectangle& rec2, int bat_speed)
{
	if (IsKeyPressed(KEY_SPACE))
	{
		space_clicked = true;
	}
	if (space_clicked == true)
	{
		ball.position.x += ball.speed.x;
		ball.position.y += ball.speed.y;
	}
	if (IsKeyDown(KEY_W))
	{
		rec1.y -= bat_speed;
	}
	else if (IsKeyDown(KEY_S))
	{
		rec1.y += bat_speed;
	}
	if (IsKeyDown(KEY_UP))
	{
		rec2.y -= bat_speed;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		rec2.y += bat_speed;
	}
}
void check_collision(Ball& ball, Rectangle& rec1, Rectangle& rec2, int screen_width, int screen_height)
{
	if (ball.position.y + ball.radius >= screen_height)
	{
		ball.speed.y *= -1;
	}
	else if (ball.position.y + ball.radius < 0)
	{
		ball.speed.y *= -1;
	}
	if (CheckCollisionCircleRec(ball.position, ball.radius, rec1))
	{
		ball.speed.x *= -1;
	}
	else if (CheckCollisionCircleRec(ball.position, ball.radius, rec2))
	{
		ball.speed.x *= -1;
	}
	if (rec1.y + rec1.height >= screen_height)
	{
		rec1.y = screen_height - rec1.height;
	}
	else if (rec1.y <= 0)
	{
		rec1.y = 0;
	}
	if (rec2.y + rec2.height >= screen_height)
	{
		rec2.y = screen_height - rec2.height;
	}
	else if (rec2.y <= 0)
	{
		rec2.y = 0;
	}
}
void GameOver(int screen_width, int screen_height, Ball& ball, int& score1, int& score2, bool& space_clicked, int& life1, int& life2)
{
	if (ball.position.x + ball.radius > screen_width)
	{
		score1++;
		life1++;
		space_clicked = false;
		ball.position.x = screen_width / 2;
		ball.position.y = screen_height / 2;
		ball.speed = { -2,2 };
	}
	if (ball.position.x + ball.radius < 0)
	{
		score2++;
		life2++;
		space_clicked = false;
		ball.position.x = screen_width / 2;
		ball.position.y = screen_height / 2;
		ball.speed = { 2,2 };
	}
	
}

int main()
{
	float time_counter = 0.0f;
	bool space_clicked = false;
	int life1 = 0;
	int life2 = 0;
	int score1 = 0;
	int score2 = 0;
	int bats_speed = 10;

	const int screen_width = 800;
	const int screen_height = 600;

	InitWindow(screen_width, screen_height, "PING_PONG");
	SetTargetFPS(60);

	Bat bat1;
	bat1.size.x = 10;
	bat1.size.y = 100;
	bat1.pos_x = 0;
	bat1.pos_y = screen_height/2;

	Bat bat2;
	bat2.size.x = bat1.size.x;
	bat2.size.y = bat1.size.y;
	bat2.pos_x = screen_width - bat2.size.x;
	bat2.pos_y = screen_height / 2;

	Ball ball;
	ball.radius = 5;
	ball.speed = { 2, 2 };
	ball.position = { screen_width / 2, screen_height / 2 };

	Rectangle rec1 = { bat1.pos_x, bat1.pos_y, bat1.size.x, bat1.size.y };
	Rectangle rec2 = { bat2.pos_x, bat2.pos_y, bat2.size.x, bat2.size.y };

	while (!WindowShouldClose())
	{
		time_counter += GetFrameTime();
		BeginDrawing();
		ClearBackground(BLACK);

		DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
		DrawRectangleRec(rec1, WHITE);
		DrawRectangleRec(rec2, WHITE);
		DrawCircleV(ball.position, ball.radius, PINK);
		DrawText(TextFormat("%d", score1), 50, 100, 25, SKYBLUE);
		DrawText(TextFormat("%d", score2), screen_width - 50, 100, 25, SKYBLUE);

		game(ball, space_clicked, rec1, rec2, bats_speed);
		check_collision(ball, rec1, rec2, screen_width, screen_height);
		if (space_clicked == false)
		{
			DrawText(TextFormat("PRESS SPACEBAR"), 250, screen_height / 2, 30, RED);
			time_counter = 0;
			ball.speed = { 2,2 };
		}
		if (time_counter >= 5.0f)
		{
			cout << "time_reached" << endl;
			ball.speed.x += (ball.speed.x > 0 ? 0.3 : -0.3);
			ball.speed.y += (ball.speed.y > 0 ? 0.3 : -0.3);
			time_counter = 0.0f;
		}
		
		GameOver(screen_width, screen_height, ball, score1, score2, space_clicked, life1, life2);

		EndDrawing();
	}
	CloseWindow();
}