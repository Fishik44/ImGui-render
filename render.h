#pragma once
#include <string>
#include "Unity.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

class c_sdk {
public:
};

struct animation {
	float animation;
};

class c_renderer {
public:
	Material* draw_material_object = nullptr;

	void draw_box(Vector3 screen, Vector3 head, float offset, ImU32 color, bool tracing);
	void draw_cornerbox(Vector3 screen, Vector3 head, float offset, ImU32 color, bool tracing);
	void draw_line(Vector3 screen, int choice, ImGuiIO& io, ImU32 color, bool tracing);
	void draw_health(Vector3 screen, Vector3 head, float offset, int32_t health, float maxhealth, bool text, ImGuiIO& io);
	void draw_name(Vector3 screen, Vector3 head, float offset, std::string name, ImGuiIO& io, ImU32 color, bool tracing);
	void DrawArrow(Vector2 center, float size, float angle, ImColor color);
};
