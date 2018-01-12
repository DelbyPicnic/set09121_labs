#include <SFML/Graphics.hpp>

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

CircleShape ball;
RectangleShape paddles[2];

void Load(){
    // Set size and origin of paddles
    for(auto &p : paddles){
        p.setSize(paddleSize - Vector2f(3,3));
        p.setOrigin(paddleSize / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ballRadius -3);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
    // Reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - paddleSize.x - 10, gameHeight / 2);
    // Reset ball position
    ball.setPosition(gameWidth / 2, gameHeight / 2);
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
    float direction = 0.0f;
    if(Keyboard::isKeyPressed(controls[0])){
        direction--;
    }
    if(Keyboard::isKeyPressed(controls[1])){
        direction++;
    }
    paddles[0].move(0, direction * paddleSpeed * dt);
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