#pragma once
class DeltaTime {
private:
    DeltaTime();

    float deltaTime = 0;
    float lastFrame = 0;
public:
    DeltaTime(const DeltaTime&) = delete;
    static DeltaTime& GetInstance() {
        static DeltaTime instance;
        return instance;
    }
    static void SetDeltaTime(float currentFrame);
    static float GetDeltaTime();
};