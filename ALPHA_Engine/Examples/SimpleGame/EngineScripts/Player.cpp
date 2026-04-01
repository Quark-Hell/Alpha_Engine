#include "Player.h"

#include "Windows/WindowsSettings.h"
#include "Modules.h"

#include "SonarEngine/Components/AudioListener.h"

void Player::Start() {
#if ANOMALY_ENGINE_INCLUDED
    auto* windowsSettings = Core::World::GetObject<Core::GameObject>("WindowsSettings");
    auto* wind = windowsSettings->GetComponentByType<WindowsSettings>();

    Core::GameObject* parent = static_cast<Core::GameObject*>(GetParentObject());
    wind->BaseWindow(*parent);
#endif

#if BINDS_ENGINE_INCLUDED
    using namespace BindsEngine;

    /*auto& leftMove =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&Player::LeftMoveCamera, this) },
        { EnumKeyboardKeysStates::KeyHold },
        { EnumKeyboardTable::A },
        wind->win1
    );

    /*auto& rightMove =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&Player::RightMoveCamera, this) },
        { EnumKeyboardKeysStates::KeyHold },
        { EnumKeyboardTable::D },
        wind->win1
    );

    /*auto& forwardMove =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&Player::ForwardMoveCamera, this) },
        { EnumKeyboardKeysStates::KeyHold },
        { EnumKeyboardTable::W },
        wind->win1
    );

    /*auto& backwardMove =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&Player::BackwardMoveCamera, this) },
        { EnumKeyboardKeysStates::KeyHold },
        { EnumKeyboardTable::S },
        wind->win1
    );

    /*auto& upMove =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&Player::UpMoveCamera, this) },
        { EnumKeyboardKeysStates::KeyHold },
        { EnumKeyboardTable::E },
        wind->win1
    );

    /*auto& downMove =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&Player::DownMoveCamera, this) },
        { EnumKeyboardKeysStates::KeyHold },
        { EnumKeyboardTable::Q },
        wind->win1
    );

    /*auto& rotateBind =*/ bindsBuffer->CreateMouseSensorBind(
        { std::bind(&Player::CameraRotate, this) },
        { EnumMouseSensorStates::MouseKeepMoved, EnumMouseSensorStates::MouseStartMoved },
        wind->win1
    );
#endif

#if SONAR_ENGINE_INCLUDED
    SonarEngine::AudioListener& audioListener = audioListenersBuffer->CreateAudioListener();
    GetParentObject()->AddComponent(audioListener);
#endif

}
void Player::Update() {

}
void Player::End() {

}

void Player::CameraRotate() {
#if ANOMALY_ENGINE_INCLUDED
    auto* windowsSettings = Core::World::GetObject<Core::GameObject>("WindowsSettings");
    auto* wind = windowsSettings->GetComponentByType<WindowsSettings>();

    Core::GameObject* parent = static_cast<Core::GameObject*>(GetParentObject());

    if (wind->win1->GetCursorVisible() == true)
        return;

    auto mouseData = Core::World::GetSystemData<BindsEngine::MouseSensors>("MouseSensorsBuffer");

    float sensitive = 0.15;
    glm::vec2 delta = mouseData->GetMouseDelta();

    targetYaw -= delta.x * sensitive;
    targetPitch -= delta.y * sensitive;

    targetPitch = glm::clamp(targetPitch, -89.0f, 89.0f);

    glm::quat qYaw = glm::angleAxis(glm::radians(targetYaw), glm::vec3(0, 1, 0));
    glm::quat qPitch = glm::angleAxis(glm::radians(targetPitch), glm::vec3(1, 0, 0));

    glm::quat targetRot = qYaw * qPitch;

    float slerpSpeed = 10.0f * Core::World::GetDeltaTime();
    slerpSpeed = glm::clamp(slerpSpeed, 0.0f, 1.0f);

    GetParentObject()->transform.SetRotationQuatSlerp(targetRot, slerpSpeed);
#endif
}

void Player::LeftMoveCamera() {
    glm::vec3 rightVector = GetParentObject()->transform.GetRight();
    float sensitive = moveSensitive * Core::World::GetDeltaTime();

    GetParentObject()->transform.AddPosition(-rightVector * sensitive);
}

void Player::RightMoveCamera() {
    glm::vec3 rightVector = GetParentObject()->transform.GetRight();
    float sensitive = moveSensitive * Core::World::GetDeltaTime();

    GetParentObject()->transform.AddPosition(rightVector * sensitive);
}

void Player::ForwardMoveCamera() {
    glm::vec3 forward = GetParentObject()->transform.GetForward();
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    float sensitive = moveSensitive * Core::World::GetDeltaTime();
    GetParentObject()->transform.AddPosition(forward * sensitive);
}

void Player::BackwardMoveCamera() {
    glm::vec3 forward = GetParentObject()->transform.GetForward();
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    float sensitive = moveSensitive * Core::World::GetDeltaTime();
    GetParentObject()->transform.AddPosition(-forward * sensitive);
}

void Player::UpMoveCamera() {
    glm::vec3 newPos = GetParentObject()->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.y += sensitive;

    GetParentObject()->transform.SetPosition(newPos);
}
void Player::DownMoveCamera() {
    glm::vec3 newPos = GetParentObject()->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.y -= sensitive;

    GetParentObject()->transform.SetPosition(newPos);
}