#pragma once
#include "Image.h"

class Texture;

class MatchScoreUI :
    public Image
{

public:
    void Render(HDC _hdc) override;

    void InitScoreTexture(Texture* p1_Zero,Texture* p1_One, Texture* p1_Two,Texture* p2_Zero, Texture * p2_One, Texture * p2_Two);
    void SetScore(int p1_Idx, int p2_Idx);

    int p1_ScoreIdx;
    int p2_ScoreIdx;

private:
    Texture* p1_textures[3];
    Texture* p2_textures[3];
};

