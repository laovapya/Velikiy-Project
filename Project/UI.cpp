#include "UI.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"

#include"Controller.h"
UI::UI(Scene* scene) {

    this->scene = scene;
}
void UI::DrawObjectMenu() {
    ImVec2 size = ImVec2(100, 100);
    float xOffset = 25;
    float yOffset = 50;
    float xDistance = 150;
   
    ImGui::SetNextWindowSize(scene->GetWindow()->GetWidget1Dimensions());
    if (ImGui::Begin("Component menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {

        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 0, yOffset));
        if (ImGui::Button("Create cube", size)) {
            int id = scene->GetObjectManager()->AddCube();
            //const char* name = ("cube" + char(cubeCount++));
            std::string name = "cube" + std::to_string(cubeCount++);

            ListedObject item(false, id, name);

            AddItem(item);
        }



        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 1, yOffset));
        if (ImGui::Button("Create cylinder", size)) { 
            int id = scene->GetObjectManager()->AddCylinder();
            std::string name = "cylinder" + std::to_string(cylinderCount++);
            ListedObject item(false, id, name);

            AddItem(item);
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 2, yOffset));
        if (ImGui::Button("Create cone", size)) {
            int id = scene->GetObjectManager()->AddCone();
            std::string name = "cone" + std::to_string(coneCount++);
            ListedObject item(false, id, name);

            AddItem(item);
        }

    }
    ImGui::End();
}



void UI::DrawObjectList() {
    ImGui::SetNextWindowSize(scene->GetWindow()->GetWidget2Dimensions());
    if (ImGui::Begin("Object list", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        
        ImGui::PushItemWidth(-1);
      
        ImVec2 vec(0, 0);
        
        if (ImGui::BeginListBox("   0", ImVec2(-FLT_MIN, 25 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (int i = 0; i < maxObjectCount; i++)
            {
                if (items[i].id == -1)
                    continue;

                if (!ImGui::Selectable(items[i].name.c_str(), items[i].isSelected))
                    continue;
                    
                items[i].isSelected = !items[i].isSelected;

                if (items[i].isSelected)
                    scene->GetObjectManager()->SelectObject(items[i].id);
                else
                    scene->GetObjectManager()->DeselectObject(items[i].id);


                if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
                    continue;
                for (int j = 0; j < maxObjectCount; ++j) {
                    if (items[i].id == -1 || i == j)
                        continue;
                    items[j].isSelected = false;
                    scene->GetObjectManager()->DeselectObject(items[j].id);
                }
                
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();

    if (ImGui::IsKeyPressed(ImGuiKey_Delete)) {
        for (int i = 0; i < maxObjectCount; ++i) {
            if (!items[i].isSelected)
                continue;
            scene->GetObjectManager()->RemoveObject(items[i].id);
            items[i] = ListedObject();
            currentCount--;
        }
        ReInitItems();
    }
}


void UI::DrawTransformMenu() {
    
    ImGui::SetNextWindowSize(scene->GetWindow()->GetWidget3Dimensions());
    if (ImGui::Begin("Transform menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        //ImVec4 v(0,0, 0, 0);
        float max = 10;
        ImGui::SliderFloat3("Translate", positionBuffer, -max, max);

        max = 360;
        ImGui::SliderFloat3("Rotate", rotationBuffer, 0, max);

        max = 10;
        ImGui::SliderFloat3("Scale", scaleBuffer, -max, max);
        

        if (ImGui::IsMouseReleased(0)) {
            for (Shape* s : scene->GetObjectManager()->GetCreatedObjects()) {
                if (!s->isSelected)
                    continue;
                s->Translate(positionBuffer);
                s->Rotate(rotationBuffer);
                s->Scale(scaleBuffer);
            }
            positionBuffer[0] = 0;
            positionBuffer[1] = 0;
            positionBuffer[2] = 0;

            rotationBuffer[0] = 0;
            rotationBuffer[1] = 0;
            rotationBuffer[2] = 0;

            scaleBuffer[0] = 0;
            scaleBuffer[1] = 0;
            scaleBuffer[2] = 0;
        }
    }
    ImGui::Text("Mouse inputs");

    Controller& instance = Controller::GetInstance();
    ImGui::Checkbox("X", &instance.isXaxisEnabled);
  
    ImGui::Checkbox("Y", &instance.isYaxisEnabled);
   
    ImGui::Checkbox("Z", &instance.isZaxisEnabled);


    ImGui::Checkbox("Translation", &instance.isTranslating);

    ImGui::Checkbox("Rotation", &instance.isRotating);

    ImGui::Checkbox("Scale", &instance.isScaling);

    if (ImGui::Button("Reset", ImVec2(100, 20)) || ImGui::IsMouseClicked(1)) {
        instance.isXaxisEnabled = false;
        instance.isYaxisEnabled = false;
        instance.isZaxisEnabled = false;

        instance.isTranslating = false;
        instance.isRotating = false;
        instance.isScaling = false;
    }

    ImGui::End();








}



void UI::AddItem(ListedObject object) {
    if (currentCount >= maxObjectCount) {
        std::cout << "max count reached" << std::endl;
        return;
    }
    items[currentCount] = object;
    currentCount++;
}

void UI::ReInitItems() {
    ListedObject temp[32];
    for (int i = 0, j = 0; i < maxObjectCount; ++i) {
        if (items[i].id != -1)
            temp[j++] = items[i];
    }
    for (int i = 0; i < maxObjectCount; ++i) 
        items[i] = temp[i];

}
