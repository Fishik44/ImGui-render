#include "render.h"

c_sdk g_sdk;

void c_renderer::draw_box(Vector3 screen, Vector3 head, float offset, ImU32 color, bool tracing) {
	head = { head.x, head.y, head.z };
	screen = { screen.x, screen.y, screen.z };

	float height = (head.y - screen.y) / offset;

	ImVec2 tl = ImVec2{ head.x - height, head.y };
	ImVec2 br = ImVec2{ screen.x + height, screen.y };

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	if (tracing) {
		draw_list->AddRect(ImVec2{ tl.x + 1, tl.y - 1 }, ImVec2{ br.x - 1, br.y + 1 }, ImColor{ 0,0,0 });
		draw_list->AddRect(ImVec2{ tl.x - 1, tl.y + 1 }, ImVec2{ br.x + 1, br.y - 1 }, ImColor{ 0,0,0 });
	}

	draw_list->AddRect(tl, br, color);
}

void c_renderer::draw_cornerbox(Vector3 screen, Vector3 head, float offset, ImU32 color, bool tracing) {
	head = { head.x, head.y, head.z };
	screen = { screen.x, screen.y, screen.z };

	float height = (head.y - screen.y) / offset;
	float cornerLength = height * 0.5f;

	ImVec2 tl = ImVec2{ head.x - height, head.y };
	ImVec2 br = ImVec2{ screen.x + height, screen.y };

	ImVec2 tr = ImVec2{ br.x, tl.y };
	ImVec2 bl = ImVec2{ tl.x, br.y };

	ImU32 outline_color = IM_COL32(0, 0, 0, 255);

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	if (tracing) {
		draw_list->AddLine(ImVec2(tl.x + 1, tl.y), ImVec2{ tl.x + 1, tl.y - cornerLength }, outline_color);
		draw_list->AddLine(ImVec2(tl.x + 1, tl.y - 1), ImVec2{ tl.x + cornerLength, tl.y - 1 }, outline_color);

		draw_list->AddLine(ImVec2(tl.x - 1, tl.y + 1), ImVec2{ tl.x - 1, tl.y - cornerLength }, outline_color);
		draw_list->AddLine(ImVec2(tl.x - 2, tl.y + 1), ImVec2{ tl.x + cornerLength, tl.y + 1 }, outline_color);

		draw_list->AddLine(ImVec2(tl.x - 2, (tl.y - cornerLength)), ImVec2{ tl.x + 1, (tl.y - cornerLength) }, outline_color);
		draw_list->AddLine(ImVec2((tl.x + cornerLength) - 1, tl.y - 1), ImVec2{ (tl.x + cornerLength) - 1, tl.y + 2 }, outline_color);

		//-----------------//

		draw_list->AddLine(ImVec2{ tr.x - 1, tl.y }, ImVec2{ tr.x - 1, tl.y - cornerLength }, outline_color);
		draw_list->AddLine(ImVec2{ tr.x - cornerLength, tl.y - 1 }, ImVec2{ tr.x - 1, tl.y - 1 }, outline_color);

		draw_list->AddLine(ImVec2{ tr.x + 1, tl.y + 1 }, ImVec2{ tr.x + 1, tl.y - cornerLength }, outline_color);
		draw_list->AddLine(ImVec2{ tr.x - cornerLength, tl.y + 1 }, ImVec2{ tr.x + 2, tl.y + 1 }, outline_color);

		draw_list->AddLine(ImVec2{ tr.x - 1, (tl.y - cornerLength) }, ImVec2{ tr.x + 2, (tl.y - cornerLength) }, outline_color);
		draw_list->AddLine(ImVec2{ (tr.x - cornerLength) + 1, tl.y - 1 }, ImVec2{ (tr.x - cornerLength) + 1, tl.y + 2 }, outline_color);

		//-----------------//

		draw_list->AddLine(ImVec2(br.x - 1, br.y + 1), ImVec2{ br.x - 1, br.y + cornerLength }, outline_color);
		draw_list->AddLine(ImVec2(br.x - 1, br.y + 1), ImVec2{ br.x - cornerLength, br.y + 1 }, outline_color);

		draw_list->AddLine(ImVec2(br.x + 1, br.y + 1), ImVec2{ br.x + 1, br.y + cornerLength }, outline_color);
		draw_list->AddLine(ImVec2(br.x + 2, br.y - 1), ImVec2{ br.x - cornerLength, br.y - 1 }, outline_color);

		draw_list->AddLine(ImVec2(br.x - 1, (br.y + cornerLength)), ImVec2{ br.x + 2, (br.y + cornerLength) }, outline_color);
		draw_list->AddLine(ImVec2((br.x - cornerLength) + 1, br.y - 1), ImVec2{ (br.x - cornerLength) + 1, br.y + 2 }, outline_color);

		//-----------------//

		draw_list->AddLine(ImVec2(bl.x + 1, bl.y + 1), ImVec2{ bl.x + 1, bl.y + cornerLength }, outline_color);
		draw_list->AddLine(ImVec2(bl.x + 1, bl.y + 1), ImVec2{ bl.x + cornerLength, bl.y + 1 }, outline_color);

		draw_list->AddLine(ImVec2(bl.x - 1, bl.y - 1), ImVec2{ bl.x - 1, bl.y + cornerLength }, outline_color);
		draw_list->AddLine(ImVec2(bl.x - 1, bl.y - 1), ImVec2{ bl.x + cornerLength, bl.y - 1 }, outline_color);

		draw_list->AddLine(ImVec2(bl.x - 2, (bl.y + cornerLength)), ImVec2{ bl.x + 1, (bl.y + cornerLength) }, outline_color);
		draw_list->AddLine(ImVec2((bl.x + cornerLength) - 1, bl.y - 1), ImVec2{ (bl.x + cornerLength) - 1, bl.y + 2 }, outline_color);

	}

	// Top-left corner
	draw_list->AddLine(ImVec2(tl.x, tl.y), ImVec2{ tl.x, tl.y - cornerLength }, color); // Vertical line
	draw_list->AddLine(ImVec2(tl.x, tl.y), ImVec2{ tl.x + cornerLength, tl.y }, color); // Horizontal line

	// Top-right corner
	draw_list->AddLine(ImVec2{ tr.x, tl.y }, ImVec2{ tr.x, tl.y - cornerLength }, color); // Vertical line
	draw_list->AddLine(ImVec2{ tr.x - cornerLength, tl.y }, ImVec2{ tr.x, tl.y }, color); // Horizontal line

	// Bottom-right corner
	draw_list->AddLine(ImVec2(br.x, br.y), ImVec2{ br.x, br.y + cornerLength }, color); // Vertical line
	draw_list->AddLine(ImVec2(br.x, br.y), ImVec2{ br.x - cornerLength, br.y }, color); // Horizontal line

	// Bottom-left corner
	draw_list->AddLine(ImVec2(bl.x, bl.y), ImVec2{ bl.x, bl.y + cornerLength }, color); // Vertical line
	draw_list->AddLine(ImVec2(bl.x, bl.y), ImVec2{ bl.x + cornerLength, bl.y }, color); // Horizontal line
}

void c_renderer::draw_line(Vector3 screen, int choice, ImGuiIO& io, ImU32 color, bool tracing) {

	int choice_selected = 0.f;

	switch (choice)
	{
	case 0:
		choice_selected = io.DisplaySize.y;
		break;
	case 1:
		choice_selected = 2.f;
		break;
	case 2:
		choice_selected = 1.f;
		break;
	}

	ImVec2 position = ImVec2(screen.x, screen.y);
	ImVec2 Screen = ImVec2((io.DisplaySize.x / 2), io.DisplaySize.y / choice_selected);

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	if (tracing) {
		draw_list->AddLine(Screen, { position.x - 1, position.y }, ImColor{ 0, 0, 0 }, 1.0f);
	}

	draw_list->AddLine(Screen, position, color, 1.0f);
}

void c_renderer::draw_health(Vector3 screen, Vector3 head, float offset, int32_t health, float maxhealth, bool text, ImGuiIO& io) {
	head = { head.x, head.y, head.z };
	screen = { screen.x, screen.y, screen.z };

	float height = head.y - screen.y;
	float amount = height / maxhealth * health;
	height /= offset;

	ImVec2 br = ImVec2{ screen.x - height, screen.y };
	float g = health / maxhealth;
	float r = 1.f - g;

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	draw_list->AddLine(ImVec2{ br.x + 1, br.y }, ImVec2{ br.x + 1, br.y + amount }, ImColor{ 0,0,0 }, 1.f);
	draw_list->AddLine(ImVec2{ br.x - 1, br.y }, ImVec2{ br.x - 1, br.y + amount }, ImColor{ 0,0,0 }, 1.f);
	draw_list->AddLine(ImVec2{ br.x - 1, br.y + amount }, ImVec2{ br.x + 1, br.y + amount }, ImColor{ 0,0,0 }, 1.f);
	draw_list->AddLine(ImVec2{ br.x - 1, br.y }, ImVec2{ br.x + 1, br.y }, ImColor{ 0,0,0 }, 1.f);

	draw_list->AddLine(br, ImVec2{ br.x, br.y + amount }, ImColor{ r, g, 0.f }, 2.f);

	if (text) {
		draw_list->AddText(ImVec2{ br.x + 6, br.y + amount + 1 }, ImColor{ 0,0,0 }, std::to_string(health).c_str());
		draw_list->AddText(ImVec2{ ImVec2{ br.x + 5, br.y + amount } }, ImColor{ 255,255,255 }, std::to_string(health).c_str());
	}
}

void c_renderer::draw_name(Vector3 screen, Vector3 head, float offset, std::string name, ImGuiIO& io, ImU32 color, bool tracing) {
	head = { head.x, head.y, head.z };
	screen = { screen.x, screen.y, screen.z };

	float height = (head.y - screen.y) / offset;

	ImVec2 tl = ImVec2{ head.x - height, head.y };
	ImVec2 br = ImVec2{ screen.x + height, screen.y };

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	if (tracing) {
		draw_list->AddText(ImVec2{ br.x + 1, br.y + 4 }, ImColor{ 0,0,0 }, name.c_str());
	}

	draw_list->AddText(ImVec2{ br.x , br.y + 3 }, color, name.c_str());
}

void c_renderer::DrawArrow(Vector2 center, float size, float angle, ImColor color) {
	const float PI = 3.14159265358979323846f;
	const float cos_angle = cosf(angle);
	const float sin_angle = sinf(angle);

	ImVec2 points[3];
	points[0] = ImVec2(center.x - size * 0.5f, center.y + size * 0.5f);
	points[1] = ImVec2(center.x + size * 0.5f, center.y + size * 0.5f);
	points[2] = ImVec2(center.x, center.y - size);

	for (int i = 0; i < 3; ++i) {
		float x = points[i].x - center.x;
		float y = points[i].y - center.y;
		points[i].x = center.x + x * cos_angle - y * sin_angle;
		points[i].y = center.y + x * sin_angle + y * cos_angle;
	}

	auto draw_list = ImGui::GetBackgroundDrawList();

	draw_list->AddTriangleFilled(points[0], points[1], points[2], color);
}