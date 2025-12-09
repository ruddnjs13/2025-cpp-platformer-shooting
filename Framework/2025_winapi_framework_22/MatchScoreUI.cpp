#include "pch.h"
#include "MatchScoreUI.h"

void MatchScoreUI::Render(HDC _hdc)
{
	Vec2 curPos = GetPos();
	Vec2 curSize = GetSize();

	Vec2 p1_pos = { curPos.x - 60, curPos.y };
	Vec2 p2_pos = { curPos.x + 60, curPos.y };

	DrawTexture(_hdc, curPos, curSize, m_texture);
	DrawTexture(_hdc, p1_pos, curSize, p1_textures[p1_ScoreIdx]);
	DrawTexture(_hdc, p2_pos, curSize, p2_textures[p2_ScoreIdx]);
}

void MatchScoreUI::InitScoreTexture(Texture* p1_Zero, Texture* p1_One, Texture* p1_Two, Texture* p2_Zero, Texture* p2_One, Texture* p2_Two)
{
	p1_textures[0] = p1_Zero;
	p1_textures[1] = p1_One;
	p1_textures[2] = p1_Two;
	p2_textures[0] = p2_Zero;
	p2_textures[1] = p2_One;
	p2_textures[2] = p2_Two;
}

void MatchScoreUI::SetScore(int p1_Idx, int p2_Idx)
{
	p1_ScoreIdx = p1_Idx;
	p2_ScoreIdx = p2_Idx;
}
