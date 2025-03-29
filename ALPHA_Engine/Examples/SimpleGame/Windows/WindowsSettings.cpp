#include "WindowsSettings.h"

#include "Modules.h"

void WindowsSettings::ShowCursor() {
    win1->SetCursorVisible(true);
}

void WindowsSettings::HideCursor() {
    win1->SetCursorVisible(false);
}

void WindowsSettings::WindowsTest1(Core::Object& Player) {
    auto& cam1_1 = camerasBuffer->CreateCamera();
    auto& cam1_2 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0,0},{0.3,0.3});
    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    win1->CreateRectangle({0.5,0},{0.5,0.5});
    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player.AddComponent(cam1_1);
    Player.AddComponent(cam1_2);
}

void WindowsSettings::WindowsTest2(Core::Object& Player) {
    auto& cam1_1 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0,0},{0.025,0.95});
    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    Player.AddComponent(cam1_1);

    //------------------------------------------------//

    auto& cam1_2 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0,0.95},{1,0.05});
    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player.AddComponent(cam1_2);

    //------------------------------------------------//
    auto& cam1_3 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0.025,0.3},{0.3,0.651});
    cam1_3.SetRenderWindow(win1);
    cam1_3.SetUseRectangle(true);
    cam1_3.SetIndexRectangle(2);

    Player.AddComponent(cam1_3);

    //------------------------------------------------//
    auto& cam1_4 = camerasBuffer->CreateCamera();

    win1->CreateRectangle({0.025,0},{0.975,0.3});
    cam1_4.SetRenderWindow(win1);
    cam1_4.SetUseRectangle(true);
    cam1_4.SetIndexRectangle(3);

    Player.AddComponent(cam1_4);

    //------------------------------------------------//
    auto& cam1_5 = camerasBuffer->CreateCamera();

    auto& rect = win1->CreateRectangle({0.355,0.4},{0.375,0.251});
    cam1_5.SetRenderWindow(win1);
    cam1_5.SetUseRectangle(true);
    cam1_5.SetIndexRectangle(4);

    Player.AddComponent(cam1_5);

    win1->RectangleFillFreeSpace(rect);
}

void WindowsSettings::WindowsTest3(Core::Object& Player) {
    auto& cam1_1 = camerasBuffer->CreateCamera();

    rect = &win1->CreateRectangle({0.3f,0.3f},{0.4f,0.4f});

    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    Player.AddComponent(cam1_1);

    //------------------------------------------------//

    auto& cam1_2 = camerasBuffer->CreateCamera();

    auto& rect2 = win1->CreateRectangle({0,0},{0.1f,0.1f});
    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player.AddComponent(cam1_2);
    win1->RectangleFillFreeSpace(rect2);

    //------------------------------------------------//

    auto& cam1_3 = camerasBuffer->CreateCamera();

    auto& rect3 = win1->CreateRectangle({0.9f,0.9f},{0.1f,0.1f});
    cam1_3.SetRenderWindow(win1);
    cam1_3.SetUseRectangle(true);
    cam1_3.SetIndexRectangle(2);

    Player.AddComponent(cam1_3);
    win1->RectangleFillFreeSpace(rect3);

    //------------------------------------------------//

    auto& cam1_4 = camerasBuffer->CreateCamera();

    auto& rect4 = win1->CreateRectangle({0.5f,0.9f},{0.1f,0.1f});
    cam1_4.SetRenderWindow(win1);
    cam1_4.SetUseRectangle(true);
    cam1_4.SetIndexRectangle(3);

    Player.AddComponent(cam1_4);
    win1->RectangleFillFreeSpace(rect4);

    //------------------------------------------------//

    auto& cam1_5 = camerasBuffer->CreateCamera();

    auto& rect5 = win1->CreateRectangle({0.5f,0.0},{0.1f,0.1f});
    cam1_5.SetRenderWindow(win1);
    cam1_5.SetUseRectangle(true);
    cam1_5.SetIndexRectangle(4);

    Player.AddComponent(cam1_5);
    win1->RectangleFillFreeSpace(rect5);

    //------------------------------------------------//

    rect->SetPosition({0.4, 0.4});
    rect->SetSize({0.2, 0.2});
    win1->RectangleFillFreeSpace(*rect);

    rect = &rect2;

    //win1->PushLeftRectEdge(-0.2f, rect1, nullptr);  // --> work
    //win1->PushLeftRectEdge(0.2f, rect1, nullptr);   // <-- work

    //win1->PushRightRectEdge(-0.2f, rect1, nullptr); // <-- work
    //win1->PushRightRectEdge(0.2f, rect1, nullptr);  // --> work
}

void WindowsSettings::WindowsTest4(Core::Object& Player) {
    auto& cam1_2 = camerasBuffer->CreateCamera();

    rect = &win1->CreateRectangle({0.0f,0.0f},{0.1f, 0.2f});

    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player.AddComponent(cam1_2);

    //------------------------------------------------//

    auto& cam1_3 = camerasBuffer->CreateCamera();

    auto& rect3 = win1->CreateRectangle({0.4f,0.0f},{0.1f, 0.2f});

    cam1_3.SetRenderWindow(win1);
    cam1_3.SetUseRectangle(true);
    cam1_3.SetIndexRectangle(2);

    Player.AddComponent(cam1_3);

    //------------------------------------------------//

    auto& cam1_1 = camerasBuffer->CreateCamera();

    auto& rect1 = win1->CreateRectangle({0.3f,0.0f},{0.05f, 1.0f});

    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    Player.AddComponent(cam1_1);

    //------------------------------------------------//

    win1->RectangleFillFreeSpace(rect3);
    win1->RectangleFillFreeSpace(*rect);
}

void WindowsSettings::WindowsTest5(Core::Object& Player) {
    auto& cam1_1 = camerasBuffer->CreateCamera();

    rect = &win1->CreateRectangle({0.0f,0.1f},{0.4f, 0.8f});
    rects.push_back(rect);

    cam1_1.SetRenderWindow(win1);
    cam1_1.SetUseRectangle(true);
    cam1_1.SetIndexRectangle(0);

    Player.AddComponent(cam1_1);

    //------------------------------------------------//

    auto& cam1_2 = camerasBuffer->CreateCamera();

    rects.push_back(&win1->CreateRectangle({0.4f,0.0f},{0.05f, 0.5f}));

    cam1_2.SetRenderWindow(win1);
    cam1_2.SetUseRectangle(true);
    cam1_2.SetIndexRectangle(1);

    Player.AddComponent(cam1_2);

    //------------------------------------------------//

    auto& cam1_3 = camerasBuffer->CreateCamera();

    rects.push_back(&win1->CreateRectangle({0.45f,0.0f},{0.05f, 0.5f}));

    cam1_3.SetRenderWindow(win1);
    cam1_3.SetUseRectangle(true);
    cam1_3.SetIndexRectangle(2);

    Player.AddComponent(cam1_3);

    //------------------------------------------------//

    auto& cam1_4 = camerasBuffer->CreateCamera();

    rects.push_back(&win1->CreateRectangle({0.5,0.0f},{0.05f, 0.5f}));

    cam1_4.SetRenderWindow(win1);
    cam1_4.SetUseRectangle(true);
    cam1_4.SetIndexRectangle(3);

    Player.AddComponent(cam1_4);

    //------------------------------------------------//

    auto& cam1_5 = camerasBuffer->CreateCamera();

    rects.push_back(&win1->CreateRectangle({0.55,0.0f},{0.05f, 0.5f}));

    cam1_5.SetRenderWindow(win1);
    cam1_5.SetUseRectangle(true);
    cam1_5.SetIndexRectangle(4);

    Player.AddComponent(cam1_5);

    //------------------------------------------------//

    auto& cam1_6 = camerasBuffer->CreateCamera();

    auto& rect6 = win1->CreateRectangle({0.6,0.0f},{0.4, 1.0f});
    rects.push_back(&rect6);

    cam1_6.SetRenderWindow(win1);
    cam1_6.SetUseRectangle(true);
    cam1_6.SetIndexRectangle(5);

    win1->RectangleFillFreeSpace(rect6);

    Player.AddComponent(cam1_6);

    //------------------------------------------------//

    auto& cam1_7 = camerasBuffer->CreateCamera();

    auto& rect7 = win1->CreateRectangle({0.45,0.55f},{0.1f, 0.2f});
    rects.push_back(&rect7);

    cam1_7.SetRenderWindow(win1);
    cam1_7.SetUseRectangle(true);
    cam1_7.SetIndexRectangle(6);

    Player.AddComponent(cam1_7);

    win1->RectangleFillFreeSpace(rect7);

    //------------------------------------------------//

    auto& cam1_8 = camerasBuffer->CreateCamera();

    auto& rect8 = win1->CreateRectangle({0.0f,0.92f},{0.1f, 0.06f});
    rects.push_back(&rect8);

    cam1_8.SetRenderWindow(win1);
    cam1_8.SetUseRectangle(true);
    cam1_8.SetIndexRectangle(7);

    Player.AddComponent(cam1_8);

    win1->RectangleFillFreeSpace(rect8);

    //------------------------------------------------//

    auto& cam1_9 = camerasBuffer->CreateCamera();
    //win1->CreateRectangle({0.0f,0.92f},{0.1f, 0.06f});
    auto& rect9 = win1->CreateRectangle({0.0f,0.0},{0.1f, 0.06f});
    rects.push_back(&rect9);

    cam1_9.SetRenderWindow(win1);
    cam1_9.SetUseRectangle(true);
    cam1_9.SetIndexRectangle(8);

    Player.AddComponent(cam1_9);

    win1->RectangleFillFreeSpace(rect9);

   std::cout << "end" << std::endl;
}
