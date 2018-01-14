#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,    // Player1 Up
    Keyboard::Z,    // Player1 Down
    Keyboard::Up,   // Player2 Up
    Keyboard::Down  // Player2 Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void Reset(){
    // Reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - paddleSize.x - 10, gameHeight / 2);
    // Reset ball position
    ball.setPosition(gameWidth / 2, gameHeight / 2);

    ballVelocity = {server ? 100.0f : -100.0f, 60.0f};
}


void Load(){
    // Set size and origin of paddles
    for(auto &p : paddles){
        p.setSize(paddleSize - Vector2f(3,3));
        p.setOrigin(paddleSize / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ballRadius -3);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);

    Reset();
}

void Update(RenderWindow &window){
    // Reset the clock and recalculate the delta
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // Check and consume events
    Event event;
    while(window.pollEvent(event)){
        if (event.type == Event::Closed){
            window.close();
            return;
        }
    }
    // Close game on escape key
    if (Keyboard::isKeyPressed(Keyboard::Escape)){
        window.close();
    }

    // Handle paddle movement
    float lp_dir = 0.0f;
    float rp_dir = 0.0f;
    if(Keyboard::isKeyPressed(controls[0])){
        lp_dir--;
    }
    if(Keyboard::isKeyPressed(controls[1])){
        lp_dir++;
    }
    if(Keyboard::isKeyPressed(controls[2])){
        rp_dir--;
    }
    if(Keyboard::isKeyPressed(controls[3])){
        rp_dir++;
    }

    paddles[0].move(0, lp_dir * paddleSpeed * dt);
    paddles[1].move(0, rp_dir * paddleSpeed * dt);

    // Manage ball movement
    ball.move(ballVelocity * dt);
    // Check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;

    
    if(bx > gameWidth){
        // Right wall
        Reset();
    }else if(bx < 0){
        // Left wall
        Reset();
    }else if(by > gameHeight){
        // Bottom wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, -10);
    }else if(by < 0){
        // Top wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, 10); 
    }else if(
        bx < paddles[0].getPosition().x &&
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
    ){
        // Bounce off left paddle
        ballVelocity.x *= -1.0f;

    }else if(
        bx > paddles[1].getPosition().x &&
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
    ){
        // Bounce off right paddle
        ballVelocity.x *= -1.0f;
    }
}

void Render(RenderWindow &window){
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main(){
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while(window.isOpen()){
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}