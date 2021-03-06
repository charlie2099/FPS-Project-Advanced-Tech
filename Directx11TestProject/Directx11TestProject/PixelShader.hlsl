struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

Texture2D tex;
SamplerState splr;

float4 main(PixelShaderInput input) : SV_TARGET
{
    return tex.Sample(splr, input.tex);
}